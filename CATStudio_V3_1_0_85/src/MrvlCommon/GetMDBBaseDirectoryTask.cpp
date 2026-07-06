#include "stdafx.h"
#include "GetMDBBaseDirectoryTask.h"
#include "MrvlCommon/CmdLineUtil.h"
#include "MrvlCommon/process_util.h"
#include "MrvlCommon/ApplicationINI.h"
#include "MrvlCommon/VersionManager.h"
#include "Logging/Logging.h"
#include "ipc/ipc_server_sock.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CGetMdbBaseDirTask implementation
//
CGetMdbBaseDirTask::CGetMdbBaseDirTask()
{
   m_pIpcMessage = NULL;
}

void CGetMdbBaseDirTask::Execute()
{
   PreWork();
   Work();
   PostWork();
   return;
}

BOOL CGetMdbBaseDirTask::OnMessageReceived( const Message& kMessage )
{
   if( kMessage.GetMessageId() == SID_CHECKDBVER_RESULT )
   {
      void* iter=NULL;
      m_MessageLock.Lock();
      delete m_pIpcMessage;
      m_pIpcMessage = new Message(kMessage);
      m_MessageLock.Unlock();
      m_newMessageEvent.SetEvent();
      return TRUE;
   }

   //!!! return FALSE only if message handler not found.
   return FALSE; 
}

CGetMdbBaseDirTask::~CGetMdbBaseDirTask()
{
	try
	{
		CCallHandler::Instance()->UnregisterListener(this);
		if(m_pIpcMessage)
		{
			delete m_pIpcMessage;
			m_pIpcMessage=NULL;
		}
	}
	catch(...)
	{
		LOG_WARN(_T("Exception thrown from ~CGetMdbBaseDirTask"));
	}
}

void CGetMdbBaseDirTask::Cancel()
{
   m_cancelTaskEvent.SetEvent();
}

void CGetMdbBaseDirTask::SetTaskTimeout( DWORD dwReleaseTimeout/*=8000*/, DWORD dwDebugTimeout/*=INFINITE*/ )
{
#ifndef NDEBUG
   m_taskTimeout = dwDebugTimeout;
#else
   m_taskTimeout = dwReleaseTimeout;
#endif
}

DWORD CGetMdbBaseDirTask::WaitTaskFinished( DWORD dwTimeout/*=INFINITE*/ )
{
   DWORD dwWait = WaitForSingleObject(m_taskFinishedEvent.m_hObject, dwTimeout);
   return dwWait;
}

TaskBase::TaskState CGetMdbBaseDirTask::GetTaskState()
{
   return (TaskBase::TaskState)m_taskState;
}
BOOL CGetMdbBaseDirTask::PostWork()
{
   CCallHandler::Instance()->UnregisterListener(this);
   return TRUE;
}

BOOL CGetMdbBaseDirTask::PreWork()
{
   CCallHandler::Instance()->RegisterListener(this);
   return TRUE;
}

BOOL CGetMdbBaseDirTask::Work()
{
   // 1 从INI中读取CheckDbVersion的ini路径，启动CheckDbVersion
   // 2. 等待CheckDbVersion返回的结果
   // 3. 读取结果
   // 4. 保存结果至SessionManager中
   AutoSetEvent autoSetter(m_taskFinishedEvent.m_hObject);
   DWORD dwStartTime  = GetTickCount();
   DWORD dwRemainTime = m_taskTimeout;

   // 1.
   CString strAppPathName= GetCurrentModuleDirectory() + CString(_T("\\")) + CHECKDBVERSION_MODULENAME;
   CString strCmdlineParam = AppIni()->GetProfileString(_T("IPC Settings"), _T("CheckDbVersionIniPath"), NULL);
   LOGEX_DEBUG(_T("CheckDbVerModulePathName=%s"), strAppPathName.GetBuffer(0));
   LOGEX_DEBUG(_T("CheckDbVerININame=%s"), strCmdlineParam.GetBuffer(0));

   if(strAppPathName.GetLength()==0 || strCmdlineParam.GetLength()==0){
      m_taskState = TaskBase::failed;
      LOGEX_ERROR(_T("CheckDbVer PathName/ININame invalid"));
      return FALSE;
   }   

   strCmdlineParam = CCmdLineInfo::Instance()->GetCfgFileDirectory() + _T("\\") + strCmdlineParam;
   strCmdlineParam = _T("/c \"") + strCmdlineParam + _T("\" /w SW_HIDE");

   LOGEX_INFO(_T("Launching %s"), strAppPathName.GetBuffer(0));
   LOGEX_INFO(_T("Launching with cmdline param: %s"), strCmdlineParam.GetBuffer(0));

   PROCESS_INFORMATION pi;
   memset(&pi, 0, sizeof(pi));
   if( ! LaunchProcess(pi, strAppPathName, strCmdlineParam ) )
   {
      LOGEX_ERROR(_T("LaunchProcess CheckDbVer failed"));
      m_taskState = TaskBase::failed;
      return FALSE;
   }
   else
   {
      LOGEX_INFO(_T("LaunchProcess CheckDbVer success"));
   }
   DWORD dwElapsed = GetTickCount()-dwStartTime;
   dwRemainTime =  max(0, (DWORD)(dwRemainTime-dwElapsed) );


   /// 2
   // 等待CheckDbVersion返回结果
   //AfxMessageBox(_T("wait"));
   HANDLE lpHandles2[2]={m_cancelTaskEvent.m_hObject, m_newMessageEvent.m_hObject};
   DWORD dwWait = WaitForMultipleObjects(2, lpHandles2, FALSE, dwRemainTime);
   if(dwWait!=WAIT_OBJECT_0+1) {
      LOGEX_ERROR(_T("Wait SW_HIDE CheckDbVer return failed"));
   }
   CleanupProcess(pi, 50);
   switch( dwWait )
   {
   case WAIT_OBJECT_0: // cancelled
      m_taskState=TaskBase::cancelled;
      return FALSE;

   case WAIT_OBJECT_0+1: // message received 
      LOGEX_INFO(_T("Wait SW_HIDE CheckDbVer return OK"));
      break;

   case WAIT_OBJECT_0+2: // process exit
      m_taskState=TaskBase::failed;
      return FALSE;

   default: //wait_failed,timeout...
      m_taskState=TaskBase::failed;
      return FALSE;
   }




   /// ///////////////////////////////////////////////////////////////////////
   /// 3
   tagCheckDbVerResult cdvRet;
   if(m_pIpcMessage)
   {
      // 取出消息
      m_MessageLock.Lock();
      bool noErr = true;
      void* iter=NULL;
      noErr = noErr && m_pIpcMessage->ReadInt(&iter, &cdvRet.iDevice);
      noErr = noErr && m_pIpcMessage->ReadBool(&iter, &cdvRet.bCpDbMatch);
      noErr = noErr && m_pIpcMessage->ReadBool(&iter, &cdvRet.bApDbMatch);
      noErr = noErr && m_pIpcMessage->ReadWString(&iter, &cdvRet.wsPcCpDbVer);
      noErr = noErr && m_pIpcMessage->ReadWString(&iter, &cdvRet.wsPcApDbVer);
      noErr = noErr && m_pIpcMessage->ReadWString(&iter, &cdvRet.wsMDBBaseDir);

      ASSERT(noErr);
      delete m_pIpcMessage;
      m_pIpcMessage=NULL;
      m_MessageLock.Unlock();

      LOGEX_INFO(_T("MDBBaseDir=%s"), cdvRet.wsMDBBaseDir.c_str());
   }
   else
   {
      m_taskState=TaskBase::failed;
      return FALSE;
   }

   GetVersionManager()->SetMdbBaseDir(cdvRet.wsMDBBaseDir);

   //PrintMessage((LPCTSTR)cdvRet.wsMDBBaseDir.c_str());

   m_taskState = TaskBase::success;

   return TRUE;
}
