#include "stdafx.h"
#include "TaskThread.h"
#include "Logging/Logging.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CTaskThreadPool::CTaskThreadPool()
{
   CWinThread* pThread = AfxBeginThread(ThreadProc, this, THREAD_PRIORITY_NORMAL, CREATE_SUSPENDED);
   BOOL bRet = DuplicateHandle(GetCurrentProcess(), 
      pThread->m_hThread, 
      GetCurrentProcess(),
      &m_hThread, 
      0,
      FALSE,
      DUPLICATE_SAME_ACCESS);
   
   pThread->ResumeThread();

   m_pCurrentTask = NULL;
}

CTaskThreadPool::~CTaskThreadPool()
{
   LOG_INFO(_T("enter dtor"));
   if(!m_hThread)
   	return;
   m_KillThreadEvent.SetEvent();
   
   //if( m_pCurrentTask)
   //   m_pCurrentTask->Cancel();
   
   DWORD dwWait = WaitForSingleObject(m_hThread, 3000);
   if( dwWait==WAIT_TIMEOUT )
   {
      LOG_WARN(_T("Terminate thread from ~CTaskThreadPool"));
      TerminateThread(m_hThread,0);
   }

   CloseHandle(m_hThread);
   m_hThread=NULL;
   LOG_INFO(_T("leave dtor"));
}

void CTaskThreadPool::PostTask(CLocation* from_here, TaskBase* pTask )
{
   if( m_pInstance==NULL )
   {
      LOG_WARN(_T("TaskThreadPool has been destroyed, PostTask() will do nothing"));
      return;
   }

   bool bSetEvent;
   m_incomingListLock.Lock();
   pTask->AddRef();
   m_incomingList.push_back(pTask);
   bSetEvent = (m_incomingList.size()==1);
   m_incomingListLock.Unlock();

   if( bSetEvent )
      m_NewIncomingEvent.SetEvent();

}

void CTaskThreadPool::PostDelayedTask( CLocation* from_here, TaskBase* pTask, __int64 delay_ms )
{
   ASSERT(FALSE);
}


UINT CTaskThreadPool::ThreadProc(LPVOID lpVoid)
{
   LOG_THREAD;
   CTaskThreadPool* pThis = (CTaskThreadPool*)lpVoid;
   list<TaskBase*>& workList = pThis->m_workList;
   list<TaskBase*>& incomeList = pThis->m_incomingList;
   CCriticalSection& lock = pThis->m_incomingListLock;
   HANDLE lpHandles[2] = { pThis->m_KillThreadEvent.m_hObject, pThis->m_NewIncomingEvent.m_hObject};
   while(true)
   {
      DWORD dwWait = WaitForMultipleObjects(2, lpHandles, FALSE, INFINITE);
      if( dwWait==WAIT_OBJECT_0 )
      {
         //Kill thread.
         break;
      }


      lock.Lock();
      workList.swap(incomeList);
      lock.Unlock();

      while( !workList.empty() )
      {
         LOG_INFO(_T("Start execute a task"));
         TaskBase* pTask = workList.front();
         pThis->m_pCurrentTask = pTask;
         workList.pop_front();
         pTask->Execute();
         pThis->m_pCurrentTask = NULL;
         pTask->Delete();
         LOG_INFO(_T("Completed a task"));
      }

   }

   return 0;
}

CTaskThreadPool* CTaskThreadPool::CreateInstance()
{
   if( m_pInstance )
      return m_pInstance;

   m_Lock.Lock();
   if( !m_pInstance )
   {
      m_pInstance = new CTaskThreadPool;
   }
   m_Lock.Unlock();
   return m_pInstance;
}

CTaskThreadPool* CTaskThreadPool::Instance()
{
   return m_pInstance;
}

void CTaskThreadPool::DestroyInstance()
{
   m_Lock.Lock();
   delete m_pInstance;
   m_pInstance=NULL;
   m_Lock.Unlock();
}

CCriticalSection CTaskThreadPool::m_Lock;

CTaskThreadPool* CTaskThreadPool::m_pInstance=NULL;
