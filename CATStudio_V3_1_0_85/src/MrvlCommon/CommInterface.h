#pragma once
#include "CommonDefs.h"
#include "imc/MessageReceiver.h"
#include "imc/ImcListener.h"
#include "MrvlCommon/tm_t.h"

typedef UE_errCode_t (*PFN_COMMANDFUNC)(int,int,BYTE*,int);
typedef UE_errCode_t (*PFN_COMMANDFUNCWITHTIMEOUT)(int,int,BYTE*,int, int);
typedef HANDLE		(*PFN_GETKILLWRITEHANDLEFUNC)(int);
typedef PFN_GETKILLWRITEHANDLEFUNC LPFN_GETKILLWRITEHANLEDFUNC;
typedef PFN_COMMANDFUNC LPFN_COMMANDFUNC;
typedef PFN_COMMANDFUNCWITHTIMEOUT LPFN_COMMANDFUNCWITHTIMEOUT;
typedef PFN_MESSAGE_FUNC LPFN_MESSAGE_FUNC;
typedef PFN_DEVICESTATUS_FUNC LPFN_DEVICESTATUS_FUNC;
// DeviceStatusFunc
typedef int (*PFN_REGSTATUS_FUNC)(LPVOID, LPFN_DEVICESTATUS_FUNC);
typedef PFN_REGSTATUS_FUNC LPFN_REGSTATUS_FUNC;

// GetConnectionStatus
typedef int (*PFN_GET_CONNECTIONSTATUS)(int);
typedef PFN_GET_CONNECTIONSTATUS LPFN_GET_CONNECTIONSTATUS;

// EnableDev
typedef PFN_ENABLEDEV LPFN_ENABLEDEV;
// DisableDev
typedef PFN_DISABLEDEV LPFN_DISABLEDEV;

//UpdataCommSettings

typedef PFN_UPDATACOMMSETTINGS LPFN_UPDATACOMMSETTINGS;
// SetCommSettings
typedef PFN_SETCOMMSETTINGS LPFN_SETCOMMSETTINGS;

// GeteCommSettings
typedef PFN_GETCOMMSETTINGS LPFN_GETCOMMSETTINGS;

// UnregMessageFunc
typedef int (*PFN_UNREG_MESSAGEFUNC)();
typedef PFN_UNREG_MESSAGEFUNC LPFN_UNREG_MESSAGEFUNC;

// RegMessageFunc
typedef int (*PFN_REG_MESSAGEFUNC)(LPVOID, LPFN_MESSAGE_FUNC);
typedef PFN_REG_MESSAGEFUNC LPFN_REG_MESSAGEFUNC;

//SendADBCommand
typedef UE_errCode_t (*PFN_ADBCOMMANDFUNC)(int,int,CString);
typedef PFN_ADBCOMMANDFUNC LPFN_ADBCOMMANDFUNC;

//ReadData
typedef BOOL (*PFN_READDATA)(int, BYTE*, DWORD, LPDWORD);
typedef PFN_READDATA LPFN_READDATA;

//SendData

typedef UE_errCode_t (*PFN_SENDDATA)(int , int , BYTE* , int );
typedef PFN_SENDDATA LPFN_SENDDATA;

//IsAlive
typedef BOOL (*PFN_ISALIVE)(int);
typedef PFN_ISALIVE LPFN_ISALIVE;

//StopADBCommand
typedef UE_errCode_t (*PFN_STOPADBFUNC)(int,int);
typedef PFN_STOPADBFUNC LPFN_STOPADBFUNC;


#ifdef _CATCORE_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

class CMessage;
class CDispatcher;
class DLL_EXPORT CCommInterface : public ImcListener
{
public:
   static CCommInterface* Instance();
   static void DestroyInstance();
   static CCommInterface* ms_pInstance;
   static CCriticalSection ms_Lock;
   
   CCommInterface(void);
   ~CCommInterface(void);

   

   int   GetAliveDiagDeviceID();
   int   GetCommProtocol(int iDevice);
   int   GetConnectionStatus(int iDevice);
   BOOL  EnableDev( int iDevice );
   BOOL  DisableDev( int iDevice );
   BOOL  SetCommSettings( CCommSettings CommSettings );
   BOOL  GetCommSettings(int iDevice, CCommSettings& pCommSettings);
   BOOL  RegStatusFunc(LPVOID lpObj, LPFN_DEVICESTATUS_FUNC pFunc);
   BOOL  UnregStatusFunc(LPVOID lpObj, LPFN_DEVICESTATUS_FUNC pFunc);
   HANDLE GetKillWriteHandle(int iDevice);
   UE_errCode_t SendCommand(int iDevice, int iProtocol, BYTE *data, int length);
   UE_errCode_t SendCommandWithTimeout(int iDevice, int iProtocol, BYTE *data, int length, int nTimeout);
   UE_errCode_t SendADBCommand( int iDevice, int protocol, CString command );
   UE_errCode_t StopADBCommand( int iDevice, int protocol );

   static void MessageFunc(LPVOID lpObj, int iDevice, int protocol, BYTE* data, int length);
   LRESULT OnMessageReceived(CMessage* pMessage);
private:
   HMODULE  m_hDevComm;
   LPFN_GETKILLWRITEHANLEDFUNC m_pKillWriteHandle;
   LPFN_COMMANDFUNC m_pCommandFunc;
   LPFN_COMMANDFUNCWITHTIMEOUT m_pCommandTimeoutFunc;
   CMessageReceiver m_ImcReceiver;
   LPFN_ADBCOMMANDFUNC m_pADBCommandFunc;
   LPFN_STOPADBFUNC m_pStopADBFunc;
   tm_t m_tmSystemTime[MAX_DEVICE_NUM]; //Copied from system time of UECPINFO PDU
   WORD m_wSystemTimeMilli[MAX_DEVICE_NUM];//Milliseconds part of the system time of UECPINFO, since time_t unit is second
   time_t m_timetSyncTime[MAX_DEVICE_NUM];//System time of UECPINFO PDU, converted to time_t
   DWORD  m_dwSyncPduTs[MAX_DEVICE_NUM]; //Time stamp filed of UECPINFO PDU
   bool   m_bUseSyncTime[MAX_DEVICE_NUM];//Device connected and UECPINFO PDU received

   
};
