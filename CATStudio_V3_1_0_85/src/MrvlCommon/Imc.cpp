#include "stdafx.h"
#include "Imc.h"
#include "imc/MessageLoop.h"
#include "DeviceStatus.h"
#include "Logging/Logging.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CImc::CImc()
{

}

CImc::~CImc()
{

}

BOOL CImc::GetCommInfo( int iDevice, int& eConnectionStatus, int& eProtocol, int& eComm )
{
   CMsgGetCommInf* pMessage = new CMsgGetCommInf;
   pMessage->iDevice = iDevice;
   pMessage->Send();

   if( pMessage->errCode==0 )
   {
      eConnectionStatus = pMessage->eStatus;
      eProtocol = pMessage->eProtocol;
      eComm = pMessage->eComm;
      pMessage->DecRef();
      return TRUE;
   }
   
   pMessage->DecRef();
   return FALSE;
}

BOOL CImc::GetLogFilesName( int num, CStringArray& fileArray, int& iFileIndex )
{
   CMsgGetLogFilesName* pMessage = new CMsgGetLogFilesName;
   pMessage->iFileIndex = iFileIndex;
   pMessage->nCount = num;
   pMessage->errCode = -1;

   pMessage->Send();

   if(pMessage->errCode==0 && pMessage->strFilenameArr.GetCount()>0)
   {
      for(int i=0; i<pMessage->strFilenameArr.GetCount(); ++i)
      {
         fileArray.Add(pMessage->strFilenameArr.GetAt(i));
      }

      iFileIndex = pMessage->iFileIndex;
      pMessage->DecRef();
      return TRUE;
   }

   pMessage->DecRef();
   return FALSE;
}


//************************************
// Method:    GetLogFileName
// FullName:  CImc::GetLogFileName
// Access:    public 
// Returns:   BOOL
// Qualifier:
// Parameter: CString & strFilename - the full path name of the log you specified by iFileIndex
// Parameter: int & iFileIndex - pass -1 to get the last recently closed log file name.
//************************************
BOOL CImc::GetLogFileName( CString& strFilename, int& iFileIndex)
{
   CMsgGetLogFilesName* pMessage = new CMsgGetLogFilesName;
   pMessage->iFileIndex = iFileIndex;
   pMessage->nCount = 1;
   pMessage->errCode = -1;
   
   pMessage->Send();

   if(pMessage->errCode==0 && pMessage->strFilenameArr.GetCount()>0)
   {
      iFileIndex = pMessage->iFileIndex;
      strFilename = pMessage->strFilenameArr.GetAt(0);
      pMessage->DecRef();
      return TRUE;
   }

   pMessage->DecRef();
   return FALSE;
}

BOOL CImc::GetLoadedLogInf( CMsgGetLoadedLogInf& LogInf, LPCTSTR lpszCallFrom/*=_T("Null")*/ )
{
   CMsgGetLoadedLogInf* pMessage = &LogInf;
   pMessage->errCode = -1;
   
   LOG_INFO(_T("GetLogInf... (call from %s)"), lpszCallFrom);

   pMessage->Send();

   LOG_INFO_WARN(pMessage->errCode==0, _T("GetLogInf(call from %s) return, errCode 0x%x, IsLogLoaded:%s."), 
      lpszCallFrom, pMessage->errCode, pMessage->bIsLogLoaded? _T("Yes"):_T("No"));

   BOOL bRet = (pMessage->errCode==0 && pMessage->bIsLogLoaded);
   return bRet;
}

void CImc::ShowMessage( UINT64 uIndex, CString strSendingModuleName, int iSendingModuleInstance )
{
   CMsgShowMessage* pMessage = new CMsgShowMessage;
   pMessage->uMessageIndex = uIndex;
   pMessage->strSendingModuleName = strSendingModuleName;
   pMessage->iSendingModuleInstance = iSendingModuleInstance;
   pMessage->ucSimIndex = 0xF;
   
   pMessage->Post();
   pMessage->DecRef();
}

void CImc::ShowMessage(UINT64 uIndex, CString strSendingModuleName, int iSendingModuleInstance, UINT8 uSimIndex)
{
	CMsgShowMessage* pMessage = new CMsgShowMessage;
	pMessage->uMessageIndex = uIndex;
	pMessage->strSendingModuleName = strSendingModuleName;
	pMessage->iSendingModuleInstance = iSendingModuleInstance;
	pMessage->ucSimIndex = uSimIndex;

	pMessage->Post();
	pMessage->DecRef();
}

void CImc::OpenNvmEditor( CString strFileName, CString strStructname, int iDevice, int targetType, CString strSendingModule)
{
   // 先判断NvmEditor是否已经启动
   // 如果没有启动，则构造一个新消息Post出去，框架是这个新消息的唯一接收者，
   // 当框架接收到这个消息后，启动NvmEditor，再调用一次OpenNvmEditor
	CMsgOpenNvmMessage* pMessage = new CMsgOpenNvmMessage;
	pMessage->strFileName = strFileName;
	pMessage->strStructname = strStructname;
	pMessage->nDeviceID = iDevice;
	pMessage->nTargetType = targetType;
   pMessage->strSendingModule = strSendingModule;

	pMessage->Post();
   pMessage->DecRef();
}

CString CImc::GetLoggingPath()
{
   CMsgGetLoggingPath* pMsg = new CMsgGetLoggingPath;
   pMsg->Send();
   CString strLogginPath = pMsg->strLoggingPath;

   pMsg->DecRef();
   return strLogginPath;
}

BOOL CImc::CloseOnlineLogFile()
{
   CMsgCloseOnlineLog* pMsg = new CMsgCloseOnlineLog;
   pMsg->Send();

   LOG_NOTICE_ERROR(pMsg->errCode==0, _T("MsgCloseOnlineLog return %d. %s."), pMsg->errCode, pMsg->strError);
   BOOL bRet = (pMsg->errCode==0);
   pMsg->DecRef();
   
   return bRet;
}

void CImc::PostMsgDatabaseChanged( int iDevice, DWORD dwCpVerOld, DWORD dwApVerOld, DWORD dwCpVerNew, DWORD dwApVerNew, DWORD dwCpNvmVerOld, DWORD dwApNvmVerOld, DWORD dwCpNvmVerNew, DWORD dwApNvmVerNew )
{
   CMsgDatabaseChanged* pMsg = new CMsgDatabaseChanged;
   pMsg->dwCpVerOld = dwCpVerOld;
   pMsg->dwApVerOld = dwApVerOld;
   pMsg->dwCpVerNew = dwCpVerNew;
   pMsg->dwApVerNew = dwApVerNew;
   pMsg->dwCpNvmVerOld = dwCpNvmVerOld;
   pMsg->dwApNvmVerOld = dwApNvmVerOld;
   pMsg->dwCpNvmVerNew = dwCpNvmVerNew;
   pMsg->dwApNvmVerNew = dwApNvmVerNew;
   pMsg->iDevice = iDevice;
   pMsg->Post();
   pMsg->DecRef();
}

void CImc::PostMsgDeviceChanged( int iDevice, int iNewStatus, int iProtocol )
{
   CMsgDeviceChanged* pMsg = new CMsgDeviceChanged;
   pMsg->iDevice = iDevice;
   pMsg->iNewStatus = iNewStatus;
   pMsg->iProtocol = iProtocol;
   pMsg->Post();
   pMsg->DecRef();
}

bool CImc::IsDatabaseLoaded( int iDevice )
{
   CMsgIsDatabaseLoaded* pMsg = new CMsgIsDatabaseLoaded;
   pMsg->iDevice = iDevice;

   pMsg->Send();
   bool bIsLoaded = pMsg->bIsDatabaseLoaded;
   pMsg->DecRef();

   return bIsLoaded;
}

void CImc::Start(LPCTSTR lpszSendingModule, bool bToModules/*=false*/)
{
   CMsgStart* pMsg = new CMsgStart;
   pMsg->strSendingModule = lpszSendingModule;
   pMsg->bToModules = bToModules;
   pMsg->Send();
   pMsg->DecRef();
}

void CImc::Pause(LPCTSTR lpszSendingModule, bool bToModules/*=false*/)
{
   CMsgPause* pMsg = new CMsgPause;
   pMsg->strSendingModule = lpszSendingModule;
   pMsg->bToModules = bToModules;
   pMsg->Send();
   pMsg->DecRef();
}

void CImc::Stop(LPCTSTR lpszSendingModule, bool bToModules/*=false*/)
{
	CMsgGetApLog* pGetApMsg = new CMsgGetApLog();
	pGetApMsg->Send();
	pGetApMsg->DecRef();
	Sleep(3000);
   CMsgStop* pMsg = new CMsgStop;
   pMsg->strSendingModule = lpszSendingModule;
   pMsg->bToModules = bToModules;
   pMsg->Send();
   pMsg->DecRef();
}

void CImc::Clear(LPCTSTR lpszSendingModule, bool bToModules/*=false*/)
{
   CMsgClear* pMsg = new CMsgClear;
   pMsg->strSendingModule = lpszSendingModule;
   pMsg->bToModules = bToModules;
   pMsg->Send();
   pMsg->DecRef();
}

EPlayState CImc::GetPlayState()
{
   CMsgGetPlayState* pMsg = new CMsgGetPlayState;
   pMsg->Send();
   EPlayState ePlayState = pMsg->ePlayState;
   pMsg->DecRef();
   return ePlayState;
}

DWORD CImc::GetUECpVersion( int iDevice )
{
   DWORD dwVersion;
   CMsgGetUEDBVersion* pMsg = new CMsgGetUEDBVersion;
   pMsg->iDevice = iDevice;
   pMsg->bAppSide = false;
   pMsg->Send();
   dwVersion = pMsg->dwVersion;
   pMsg->DecRef();
   return dwVersion;
}

DWORD CImc::GetUEApVersion( int iDevice )
{
   DWORD dwVersion;
   CMsgGetUEDBVersion* pMsg = new CMsgGetUEDBVersion;
   pMsg->iDevice = iDevice;
   pMsg->bAppSide = true;
   pMsg->Send();
   dwVersion = pMsg->dwVersion;
   pMsg->DecRef();
   return dwVersion;
}

BOOL CImc::GetLogFileNameByIndex( UINT64 uMesageIndex, CString& strFilename, int* pFileIndex/*=NULL*/, UINT64* pFirstIndex/*=NULL*/, UINT64* pLastIndex/*=NULL*/ )
{
   BOOL bRet = FALSE;
   CMsgGetLogFileNameByIndex* pMsg = new CMsgGetLogFileNameByIndex(uMesageIndex);
   pMsg->Send();
   if(pMsg->lError==0)
   {
      strFilename = pMsg->strFilename;
      if(pFileIndex)
         *pFileIndex = pMsg->iFileIndex;
      if(pFirstIndex)
         *pFirstIndex = pMsg->uFirst;
      if(pLastIndex)
         *pLastIndex = pMsg->uLast;
      
      bRet = TRUE;
   }

   pMsg->DecRef();
   return bRet;
}

bool CImc::GetUeCpInfo( int iDevice, CUeCpInfo& oUeCpInfo, CString strSendingModule/*=_T("")*/ )
{
   bool bRet = false;
   CMsgGetUeCpInfo* pMsg = new CMsgGetUeCpInfo();
   pMsg->iDevice = iDevice;
   pMsg->Send();
   if(pMsg->lError!=-1)
   {
      oUeCpInfo.m_i32Version = pMsg->i32Version;
      oUeCpInfo.m_strUeRatType = pMsg->strUeRatType;
      oUeCpInfo.m_strSimType = pMsg->strSimType;
      oUeCpInfo.m_strCpVersion = pMsg->strCpVersion;
      oUeCpInfo.m_strMsaVersion = pMsg->strMsaVersion;
      oUeCpInfo.m_strBoardVersion = pMsg->strBoardVersion;
      oUeCpInfo.m_strPlatformStream = pMsg->strPlatformStream;
      oUeCpInfo.m_strProtocolStream = pMsg->strProtocolStream;
      oUeCpInfo.m_strMsaStream = pMsg->strMsaStream;
      bRet = true;
   }
   
   pMsg->DecRef();
   return bRet;
}

bool CImc::IsAutoUpdateDBEnabled()
{
   bool bAutoUpdate = false;
   CMsgGetIsAutoUpdateDB* pMsg = new CMsgGetIsAutoUpdateDB();
   pMsg->lError = -1;
   pMsg->Send();
   bAutoUpdate = pMsg->bAutoUpdate; 
   pMsg->DecRef();
   return bAutoUpdate;
}

void CImc::OpenOnlineNewLog(const CString & strLogName )
{
   CMsgOpenOnlineNewLog* pMsg = new CMsgOpenOnlineNewLog();
   pMsg->strLogFileName = strLogName;
   pMsg->Post();
   pMsg->DecRef();
}

void CImc::OnlineLogClosed( CString strLogPathName )
{
   CMsgLogFileClosed* pMsg = new CMsgLogFileClosed();
   pMsg->strLogPathName = strLogPathName;
   pMsg->Post();
   pMsg->DecRef();
}

void CImc::ExportExtractedLog( CString strLogPathName )
{
   CMsgExportExtractedLog* pMsg = new CMsgExportExtractedLog();
   pMsg->strLogPathName = strLogPathName;
   pMsg->Post();
   pMsg->DecRef();
}

CString CImc::GetBinLogsPath( CString strSendingModule/*=_T("")*/ )
{
   CString strRes;
   CMsgGetBinLogsPath* pMsg  = new CMsgGetBinLogsPath;
   pMsg->Send();
   strRes = pMsg->strBinLogsPath;
   pMsg->DecRef();
   
   return strRes;
}

CView* CImc::GetActiveView()
{
   CMsgGetActiveView* pMsg = new CMsgGetActiveView;
   pMsg->Send();
   CView* pView = pMsg->pView;
   pMsg->DecRef();
   return pView;
}

void CImc::OpenEntireFilter(int nDevice/* = -1*/ )
{
	CMsgOpenEntireFilter* pMsg = new CMsgOpenEntireFilter;
	pMsg->iDevice = nDevice;
	pMsg->Send();
	pMsg->DecRef();
}

void CImc::CloseEntireFilter(int nDevice/* = -1*/ )
{
	CMsgCloseEntireFilter* pMsg = new CMsgCloseEntireFilter;
	pMsg->iDevice = nDevice;
	pMsg->Send();
	pMsg->DecRef();
}

void CImc::SetDiagFilter(int nDevice, USHORT MessagId, int TargetType, bool bPass)
{
	CMsgSetDiagFilter * pMsg = new CMsgSetDiagFilter(bPass, MessagId, TargetType, nDevice);
	pMsg->Send();
	pMsg->DecRef();
}

void CImc::SetDiagFilter(int nDevice, const CString & strCat1, const CString & strCat2, const CString & strCat3, int TargetType, bool bPass)
{
	CMsgSetDiagFilter * pMsg = new CMsgSetDiagFilter(bPass, strCat1, strCat2, strCat3, TargetType, nDevice);
	pMsg->Send();
	pMsg->DecRef();
}

void CImc::SetDspFilter(int nDevice, int type, USHORT opCode, bool bPass)
{
	CMsgSetDspFilter * pMsg = new CMsgSetDspFilter(bPass, type, opCode, nDevice);
	pMsg->Send();
	pMsg->DecRef();
}

void CImc::SetDspFilter(int nDevice, int type, const CString & name, bool bPass)
{
	CMsgSetDspFilter * pMsg = new CMsgSetDspFilter(bPass, type, name, nDevice);
	pMsg->Send();
	pMsg->DecRef();
}

void CImc::SetGkiFilter(int nDevice, DWORD dwSigId, bool bPass)
{
	CMsgSetGkiFilter * pMsg = new CMsgSetGkiFilter(bPass, dwSigId, nDevice);
	pMsg->Send();
	pMsg->DecRef();
}

void CImc::SetGkiFilter(int nDevice, const CString & name, bool bPass)
{
	CMsgSetGkiFilter * pMsg = new CMsgSetGkiFilter(bPass, name, nDevice);
	pMsg->Send();
	pMsg->DecRef();
}

void CImc::OpenViewer(const CString & name, int type /*= 0*/)
{
	CMsgOpenViewer * pMsg = new CMsgOpenViewer(name, type);
	pMsg->Send();
	pMsg->DecRef();
}

void CImc::CloseCurrentViewer(int type /*= 0*/)
{
	CMsgCloseViewer * pMsg = new CMsgCloseViewer(type);
	pMsg->Post();
	pMsg->DecRef();
}

CString CImc::GetLogName()
{
	CString strRes;
	CMsgGetLogName* pMsg  = new CMsgGetLogName;
	pMsg->Send();
	strRes = pMsg->strLogName;
	pMsg->DecRef();

	return strRes;
}

CString CImc::GetLogFullPathName()
{
	CString strRes;
	CMsgGetLogFullPathName* pMsg  = new CMsgGetLogFullPathName;
	pMsg->Send();
	strRes = pMsg->strLogFullPathName;
	pMsg->DecRef();

	return strRes;
}

CString CImc::GetCurrentLogName()
{
	CString strRes;
	CMsgGetCurrentLogName* pMsg  = new CMsgGetCurrentLogName;
	pMsg->Send();
	strRes = pMsg->strCurrentLogName;
	pMsg->DecRef();

	return strRes;
}

UINT64 CImc::GetLastLogMsgIdx()
{
	UINT64 uMesageIndex;
	CMsgGetLastMessageIndex *pMsg = new CMsgGetLastMessageIndex;
	pMsg->Send();
	uMesageIndex = pMsg->uMessageIndex;
	pMsg->DecRef();
	return uMesageIndex;
}

void CImc::InformLoggerUpdateDb()
{
	CMsgInformLoggerUpdateDb* pMsg  = new CMsgInformLoggerUpdateDb;
	pMsg->Send();
	pMsg->DecRef();
}


void CImc::EnableLogOperations()
{
	CMsgEnableLogOperations* pMsg = new CMsgEnableLogOperations;
	pMsg->Send();
	pMsg->DecRef();
}


void CImc::DisableLogOperations()
{
	CMsgDisableLogOperations* pMsg = new CMsgDisableLogOperations;
	pMsg->Send();
	pMsg->DecRef();
}


void CImc::ChangeDeviceState(int device, bool deviceEnabled, CCommSettings* commSettings)
{
	CMsgDeviceStateChanged* pMsg = new CMsgDeviceStateChanged(device, deviceEnabled, commSettings);
	pMsg->Send();
	pMsg->DecRef();
}
