#pragma once
#include <list>
#include <afxmt.h>
#include "TaskBase.h"
using namespace std;

class CLocation {
public:
};

class CTaskThreadPool
{
public:
   static CTaskThreadPool* CreateInstance();
   static CTaskThreadPool* Instance();
   static CTaskThreadPool* m_pInstance;
   static CCriticalSection m_Lock;
   static void   DestroyInstance();
   CTaskThreadPool();
   ~CTaskThreadPool();

   // 
   void PostTask(
      CLocation* from_here, 
      TaskBase* pTask);

   //
   void PostDelayedTask(
      CLocation* from_here,
      TaskBase* pTask,
      __int64  delay_ms);


   static UINT ThreadProc(LPVOID lpVoid);



private:
   list<TaskBase*> m_incomingList;
   list<TaskBase*> m_workList;  
   CCriticalSection m_incomingListLock;
   CEvent          m_KillThreadEvent;
   CEvent          m_NewIncomingEvent;
   HANDLE          m_hThread;
   TaskBase*       m_pCurrentTask;
};
