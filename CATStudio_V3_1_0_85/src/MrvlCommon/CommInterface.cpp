#include "StdAfx.h"
#include "CommInterface.h"
#include "Dispatcher.h"
#include "ICATMessage.h"
#include "DiagMessage.h"
#include "Logging/Logging.h"
#include "CommSettings.h"
#include "MessageDefs.h"
#include "DeviceStatus.h"
#include "TimeUtil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CCommInterface* CCommInterface::ms_pInstance;
CCriticalSection CCommInterface::ms_Lock;

CCommInterface* CCommInterface::Instance()
{
   if( ms_pInstance )
      return ms_pInstance;

   ms_Lock.Lock();
   if( !ms_pInstance )
   {
      ms_pInstance = new CCommInterface;
   }
   ms_Lock.Unlock();

   return ms_pInstance;
}

void CCommInterface::DestroyInstance()
{
   delete ms_pInstance;
   ms_pInstance = NULL;
}

CCommInterface::CCommInterface(void)
{
   LPFN_REG_MESSAGEFUNC pRegMessageFunc = NULL; 
   



   ZeroMemory(m_tmSystemTime, sizeof(m_tmSystemTime));
   ZeroMemory(m_wSystemTimeMilli, sizeof(m_wSystemTimeMilli));
   ZeroMemory(m_timetSyncTime, sizeof(m_timetSyncTime));
   ZeroMemory(m_dwSyncPduTs, sizeof(m_dwSyncPduTs));
   ZeroMemory(m_bUseSyncTime, sizeof(m_bUseSyncTime));


   m_hDevComm = LoadLibrary(_T("DevComm.dll"));
   m_pCommandFunc = NULL;
   m_pADBCommandFunc = NULL;
   m_pStopADBFunc = NULL;
   if(m_hDevComm)
   {
	  m_pKillWriteHandle = (LPFN_GETKILLWRITEHANLEDFUNC)GetProcAddress(m_hDevComm, "DevComm_GetKillWriteHandle");
      m_pCommandFunc = (LPFN_COMMANDFUNC) GetProcAddress(m_hDevComm, "DevComm_SendCommand");
	  m_pCommandTimeoutFunc = (LPFN_COMMANDFUNCWITHTIMEOUT) GetProcAddress(m_hDevComm, "DevComm_SendCommandWithTimeout");
      pRegMessageFunc = (LPFN_REG_MESSAGEFUNC) GetProcAddress(m_hDevComm, "DevComm_RegMessageFunc");
	  m_pADBCommandFunc = (LPFN_ADBCOMMANDFUNC) GetProcAddress(m_hDevComm, "DevComm_SendADBCommand");
	  m_pStopADBFunc = (LPFN_STOPADBFUNC) GetProcAddress(m_hDevComm, "DevComm_StopADBCommand");
   }

   
   m_ImcReceiver.Listen(IMC_GET_COMMINF);
   m_ImcReceiver.Listen(IMC_TARGET_TIME_SYNC);
   m_ImcReceiver.Listen(IMC_DEVICE_CHANGED);
   m_ImcReceiver.Register(this);



   // Put messagefunc registering at the end of ctor
   // to avoid the situation that devcomm calling the 
   // registered messagefunc but commInterface 
   // construction is not completed.
   if(pRegMessageFunc)
   {
      pRegMessageFunc(this, MessageFunc);
   }
}

CCommInterface::~CCommInterface(void)
{
	try
	{
	   m_ImcReceiver.Unregister();

	   if(m_hDevComm)
	   {
	      LPFN_UNREG_MESSAGEFUNC pUnregMessageFunc = (LPFN_UNREG_MESSAGEFUNC) GetProcAddress(m_hDevComm, "DevComm_UnregMessageFunc");
	      int retCode = pUnregMessageFunc();
	      LOG_INFO(_T("UnregMessageFunc return errcode:0x%0x"), retCode);

	      FreeLibrary(m_hDevComm);
	   }
	}
	catch(...)
	{
		LOG_WARN(_T("Exception thrown from ~CCommInterface"));
	}
}

void CCommInterface::MessageFunc(LPVOID lpObj, int iDevice, int protocol, BYTE* data, int length )
{
   CCommInterface* pThis =(CCommInterface*)lpObj;
   
   CICATMessage* pMessage = NULL;
   try
   {
      pMessage = new CICATMessage(protocol, 1, iDevice, data, length, true);

      if(protocol==eDIAGProtocol && pThis->m_bUseSyncTime[iDevice])
      {
         WORD wDiagSap = (data[0/*CDiag1Message::diag1To_SAP*/] & 0x0F);
         DWORD dwTargetTs = *(LPDWORD)&data[8/*CDiag1Message::diag1From_TimeStamp*/];
         if(wDiagSap==DIAG_MI_LOGGED_SIGNAL || wDiagSap==DIAG_MI_SIGNAL)
         {
            dwTargetTs = *(LPDWORD)&data[4/*CDiag1Message::diag1GKIFrom_TimeStamp*/];
         }

         UINT64  u64DiffMilliSeconds = (dwTargetTs-pThis->m_dwSyncPduTs[iDevice])*(UINT64)1000/32768;
         time_t totalSeconds = (DWORD)(u64DiffMilliSeconds/1000) + pThis->m_timetSyncTime[iDevice];

         SYSTEMTIME* pSystemTime = dynamic_cast<SYSTEMTIME*>(&pMessage->m_Time);
         TimeUtil::TimetToSystemTime(totalSeconds, pSystemTime);
         pSystemTime->wMilliseconds = (DWORD)(u64DiffMilliSeconds%1000);

         //LOG_DEBUG(_T("DiffMilliSec:%u = (TargetTs:%u - SyncPduTs:%u)*(UINT64)1000/32768, totalSeconds:%u"), (DWORD)u64DiffMilliSeconds, dwTargetTs, pThis->m_dwSyncPduTs[iDevice], (DWORD)totalSeconds);
         //TCHAR systemTimeString[MAX_PATH];
         //GetTimeFormat(LOCALE_CUSTOM_DEFAULT, 0, pSystemTime, NULL, systemTimeString, MAX_PATH);
         //LOG_DEBUG(_T("PC Time Stamp:%u-%u-%u %s.%u"),pSystemTime->wYear, pSystemTime->wMonth, pSystemTime->wDay, (LPCTSTR)systemTimeString, pSystemTime->wMilliseconds);
      }

   }
   catch (CMemoryException* e)
   {
      DWORD dwErr = GetLastError();
      UINT nMemUse = CSystemInfo::WorkingSetSizeMB();
      LOG_ERROR(_T("MemException throw from new ICATMessage(Device%d, Protocol%d, dataLen:%d). ErrCode:%d CurrentWorkingSetSize:%u MB"), iDevice, protocol, length, dwErr, nMemUse);
      return;
   }
   catch (...)
   {
      DWORD dwErr = GetLastError();
      UINT nMemUse = CSystemInfo::WorkingSetSizeMB();
      LOG_ERROR(_T("Exception throw from new ICATMessage(Device%d, Protocol%d, dataLen:%d). ErrCode:%d CurrentWorkingSetSize:%u MB"), iDevice, protocol, length, dwErr, nMemUse);
      return;
   }
   
   CDispatcher::Instance()->HandleMessage(pMessage);
}

HANDLE CCommInterface::GetKillWriteHandle(int iDevice)
{
	if (m_pKillWriteHandle)
		return m_pKillWriteHandle(iDevice);
	return NULL;
}

UE_errCode_t CCommInterface::SendCommandWithTimeout( int iDevice, int protocol, BYTE *command, int length, int nTimeout)
{
	ASSERT(command);
	ASSERT(iDevice>=0);
	ASSERT(iDevice<MAX_DEVICE_NUM);
	if(protocol==(int)eDIAGProtocol)
	{
		ASSERT(length>=16);
		if(length<16)
		{
			ASSERT(FALSE);
			LOG_ERROR(_T("command data length error"));
			return UE_PARAM_ERR;
		}
	}
	else if(protocol==(int)eStringProtocol)
	{
		if(length==0)
		{
			ASSERT(FALSE);
			LOG_ERROR(_T("command data length error"));
			return UE_PARAM_ERR;
		}
	}
	else
	{
		LOG_ERROR(_T("command protocol error"));
		return UE_PARAM_ERR;
	}



	// logging to icl
	BYTE* data=NULL;
	int dataLen=0;
	if(protocol==(int)eStringProtocol)
	{
		data = command;
		dataLen = length;
	}
	else
	{
		data = command + 2*sizeof(WORD);
		dataLen = length - 2*sizeof(WORD);
	}

	try
	{
		CICATMessage* pMessage = new CICATMessage(protocol, 3, iDevice, data, dataLen);
		pMessage->m_Direction = (CICATMessage::eDirection)(1<<(iDevice+1));
		CDispatcher::Instance()->HandleMessage(pMessage);
	}
	catch (...)
	{
		LOG_ERROR(_T("Exception throw from new CICATMessage"));
		return UE_PARAM_ERR;
	}


	// send to UE
	UE_errCode_t errCode = UE_WRITE_TO_TARGET_ERR;
	if(m_pCommandTimeoutFunc)
	{
		errCode = m_pCommandTimeoutFunc(iDevice, protocol, command, length,nTimeout);
	}

	return errCode;
}
UE_errCode_t CCommInterface::SendCommand( int iDevice, int protocol, BYTE *command, int length )
{
   ASSERT(command);
   ASSERT(iDevice>=0);
   ASSERT(iDevice<MAX_DEVICE_NUM);
   if(protocol==(int)eDIAGProtocol)
   {
      ASSERT(length>=16);
      if(length<16)
      {
         ASSERT(FALSE);
         LOG_ERROR(_T("command data length error"));
         return UE_PARAM_ERR;
      }
   }
   else if(protocol==(int)eStringProtocol)
   {
      if(length==0)
      {
         ASSERT(FALSE);
         LOG_ERROR(_T("command data length error"));
         return UE_PARAM_ERR;
      }
   }
   else
   {
      LOG_ERROR(_T("command protocol error"));
      return UE_PARAM_ERR;
   }

   
   
   // logging to icl
   BYTE* data=NULL;
   int dataLen=0;
   if(protocol==(int)eStringProtocol)
   {
      data = command;
      dataLen = length;
   }
   else
   {
      data = command + 2*sizeof(WORD);
      dataLen = length - 2*sizeof(WORD);
   }

   try
   {
      CICATMessage* pMessage = new CICATMessage(protocol, 3, iDevice, data, dataLen);
      pMessage->m_Direction = (CICATMessage::eDirection)(1<<(iDevice+1));
      CDispatcher::Instance()->HandleMessage(pMessage);
   }
   catch (...)
   {
      LOG_ERROR(_T("Exception throw from new CICATMessage"));
      return UE_PARAM_ERR;
   }


   // send to UE
   UE_errCode_t errCode = UE_WRITE_TO_TARGET_ERR;
   if(m_pCommandFunc)
   {
      errCode = m_pCommandFunc(iDevice, protocol, command, length);
   }

   return errCode;
}

// bool CCommInterface::IsDiag( int iDevice )
// {
//    ASSERT(FALSE);
//    return true;
// }
// 
// bool CCommInterface::IsRawData(int iDevice)
// {
//    return true;
// }

int CCommInterface::GetCommProtocol( int iDevice )
{
   CCommSettings commSettings;
   EProtocolType eCommProtocol = eDIAGProtocol;
   if( GetCommSettings(iDevice, commSettings) )
   {
      eCommProtocol = commSettings.m_eProtType;
   }

   return eCommProtocol;
}

BOOL CCommInterface::RegStatusFunc( LPVOID lpObj, LPFN_DEVICESTATUS_FUNC pFunc )
{
   LPFN_REGSTATUS_FUNC pRegStatusFunc=NULL;
   if(m_hDevComm)
   {
      pRegStatusFunc = (LPFN_REGSTATUS_FUNC)GetProcAddress(m_hDevComm, "DevComm_RegStatusFunc");
   }
   
   int retCode = -1;
   if(pRegStatusFunc)
   {
      retCode = pRegStatusFunc(lpObj, pFunc);
      LOG_INFO_WARN(retCode==0, _T("RegDeviceStatusFunc retrun 0x%x"), retCode);
   }

   return retCode==0? TRUE:FALSE;
}

int CCommInterface::GetConnectionStatus( int iDevice )
{
   LPFN_GET_CONNECTIONSTATUS pGetDeviceStatus=NULL;
   if(m_hDevComm)
   {
      pGetDeviceStatus = (LPFN_GET_CONNECTIONSTATUS)GetProcAddress(m_hDevComm, "DevComm_GetConnectionStatus");
   }

   int eStatus=eDISABLED;
   if(pGetDeviceStatus)
   {
      eStatus = pGetDeviceStatus(iDevice);
   }

   return eStatus;
}

BOOL CCommInterface::EnableDev( int iDevice )
{
	LPFN_ENABLEDEV pGetCommSettingsFunc=NULL;
	if(m_hDevComm)
	{
		pGetCommSettingsFunc = (LPFN_ENABLEDEV)GetProcAddress(m_hDevComm, "DevComm_EnableDev");
	}

	int retCode = -1;
	if(pGetCommSettingsFunc)
	{
		retCode = pGetCommSettingsFunc(iDevice);
		LOG_WARN_IF(retCode!=0, _T("DevComm_EnableDev retrun errCode:0x%08x"), retCode);
	}

	return retCode==0? TRUE:FALSE;
}

BOOL CCommInterface::DisableDev( int iDevice )
{
	LPFN_DISABLEDEV pGetCommSettingsFunc=NULL;
	if(m_hDevComm)
	{
		pGetCommSettingsFunc = (LPFN_DISABLEDEV)GetProcAddress(m_hDevComm, "DevComm_DisableDev");
	}

	int retCode = -1;
	if(pGetCommSettingsFunc)
	{
		retCode = pGetCommSettingsFunc(iDevice);
		LOG_WARN_IF(retCode!=0, _T("DevComm_DisableDev retrun errCode:0x%08x"), retCode);
	}

	return retCode==0? TRUE:FALSE;
}

BOOL CCommInterface::SetCommSettings( CCommSettings CommSettings )
{
	LPFN_SETCOMMSETTINGS pGetCommSettingsFunc=NULL;
	if(m_hDevComm)
	{
		pGetCommSettingsFunc = (LPFN_SETCOMMSETTINGS)GetProcAddress(m_hDevComm, "DevComm_SetCommSettings");
	}

	int retCode = -1;
	if(pGetCommSettingsFunc)
	{
		retCode = pGetCommSettingsFunc(CommSettings);
		LOG_WARN_IF(retCode!=0, _T("SetCommSettingsFunc retrun errCode:0x%08x"), retCode);
	}

	return retCode==0? TRUE:FALSE;
}

BOOL CCommInterface::GetCommSettings( int iDevice, CCommSettings& CommSettings )
{
   LPFN_GETCOMMSETTINGS pGetCommSettingsFunc=NULL;
   if(m_hDevComm)
   {
      pGetCommSettingsFunc = (LPFN_GETCOMMSETTINGS)GetProcAddress(m_hDevComm, "DevComm_GetCommSettings");
   }

   int retCode = -1;
   if(pGetCommSettingsFunc)
   {
      retCode = pGetCommSettingsFunc(iDevice, CommSettings);
      LOG_WARN_IF(retCode!=0, _T("GetCommSettingsFunc retrun errCode:0x%08x"), retCode);
   }

   return retCode==0? TRUE:FALSE;
}

LRESULT CCommInterface::OnMessageReceived( CMessage* pMessage )
{
    switch( pMessage->message )
    {
    case IMC_GET_COMMINF:
       {
          CMsgGetCommInf* pMsg = dynamic_cast<CMsgGetCommInf*>(pMessage);
          ASSERT(pMsg);

          int iStatus = GetConnectionStatus(pMsg->iDevice);
          CCommSettings commSettings;
          BOOL bRet = GetCommSettings(pMsg->iDevice, commSettings);
          if(bRet)
          {
             pMsg->errCode = 0;
             pMsg->eStatus = iStatus;
             pMsg->eProtocol = (int)commSettings.m_eProtType;
             pMsg->eComm = (int)commSettings.m_eCommType;
             return 0;
          }
          else
          {
             pMsg->errCode = -1;
             return -1;
          }
       }

    case IMC_GET_UECPINFO:
       {
          //CMsgGetUeCpInfo* pMsg = dynamic_cast<CMsgGetUeCpInfo*>(pMessage);
          //ASSERT(pMsg);
          //if(pMsg)
          //{
          //   SYSTEMTIME st;
          //   tm_t& tmt = pMsg->tmSystemTime;
          //   st.wYear = tmt.tm_year;
          //   st.wMonth = tmt.tm_mon;
          //   st.wDay = tmt.tm_mday;
          //   st.wDayOfWeek = tmt.tm_wday;
          //   st.wHour = tmt.tm_hour;
          //   st.wMinute = tmt.tm_min;
          //   st.wSecond = tmt.tm_sec;
          //   st.wMilliseconds = tmt.tm_uSec/1000;
          // 
          //   
          //   TimeUtil::SystemTimeToTimet(st, &m_timetSyncTime[pMsg->iDevice]);//seconds from 1970.1.1
          //   m_wSystemTimeMilli[pMsg->iDevice] = st.wMilliseconds;//milliseconds
          //   m_bUseSyncTime[pMsg->iDevice] = true;
          //}
       }
       break;

    case IMC_TARGET_TIME_SYNC:
       {
          CMsgTargetTimeSync* pMsg = dynamic_cast<CMsgTargetTimeSync*>(pMessage);
          ASSERT(pMsg);
          if(pMsg)
          {
             m_dwSyncPduTs[pMsg->iDevice] =  pMsg->dwSyncPduTs;

             SYSTEMTIME st;
             tm_t& tmt = pMsg->tmSystemTime;
             st.wYear = tmt.tm_year+1900;
             st.wMonth = tmt.tm_mon;
             st.wDay = tmt.tm_mday;
             st.wDayOfWeek = tmt.tm_wday;
             st.wHour = tmt.tm_hour;
             st.wMinute = tmt.tm_min;
             st.wSecond = tmt.tm_sec;
             st.wMilliseconds = tmt.tm_uSec/1000;
             


             TimeUtil::SystemTimeToTimet(st, &m_timetSyncTime[pMsg->iDevice]);//seconds from 1970.1.1
             TimeUtil::TimetToSystemTime(m_timetSyncTime[pMsg->iDevice], &st);

             m_wSystemTimeMilli[pMsg->iDevice] = st.wMilliseconds;//milliseconds
             m_bUseSyncTime[pMsg->iDevice] = true;
             m_dwSyncPduTs[pMsg->iDevice] = pMsg->dwSyncPduTs;

             LOG_INFO(_T("ConvertedToTimet,Second:%u, milliSecond:%u"), m_timetSyncTime[pMsg->iDevice], st.wMilliseconds);
             LOG_INFO(_T("SyncPduTs:%u"), pMsg->dwSyncPduTs);
          }
       }
       break;

    case IMC_DEVICE_CHANGED:
       {
          CMsgDeviceChanged* pMsg = dynamic_cast<CMsgDeviceChanged*>(pMessage);
          ASSERT(pMsg);
          if(pMsg && pMsg->iProtocol == eDIAGProtocol)
          {
             if( pMsg->iNewStatus != (int)eCONNECTED)
             {
                ZeroMemory(&m_timetSyncTime[pMsg->iDevice], sizeof(m_timetSyncTime[pMsg->iDevice]));
                m_bUseSyncTime[pMsg->iDevice] = false;
             }
          }
       }
       break;


    default:

       break;
    }


    return 0;
}


UE_errCode_t CCommInterface::SendADBCommand( int iDevice, int protocol, CString command )
{
	ASSERT(iDevice>=0);
	ASSERT(iDevice<MAX_DEVICE_NUM);

#if 0
	if(protocol != (int)eADBProtocol)
	{
		LOG_ERROR(_T("command data length error"));
		return UE_PARAM_ERR;
	}
#endif

	// logging to icl
	int dataLen = WideCharToMultiByte(CP_ACP, 0, command, -1, NULL, 0, NULL, NULL);  
	char* data = new char[dataLen + 1];  
	memset(data, 0, dataLen + 1);  
	WideCharToMultiByte (CP_ACP, 0,command, -1, data, dataLen, NULL,NULL);  

	try
	{
		CICATMessage* pMessage = new CICATMessage(protocol, 3, iDevice, (BYTE*)data, dataLen);
		pMessage->m_Direction = (CICATMessage::eDirection)(1<<(iDevice+1));
		CDispatcher::Instance()->HandleMessage(pMessage);
	}
	catch (...)
	{
		LOG_ERROR(_T("Exception throw from new CICATMessage"));
		return UE_PARAM_ERR;
	}


	// send to UE
	UE_errCode_t errCode = UE_WRITE_TO_TARGET_ERR;
	if(m_pADBCommandFunc)
	{
		errCode = m_pADBCommandFunc(iDevice, protocol, command);
	}

	return errCode;
}

UE_errCode_t CCommInterface::StopADBCommand( int iDevice, int protocol )
{
	ASSERT(iDevice>=0);
	ASSERT(iDevice<MAX_DEVICE_NUM);

#if 0
	if(protocol != (int)eADBProtocol)
	{
		LOG_ERROR(_T("command data length error"));
		return UE_PARAM_ERR;
	}
#endif

	CString command = _T("ctrl+c");

	// logging to icl
	int dataLen = WideCharToMultiByte(CP_ACP, 0, command, -1, NULL, 0, NULL, NULL);  
	char* data = new char[dataLen + 1];  
	memset(data, 0, dataLen + 1);  
	WideCharToMultiByte (CP_ACP, 0,command, -1, data, dataLen, NULL,NULL);  

	try
	{
		CICATMessage* pMessage = new CICATMessage(protocol, 3, iDevice, (BYTE*)data, dataLen);
		pMessage->m_Direction = (CICATMessage::eDirection)(1<<(iDevice+1));
		CDispatcher::Instance()->HandleMessage(pMessage);
	}
	catch (...)
	{
		LOG_ERROR(_T("Exception throw from new CICATMessage"));
		return UE_PARAM_ERR;
	}


	// send to UE
	UE_errCode_t errCode = UE_WRITE_TO_TARGET_ERR;
	if(m_pStopADBFunc)
	{
		errCode = m_pStopADBFunc(iDevice, protocol);
	}

	return errCode;
}

int CCommInterface::GetAliveDiagDeviceID()
{
   for(int i=0; i<MAX_DEVICE_NUM; ++i)
   {
      int iState = GetConnectionStatus(i);
      if(iState==(int)eCONNECTED && GetCommProtocol(i)==(int)eDIAGProtocol)
      {
         return i;
      }
   }

   for(int i=0; i<MAX_DEVICE_NUM; ++i)
   {
      int iState = GetConnectionStatus(i);
      if(iState==(int)eDISCONNECTED && GetCommProtocol(i)==(int)eDIAGProtocol)
      {
         return i;
      }
   }

   return 0;
}
