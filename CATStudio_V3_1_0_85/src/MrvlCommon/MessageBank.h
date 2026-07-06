#pragma once
#include <list>

#include "MrvlCommon/CommonDefs.h"
#include "ipc/IPPCDefs.h"
#include "ipc/ipc_syncblock_server.h"
#include "MrvlCommon/Dispatcher.h"
#include "MrvlCommon/DeviceFilter.h"
#include "ipc/ipc_listener.h"
#include "SFilter.h"

using namespace std;



class SyncBlockServer;
class CMessageBank : public IpcListener
{
public:
enum EMSGBankErr
{
    eNoErr=0,
    eShmCreationFailed=1,
    eShmAlreadyExists=2
};
  
public:
   static CMessageBank*    CreateInstance(int nTcpPort);
   static CMessageBank*    Instance();
   static void             Destroy();
   CMessageBank(int nTcpPort);
   ~CMessageBank();
   static CMessageBank*    m_pInstance;
   static CCriticalSection m_Lock;

public:
   static void HandleICATMessage(LPVOID lpVoid, CICATMessage* pMessage);
   BOOL  HandleMessage(CICATMessage* pMessage);
   void  CreateReceiver();
   void  DeleteReceiver();
   void  StartReceiver();
   void  StopReceiver();
   BOOL  IsOpen(){return m_bBankOK;};
   BOOL  IsAlreadyExist(){ return (BOOL)(m_BankErr==eShmAlreadyExists);};
   wstring AcsrLogin(uint32 processId, uint32 accessorId);
   void    AcsrLogout(uint32 processId, uint32 accessorId);
   virtual BOOL OnMessageReceived(const Message& kMessage);
   void  PlayEnded();
   
private:
   BOOL       BankMessage(const CICATMessage* pMessage);
   void       UnMapMem();
   CString    m_sShmemName;
   HANDLE     m_hFileMap;
   HANDLE     m_pFileView;
   SHMINFO*   m_pSmInfo;   
   CxMessage* m_Que;
   LPBYTE     m_pBuf;
   int        m_QueSize;
   int        m_iQueNextWritePos;
   int        m_BufLen;
   int        m_iBufNextPos;
   INT64      m_iNextIndex;
   BOOL       m_bBankOK;
   EMSGBankErr m_BankErr;
   BOOL       m_bFilterEnabled;
   UINT64     m_PassedMessageMaxIndex;

   map<uint64, HANDLE> m_mapEvent;
   CCriticalSection m_mapEventLock;

   SyncBlockServer* m_pSyncBlock;
   SHM        m_shm;

   CICATMessageReceiver* m_pMessageReceiver;

   CSFilter*      m_FilterBank[MAX_DEVICE_NUM];
   CDeviceFilter* m_DeviceFilter[MAX_DEVICE_NUM];

public:  
   BOOL        MapMem();
   CSFilter*    GetAndLockFilter(int iDevice);
   void        UnlockFilter(int iDevice);
   CCriticalSection m_FilterLock;


};

#define theBank CMessageBank::Instance()


