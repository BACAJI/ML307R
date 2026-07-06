/*--------------------------------------------------------------------------------------------------------------------

 (C) Copyright 2006,2007 Marvell Semiconductor Israel Ltd. All Rights Reserved  

-------------------------------------------------------------------------------------------------------------------*/



#if !defined(AFX_CXDEVMANAGER_H__3DC59F95_DB71_43CC_B25E_E5DABA16F3D0__INCLUDED_)
#define AFX_CXDEVMANAGER_H__3DC59F95_DB71_43CC_B25E_E5DABA16F3D0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>
#include "XDEVStructures.h"
#include "SingletonDestroyer.h"
#include "XDEVDefinitions.h"
#include "ConfigDevice.h"
#include "DBLayer.h"


#define				TheXDEVManager				CXDEVManager::Instance()

class CDBLayer;
struct sInitialization;
class CDevAndCfgImportExport;

class CATCORE_DLLEXPORT CXDEVManager
{
public:
	static CXDEVManager * Instance();
	void SetWasKilledInInitialization(BOOL bWasKilled);
	void SetDBPath(CString &strDBPath);
	CString FindDirectory();
	static CString GetXDevDBPath();
	void SetIcatExecPath(CString &strIniFilePath);
	BOOL GetConfigurationDeviceGroup(CArray<sConfigDevParams,sConfigDevParams&> &arrConfigDevice, const CString &strConfigName, const CString &strDevGroup, CString &strErrMsg);
	BOOL GetConfigurationDeviceGroup(CArray<CConfigDevice,CConfigDevice&> &arrConfigDevice, const CString &strConfigName, CString &strErrMsg);
	BOOL GetConfigurationDevices(const CString &strConfigName,CStringList &deviceCfgNameList);
	BOOL InitializationInteruptHandler(sInitialization *pInit);
	int FreeViInterface(sInitialization *sInit);
	void InitializeDevices(sInitialization *sInit);
	void TerminateDevices(sInitialization *sInit);
	BOOL ImportDevOrCfg(const CString &strFilePath, CString &strErrMsg = CString(""));
	BOOL ImportDevOrCfgToDB(const CString &strFilePath, const CString &strDBPath, CString &strErrMsg);

	BOOL GetDeviceAttenuation(double &dAttenuation,const CString &strDeviceName, const CString &strPort = _T(""), const CString &strBandOrFreq = _T(""), CString &strErrMsg = CString(_T("")));
	BOOL SetDeviceAttenuation(double dAttenuation,const CString &strDeviceName, const CString &strPort = _T(""), const CString &strBandOrFreq = _T(""), CString &strErrMsg = CString(_T("")));
	BOOL GetAllConfigurations(CStringList &strList);

	BOOL GetConfigurationByGroup(const CString & strGroup ,CStringList & strList);
	BOOL GetGroupOfConfiguration(const CString & strConfig, CString & strGroup);
	BOOL AddConfiguration(const CString & strConfig, const CString & strGroup);
	BOOL GetConfogurationDevices(const CString & strConfig, CArray<sConfigDevParams, sConfigDevParams&> & ConfigDevicesArray);
	BOOL SetConfogurationDevice(const CString & strConfig, sConfigDevParams & configDeviceParams);
	BOOL RemoveConfogurationDevice(const CString & strConfig, const CString & strConfigDevice);

	BOOL GetAllDevices(CStringList & DevicesList);
	BOOL GetDeviceParam(const CString & strDeviceName, tDeviceParam & DeviceParam);
	BOOL GetDeviceParamEx(const CString & strDeviceName, tDeviceParamEx & DeviceParam);
	BOOL SetDevice(const tDeviceParam & DeviceParam);
	BOOL SetDeviceEx(const tDeviceParamEx & DeviceParam);
	BOOL RemoveDevice(const CString & strDeviceName);

	BOOL AddDeviceAttenuation(const CString &strDeviceName, const CString &strPort, const CString &strBandOrFreq, double dAttenuation);
	BOOL RemoveDeviceAttenuation(const CString &strDeviceName, const CString &strPort, const CString &strBandOrFreq);
	BOOL AddDeviceSecAddress(const CString &strDeviceName, int nSecAddress, const CString & strInitMode);
	BOOL RemoveDeviceSecAddress(const CString &strDeviceName, int nSecAddress);
	BOOL SetDeviceSecAddress(const CString &strDeviceName, int nSecAddress, const CString & strInitMode);
	BOOL GetDeviceSecAddress(const CString &strDeviceName, int nSecAddress, CString & strInitMode);

	CSyncObject* GetLockEvent();
	BOOL ImportConfiguration();
	
protected:

	CXDEVManager();
	virtual ~CXDEVManager();
	static CSingletonDestroyer<CXDEVManager> m_Destroyer;
	friend class CSingletonDestroyer<CXDEVManager>;

	static CXDEVManager *m_pThis;
	
	CDBLayer *m_pDbLayer;
	CDevAndCfgImportExport *m_pExportImportManager;

	int m_iDlgMode;
	CString m_strDevName;
	CString m_strConfigName;

	CString	m_strDBPath;

	void Clear();
};

#endif // !defined(AFX_XDEVMANAGER_H__3DC59F95_DB71_43CC_B25E_E5DABA16F3D0__INCLUDED_)



