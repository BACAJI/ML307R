#include "stdafx.h"
#include <process.h>
#include "ICATMessage.h"
#include "Dispatcher.h"
#include "Logging/Logging.h"
#include "Threading.h"
#include "CATCore/MiniDumper/MiniDumper.h"

#if 0 // moved down to avoid leak report filename unaccessible
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#endif

using namespace std;

#ifdef DEBUG
// allocate on heap to avoid CString being destructed before CDispatcher
const CString* c_dispatcherLogName = new CString(_T("CDispatcher"));
#else // DEBUG
const CString* c_dispatcherLogName = NULL;
#endif // DEBUG

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////// 
// CDispatcher implementation
// 
CCriticalSection CDispatcher::m_csLock;
CDispatcher* CDispatcher::m_pInstance=NULL;

CDispatcher* CDispatcher::Instance()
{
   if( m_pInstance )
      return m_pInstance;
	CSingleLock csSingleLock(&m_csLock);
   csSingleLock.Lock();
   if( !m_pInstance )
   {
      m_pInstance = new CDispatcher();
   }
   

   return m_pInstance;
}

CDispatcher* CDispatcher::GetInstance()
{
   return m_pInstance;
}

void CDispatcher::DestroyInstance()
{
   LOG_INFO(_T("Destroy..."));
   Sleep(50);//
	CSingleLock csSingleLock(&m_csLock);
   csSingleLock.Lock();

   delete m_pInstance;
   m_pInstance = NULL;

}

CDispatcher::CDispatcher()
{
   m_pIncomingQueue = new CICATMessageQueue;
   m_pWorkQueue  = new CICATMessageQueue;
   m_hExitEvent  = CreateEvent(NULL, TRUE, FALSE, NULL);
   m_hQueueEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
   m_nMessageNumber = 0;
   m_bDispatchMessage = TRUE;
   //m_ImcReceiver.Listen(IMC_START);
   //m_ImcReceiver.Listen(IMC_STOP);
   //m_ImcReceiver.Register(this);
   StartThread();
}

CDispatcher::~CDispatcher()
{
	try
	{
	   StopThread();
	   ClearIncomingQueue();
	   ClearWorkQueue();


		if(m_pIncomingQueue)
		{
			delete m_pIncomingQueue;
			m_pIncomingQueue=NULL;
		}
		if(m_pWorkQueue)
		{
			delete m_pWorkQueue;
			m_pWorkQueue=NULL;
		}
	   CSingleLock RegistrySingleLock(&m_RegistryLock); 
	   RegistrySingleLock.Lock();
	   m_ReceiverList.clear();
	   RegistrySingleLock.Unlock();
	}
	catch(...)
	{
		LOG_WARN(_T("Exception thrown from ~CDispatcher"));
	}
}

void CDispatcher::RegisterReceiver( CMessageReceiverBase* pReceiver )
{
   if( m_pInstance==NULL )
      return;

   CSingleLock RegistrySingleLock(&m_RegistryLock); 
   RegistrySingleLock.Lock();

   m_ReceiverList.push_back(pReceiver);
    int iCurrRecieverNum=m_ReceiverList.size(); // log to trace receiver list change.
   RegistrySingleLock.Unlock();

   CString strModule = pReceiver->GetReceiverName();
   LOG_NOTICE(_T("Register ICATMessageReceiver[%s], RxrCount:%d"), strModule, iCurrRecieverNum);
}

void CDispatcher::UnregisterReceiver( CMessageReceiverBase* pReceiver )
{
   if( m_pInstance==NULL )
      return;

   CSingleLock RegistrySingleLock(&m_RegistryLock); 
   RegistrySingleLock.Lock();

   vector<CMessageReceiverBase*>::iterator it;
   it = std::find( m_ReceiverList.begin(), m_ReceiverList.end(), pReceiver);
   if(it != m_ReceiverList.end())
   {
      m_ReceiverList.erase(it);
   }
   int iCurrRecieverNum=m_ReceiverList.size(); // log to trace receiver list change.
   RegistrySingleLock.Unlock();  

   CString strModule = pReceiver->GetReceiverName();
   LOG_NOTICE(_T("Unregister ICATMessageReceiver[%s], RxrCount:%d"), strModule, iCurrRecieverNum);
}

void CDispatcher::HandleMessage( CICATMessage* pMessage )
{
   if ( (NULL == m_pInstance) || (!m_bDispatchMessage) )
   {
		pMessage->Delete(c_dispatcherLogName);
		return;
   }

   size_t szCount;
   CSingleLock QueueSingleLock(&m_QueueLock);
   QueueSingleLock.Lock();
   pMessage->m_MessageNumber = m_nMessageNumber++;
   pMessage->AddRef(c_dispatcherLogName);
   m_pIncomingQueue->push(pMessage);
   szCount = m_pIncomingQueue->size();
   QueueSingleLock.Unlock();

   if(szCount==1)
   {
      SetEvent(m_hQueueEvent);
   }
}

UINT CDispatcher::ThreadProc( LPVOID lpVoid)
{
    CDispatcher* pThis = (CDispatcher*) lpVoid;

	CATS_TRY
	{
		pThis->ThreadFunc();
	}
    CATS_EXCEPT( CATStudio_MiniDump_Handled( GetExceptionInformation(), _T("CATCORE") ) )
    {
       LOG_ERROR(_T("Exception throw from ThreadFunc."));
    }

    return 0;
}

UINT CDispatcher::ThreadFunc()
{
#if 0
   //LOG_THREAD;
#else
   LOG_THREAD;
#endif
   ClearWorkQueue();

   HANDLE lpHandles[2] = {m_hExitEvent, m_hQueueEvent};
   
	LARGE_INTEGER liStartWaitTimestamp; 
	for(;;)
	{
 	// Used to check if thread have been blocked for long? Use it before WaitForMultipleObjects within main loop of thread.  Tom Zhuang, 20131122
	QueryPerformanceCounter(&liStartWaitTimestamp);
    if( WaitForMultipleObjects(2, lpHandles, FALSE, INFINITE)==WAIT_OBJECT_0 )
	{
		break;
    }

      SwapQueue();
      while(!WorkQueue()->empty())
      {
         if (WaitForSingleObject(lpHandles[0], 0) == WAIT_OBJECT_0)
            break;

         CICATMessage* pMessage = GetMessage();
         DispatchMessage(pMessage);
      }
   }
   return 0;
}


void CDispatcher::DispatchMessage()
{
   // Dispatcher message
   while( !m_pWorkQueue->empty() )
   {
      CICATMessage* pMessage = m_pWorkQueue->front();
      UINT64 nMessageNumber = pMessage->m_MessageNumber;
      m_pWorkQueue->pop();

	  CSingleLock RegistrySingleLock(&m_RegistryLock);
	  RegistrySingleLock.Lock();	
      for(size_t i=0; i<m_ReceiverList.size(); ++i)
      {
         m_ReceiverList.at(i)->AddToFIFO( pMessage );
      }

	  pMessage->Delete(c_dispatcherLogName);
   }
}

void CDispatcher::DispatchMessage( CICATMessage* pMessage)
{
	CSingleLock RegistrySingleLock(&m_RegistryLock);
	RegistrySingleLock.Lock();	
	for(size_t i=0; i<m_ReceiverList.size(); ++i)
	{
		m_ReceiverList.at(i)->AddToFIFO( pMessage );
	}

	pMessage->Delete(c_dispatcherLogName);
}



void CDispatcher::StartThread()
{
   ResetEvent(m_hQueueEvent);
   ResetEvent(m_hExitEvent);
   m_hThread = (HANDLE) BeginThread(ThreadProc, this);
};

void CDispatcher::StopThread(DWORD dwTimeout)
{
   SetEvent(m_hExitEvent);

   if(WaitForSingleObject(m_hThread, dwTimeout)==WAIT_TIMEOUT)
   {
      LOG_ERROR(_T("Stop message dispatching thread timeout"));
   }
}

void CDispatcher::ClearIncomingQueue()
{
   while( !m_pIncomingQueue->empty() )
   {
      CICATMessage* pMessage = m_pIncomingQueue->front();
      m_pIncomingQueue->pop();
      pMessage->Delete(c_dispatcherLogName);
   }
}

void CDispatcher::ClearWorkQueue()
{
   while( !m_pWorkQueue->empty() )
   {
      CICATMessage* pMessage = m_pWorkQueue->front();
      m_pWorkQueue->pop();
      pMessage->Delete(c_dispatcherLogName);
   }
}

void CDispatcher::SwapQueue()
{
	CSingleLock QueueSingleLock(&m_QueueLock);
	QueueSingleLock.Lock();
   CICATMessageQueue* pQueue = m_pIncomingQueue;
   m_pIncomingQueue = m_pWorkQueue;
   m_pWorkQueue = pQueue;
}

CICATMessage* CDispatcher::GetMessage()
{
   CICATMessage* pMessage = m_pWorkQueue->front();
   m_pWorkQueue->pop();
   return pMessage;
}

//LRESULT CDispatcher::OnMessageReceived( CMessage* pMessage )
//{
//   switch(pMessage->message)
//   {
//   case IMC_START:
//      {
//         CMsgStart* pMsg = dynamic_cast<CMsgStart*>(pMessage);
//         ASSERT(pMsg);
//         if(pMsg)
//         {
//         	if(pMsg->eLastState==eStopped)
//               ResumeDispather();
//            return 0;
//         }
//         return -1;
//      }
//      break;
//
//   case IMC_STOP:
//      {
//         CMsgStop* pMsg = dynamic_cast<CMsgStop*>(pMessage);
//         ASSERT(pMsg);
//         if(pMsg)
//         {
//         	StopDispatcher();
//            return 0;
//         }
//         return -1; 
//      }
//      break;
//   }
//
//   return 0;
//}

void CDispatcher::StopDispatcher()
{
   m_bDispatchMessage = FALSE;
   CSingleLock QueueSingleLock(&m_QueueLock);
   QueueSingleLock.Lock();
   while(!m_pIncomingQueue->empty())
   {
      CICATMessage* pMessage = m_pIncomingQueue->front();
      m_pIncomingQueue->pop();
	  pMessage->Delete(c_dispatcherLogName);
   }


}


void CDispatcher::ResumeDispather()
{
   m_bDispatchMessage = TRUE;
}

