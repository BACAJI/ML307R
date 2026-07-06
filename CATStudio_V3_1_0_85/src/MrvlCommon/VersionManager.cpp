#include "StdAfx.h"
#include "VersionManager.h"
#include "TaskThread.h"

#ifdef _CATENGINE
#include "CATEngine.h"
#endif

#ifdef _LOGPLAYER
#include "LogFilePlayerDlg.h"
#endif

#ifdef _EXPORTLOG
#include "ExportLogDlg.h"
#endif


CVersionManager::CVersionManager(void)
{
   for(int i=0; i<MAX_DEVICE_NUM; ++i)
   {
      SetDeviceStatus(i, eDISABLED);
      SetProtocolType(i, eDIAGProtocol);
      SetCommType(i, eUSB);
   }
}

CVersionManager::~CVersionManager(void)
{
}

// void CVersionManager::StartGetMdbBaseDirTask()
// {
//    CCheckDbVerTask* pTask = new CCheckDbVerTask(0);
//    pTask->SetDeviceStatus(eDISABLED, eDISCONNECTED);
//    pTask->SetProtocol(eDIAGProtocol);
//    pTask->SetCommType(eUSB);
//    CTaskThreadPool::Instance()->PostTask(NULL, pTask);
//    pTask->Delete();  
// }

void CVersionManager::SetMdbBaseDir( wstring& wsMdbBaseDir )
{
   m_mdbBasedirLock.Lock();
   m_wsMdbBaseDir = wsMdbBaseDir;
   m_mdbBasedirLock.Unlock();
}

void CVersionManager::GetMdbBaseDir( wstring& wsMdbBaseDir )
{
   m_mdbBasedirLock.Lock();
   wsMdbBaseDir = m_wsMdbBaseDir;
   m_mdbBasedirLock.Unlock();
}

std::wstring CVersionManager::GetMdbBaseDir()
{
   return m_wsMdbBaseDir;
}

void CVersionManager::GetPcCpDbVersion( int iDevice, wstring& wsPcCpDbVer )
{
   ASSERT(iDevice>=0 && iDevice<MAX_DEVICE_NUM && _T("Invalid device number") );
   if( iDevice<0 || iDevice>= MAX_DEVICE_NUM )
      return ;

   m_VersionLock.Lock();
   wsPcCpDbVer = m_arPcUeDbVer[iDevice].wsPcCpDbVer;
   m_VersionLock.Unlock();
   return ;
}


void CVersionManager::GetPcApDbVersion( int iDevice, wstring& wsPcApDbVer )
{
   ASSERT(iDevice>=0 && iDevice<MAX_DEVICE_NUM && _T("Invalid device number") );
   if( iDevice<0 || iDevice>= MAX_DEVICE_NUM )
      return ;

   m_VersionLock.Lock();
   wsPcApDbVer = m_arPcUeDbVer[iDevice].wsPcApDbVer;
   m_VersionLock.Unlock();
   return ;
}

void CVersionManager::SetPcCpDbVersion( int iDevice, wstring& wsPcCpDbVer )
{
   ASSERT(iDevice>=0 && iDevice<MAX_DEVICE_NUM && _T("Invalid device number") );
   if( iDevice<0 || iDevice>= MAX_DEVICE_NUM )
      return;

   m_VersionLock.Lock();
   m_arPcUeDbVer[iDevice].wsPcCpDbVer = wsPcCpDbVer;
   m_VersionLock.Unlock();
}

void CVersionManager::SetPcApDbVersion( int iDevice, wstring& wsPcApDbVer )
{
   ASSERT(iDevice>=0 && iDevice<MAX_DEVICE_NUM && _T("Invalid device number") );
   if( iDevice<0 || iDevice>= MAX_DEVICE_NUM )
      return;

   m_VersionLock.Lock();
   m_arPcUeDbVer[iDevice].wsPcApDbVer = wsPcApDbVer;
   m_VersionLock.Unlock();
}

void CVersionManager::SetUeCpDbVersion( int iDevice, wstring& wsUeCpDbVer )
{
   ASSERT(iDevice>=0 && iDevice<MAX_DEVICE_NUM && _T("Invalid device number") );
   if( iDevice<0 || iDevice>= MAX_DEVICE_NUM )
      return;

   m_VersionLock.Lock();
   m_arPcUeDbVer[iDevice].wsUeCpDbVer = wsUeCpDbVer;
   m_VersionLock.Unlock();
}

void CVersionManager::SetUeApDbVersion( int iDevice, wstring& wsUeApDbVer )
{
   ASSERT(iDevice>=0 && iDevice<MAX_DEVICE_NUM && _T("Invalid device number") );
   if( iDevice<0 || iDevice>= MAX_DEVICE_NUM )
      return;

   m_VersionLock.Lock();
   m_arPcUeDbVer[iDevice].wsUeApDbVer = wsUeApDbVer;
   m_VersionLock.Unlock();
}

std::wstring CVersionManager::GetUeCpDbVersion( int iDevice )
{
   ASSERT(iDevice>=0 && iDevice<MAX_DEVICE_NUM && _T("Invalid device number") );
   if( iDevice<0 || iDevice>= MAX_DEVICE_NUM )
      return L"";

   m_VersionLock.Lock();
   std::wstring wsUeCpDbVer = m_arPcUeDbVer[iDevice].wsUeCpDbVer;
   m_VersionLock.Unlock();
   return wsUeCpDbVer;
}

void CVersionManager::GetUeCpDbVersion( int iDevice, wstring& wsUeCpDbVer )
{
   ASSERT(iDevice>=0 && iDevice<MAX_DEVICE_NUM && _T("Invalid device number") );
   if( iDevice<0 || iDevice>= MAX_DEVICE_NUM )
      return;

   m_VersionLock.Lock();
   wsUeCpDbVer = m_arPcUeDbVer[iDevice].wsUeCpDbVer;
   m_VersionLock.Unlock();
}

std::wstring CVersionManager::GetUeApDbVersion( int iDevice )
{
   ASSERT(iDevice>=0 && iDevice<MAX_DEVICE_NUM && _T("Invalid device number") );
   if( iDevice<0 || iDevice>= MAX_DEVICE_NUM )
      return L"";

   m_VersionLock.Lock();
   std::wstring wsUeApDbVer = m_arPcUeDbVer[iDevice].wsUeApDbVer;
   m_VersionLock.Unlock();
   return wsUeApDbVer;
}

void CVersionManager::GetUeApDbVersion( int iDevice, wstring& wsUeApDbVer )
{
   ASSERT(iDevice>=0 && iDevice<MAX_DEVICE_NUM && _T("Invalid device number") );
   if( iDevice<0 || iDevice>= MAX_DEVICE_NUM )
      return;

   m_VersionLock.Lock();
   wsUeApDbVer = m_arPcUeDbVer[iDevice].wsUeApDbVer;
   m_VersionLock.Unlock();
}

void CVersionManager::SetProtocolType( int iDevice, EProtocolType protoType )
{
   ASSERT(iDevice>=0 && iDevice<MAX_DEVICE_NUM && _T("Invalid device number") );
   if( iDevice<0 || iDevice>= MAX_DEVICE_NUM )
      return;
   m_protocolType[iDevice] = protoType;
}

void CVersionManager::SetCommType( int iDevice, ECommType commType )
{
   ASSERT(iDevice>=0 && iDevice<MAX_DEVICE_NUM && _T("Invalid device number") );
   if( iDevice<0 || iDevice>= MAX_DEVICE_NUM )
      return;

   m_commType[iDevice] = commType;
}

void CVersionManager::SetDeviceStatus( int iDevice, DeviceStatus deviceStatus )
{
   ASSERT(iDevice>=0 && iDevice<MAX_DEVICE_NUM && _T("Invalid device number") );
   if( iDevice<0 || iDevice>= MAX_DEVICE_NUM )
      return;
   m_deviceStatus[iDevice] = deviceStatus;
}

EProtocolType CVersionManager::GetProtocolType( int iDevice )
{
   ASSERT(iDevice>=0 && iDevice<MAX_DEVICE_NUM && _T("Invalid device number") );
   if( iDevice<0 || iDevice>= MAX_DEVICE_NUM )
      return eDIAGProtocol;

   return m_protocolType[iDevice];
}

ECommType CVersionManager::GetCommType( int iDevice )
{
   ASSERT(iDevice>=0 && iDevice<MAX_DEVICE_NUM && _T("Invalid device number") );
   if( iDevice<0 || iDevice>= MAX_DEVICE_NUM )
      return eUSB;

   return m_commType[iDevice];
}

DeviceStatus CVersionManager::GetDeviceStatus( int iDevice )
{
   ASSERT(iDevice>=0 && iDevice<MAX_DEVICE_NUM && _T("Invalid device number") );
   if( iDevice<0 || iDevice>= MAX_DEVICE_NUM )
      return eDISABLED;

   return m_deviceStatus[iDevice];
}

void CVersionManager::Clear()
{
   for(int i=0; i<MAX_DEVICE_NUM; ++i)
   {
      m_commType[i] = eUSB;
      m_deviceStatus[i] = eDISABLED;
      m_protocolType[i] = eDIAGProtocol;
      m_arPcUeDbVer[i].wsPcApDbVer = _T("");
      m_arPcUeDbVer[i].wsPcCpDbVer = _T("");
      m_arPcUeDbVer[i].wsUeApDbVer = _T("");
      m_arPcUeDbVer[i].wsUeCpDbVer = _T("");
   }
}



CVersionManager* GetVersionManager()
{

#ifdef _CATENGINE
      return CCATEngine::Instance()->GetVersionManager();
#endif


#ifdef _LOGPLAYER
      CLogFilePlayerDlg* pMainWnd = dynamic_cast<CLogFilePlayerDlg*>(AfxGetApp()->GetMainWnd());
      ASSERT(pMainWnd);
      return pMainWnd->GetVersionManager();
#endif

#ifdef _EXPORTLOG
	  CExportLogDlg* pMainWnd = dynamic_cast<CExportLogDlg*>(AfxGetApp()->GetMainWnd());
	  ASSERT(pMainWnd);
	  return pMainWnd->GetVersionManager();
#endif
	return NULL;
}
