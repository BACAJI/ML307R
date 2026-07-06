#pragma once
#include "imc/Message.h"
#include "tm_t.h"
#include <vector>
#include <map>
#include "CommSettings.h"


using namespace std;

enum IMC_MESSAGE
{
   IMC_MESSAGEID_BEGIN = WM_USER+5000,
   IMC_DEVICE_CHANGED = IMC_MESSAGEID_BEGIN,
   IMC_LOADING_NEWLOG,
   IMC_NEWLOG_LOADED,
   IMC_CHANGING_DATABSE,
   IMC_DATABASE_CHANGED,
   IMC_NEWLOG_OPENED,
   IMC_LOADLOG_CMD,


   IMC_GET_LOADEDLOGINF,
   IMC_GET_COMMINF,
   IMC_GET_LOGFILENAMES,
   IMC_SHOW_MESSAGE,
   IMC_UEVERSION,
   IMC_GET_LOGGINGPATH,   
   IMC_SHOW_NVM_MESSAGE,
   IMC_CLOSE_ONLINELOG,
   IMC_AUTOPULLDATABSE_RESULT,
   IMC_GET_ISDATABSELOADED,
   IMC_START,
   IMC_PAUSE,
   IMC_STOP,
   IMC_CLEAR,
   IMC_GET_PLAYSTATE,
   IMC_INSERT_BOOKMARK,
   IMC_GET_UEDBVERSION,
   IMC_GET_DROPPEDICATMSGCOUNT,
   IMC_GET_LOGFILENAME_BYINDEX,
   IMC_GET_UECPINFO,
   IMC_OPEN_ONLINE_NEWLOG,
   IMC_LOG_STRMSG,
   IMC_GET_ISAUTOUPDATEDB,
   IMC_LOGFILE_CLOSED,
   IMC_EXPORT_EXTRACTEDLOG,
   IMC_GET_BINLOGSPATH,
   IMC_GET_ACTIVEVIEW,
   IMC_GET_VOBSTREAMNAME,
   IMC_UECPINFO,
   
   IMC_OPEN_ENTIRE_FILTER,
   IMC_CLOSE_ENTIRE_FILTER,
   IMC_SET_DIAG_FILTER,
   IMC_SET_DSP_FILTER,
   IMC_SET_GKI_FILTER,

   IMC_OPEN_VIEWER,
   IMC_CLOSE_VIEWER,
   IMC_GET_LOG_NAME,
   IMC_GET_LOG_FULLPATH_NAME,
   IMC_GET_CURRENT_LOG_NAME,
   IMC_INFORM_LOGGER_UPDATE_DB,

   IMC_LOG_OPERATIONS_ENABLE,
   IMC_LOG_OPERATIONS_DISABLE,
   IMC_DEVICE_STATE_CHANGED,
   IMC_TARGET_TIME_SYNC,
   IMC_GET_AP_LOG,	
   IMC_CPLOG_START,
   IMC_CPLOG_STOP,
   IMC_SET_DEVCOMM,
   IMC_GET_LAST_MSG_IDX,
   IMC_MERGE_BOOKMARKS,
   // !!! NOTE !!!
   // Place new added enum definition before IMC_MESSAGE_END, 
   // and add correspond name string to ImcMessageName below.
   IMC_MESSAGEID_END,
};

static const CString ImcMessageName[]=
{
   _T("IMC_DEVICE_CHANGED"),
   _T("IMC_LOADING_NEWLOG"),
   _T("IMC_NEWLOG_LOADED"),
   _T("IMC_CHANGING_DATABSE"),
   _T("IMC_DATABASE_CHANGED"),
   _T("IMC_NEWLOG_OPENED"),
   _T("IMC_LOADLOG_CMD"),

   _T("IMC_GET_LOADEDLOGINF"),
   _T("IMC_GET_COMMINF"),
   _T("IMC_GET_LOGFILENAMES"),
   _T("IMC_SHOW_MESSAGE"),
   _T("IMC_UEVERSION"),
   _T("IMC_GET_LOGGINGPATH"),   
   _T("IMC_SHOW_NVM_MESSAGE"),
   _T("IMC_CLOSE_ONLINELOG"),
   _T("IMC_AUTOPULLDATABSE_RESULT"),
   _T("IMC_GET_ISDATABSELOADED"),
   _T("IMC_START"),
   _T("IMC_PAUSE"),
   _T("IMC_STOP"),
   _T("IMC_CLEAR"),
   _T("IMC_GET_PLAYSTATE"),
   _T("IMC_INSERT_BOOKMARK"),
   _T("IMC_GET_UEDBVERSION"),
   _T("IMC_GET_DROPPEDICATMSGCOUNT"),
   _T("IMC_GET_LOGFILENAME_BYINDEX"),
   _T("IMC_GET_UECPINFO"),
   _T("IMC_OPEN_ONLINE_NEWLOG"),
   _T("IMC_LOG_STRMSG"),
   _T("IMC_GET_ISAUTOUPDATEDB"),
   _T("IMC_LOGFILE_CLOSED"),
   _T("IMC_EXPORT_EXTRACTEDLOG"),
   _T("IMC_GET_BINLOGSPATH"),
   _T("IMC_GET_ACTIVEVIEW"),
   _T("IMC_GET_VOBSTREAMNAME"),
   _T("IMC_UECPINFO"),

   _T("IMC_OPEN_ALL_FILTER"),
   _T("IMC_CLOSE_ALL_FILTER"),
   _T("IMC_SET_DIAG_FILTER"),
   _T("IMC_SET_DSP_FILTER"),
   _T("IMC_SET_GKI_FILTER"),
   _T("IMC_OPEN_VIEWER"),
   _T("IMC_CLOSE_VIEWER"),
   _T("IMC_GET_LOG_NAME"),
   _T("IMC_GET_LOG_FULLPATH_NAME"),
   _T("IMC_GET_CURRENT_LOG_NAME"),
   _T("IMC_INFORM_LOGGER_UPDATE_DB"),

   _T("IMC_LOG_OPERATIONS_ENABLE"),
   _T("IMC_LOG_OPERATIONS_DISABLE"),
   _T("IMC_DEVICE_STATE_CHANGED"),
   _T("IMC_TARGET_TIME_SYNC"),
   _T("IMC_GET_AP_LOG"),
   _T("IMC_CPLOG_START"),
   _T("IMC_CPLOG_STOP"),
   _T("IMC_SET_DEVCOMM"),
   _T("IMC_GET_LAST_MSG_IDX"),
   _T("IMC_MERGE_BOOKMARKS"),
   //End of Table
   _T("IMC_MESSAGEID_END")
};

static void GetImcMessageName(const CMessage* pMessage, CString& outString)
{
   const static int nImcMsgCount = IMC_MESSAGEID_END - IMC_MESSAGEID_BEGIN;
   
   int index = pMessage->message - IMC_MESSAGEID_BEGIN;
   if(index>=0 && index<nImcMsgCount)
   {
      outString = ImcMessageName[index];
   }
   else
   {
      outString.Format(_T("(Invalid MessageID:%d)"), pMessage->message);
   }
}

class CMsgCPLogStart : public CMessage
{
protected:
   virtual ~CMsgCPLogStart(){};

public:
   CMsgCPLogStart(){ message = IMC_CPLOG_START; iDevice = 0;};
   CMsgCPLogStart(int _iDevice){ message = IMC_CPLOG_START; iDevice = _iDevice;};
   int iDevice;
};

class CMsgCPLogStop : public CMessage
{
protected:
	virtual ~CMsgCPLogStop(){};

public:
	CMsgCPLogStop(){ message = IMC_CPLOG_STOP; iDevice = 0;};
	CMsgCPLogStop(int _iDevice){ message = IMC_CPLOG_STOP; iDevice = _iDevice;};
	int iDevice;
};

class CMsgGetApLog : public CMessage
{
protected:
	virtual ~CMsgGetApLog(){};

public:
	CMsgGetApLog(){ message = IMC_GET_AP_LOG; iDevice = 0;};
	CMsgGetApLog(int _iDevice){ message = IMC_GET_AP_LOG; iDevice = _iDevice;};
	int iDevice;
};

class CMsgDeviceChanged : public CMessage
{
protected:
   virtual ~CMsgDeviceChanged(){};

public:
   CMsgDeviceChanged(){ message = IMC_DEVICE_CHANGED; };

   int iDevice;
   int iNewStatus;
   int iProtocol;
};

class CMsgUEVersion : public CMessage
{
protected:
   virtual ~CMsgUEVersion(){};
public:
   CMsgUEVersion(){ message = IMC_UEVERSION; };

   
   int   iDevice;
   bool  bAppSide;
   DWORD dwVersion;
};


class CMsgLoadingNewLog: public CMessage
{
public:
   virtual ~CMsgLoadingNewLog(){};

public:
   CMsgLoadingNewLog(){ message = IMC_LOADING_NEWLOG; }

   CString      strFilename;
};

class CMsgLoadLogCmd : public CMessage
{
protected:
   virtual ~CMsgLoadLogCmd(){};

public:
   CMsgLoadLogCmd(){ message = IMC_LOADLOG_CMD; }

   CString strLogPathName;

};

class CMsgNewLogLoaded : public CMessage
{
protected:
   virtual ~CMsgNewLogLoaded(){
      dwFilesize = 0;
      roiBegin = -1;
      roiEnd = -1;
      errCode = -1;
   };

public:
   CMsgNewLogLoaded(){ message = IMC_NEWLOG_LOADED; };

   long         errCode;
   CString      strFile;
   CString      strDBPath;
   DWORD        dwFilesize;
   vector<int>  devices;
   vector<int>  protocols;
   vector<bool> dbchanged;
   vector<DWORD> dwCpVers;
   vector<DWORD> dwApVers;
   UINT64       roiBegin;//range of interest
   UINT64       roiEnd;
   CString      strLogDecription;
   map<int, CString> m_mapRatMode;
   map<int, CString> m_mapSimType;
   map<int, CString> m_mapCpVersion;
   map<int, CString> m_mapMsaVersion;
   map<int, CString> m_mapBoardVersion;
   map<int, CString> m_mapPlatformStream;
   map<int, CString> m_mapProtocolStream;
   map<int, CString> m_mapMsaStream;
};

class CMsgGetLoadedLogInf : public CMsgNewLogLoaded
{
protected:
   virtual ~CMsgGetLoadedLogInf(){};

public:
   CMsgGetLoadedLogInf()
   { 
      message = IMC_GET_LOADEDLOGINF; 
      errCode = -1;
      bIsLogLoaded = false;
   };

   CMsgGetLoadedLogInf(const CMsgNewLogLoaded* msg)
   {
      devices = msg->devices;
      protocols = msg->protocols;
      dbchanged = msg->dbchanged;
      roiBegin = msg->roiBegin;
      roiEnd = msg->roiEnd;
      strFile = msg->strFile;
      strDBPath = msg->strDBPath;
      strLogDecription = msg->strLogDecription;
      m_mapBoardVersion = msg->m_mapBoardVersion;
      m_mapCpVersion = msg->m_mapCpVersion;
      m_mapMsaVersion = msg->m_mapMsaVersion;
      m_mapSimType = msg->m_mapSimType;
      m_mapRatMode = msg->m_mapRatMode;
      m_mapPlatformStream = msg->m_mapPlatformStream;
      m_mapProtocolStream = msg->m_mapProtocolStream;
      m_mapMsaStream = msg->m_mapMsaStream;
   }
   CMsgGetLoadedLogInf& operator=(const CMsgNewLogLoaded& msg)
   {
      devices = msg.devices;
      protocols = msg.protocols;
      dbchanged = msg.dbchanged;
      roiBegin = msg.roiBegin;
      roiEnd = msg.roiEnd;
      strFile = msg.strFile;
      strDBPath = msg.strDBPath;
      strLogDecription = msg.strLogDecription;
      m_mapBoardVersion = msg.m_mapBoardVersion;
      m_mapCpVersion = msg.m_mapCpVersion;
      m_mapMsaVersion = msg.m_mapMsaVersion;
      m_mapSimType = msg.m_mapSimType;
      m_mapRatMode = msg.m_mapRatMode;
      m_mapPlatformStream = msg.m_mapPlatformStream;
      m_mapProtocolStream = msg.m_mapProtocolStream;
      m_mapMsaStream = msg.m_mapMsaStream;
      return *this;
   }

   long errCode;
   bool bIsLogLoaded;
};

class CMsgChangingDatabase : public CMessage
{
protected:
   virtual ~CMsgChangingDatabase(){};

public:
   CMsgChangingDatabase(){ message = IMC_CHANGING_DATABSE; };
   
   int iDevice;
};

class CMsgDatabaseChanged : public CMessage
{
protected:
   virtual ~CMsgDatabaseChanged(){};

public:
   CMsgDatabaseChanged(){ message = IMC_DATABASE_CHANGED; };
   
   int iDevice;

   DWORD dwCpVerOld;
   DWORD dwApVerOld;
   DWORD dwCpVerNew;
   DWORD dwApVerNew;
   DWORD dwCpNvmVerOld;
   DWORD dwApNvmVerOld;
   DWORD dwCpNvmVerNew;
   DWORD dwApNvmVerNew;

};

class CMsgGetCommInf : public CMessage
{
protected:
   virtual ~CMsgGetCommInf(){};

public:
   CMsgGetCommInf(){ message = IMC_GET_COMMINF; errCode=-1;};
   
   int  iDevice;
   long errCode;
   int  eStatus;
   int  eProtocol;
   int  eComm;
};


class CMsgGetLogFilesName: public CMessage
{
protected:
   virtual ~CMsgGetLogFilesName(){};

public:
   CMsgGetLogFilesName(){ message = IMC_GET_LOGFILENAMES; errCode=-1;};
   
   int iFileIndex;
   int nCount;
   long errCode;
   CStringArray strFilenameArr;

};

class CMsgShowMessage: public CMessage
{
protected:
   virtual ~CMsgShowMessage(){};

public:
   CMsgShowMessage(){ message = IMC_SHOW_MESSAGE;};

   UINT64   uMessageIndex;
   CString  strSendingModuleName;
   int      iSendingModuleInstance;
   UINT8    ucSimIndex;
};

class CMsgOpenNvmMessage : public CMessage
{
public:
   virtual ~CMsgOpenNvmMessage() {}

public:
	CMsgOpenNvmMessage()
	{
		message = IMC_SHOW_NVM_MESSAGE;
      bToModules = false;
	}

   bool IsToModules() const { return bToModules; }
   void CloneTo(CMsgOpenNvmMessage* pMsg) const
   {
      pMsg->nDeviceID = nDeviceID;
      pMsg->nTargetType = nTargetType;
      pMsg->strFileName = strFileName;
      pMsg->strStructname = strStructname;
      pMsg->bToModules = bToModules;
      pMsg->strSendingModule = strSendingModule;
   }

	CString strFileName;
	CString strStructname;
	int nDeviceID;
	int nTargetType;
   bool bToModules;
   CString strSendingModule;
};

class CMsgNewLogOpened : public CMessage
{
protected:
   virtual ~CMsgNewLogOpened(){};

public:
   CMsgNewLogOpened(){ message = IMC_NEWLOG_OPENED; }

   CString  strLogFilename;
   CString  strLogFolder;
   int      iFileIndex;
};

class CMsgGetLoggingPath : public CMessage
{
protected:
   virtual ~CMsgGetLoggingPath(){};

public:
   CMsgGetLoggingPath(){ message = IMC_GET_LOGGINGPATH; }

   CString strLoggingPath;
};

class CMsgCloseOnlineLog : public CMessage
{
protected:
   virtual ~CMsgCloseOnlineLog(){};
public:
   CMsgCloseOnlineLog()
   { 
      message = IMC_CLOSE_ONLINELOG; 
      errCode = -1;
   }

   long errCode;
   CString strError;
};

class CMsgAutoPullDatabaseResult : public CMessage
{
protected:
   virtual ~CMsgAutoPullDatabaseResult(){};
public:
   CMsgAutoPullDatabaseResult()
   { 
      message = IMC_AUTOPULLDATABSE_RESULT;
      bCpOK = bApOK = false;
   }

   bool bCpOK;
   bool bApOK;
   CString strFilePath;
};

class CMsgIsDatabaseLoaded : public CMessage
{
protected:
   virtual ~CMsgIsDatabaseLoaded(){};

public:
   CMsgIsDatabaseLoaded()
   { 
      message = IMC_GET_ISDATABSELOADED; 
      iDevice = 0;
      bIsDatabaseLoaded = false;
   }

   int iDevice;
   bool bIsDatabaseLoaded;
};

enum EPlayState
{
   eStarted,
   ePaused,
   eStopped
};

class CMsgStart : public CMessage
{
protected:
   virtual ~CMsgStart(){};

public:
   CMsgStart()
   { 
      message = IMC_START; 
      userData = NULL;
      bToModules = false;
   }

   bool IsToModules() const 
   {
      return bToModules;
   }
   void CloneTo(CMsgStart* pMsg) const
   {
      pMsg->bToModules = bToModules;
      pMsg->eLastState = eLastState;
      pMsg->strSendingModule = strSendingModule;
      pMsg->userData = userData;
   }

   bool     bToModules;
   EPlayState eLastState;
   CString  strSendingModule;
   UINT_PTR userData;
   

};

class CMsgPause : public CMessage
{
protected:
   virtual ~CMsgPause(){};

public:
   CMsgPause()
   { 
      message = IMC_PAUSE;
      userData = NULL;
      bToModules = false;
   }

   bool IsToModules() const {return bToModules;}
   void CloneTo(CMsgPause* pMsg) const
   {
      pMsg->bToModules = bToModules;
      pMsg->eLastState = eLastState;
      pMsg->strSendingModule = strSendingModule;
      pMsg->userData = userData;
   }

   bool     bToModules;
   EPlayState eLastState;
   CString  strSendingModule;
   UINT_PTR userData;
};

class CMsgStop : public CMessage
{
protected:
   virtual ~CMsgStop(){};

public:
   CMsgStop()
   { 
      message = IMC_STOP;
      userData = NULL;
      bToModules = false;
   }

   bool IsToModules() const {return bToModules;}
   void CloneTo(CMsgStop* pMsg) const
   {
      pMsg->bToModules = bToModules;
      pMsg->eLastState = eLastState;
      pMsg->strSendingModule = strSendingModule;
      pMsg->userData = userData;
   }

   bool     bToModules;
   EPlayState eLastState;
   CString  strSendingModule;
   UINT_PTR userData;
};

class CMsgClear : public CMessage
{
protected:
   virtual ~CMsgClear(){};

public:
   CMsgClear()
   { 
      message = IMC_CLEAR; 
      userData = NULL;
      bToModules = false;
   }

   bool IsToModules() const {return bToModules;}
   void CloneTo(CMsgClear* pMsg) const
   {
      pMsg->bToModules = bToModules;
      pMsg->strSendingModule = strSendingModule;
      pMsg->userData = userData;
   }

   CString  strSendingModule;
   UINT_PTR userData;
   bool     bToModules;
};

class CMsgGetPlayState : public CMessage
{
protected:
   virtual ~CMsgGetPlayState(){};

public:
   CMsgGetPlayState()
   {
      message = IMC_GET_PLAYSTATE;
   }

   bool IsStarted() { return ePlayState==eStarted; }
   bool IsPaused()  { return ePlayState==ePaused;  }
   bool IsStopped() { return ePlayState==eStopped; }



   EPlayState ePlayState;
};

class CMsgInsertBookmark : public CMessage
{
protected:
	virtual ~CMsgInsertBookmark(){};

public:
	CMsgInsertBookmark(){ message = IMC_INSERT_BOOKMARK; };

	vector<UINT64>  msgIndex;
	vector<CString>  strDesc;
};

class CMsgGetUEDBVersion : public CMessage
{
protected:
   virtual ~CMsgGetUEDBVersion(){};

public:
   CMsgGetUEDBVersion()
   { 
      message = IMC_GET_UEDBVERSION;
      iDevice = 0;
      dwVersion = 0;
      bAppSide = false;
   }

   int   iDevice;
   bool  bAppSide;
   DWORD dwVersion;
};

class CMsgGetDroppedMsgCount : public CMessage
{
protected:
   virtual ~CMsgGetDroppedMsgCount(){};

public:
   CMsgGetDroppedMsgCount()
   {
      message = IMC_GET_DROPPEDICATMSGCOUNT;
      lError = -1;
   }

   long     lError;
   UINT     nDroppedCount;
   CString  strReceiverName;
};

class CMsgGetLogFileNameByIndex : public CMessage
{
private:
   virtual ~CMsgGetLogFileNameByIndex(){};

public:
   CMsgGetLogFileNameByIndex(UINT64 uMessageIndex)
   {
      message = IMC_GET_LOGFILENAME_BYINDEX;
      uIndex = uMessageIndex;
      lError = -1; 
   }

   
   UINT64 uIndex;
   long   lError;
   UINT64 uFirst;
   UINT64 uLast;
   CString strFilename;
   int    iFileIndex;
};

class CMsgUeCpInfo : public CMessage
{
private:
   virtual ~CMsgUeCpInfo(){};

public:
   CMsgUeCpInfo()
   {
      message  = IMC_UECPINFO;
      iDevice = 0;
   };

   int      iDevice;
   long     i32Version;
   CString  strUeRatType;
   CString  strSimType;
   CString  strCpVersion;
   CString  strMsaVersion;
   CString  strBoardVersion;
   CString  strPlatformStream;
   CString  strProtocolStream;
   CString  strMsaStream;

};



class CMsgGetUeCpInfo : public CMessage
{
private:
   virtual ~CMsgGetUeCpInfo(){};

public:
   CMsgGetUeCpInfo()
   {
      message  = IMC_GET_UECPINFO;
      iDevice = 0;
      lError = -1;
   };

   long     lError;
   int      iDevice;
   long     i32Version;
   CString  strUeRatType;
   CString  strSimType;
   CString  strCpVersion;
   CString  strMsaVersion;
   CString  strBoardVersion;
   CString  strPlatformStream;
   CString  strProtocolStream;
   CString  strMsaStream;
   tm_t     tmSystemTime;
   
};

class CMsgTargetTimeSync : public CMessage
{
private:
   virtual ~CMsgTargetTimeSync(){};

public:
   CMsgTargetTimeSync()
   {
      message = IMC_TARGET_TIME_SYNC;
      ZeroMemory(&tmSystemTime, sizeof(tmSystemTime));
      dwSyncPduTs = 0;
      iDevice = 0;
   }

   int   iDevice;
   tm_t  tmSystemTime;
   DWORD dwSyncPduTs;
};

class CMsgGetVobStreamName : public CMessage
{
private:
   virtual ~CMsgGetVobStreamName(){};

public:
   CMsgGetVobStreamName()
   {
      message = IMC_GET_VOBSTREAMNAME;
      lError = -1;
      iDevice = 0;
   }

   long lError;
   int  iDevice;
   CString strVobStreamName;
};

class CMsgOpenOnlineNewLog : public CMessage
{
public:
   CMsgOpenOnlineNewLog(){
      message = IMC_OPEN_ONLINE_NEWLOG;
   }
   virtual ~CMsgOpenOnlineNewLog(){
   }

   CString strLogFileName;
};

class CMsgLogStringMessage : public CMessage
{
public:
   CMsgLogStringMessage(){
      message = IMC_LOG_STRMSG;
   }
   virtual ~CMsgLogStringMessage()
   {

   }

   int  iDevice;
   CString strMessage;
};

class CMsgGetIsAutoUpdateDB : public CMessage
{
public:
   CMsgGetIsAutoUpdateDB(){
      message = IMC_GET_ISAUTOUPDATEDB;
      lError = -1;
   }
   virtual ~CMsgGetIsAutoUpdateDB()
   {
   }

   bool  bAutoUpdate;
   long  lError;
};

class CMsgLogFileClosed : public CMessage
{
public:
   CMsgLogFileClosed(){
      message = IMC_LOGFILE_CLOSED;
   }
   virtual ~CMsgLogFileClosed()
   {
   }

   CString strLogPathName;

};

class CMsgExportExtractedLog : public CMessage
{
public:
   CMsgExportExtractedLog(){
      message = IMC_EXPORT_EXTRACTEDLOG;
   }
   virtual ~CMsgExportExtractedLog()
   {
   }

   CString strLogPathName;

};

class CMsgGetBinLogsPath : public CMessage
{
public:
   CMsgGetBinLogsPath(){
      message = IMC_GET_BINLOGSPATH;
   }
   virtual ~CMsgGetBinLogsPath()
   {
   }

   CString strBinLogsPath;
};

class CMsgGetActiveView : public CMessage
{
public:
   CMsgGetActiveView(){
      message = IMC_GET_ACTIVEVIEW;
      pView = NULL;
   }

   virtual ~CMsgGetActiveView(){}

   CView* pView;
};

class CMsgOpenEntireFilter : public CMessage
{
public:
	CMsgOpenEntireFilter()
	{
		message = IMC_OPEN_ENTIRE_FILTER;
		iDevice = -1;
	}
	virtual ~CMsgOpenEntireFilter()
	{
	}

	int	iDevice;
};

class CMsgCloseEntireFilter : public CMessage
{
public:
	CMsgCloseEntireFilter()
	{
		message = IMC_CLOSE_ENTIRE_FILTER;
		iDevice = -1;
	}
	virtual ~CMsgCloseEntireFilter()
	{
	}

	int	iDevice;
};

class CMsgSetDiagFilter : public CMessage
{
public:
	CMsgSetDiagFilter(bool bpass, USHORT msgid, int targettype = 0, int Device = -1)
	{
		message = IMC_SET_DIAG_FILTER;
		bPass = bpass;
		MessageId = msgid;
		TargetType = targettype;
		iDevice = Device;
		bUseName = false;
	}
	CMsgSetDiagFilter(bool bpass, const CString & cat1, const CString & cat2, const CString & cat3, int targettype = 0, int Device = -1)
	{
		message = IMC_SET_DIAG_FILTER;
		bPass = bpass;
		strCat1 = cat1;
		strCat2 = cat2;
		strCat3 = cat3;
		TargetType = targettype;
		iDevice = Device;
		bUseName = true;
	}
	virtual ~CMsgSetDiagFilter()
	{
	}

	int			iDevice;
	int			TargetType;/* Comm / App*/
	bool		bUseName;
	USHORT		MessageId;
	CString		strCat1;
	CString		strCat2;
	CString		strCat3;
	bool		bPass;
};

class CMsgSetDspFilter : public CMessage
{
public:
	CMsgSetDspFilter(bool bpass, int type, USHORT opCode, int Device = -1)
	{
		message = IMC_SET_DSP_FILTER;
		bPass = bpass;
		iType = type;
		Opcode = opCode;
		iDevice = Device;
		bUseName = false;
	}
	CMsgSetDspFilter(bool bpass, int type, const CString & name, int Device = -1)
	{
		message = IMC_SET_DSP_FILTER;
		bPass = bpass;
		iType = type;
		strName = name;
		iDevice = Device;
		bUseName = true;
	}
	virtual ~CMsgSetDspFilter()
	{
	}

	int			iDevice;
	bool		bUseName;
	int			iType;
	USHORT		Opcode;
	CString		strName;
	bool		bPass;
};

class CMsgSetGkiFilter : public CMessage
{
public:
	CMsgSetGkiFilter(bool bpass, DWORD SigID, int Device = -1)
	{
		message = IMC_SET_GKI_FILTER;
		bPass = bpass;
		dwSigId = SigID;
		iDevice = Device;
		bUseName = false;
	}
	CMsgSetGkiFilter(bool bpass, const CString & name, int Device = -1)
	{
		message = IMC_SET_GKI_FILTER;
		bPass = bpass;
		strName = name;
		iDevice = Device;
		bUseName = true;
	}
	virtual ~CMsgSetGkiFilter()
	{
	}

	int			iDevice;
	bool		bUseName;
	DWORD		dwSigId;
	CString		strName;
	bool		bPass;
};

class CMsgOpenViewer : public CMessage
{
public:
	CMsgOpenViewer(const CString & name, int nType = 0)
	{
		message = IMC_OPEN_VIEWER;
		strName = name;
		type = nType;
	}
	virtual ~CMsgOpenViewer()
	{
	}

	int		type;
	CString	strName;
};

class CMsgCloseViewer : public CMessage
{
public:
	CMsgCloseViewer(int nType = 0)
	{
		message = IMC_CLOSE_VIEWER;
		type = nType;
	}
	virtual ~CMsgCloseViewer()
	{
	}

	int		type;
};

class CMsgGetLogName : public CMessage
{
public:
	CMsgGetLogName()
	{
		message = IMC_GET_LOG_NAME;
	}
	virtual ~CMsgGetLogName()
	{
	}

	CString strLogName;
};

class CMsgGetLogFullPathName : public CMessage
{
public:
	CMsgGetLogFullPathName()
	{
		message = IMC_GET_LOG_FULLPATH_NAME;
	}
	virtual ~CMsgGetLogFullPathName()
	{
	}

	CString strLogFullPathName;
};


class CMsgEnableLogOperations : public CMessage
{
public:
	CMsgEnableLogOperations() : CMessage(IMC_LOG_OPERATIONS_ENABLE) {}

	virtual ~CMsgEnableLogOperations() {}

	CString strLogFileName;
};


class CMsgGetCurrentLogName : public CMessage
{
public:
	CMsgGetCurrentLogName()
	{
		message = IMC_GET_CURRENT_LOG_NAME;
	}
	
	virtual ~CMsgGetCurrentLogName()
	{
	}
	
	CString strCurrentLogName;
};


class CMsgDisableLogOperations : public CMessage
{
public:
	CMsgDisableLogOperations() : CMessage(IMC_LOG_OPERATIONS_DISABLE) {}

	virtual ~CMsgDisableLogOperations() {}

	CString strLogFileName;
};


class CMsgInformLoggerUpdateDb : public CMessage
{
public:
	CMsgInformLoggerUpdateDb()
	{
		message = IMC_INFORM_LOGGER_UPDATE_DB;
	}

	virtual ~CMsgInformLoggerUpdateDb()
	{
	}
};


class CMsgDeviceStateChanged : public CMessage
{
public:
	CMsgDeviceStateChanged(int device, bool deviceEnabled, CCommSettings* commSettings) : CMessage(IMC_DEVICE_STATE_CHANGED) { this->m_device = device; this->m_deviceEnabled = deviceEnabled; this->m_commSettings = commSettings; }

	virtual ~CMsgDeviceStateChanged() {}

	int m_device;
	bool m_deviceEnabled;
	CCommSettings* m_commSettings;
};


class CMsgDevControl : public CMessage
{
protected:
	virtual ~CMsgDevControl(){};

public:
	CMsgDevControl()
	{ 
		message = IMC_SET_DEVCOMM; 
		bEnable = true;
		iDeviceNum = 0;
	}

	void CloneTo(CMsgDevControl* pMsg) const
	{
		pMsg->iDeviceNum = iDeviceNum;
		pMsg->bEnable = bEnable;
		pMsg->strSendingModule = strSendingModule;
	}
	bool     bEnable;
	int		 iDeviceNum;
	CString  strSendingModule;
};

class CMsgGetLastMessageIndex : public CMessage
{
public:
	CMsgGetLastMessageIndex()
	{
		message = IMC_GET_LAST_MSG_IDX;
		uMessageIndex = (UINT64) -1;
	}

	virtual ~CMsgGetLastMessageIndex()
	{
	}

	UINT64   uMessageIndex;
};

class CMsgMergeBookmarks : public CMessage
{
public:
	CMsgMergeBookmarks()
	{
		message = IMC_MERGE_BOOKMARKS;
		bSuccess = FALSE;
	}

	virtual ~CMsgMergeBookmarks()
	{
	}

	CStringArray strBookmarkSrcPathNames;
	CString strBookmarkDestPathName;
	BOOL bSuccess;
};