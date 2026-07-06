#pragma once
#include <string>
#include "ipc/IPPCDefs.h"
#include "MrvlCommon/CommonDefs.h"
#include "MrvlCommon/DeviceStatus.h"
#include "MrvlCommon/ICATMessage.h"
using namespace std;

struct CPcUeDbVersion
{
   wstring wsPcCpDbVer;
   wstring wsPcApDbVer;
   wstring wsUeCpDbVer;
   wstring wsUeApDbVer;
   bool IsCpVerEqual(){ return wsPcCpDbVer.compare(wsUeCpDbVer)==0 ;};
   bool IsApVerEqual(){ return wsPcApDbVer.compare(wsUeApDbVer)==0 ;};
};


class CVersionManager
{
public:
   CVersionManager(void);
   virtual ~CVersionManager(void);

   void      SetMdbBaseDir(wstring& wsMdbBaseDir);
   void      GetMdbBaseDir(wstring& wsMdbBaseDir);
   wstring   GetMdbBaseDir();
   void      GetPcCpDbVersion(int iDevice, wstring& wsOldPcCpDbVer);
   void      GetPcApDbVersion(int iDevice, wstring& wsOldPcApDbVer);
   wstring   GetUeCpDbVersion(int iDevice);
   wstring   GetUeApDbVersion(int iDevice);
   void      GetUeCpDbVersion(int iDevice, wstring& wsUeCpDbVer);
   void      GetUeApDbVersion(int iDevice, wstring& wsUeApDbVer);
   void      SetPcCpDbVersion(int iDevice, wstring& wsOldPcCpDbVer);
   void      SetPcApDbVersion(int iDevice, wstring& wsOldPcApDbVer);  
   void      SetUeCpDbVersion(int iDevice, wstring& wsUeCpDbVer);
   void      SetUeApDbVersion(int iDevice, wstring& wsUeApDbVer);

   void  SetProtocolType(int iDevice, EProtocolType protoType);
   void  SetCommType( int iDevice, ECommType commType );
   void  SetDeviceStatus(int iDevice, DeviceStatus protoType);

   EProtocolType  GetProtocolType(int iDevice);
   ECommType      GetCommType( int iDevice);
   DeviceStatus   GetDeviceStatus(int iDevice);

   void     Clear();

protected:


private:
   CCriticalSection  m_mdbBasedirLock;
   CCriticalSection  m_VersionLock;
   wstring           m_wsMdbBaseDir;
   CPcUeDbVersion    m_arPcUeDbVer[MAX_DEVICE_NUM];
   DeviceStatus      m_deviceStatus[MAX_DEVICE_NUM];
   EProtocolType     m_protocolType[MAX_DEVICE_NUM];
   ECommType         m_commType[MAX_DEVICE_NUM];
};

CVersionManager* GetVersionManager();

#define theVersionManager GetVersionManager()