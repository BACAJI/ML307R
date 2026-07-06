/*------------------------------------------------------------------------------------------*
 |(C) Copyright 2006,2007 Marvell Semiconductor Israel Ltd. All Rights Reserved				|
 *------------------------------------------------------------------------------------------*/

/******************************************************
 *                         Manager.h
 *
 * Project : SimulationStationListener     Ver : 1.0
 * Programmer : Maya Shtern        Date : 03/05/2003
 * Language : VC 6.0                Target : Win32
 * Purpose :
*****************************************************/

#if !defined(AFX_MANAGER_H__67545F8D_D285_493A_8408_9940EF3917EA__INCLUDED_)
#define AFX_MANAGER_H__67545F8D_D285_493A_8408_9940EF3917EA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define NULL_STRING _T("")

#include "SingletonDestroyer.h"
#include "ConfigurationData.h"
#include "ICATMessage.h"
#include "../CATCore/BasicComponents/LogListCtrl.h"
#include "../CATCore/Converter/CommandAndMessageStructures.h"

#ifdef _APT_CONTROLLER_DLL
#define AptControllerManager_Export __declspec(dllexport)
#else					
#define AptControllerManager_Export
#endif


class CListener;
class CControllerNotificationDlg;
class CAPTC_ModuleDlg;
class CViewer;
struct ListenerSetupData;
struct SAWSClientSetupData;

/************************************************************************
*	Class CAPTControllerManager														*
*	--------------														*
*	This class interfaces the module into the ICAT the class			*
*	commites to tree API functions that the ICAT demand from any		*
*	user customized module (Terminate() , Instance() , InitMenu())		*
*																		*
************************************************************************/

class CModuleManager;
class AptControllerManager_Export CAPTControllerManager : public CCmdTarget
{
	DECLARE_DYNCREATE(CAPTControllerManager)

protected:
	CAPTControllerManager();           // protected constructor used by dynamic creation

private:
	UINT m_nInstanceID;
	CMFCToolBar*    m_pToolbar;
	CLogListCtrl*  m_pLogListCtrl;
	CList<CFrameWnd*, CFrameWnd*> m_InstanceList;
	CMap<UINT,UINT,CMDIChildWndEx*,CMDIChildWndEx*> m_mapInstanceIdFrame;
	CModuleManager* m_pModuleManager;
	static CAPTControllerManager		*m_pThis;
	static CSingletonDestroyer<CAPTControllerManager> m_Destroyer;
	friend class CSingletonDestroyer<CAPTControllerManager>;
	CControllerNotificationDlg* m_NotificationDlg;	// notification dialog for Controller messages
	CConfigurationData			m_ConfigurationData;	// handles all the APT-Controller configuration
	bool	m_RunningFromScript;
	int		m_bSaveScriptResultsToDB;

	CAPTC_ModuleDlg	*m_pModuleDlg;
	friend class CAPTC_ModuleDlg;
	friend class CListener;

	CViewer*	m_pViewer;

	void ConfigureDevices();
	void ConfigureSpecificDevice(int &device);	// match the APT-Controller devices to the ICAT
	BOOL ConfigureController();
	void GetListenerSetupData(ListenerSetupData& setupData);
	void ActivateViewer();		// activate the APT-Controller specific viewer
	void ConfigureTestEngine();
	void RestoreTestEngine();
	
	const CString& GetModuleType ();	// getting the APT-Controller's module type
	const CString& GetDefaultResponse();	// getting the APT-Controller's default response
	const CString& GetNewTestCaseInd();		// getting the APT-Controller's new test case indication
	const CString& GetResetScript();		// getting the APT-Controller's reset script name
	const CString& GetTestPassInd();		// getting the APT-Controller's test pass indication
	const CString& GetTestFailInd();		// getting the APT-Controller's test fail indication
	const CString& GetTestInconInd();		// getting the APT-Controller's test inconclusive indication
	const CString& GetDatabasePath();	// getting the database for test mode
	const CString& GetXDEVConfigurationSequential();	// geting the XDEV configuration for sequential scripts
	const CString& GetXDEVConfigurationParallel();	// geting the XDEV configuration for parallel scripts
	int			   GetCampaignType();		// getting the campaign running mode (single/multiple)	
	const CString& GetStartCampaignCommand();	// getting the indication for start of campaign
	const CString& GetEndCampaignCommand();	// getting the indication for end of campaign
	int			   GetParamsSetsSelsction();	// getting the parameters sets selection (all/selected only)
	BOOL		   GetIncomingDiagMsgProcess();
	BOOL		   GetIdenticalMsgStatus();
	UINT		   GetIdenticalMsgTimer();

	BOOL IsTimerActive();
	UINT GetTimeoutDuration();
 	int	GetTimerApplicationType();
	const CString& GetTimerApplicationPath();
	const CString& GetDllExportedFun();

	BOOL CheckLogFileSize();
	bool m_IsFirstTimeOpenLogFile;

	BOOL IsRunDllBeforeStartController();
	BOOL IsRunDllAfterStopController();
	const CString& GetBeforeDllPath();
	const CString& GetAfterDllPath();
	const CString& GetBeforeFunctionName();
	const CString& GetAfterFunctionName();
	BOOL RunDllFunction (const CString& sDllPath, const CString& sFunc);

	void SendUserNotification(const CString& sMessage, UINT nTimeout = 10000);
 // Attributes
public:
	static CAPTControllerManager * Instance();
	BOOL RegisterDocTemplate();
	BOOL RegisterToolBar();
	BOOL RegisterModulePane();
	void RemoveToolBar();
	CMFCToolBar* GetToolBar();
	void ShowToolBar(BOOL bShow=TRUE);
	void AddFrameWnd(CFrameWnd* pFrmaeWnd);
	void RemoveFrameWnd(CFrameWnd* pFrmeWnd);
	void UnregisterModulePane(UINT nInstanceID);
	CLogListCtrl* GetLogListCtrl();
	void SetLogListCtrl(CLogListCtrl* pLogListCtrl);

	CListener	*m_pListener;	//a pointer to a Listener object that would handle all incoming messages
	
	CAPTC_ModuleDlg * GetModuleDlg() { return m_pModuleDlg; }
	CString GetDefaultBatchPath();
	BOOL CanClose();
	void Terminate();
	
	CMap <CString, LPCTSTR, CString, LPCTSTR> m_ScriptsParametersMap;

	// API functions for scripts
	//***************************
	BOOL BeginController();
	BOOL EndController();

	void						GetErrorInfo(int nErrorCode, CString& sError);					

/*	
	ERROR_CODE					SetDevice(int nDeviceName, UINT nDeviceValue);
	ERROR_CODE					SetModuleType(const CString& sModuleType);
	ERROR_CODE					SetDatabasePath(const CString& sDBPath);
	ERROR_CODE					SetTimer(int nTimeoutDuration, int nAppType, const CString& sAppPath, const CString& sDllExportedFunc = NULL_STRING);
	ERROR_CODE					SetXDEVConfiguration(const CString& sXDEVConfiguration, int nTestEngineMode = SEQUENTIAL_MODE);
*/
	ERROR_CODE					IsAPTControllerRunning();

	CICATMessage::eDirection	GetDeviceValue(int nDeviceName);
	const int					GetTotalTestsNo();
	const int					GetPassedTestsNo();
	const int					GetFailedTestsNo();
	const int					GetInconTestsNo();
	const int					GetResetsNo() ;
	void						ResetMonitoringData();

	BOOL						SetAPTCScriptParameter(const CString& sParameterName, const CString& sParameterValue);
	BOOL						GetAPTCScriptParameter(const CString& sParameterName, CString& sParameterValue);

	BOOL						GetCurrPTSMessage(CString& sMessage);
	BOOL						GetPrevPTSMessage(CString& sMessage);
	BOOL						GetLastUEMessage(UE_Message& UEMessage);

	BOOL						GetTestQuestStatus();
	bool						RunTestQuestScript(const CString& sScriptName, bool& bScriptResult, int nScriptTimeout=300000);
	
	void						ClearViewerAndLogFile();

	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAPTControllerManager)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CAPTControllerManager();

	void OnControllerBegin();
	void OnControllerEnd();
	void OnDevicesConfiguration();
	void OnControllerConfiguration();
	void OnOpenlogfile();
	void OnSetTestParams();
	void OnUpdateDB();

	// Generated message map functions
	//{{AFX_MSG(CAPTControllerManager)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};


#define theAPTController	CAPTControllerManager::Instance()

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MANAGER_H__67545F8D_D285_493A_8408_9940EF3917EA__INCLUDED_)
