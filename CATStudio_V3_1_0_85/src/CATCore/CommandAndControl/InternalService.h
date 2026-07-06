#pragma once
#include "MrvlCommon/imc.h"
#include "MrvlCommon/ICATMessageReceiver.h"
#include "MrvlCommon/UEInfo.h"
#include "CATCore/CommandAndControl/CommandChannel.h"


class __declspec(dllexport)  CInternalService 
{
public:
   CInternalService();
   ~CInternalService();


   int          m_iDevice;
   HANDLE       m_hExitThread;
   HANDLE       m_hThread;
   DWORD        m_dwUECPVer;
   DWORD        m_dwUEAPVer;
   CUeCpInfo    m_UeCpInfo;
   bool         m_bUeCpInfoEmpty;
   CCriticalSection m_UeInfoLock;

   
   void         SetDeviceID(int iDevice);
   DWORD        GetUECpVersion();
   DWORD        GetUEApVersion();
   bool         GetUECpInfo(CUeCpInfo& UeCpInfo);
   void         StartGetVersionThread(bool bGetCpVersion, bool bGetApVersion);
   void         StopGetVersionThread(DWORD dwTimeout);

private:
   static UINT  ThreadProc(LPVOID);
   UINT         ThreadFunc(bool bGetCpVer, bool bGetApVer);


public:
   HANDLE GetKillWriteHandle();
   UE_errCode_t SendInternalServiceCommand(BYTE serviceID, eTargetType targetType);
   UE_errCode_t SendInternalServiceCommand(BYTE serviceID, eTargetType targetType, int nTimeout);
   UE_errCode_t WaitForInternalServiceCommand(USHORT serviceID, eTargetType targetType, BYTE *messageBuf, int bufferLen, CICATMessageReceiver* pReceiver, DWORD timeout =2000);
   UE_errCode_t WaitForInternalServiceCommand(USHORT serviceID, BYTE *messageBuf, int bufferLen, CICATMessageReceiver* pReceiver, DWORD timeout =2000);
   UE_errCode_t SendInternalServiceCommandAndWait(BYTE sendServiceID, eTargetType targetType, USHORT waitServiceID, eTargetType replyTargetType, BYTE *messageBuf, int bufferLen, DWORD timeout = 2000);
   UE_errCode_t SendInternalServiceCommandAndWait(BYTE sendServiceID, USHORT waitServiceID, BYTE *messageBuf, int bufferLen, DWORD timeout =2000);

};


class __declspec(dllexport) CInternalServiceManager: public ImcListener
{
public:
   static CInternalServiceManager* Instance();
   static CInternalServiceManager* ms_pInstance;
   static CCriticalSection m_msLock;
   static void DestroyInstance();

   CInternalServiceManager();
   ~CInternalServiceManager();

   inline CInternalService* GetInternalService(int device) { return ( (MAX_DEVICE_NUM > device) ? m_pISObj[device] : NULL ); };

   virtual LRESULT OnMessageReceived(CMessage*);

   void StartListenThread();
   static UINT ListenProc(LPVOID lpVoid);
   UINT ListenFunc();

   CInternalService*  m_pISObj[MAX_DEVICE_NUM];

   CImcReceiver      m_ImcReceiver;
   CEvent            m_ExitEvent;
   HANDLE            m_hListenThread;
};