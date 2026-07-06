#include "stdafx.h"
#include "ICATMessage.h"
#include "ICATMessageReceiver.h"
#include "Dispatcher.h"
#include "Threading.h"
#include "MrvlCommon/Logging/Logging.h"

//200*1024*160Byte = 32MB
#define MAX_ICATFIFO_SIZE  200*1024

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CMessageReceiverBase::CMessageReceiverBase()
{
   m_bReceiveMessage = true;
   m_bRegistered = false;
   m_uDropMsgCnt=0;
}

CMessageReceiverBase::~CMessageReceiverBase()
{
   if(m_bRegistered)
   {
      ASSERT(FALSE);//Did you forget unregister?
   }

}

void CMessageReceiverBase::Register(bool bStartReceiving)
{
   ASSERT(!m_strReceiverName.IsEmpty());
   m_bReceiveMessage = bStartReceiving;
   CDispatcher::Instance()->RegisterReceiver(this);
   m_bRegistered = true;
}

void CMessageReceiverBase::Unregister()
{
   CDispatcher* pDisp = CDispatcher::GetInstance();
   if(pDisp)
   {
      pDisp->UnregisterReceiver(this);
   }
   m_bRegistered = false;
}


void CMessageReceiverBase::StartReceiver()
{
   m_bReceiveMessage = true;
   LOG_NOTICE(_T("IMRxer_Start: %s"), m_strReceiverName);
}

void CMessageReceiverBase::StopReceiver()
{
   m_bReceiveMessage = false;
   if(m_uDropMsgCnt)
   {
      LOG_NOTICE(_T("IMRxer_Stop: %s, dropped: %u, Index:%I64u"), m_strReceiverName,m_uDropMsgCnt, CICATMessage::m_MessageCounter);
      m_uDropMsgCnt=0;
   }
}


void CMessageReceiverBase::SetReceiverName( const CString& strModule )
{
	CSingleLock ReceiverNameSingleLock(&m_ReceiverNameLock);
	ReceiverNameSingleLock.Lock();
    m_strReceiverName = strModule;
}

CString CMessageReceiverBase::GetReceiverName()
{
   CString strRetName;
   CSingleLock ReceiverNameSingleLock(&m_ReceiverNameLock);
   ReceiverNameSingleLock.Lock();
   strRetName = m_strReceiverName;

   return strRetName;
}


UINT CMessageReceiverBase::GetDroppedCount()
{
   return m_uDropMsgCnt;
}


//////////////////////////////////////////////////////////////////////////
// Implementation of CICATMessageReceiver
// 
CICATMessageReceiver::CICATMessageReceiver()
{
	m_nPreMessageNumber = 0;
   m_nMaxsize = MAX_ICATFIFO_SIZE;
   m_hFIFOEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
   m_nAvailableMemoryMB = CSystemInfo::Instance()->AvailableMemoryMB();
}

CICATMessageReceiver::~CICATMessageReceiver()
{
	try
	{
	   //Unregister();
	   RemoveAll();
	   CloseHandle(m_hFIFOEvent);
	   if(m_uDropMsgCnt)
	   {
		   LOG_NOTICE(_T("IMRxer_Exit: %s, dropped: %u, Index:%I64u"), m_strReceiverName,m_uDropMsgCnt, CICATMessage::m_MessageCounter);
	   }
	}
	catch(...)
	{
		LOG_WARN(_T("Exception thrown from ~CICATMessageReceiver"));
	}
}


void CICATMessageReceiver::AddToFIFO( CICATMessage* pMessage )
{
   if ( (!m_bReceiveMessage) || (!pMessage) )	return;

   //isPassFilter

   // Lock & Unlock
   CCriticalSectionLock lock(m_FIFOSync);

   if (m_FIFO.size() < m_nMaxsize)
   {
	   pMessage->AddRef(&this->m_fifoOwnerName);
	   m_FIFO.push_back(pMessage); // Received message is here added to the message-receiver's list, which is used by CCommandChannel::Get*Message methods.
   } else
   {
	   while (m_FIFO.size() >= (size_t)(m_nMaxsize*0.8))
	   {
		   CICATMessage* pMessage1 = m_FIFO.front();
		   m_FIFO.pop_front();
		   m_uDropMsgCnt++;
		   if(m_uDropMsgCnt<100 || m_uDropMsgCnt%20000==0)
		   {
			   LOG_WARN(_T("MsgRxr:%s, Drop(Cnt%u,Idx:%I64u), New(Idx:%I64u)"), m_strReceiverName.GetString(), m_uDropMsgCnt, pMessage1->m_MessageNumber, pMessage->m_MessageNumber);
			   //LOG_WARN(_T( "Free disk size : %fGB, Available physical memory : %dMB."),CSystemInfo::Instance()->GetFreeDiskSpaceGB(),CSystemInfo::Instance()->AvailableMemoryMB());
		   }
		   pMessage1->Delete(&this->m_fifoOwnerName);
	   }
   }

   if( m_FIFO.size()==1 )
   {
	   SetEvent(m_hFIFOEvent);
   }
}

CICATMessage* CICATMessageReceiver::RemoveHead()
{
	CSingleLock FIFOSyncSingleLock(&m_FIFOSync);
	FIFOSyncSingleLock.Lock();

   CICATMessage* pMessage = NULL;
   if(m_FIFO.size())
   {
      pMessage = m_FIFO.front();
      m_FIFO.pop_front();
   }
   
   if (0 == m_FIFO.size())
   {
	   ResetEvent(m_hFIFOEvent);
   }

//remove useless logs.
//   if(pMessage)
//   {
//	   int nAvailableMemoryMB = CSystemInfo::Instance()->AvailableMemoryMB();
//	   if(m_nAvailableMemoryMB - nAvailableMemoryMB > 1)
//		   LOG_WARN(_T( "Increase: %dMB, MsgRxr:%s, Previous (Available memory : %dMB), Current (Available memory: %dMB), Previous (Idx:%I64u), Current (Idx:%I64u)."), m_nAvailableMemoryMB - nAvailableMemoryMB,m_strReceiverName.GetString(), m_nAvailableMemoryMB,nAvailableMemoryMB,m_nPreMessageNumber,pMessage->m_MessageNumber);
//	   m_nAvailableMemoryMB = nAvailableMemoryMB;
//	   m_nPreMessageNumber = pMessage->m_MessageNumber;
//   }
   return pMessage;
}

void CICATMessageReceiver::RemoveAll()
{
   CSingleLock FIFOSyncSingleLock(&m_FIFOSync);
   FIFOSyncSingleLock.Lock();

   CICATMessage* pMessage=NULL;
   
   size_t szSize = m_FIFO.size();

   list<CICATMessage*>::iterator iter = m_FIFO.begin();
   for(; iter!=m_FIFO.end(); ++iter)
   {
      pMessage = *iter;
      pMessage->Delete(&this->m_fifoOwnerName);
   }

   m_FIFO.clear();
   ResetEvent(m_hFIFOEvent);

   LOG_INFO(_T("%s, Removed %u unprocessed messages"), GetReceiverName(), szSize);

}

void CICATMessageReceiver::SetFIFOSize( size_t sz )
{
   m_nMaxsize = sz;
}

void CICATMessageReceiver::FitSize()
{
   // Lock & Unlock
   CCriticalSectionLock lock(m_FIFOSync);

   while( m_FIFO.size()>m_nMaxsize )
   {
      CICATMessage* pMessage = m_FIFO.front();
      m_FIFO.pop_front();
      pMessage->Delete(&this->m_fifoOwnerName);
   }

   if (0 == m_FIFO.size())	ResetEvent(this->m_hFIFOEvent); // Assumes that m_nMaxsize may be zero.
}


//UINT64 CICATMessageReceiver::RemoveMsg( UINT64 messageNum )
//{
//	m_FIFOSync.Lock();
//
//	UINT64 result;
//
//	list<CICATMessage*>::iterator iter = m_FIFO.begin();
//	list<CICATMessage*>::iterator iterMatched;
//	list<CICATMessage*>::iterator iterNext;
//	for(; iter != m_FIFO.end(); ++iter)
//	{	
//		if((*iter)->m_MessageNumber == messageNum)
//		{
//			break;
//		}	
//	}
//
//	if(iter != m_FIFO.end() )
//	{
//		iterMatched = iter;
//		iterNext = ++iter;
//		if(iterNext != m_FIFO.end())
//		{
//			result = (*iter)->m_MessageNumber;
//			(*iterMatched)->Delete();
//			m_FIFO.erase(iterMatched);
//		}
//		else
//		{
//			result = -2;
//		}
//		
//	}
//	else
//	{
//		result = -1;
//	}
//
//	if(m_FIFO.size()==0)
//	{
//		ResetEvent(m_hFIFOEvent);
//	}
//
//	m_FIFOSync.Unlock();
//
//	return result;
//}

//////////////////////////////////////////////////////////////////////////
// 
void CICATMessageReceiverPTK::AddToFIFO( CICATMessage* pMessage )
{
	
   if(m_bPtkReceiveMessage)
   {
      ASSERT(m_pfnHandleMessage);
      ASSERT(m_pfnObj);
      m_pfnHandleMessage(m_pfnObj, pMessage); // Received message is here added to the owning CCommandChannel's message-logger, which is used by CCommandChannel::Wait*Message methods.
   }

   CICATMessageReceiver::AddToFIFO(pMessage); // Received message is here added to the underlying message-receiver's list, which is used by CCommandChannel::Get*Message methods.
}

CICATMessageReceiverPTK::CICATMessageReceiverPTK()
{
	m_bPtkReceiveMessage = true;
   m_pfnHandleMessage = NULL;
   m_pfnObj = NULL;
}

CICATMessageReceiverPTK::~CICATMessageReceiverPTK()
{

}

//////////////////////////////////////////////////////////////////////////
// Implementation of CICATMessageReceiver
// 
CICATMessageReceiverEx::CICATMessageReceiverEx(LPVOID pClass, BOOL bStartReceiving, LP_ICAT_MESSAGE_FUNC *pICATMessageFunc):
	m_pHandlingClass(pClass),
	m_pICATMessageFunc(pICATMessageFunc),
	m_KillEvent(0,1),
	m_pThread(NULL)
{
	SetReceiverName(_T("ReceiverEx"));
	m_pThread = AfxBeginThread(ThreadProc, (LPVOID)this);

}

CICATMessageReceiverEx::~CICATMessageReceiverEx()
{
	m_KillEvent.SetEvent();
	if ( m_pThread != NULL )
	{
		if (WaitForSingleObject(m_pThread->m_hThread, 3000) == WAIT_TIMEOUT)
			TerminateThread(m_pThread->m_hThread, 0);
		m_pThread = NULL;
	}
}

CICATMessageReceiverEx* CICATMessageReceiverEx::CreateMsgReceiver(LPVOID pClass, BOOL bStartReceiving, LP_ICAT_MESSAGE_FUNC *pICATMessageFunc)
{
	return new CICATMessageReceiverEx(pClass, bStartReceiving, pICATMessageFunc);
}

void CICATMessageReceiverEx::DeleteMsgReceiver(CICATMessageReceiverEx*& pReceiver)
{
	if (pReceiver->m_bRegistered)
		pReceiver->Unregister();
	delete pReceiver;

	pReceiver = NULL;
}

UINT CICATMessageReceiverEx::ThreadProc(LPVOID pParam) 
{
	LOG_THREAD;
	CICATMessageReceiverEx* pThis = (CICATMessageReceiverEx*)pParam;

	bool bExit = false;

	while ( !bExit)
	{
		const HANDLE hThirdWaits[2] = {pThis->m_KillEvent.m_hObject, pThis->m_hFIFOEvent};

		DWORD dwResult = WaitForMultipleObjects(2, hThirdWaits, FALSE, INFINITE);
		bExit = (dwResult == WAIT_OBJECT_0);
		if ( !bExit )
		{
			pThis->ReceiveMessage();
		}
	}


	return 1;
}

void CICATMessageReceiverEx::ReceiveMessage()
{
	CICATMessage *pMessage = RemoveHead();
	if ( pMessage == NULL )
		return;

	if ( m_pICATMessageFunc )
	{
			m_pICATMessageFunc(m_pHandlingClass, pMessage);
	}	

	DeleteMessage(pMessage);
}

bool CICATMessageReceiverEx::DeleteMessage(CICATMessage *pMessage)
{
	TRY
	{
		pMessage->Delete();
	}
	CATCH_ALL(e)
	{
		e->Delete();
		return false;
	}
	END_CATCH_ALL

	return true;
}
