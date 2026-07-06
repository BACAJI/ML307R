/*------------------------------------------------------------------------------------------*
 |(C) Copyright 2006,2007 Marvell Semiconductor Israel Ltd. All Rights Reserved				|
 *------------------------------------------------------------------------------------------*/

/******************************************************
*                         ConfigurationData.h
*
* Project : APTController                 Ver : 1.0
* Programmer : Maya Shtern        Date : 03/05/2003
* Language : VC 6.0                Target : Win32
* Purpose :
*****************************************************/

#if !defined(AFX_CONFIGURATIONDATA_H__22E29E15_EB8E_4AE8_96F9_624863D60E0F__INCLUDED_)
#define AFX_CONFIGURATIONDATA_H__22E29E15_EB8E_4AE8_96F9_624863D60E0F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ErrorCodes.h"

// APT-Controller Devices
//#define	SYSTEM_SIMULATOR	1
#define	SYSTEM_SIMULATOR_1	1
#define	AT_COMMANDS			2
#define	DIAG				3
#define	SIM_SIMULATOR		4
#define	SYSTEM_SIMULATOR_2	5
#define AWS_CLIENT			6


// Test Engine Modes
#define SEQUENTIAL_MODE		0
#define PARALLEL_MODE		1

class CControllerConfigurationDlg;
class CDevicesConfigurationDlg;

/********************************************************************************
*																				*
*	class CConfigurationData													*
*	------------------------													*
*	This class handles all the data concerning the APT-Controller configuration	*
*																				*
********************************************************************************/
class CConfigurationData  
{
public:
	CConfigurationData();
	virtual ~CConfigurationData();

	bool m_bRunningFromScript;

	// configuration data information
	// ------------------------------
	// Protocol
	int		m_nModuleType;
	CString	m_sModuleType;
	CString	m_sDefaultResponse;
	CString	m_sNewTestCaseInd;
	CString m_sResetScript;
	CString m_sTestPassInd;
	CString m_sTestFailInd;
	CString m_sTestInconInd;
	CString	m_sStartCampaignInd;
	CString	m_sEndCampaignInd;
	// Database
	CString	m_sDBPath;
	// Timer
	BOOL	m_bTimerActivated;
	UINT	m_nTimeoutDuration;
	int		m_nTimerAppType;
	CString	m_sTimerAppPath;
	CString	m_sTimerExportedFunc;
	//Identical Messages Timing
	BOOL	m_bIgnoreIdenticalMsg;
	UINT	m_nIgnoreMsgTimer;
	// Actions (pre & post DLLs)
	BOOL	m_bRunDllAfterSession;
	BOOL	m_bRunDllBeforeSession;
	CString	m_sAfterFuncName;
	CString	m_sBeforeFuncName;
	CString	m_sAfterDllPath;
	CString	m_sBeforeDllPath;
	// XDEV Configuration
	CString	m_sXDEVConfigurationSequential;
	CString	m_sXDEVConfigurationParallel;
	// Campaign Settings
	int		m_nRunCampaign;
	int		m_nRunParamsSets;
	// Devices
	int		m_nSystemSimulatorDevice1;
	int		m_nSystemSimulatorDevice2;
	int		m_nATCommandsDevice;
	int		m_nDIAGDevice;
	int		m_nSIMSimulatorDevice;
	int		m_nAWSClientDevice;
	// DIAG Messages
	BOOL	m_bProcessDIAGMsg;
	// AWS Client
	BOOL	m_bActiveAWSClient;
	BOOL	m_bPCMonitoring;
	BOOL	m_bPTSMonitoring;
	BOOL	m_bTCMonitoring;
	int		m_nTCMonitoringMethod;
	UINT	m_nTCPercentageLimit;
	UINT	m_nTCSequentialLimit;
	UINT	m_nTCCalcStartNumber;
	int		m_nMonitoringStartPoint;
	// TestQuest Configuration
	BOOL	m_bUseTQ;
	CString	m_sTQProject;
	CString m_sTQInstallPath;
	
	// data configuration functions
	void		OpenConfigurationDlg();
	BOOL		IsFirstTimeConfiguration();
	BOOL		SetControllerConfiguration();
	void		GetDataFromDialogs();
	ERROR_CODE	IsDatabaseValid(const CString& sDBPath);
	BOOL		ValidateConfiguration();
	BOOL		IsConfigurationExist(const CString& sXDEVConfiguration);
	// devices configuration functions
	void	RunDevicesConfiguration();
	int		GetDevice(int nDeviceName);
	ERROR_CODE	SetDevice(int nDeviceName, UINT nDeviceValue);
	ERROR_CODE	SetModuleType(const CString& sModuleType);
	ERROR_CODE	SetDatabasePath(const CString& sDBPath);
	ERROR_CODE  SetTimer(int nTimeoutDuration, int nAppType, const CString& sAppPath, const CString& sDllExportedFunc =_T(""));
	ERROR_CODE	SetXDEVConfiguration(const CString& sXDEVConfiguration, int nTestEngineMode);

private:
	CControllerConfigurationDlg	*m_pControllerConfigurationDlg;	//a dialog object for the APTC configuration dialog
	CDevicesConfigurationDlg	*m_pDevicesConfigurationDlg;	//a dialog object for the devices configuration dialog

	void ConvertModuleTypeToInt(int& nModuleType, const CString& strModule);

};

#endif // !defined(AFX_CONFIGURATIONDATA_H__22E29E15_EB8E_4AE8_96F9_624863D60E0F__INCLUDED_)
