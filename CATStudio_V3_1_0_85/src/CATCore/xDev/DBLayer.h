/*--------------------------------------------------------------------------------------------------------------------

 (C) Copyright 2006,2007 Marvell Semiconductor Israel Ltd. All Rights Reserved  

-------------------------------------------------------------------------------------------------------------------*/




#if !defined(AFX_DBLAYER_H__3A26F0C8_39A2_4437_A1C5_38BB6B043307__INCLUDED_)
#define AFX_DBLAYER_H__3A26F0C8_39A2_4437_A1C5_38BB6B043307__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <afxtempl.h>
#include "XDEVStructures.h"
#include "ConfigDevice.h"
#include "..\BasicComponents\EventForMultiLock.h"

class CAdoDbConnector;
class CDevParams;
class CConfigParams;


class CATCORE_DLLEXPORT CDBLayer  
{
public:
	CDBLayer();
	virtual ~CDBLayer();

	static CSyncObject* GetLockEvent() { return &m_cLockEvent;}
	//loading functions:
	BOOL DbToDevTree(CTreeCtrl &devTree, CString &strErrMsg);
	BOOL DbToConfigTree(CTreeCtrl &configTree, CString &strErrMsg);
	BOOL GetAllConfigurations(CStringList &strList);
	BOOL DbToConfigDevicesList(const CString &strConfigToLoad, CStringList &deviceCfgNameList, CString &strErrMsg);
	BOOL DbToDevGuiParams(const CString &strDevToLoad,CDevParams *m_pDevParams,CString &strErrMsg);
	BOOL DbToConfigGuiParams(const CString &strConfigToLoad,CConfigParams *m_pConfigParams,CString &strErrMsg);
	BOOL DbToConfigDevParams(const CString &strDevToLoad,sConfigDevParams &sConfigDev,CString &strErrMsg);
	BOOL DbToDevSecAddressSetting(const CString &strDevToLoad,CDevParams *m_pDevParams,CString &strErrMsg);
	BOOL DbToDevAttenuationSetting(const CString &strDevToLoad,CDevParams *m_pDevParams,CString &strErrMsg);
	BOOL DbToConfigDevicesParams(const CString &strConfigToLoad,CConfigParams *m_pConfigParams,CString &strErrMsg);
	BOOL LoadDeviceGroups(CMapStringToString &MapDevToTevGroup,CString &strErrMsg);
	BOOL LoadAllDevGroups(CStringList &strlistDevGroup,CString &strErrMsg);
	BOOL LoadAllConfigGroups(CStringList &strlistConfigGroup,CString &strErrMsg);
	BOOL LoadAllProtocols(CStringList &strlistProtocol,CString &strErrMsg);
	BOOL LoadAllIDNStrings(CStringList &strlistIDNString,CString &strErrMsg);
	BOOL DbToXDEVSessionArray(sInitialization *initStruct, BOOL &ConfigExistandHasDev, CString &strErrMsg);
	BOOL SecAddressToXDEVSessionArray(sInitialization *initStruct, CString &strErrMsg);
	BOOL GetDeviceAttenuation(double & dAttenuation,const CString &strDeviceName, const CString &strPort = _T(""), const CString &strBandOrFreq = _T(""), CString &strErrMsg = CString(_T("")));
	BOOL SetDeviceAttenuation(double dAttenuation,const CString &strDeviceName, const CString &strPort, const CString &strBandOrFreq = _T(""), CString &strErrMsg = CString(_T("")));
	BOOL DbToConfigDeviceGroupArray(CArray<sConfigDevParams,sConfigDevParams&> &arrConfigDevice, const CString &strConfigName, const CString &strDevGroup, CString &strErrMsg = CString(_T("")));
	BOOL DbToConfigDeviceGroupArray(CArray<CConfigDevice,CConfigDevice&> &arrConfigDevice, const CString &strConfigName, CString &strErrMsg);

	//saving/changing functions:
	BOOL DeleteDevicesFromDB(const CStringList &strlistItemsToDelete,CString &strErrMsg);
	BOOL DeleteConfigurationsFromDB(const CStringList &strlistItemsToDelete,CString &strErrMsg);
	BOOL DevGuiParamsToDb(const CDevParams *m_pDevParams,CString &strErrMsg);
	BOOL DevSecAddressToDb(const CDevParams *m_pDevParams,CString &strErrMsg);
	BOOL DevAttenuationSettingToDb(const CDevParams *m_pDevParams,CString &strErrMsg);
	BOOL ConfigGuiParamsToDb(const CConfigParams *m_pConfigParams,CString &strErrMsg);
	BOOL ConfigDevicesToDb(const CConfigParams *m_pConfigParams,CString &strErrMsg);
	BOOL ChangeDevName(const CString &strOriginalDevName, const CString &strNewDevName, CString &strErrMsg);
	BOOL ChangeConfigName(const CString &strOriginalConfigName, const CString &strNewConfigName, CString &strErrMsg);
	
	//other:
	BOOL DoesDevExist(const CString &strDevToCheck, CString &strErrMsg);
	BOOL DoesConfigExist(const CString &strConfigToCheck, CString &strErrMsg);
	BOOL DoseConfigDevicesExist(CConfigParams *pConfigParams,CString &strDevices);
	
	//External configuration
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

protected:
	
	BOOL m_bIsDbInUse;
	CAdoDbConnector *m_pDbConnector;
	CDevParams *m_pDevParams;
	CConfigParams *m_pConfigParams;
	BOOL OpenDb(CString &strErrMsg = CString(""));
	void CloseDb();

	CString		m_strLastError;

	BOOL _GetSecAddresses(const CString &strDevToLoad, CArray<sSecAddressParams, sSecAddressParams&> & arrSecAddress);
	BOOL _GetAttenuations(const CString &strDevToLoad, CArray<sAttenuationParams, sAttenuationParams&> & arrAttenuation);
	BOOL _SetDeviceSecAddress(const CString &strDeviceName, int nSecAddress, const CString & strInitMode);
	BOOL _SetDeviceAttenuation(double dAttenuation,const CString &strDeviceName, const CString &strPort, const CString &strBandOrFreq,CString &strErrMsg);

	static CEventForMultiLock m_cLockEvent;	

};

#endif // !defined(AFX_DBLAYER_H__3A26F0C8_39A2_4437_A1C5_38BB6B043307__INCLUDED_)
