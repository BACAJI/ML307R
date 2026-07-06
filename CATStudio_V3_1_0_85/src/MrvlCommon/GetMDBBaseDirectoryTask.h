#pragma once
#include <string>
#include <afxmt.h>
#include "ipc/ipc_listener.h"
#include "MrvlCommon/TaskBase.h"

using namespace std;


class Message;
class CGetMdbBaseDirTask : public TaskBase, public IpcListener
{
public:
   CGetMdbBaseDirTask();

   // Overrides
   virtual void Execute();
   virtual void Cancel();
   virtual DWORD WaitTaskFinished(DWORD dwTimeout=INFINITE);
   virtual TaskState GetTaskState();
   virtual BOOL OnMessageReceived(const Message& kMessage);

   // Methods
   void  SetTaskTimeout(DWORD dwReleaseTimeout=10000, DWORD dwDebugTimeout=INFINITE);

private:
   BOOL  PreWork();
   BOOL  Work();
   BOOL  PostWork();
   ~CGetMdbBaseDirTask();
   wstring m_wsMDBBaseDir;

   CCriticalSection  m_MessageLock;
   Message* m_pIpcMessage;

   CEvent   m_cancelTaskEvent;
   CEvent   m_newMessageEvent;
   DWORD    m_taskTimeout;
   int      m_taskState;
   CEvent   m_taskFinishedEvent;

};
