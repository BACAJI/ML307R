/*--------------------------------------------------------------------------------------*
 | (C) Copyright 2006,2007 Marvell Semiconductor Israel Ltd. All Rights Reserved		|
 *--------------------------------------------------------------------------------------*/

// TestEngine1.h: interface for the CTestEngine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTENGINE1_H__7FB3F70D_0641_4AAE_A7ED_95BCF3A7DEC6__INCLUDED_)
#define AFX_TESTENGINE1_H__7FB3F70D_0641_4AAE_A7ED_95BCF3A7DEC6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <eh.h>
#include <afxtempl.h>
#include "ScriptData.h"
#include "ParameterMap.h"
#include "../Converter/DBUtils.h"
#include "../BasicComponents/XDEVStructures.h"
#include "../CommandAndControl/CommandAndControl.h"
#include "TestResults/SubScriptResultParamsDB.h"
#include "../xDev/ConfigDevice.h"
#include "ICATMessageReceiver.h"

#if !MICL_BUILD
#if _MSC_VER > 1200
#include "Logging/Logging.h"
#endif
#endif

#define WM_SCRIPT_MESSAGE			(WM_USER+31)
#define WM_SCRIPT_ITERATION			(WM_USER+32)
#define WM_BATCH_STARTED			(WM_USER+33)
#define WM_BATCH_ENDED				(WM_USER+34)
#define WM_BATCH_ITERATION			(WM_USER+35)
#define WM_SCRIPT_ITERATION_ENDED	(WM_USER+36)
#define WM_BATCH_MESSAGE			(WM_USER+37)
#define WM_SCRIPT_CURPROGNUM		(WM_USER+38)
#define WM_SCRIPT_MAXPROGNUM		(WM_USER+39)

class CScriptData;
class CMessageSender;
class CICATMessageReceiverEx;
struct TestInterface;


struct MinStandard {
	CString m_TestName;
	CString m_SubTestName;
	double m_Min;
	double m_Max;
	short m_RangeID;
	CString m_Notes;
	CString m_Section;
};


#define TEST_FUNC extern "C" __declspec(dllexport)

typedef bool(LPSCRIPTFUNC)(TestInterface *);
typedef void(LPBATCHPARMETERSFUNC)(CTestEngine* pTestEngine, CWnd* pWnd);

typedef enum  {
	InvalidTest	  = -1,	
	TestReady = 0,
	TestRunning,
	TestPassed,
	TestFailed,
	TestStopped,
	TestError
} TestState;


#define SCRIPT_ENABLED	0
#define SCRIPT_DISABLED	1
#define HW_CONFIG_MISMATCH	2
#define	PROGRESS_STEP_PERCENT_MIN		1
#define	MAX_CLEANUP_WAIT_TIME			60 // in seconds


enum eScriptRunType
{
	eFailStop = 1,
	eFailContinue,
	eFailAsk
};

enum eSNType
{
	eSNNone = 1,
	eSNInput,
	eSNReadFromUE
};

struct tagBatchFilePathAndName
{
	CString strBatchFilePath;
	CString strBatchFileName;
};

class __declspec(dllexport)  CTestEngine
{
public:
	CTestEngine(CWnd *pMainWnd/* = NULL*/);
	virtual ~CTestEngine();
	CMessageSender *m_pMessageSender;	// Interface for sending messages to the ICAT.
	void DeleteScript(int nScriptIndex);
	UINT GetScriptStatus(int nScriptIndex);
	void EnableScript(int nScriptIndex, UINT mode);
	BOOL UpdateBatch();
	int GetNumScripts();
	void EnableScriptsByConfig();
	int GetNumOfBatchIterations();
	CString (CALLBACK *pfnUpdateParameter)(CScriptParamsDB &db,CString strName, CString strValue);
	CWinThread* BeginCleanUpThread( AFX_THREADPROC pfnThreadProc, LPVOID pParam, UINT nTimeoutInSec = MAX_CLEANUP_WAIT_TIME); //Gregory
	void SetCleanUpThread( AFX_THREADPROC pfnThreadProc, LPVOID pParam, UINT nTimeoutInSec = MAX_CLEANUP_WAIT_TIME);
	void ResetCleanUpThread(TCHAR* strFuncLine = _T("")); //Gregory
	void SetNightMode(BOOL bNightMode = TRUE);
	void DeleteBatchParameterMaps();
	void SetAssertMode(BOOL val){m_bAssertManually = val;}
	BOOL GetAssertMode(){return m_bAssertManually;}
	CStringA GetScriptName(const CStringA &strGroupName, int nScriptIndex);
	void (CALLBACK *pfnSendLogToUICallback)(CString strLogMsg);
	long (CALLBACK *pfnGetBatchFilePathAndNameCallback)(void * pObject, WPARAM & wParam, LPARAM & lParam);
	CListEx <CParameterMap *, CParameterMap *> * GetBatchParameterMapList();
	BOOL			m_bStopAfterNextIteration;
	int m_nBatchIterations;
	int	m_CurrentScriptIndex;
	CListEx <CScriptData *, CScriptData *> m_ScriptList;	// List of scritps to run.
	CWnd	*m_pMainWnd;
	CList <HMODULE, HMODULE> m_OpenDllsList;
	CArray<bool, bool> m_ParamSetsEnabled;

	AFX_THREADPROC m_pfnCleanUpThreadProc;
	LPVOID m_pCleanUpParam;
	UINT m_nCleanUpThreadTimeout;

private:
	CWinThread		*m_pStopScriptsThread;
	CWordArray		m_SelectedScripts;
	CScriptData		*m_pCurrentScript;
	TestInterface	*m_pTestInterface;
	int				m_CurrentBatchResultID;
	/*BOOL			m_bStopAfterNextIteration;*/
	CWinThread		*m_pScriptThread;
	CString m_strBatchFilePathAndName;
/*	sInitialization m_InitStruct;*/
	BOOL m_bNightMode;
	BOOL m_bSaveToDB;
	BOOL m_bAssertManually;
	CStringList		m_FailedScripts;
	int		m_LastUserAction;
	CString m_strInstanceName;

	CEvent m_KillEvent;
	CEvent m_CanKillEvent;
	CEvent m_XDevTermEvent;
	CEvent m_PauseEvent;
	CEvent m_ResumeEvent;
	CEvent m_EventDeviceStatus[MAX_DEVICE_NUM];
	CEvent m_EventDatabaseStatus[MAX_DEVICE_NUM];
	BOOL			m_bPaused;

	CWinThread* m_pCleanUpThread;
	CParameterMap	m_CurrentBatchParameterMap;
	CParameterMap	m_EnvironmentParameters;
	friend class CBatchSerializer;
	friend class CScriptData;
	friend class CBatchParametersTab;
	
	sInitialization m_InitStruct;
	/*int	m_CurrentScriptIndex;*/
	int m_BatchStartIteration;
	int m_ScriptStartIndex;
	int m_CurrentBatchIteration;
	int m_ScriptStartIteration;
	/*int m_nBatchIterations;*/
	BOOL m_bUseBatchFilters;
	CStringList m_ExtraBatchData;
	CParameterMap	m_HWConfigParameterMap;
	CListEx<CStringArrayEx, CStringArrayEx&> m_BatchParamDescriptionList;
	BOOL m_bReportLoadErrors;
	BOOL	m_bCanSaveResultsToFile;
	CTime	m_LastBatchStartTime;
	CString m_CurrentTestBatchPath;
	//Parameters for the Progress column (in Script list window)
	int		m_iProgMaxNum;
	int		m_iProgCurNum;
	/*CListEx <CScriptData *, CScriptData *> m_ScriptList;	// List of scritps to run.*/
	CListEx <CParameterMap *, CParameterMap *> m_BatchParameterMapList;
	CString			m_CurrentHWConfig;
	CMap<CString,LPCTSTR,CEvent*,CEvent*> m_mapEventLogFileName;
	CStringArray m_strArrayLogFileNames;
public:
	CCommandAndControl m_CommandAndControl;

public:
	void SaveTestResultToFile();
	BOOL CanSaveResultsToFile();
	int GetDeviceNumber();
	void PauseScripts();
	void ResumeScripts();
	BOOL UpdateDeviceStatus(int nDevice,BOOL bConnected);
	BOOL UpdateDatabaseStatus(int nDevice,BOOL bLoadFinish);
	BOOL WaitForDeviceConnected(int nDevice);
	BOOL WaitForDatabaseLoadedFinish(int nDevice);
	void UpdateLogFileCloseState(CString strLogFileName, BOOL bFinishClose);
	void WaitForLogFileClose(CString strLogFileName);

	void SendMessageToViewer(const CStringW &strMessage);

	int GetBatchStartIteration();
	static CString GetTestResultsDBPath();
	BOOL GetUeHwParameter(const CString &strParamName, CString &strParamValue);
	void SetNumScriptIterations(int nScriptIndex, int nIterations);
	void GetBatchFilePathAndName(CString &strPath);
	BOOL LoadBatchFile(const CString &strFileName);
	BOOL SaveBatchFile(const CString &strFileName);
	static CStringA FindDirectory();
	void SetSelectedScripts(CWordArray &selectedScripts);
	void PlayScripts(BOOL bPlayAll = TRUE);
	TestInterface * GetTestInterface();
	BOOL IsTestRunning();
	BOOL IsTestPaused();
	BOOL StoreResults();
	void AddBatchParameterSet();
	//void AddDllToList(HMODULE hDll);
	void FreeAllOpenDlls();
	BOOL StoreBoardsSerialNumbers(int a_iBatchResultID);
	int GetScriptStartIndex();
	void ShowBatchParameters();
	void AddScript(CScriptData *pData);
	BOOL AddScript(const CString &strGroup, const CString &strScript);
	BOOL GetEnvironmentParameter(const CString &strName, CString &strValue);
	void DeleteScriptList();
	CScriptData * GetScriptAt(int index);
	void SetProgressMaxNum(int iProgMaxNum);
	BOOL GetCurrentBatchName(CString &strName);
	int GetScriptStartIteration();
	BOOL InitializeHWConfiguration();
	void LoadHwConfigParameters();
	void LoadEnvironmentParameters();
	CParameterMap * GetEnvironmentParametersMap();
	void SetProgressCurrentNum(int iProgCurNum,BOOL bSucceed=TRUE);
#ifdef _UNICODE
	BOOL GetBatchParameter(const CString &strName, CString &strValue);
	void SetScriptFailureReason(const CString & strReason);
	CString	GetScriptName(const CString &strGroupName, int nScriptIndex);
	BOOL GetScriptParameter(const CString &strName, CString &strValue);
#endif
	BOOL GetBatchParameter(const CStringA &strName, CStringA &strValue);
	void SetScriptFailureReason(const CStringA & strReason);
	void SetNumOfBatchIterations(int nBatchIterations);
	int GetCurrentBatchResultID();
	void SetLastUserAction(int action);
	void PostScriptMessage(UINT message, LPARAM lParam);
	void ScriptFailed(const CString &strGroup, const CString &strScript, int nScriptIteration);

	void SaveAndSendMessage( const char *strFmt, ... );
	void SaveAndSendMessage(CMessageSender * pSender, const wchar_t *strFmt, ... );
	void SaveAndSendMessage(CMessageSender * pSender, const char *strFmt, ... );
	void SaveAndSendMessage( const wchar_t *strFmt, ... );
#ifdef _UNICODE
	void SaveAndSendMessage( const CStringW & strMessage);
	void SaveAndSendMessage(CMessageSender * pSender, const CStringW & strMessage);
#endif
	void SaveAndSendMessage( const CStringA & strMessage);
	void SaveAndSendMessage(CMessageSender * pSender, const CStringA & strMessage);
	CEvent* GetKillEvent(){ return &m_KillEvent;};
	void SetTestEngineName(const CString &strName);
	void SetScriptList(CList<CScriptData *, CScriptData *> *pList);
	unsigned long GetPrimaryViSession(const CString &strInstName);
	int GetScriptIndex(const CString &strGroupName, const CString &strScriptName);
	BOOL AddBatchParameter(const CString &strParamName, const CString &strParamValue);
	BOOL SetBatchParameterValue(int nParamSetIndex, const CString &strParamName, const CString &strParamValue);
	BOOL SetScriptParameterValue(int nScriptIndex, int nParamSetIndex, const CString &strParamName, const CString &strParamValue);
	BOOL SetScriptParameterValue(int nScriptIndex, int nParamSetIndex, const CString &strParamName, int nParamValue);
	BOOL SetScriptParameterValue(int nScriptIndex, int nParamSetIndex, const CString &strParamName, UINT unParamValue);
	BOOL SetScriptParameterValue(int nScriptIndex, int nParamSetIndex, const CString &strParamName, double fParamValue);
	BOOL SetScriptParameterValue(int nScriptIndex, int nParamSetIndex, const CString &strParamName, bool bParamValue);
	BOOL SetBatchStartingPoint(int nBatchStartIteration, int nScriptStartIndex, int nScriptStartIteration);
// 	template <class T> BOOL GetScriptParameter(const CString &strName, T &tValue)
// 	{
// 		BOOL bRet;
// 		bRet = m_pCurrentScript->GetParameter(strName, tValue);
// 		return(bRet);
// 	};

 	BOOL GetScriptParameter(const CString &strName, bool &bValue);
 	BOOL GetScriptParameter(const CString &strName, double &fValue);
 	BOOL GetScriptParameter(const CString &strName, int &nValue);
 	BOOL GetScriptParameter(const CString &strName, UINT &unValue);
	BOOL GetScriptParameter(const CStringA &strName, CStringA &strValue);

	//////////////////////////////////////////////////////////////////////////
	//Richard added 2011-11-23	Begin
	CSubScriptResultParamsDB	m_SubScriptResultParamsDB;
			///// API functions for scripts ///////////////////

 	BOOL SetScriptParameter(const CString &strName, bool &bValue);
 	BOOL SetScriptParameter(const CString &strName, double &fValue);
 	BOOL SetScriptParameter(const CString &strName, int &nValue);
 	BOOL SetScriptParameter(const CString &strName, UINT &unValue);
 	BOOL SetScriptParameter(const CString &strName, CString &strValue);


	BOOL GetScriptParameter(const CString &strName, bool &bValue, CString &dllName,CString &scriptName);
	BOOL GetScriptParameter(const CString &strName, double &fValue, CString &dllName,CString &scriptName);
	BOOL GetScriptParameter(const CString &strName, int &nValue, CString &dllName,CString &scriptName);
	BOOL GetScriptParameter(const CString &strName, UINT &unValue, CString &dllName,CString &scriptName);
	BOOL GetScriptParameter(const CString &strName, CString &strValue, CString &dllName,CString &scriptName);

	BOOL SetScriptParameter(const CString &strName, bool &bValue, CString &dllName,CString &scriptName);
	BOOL SetScriptParameter(const CString &strName, double &fValue, CString &dllName,CString &scriptName);
	BOOL SetScriptParameter(const CString &strName, int &nValue, CString &dllName,CString &scriptName);
	BOOL SetScriptParameter(const CString &strName, UINT &unValue, CString &dllName,CString &scriptName);
	BOOL SetScriptParameter(const CString &strName, CString &strValue, CString &dllName,CString &scriptName);


	BOOL SetBatchParameter(const CString &strName, const CString &strValue);
	BOOL GetMinStandard(MinStandard *pMinStandard);
	BOOL GetMinStandard(const CString &strTestName, const CString &strSubTestName, MinStandard *pMinStandard);

	BOOL UpdateSubScriptResult(long nResultID, const CString &subTestValue, BOOL bPassFail, const CString &strCriteria = _T(""), const CString &strFailureReason = _T(""), long nIndex =(-1));
	long SaveSubScriptResult(const CString &strTestName, const CString &strSubTestName, const CString &subTestValue, BOOL bPassFail, const CString &strCriteria = _T(""), const CString &strFailureReason = _T(""), long nIndex =(-1));
	long SaveSubScriptResult(const CString &strSubScriptName, const CString &subScriptValue, BOOL bPassFail, const CString &strCriteria = _T(""), const CString &strFailureReason = _T(""), long nIndex =(-1));
	BOOL SetSubScriptResultParameter(long nSubScriptResultID, const CString &strParamName, const CString &strParamValue);
#ifdef _UNICODE
	BOOL GetScriptFailureReason(CString &strReason,int nScriptIndex=0, int nIteration=0);
#endif
	BOOL GetScriptFailureReason(CStringA &strReason,int nScriptIndex=0, int nIteration=0);

	long CheckSubScriptResult(const CString &msTestName, const CString &msSubTestName, double fSubScriptValue, BOOL &bPassFail, BOOL bSaveToDB = TRUE);

	unsigned long GetSecondaryViSession (const CString &strDeviceName,int iSecAddress);
	unsigned long GetSecondaryViSession (const CString &strDeviceName,const CString &strSecAddrInitMode);


	CScriptData * GetScriptByDllAndScriptName(CString &dllName,CString &scriptName);
	BOOL XDEVImportDevOrCfg(const CString &strFilePath, CString &strErrMsg = CString(_T("")));
	BOOL GetDeviceAttenuation(double & dAttenuation,const CString &strDeviceName, const CString &strPort = _T(""), const CString &strBandOrFreq = _T(""), CString &strErrMsg = CString(_T("")));
	BOOL GetDeviceAttenuation(const CString &strDeviceName, double &fAttenuation);
	BOOL SetDeviceAttenuation(double dAttenuation,const CString &strDeviceName, const CString &strPort, const CString &strBandOrFreq = _T("") , CString &strErrMsg = CString(_T("")));
	BOOL GetXDEVConfigDevices(CStringList &deviceCfgNameList, const CString &strConfigName = _T(""));
	CString GetCurrentHWConfig();
	void SetCurrentHWConfig(const CString & strHWConfig);
	BOOL GetXDEVConfigurationDeviceGroup(CArray<sConfigDevParams,sConfigDevParams&> &arrConfigDevice, const CString &strDevGroup, CString &strErrMsg = CString(""), const CString &strConfigName = CString(""));
	BOOL GetXDEVConfigurationDeviceGroup(CArray<CConfigDevice,CConfigDevice&> &arrConfigDevice, int iDeviceGroupID, CString &strErrMsg = CString(""), const CString &strConfigName = CString(""));

	//Richard added 2011-11-23	End
	//////////////////////////////////////////////////////////////////////////

	bool UpdateCommandsDB(int nDevice, const CString& strDBPath, CString& strError, bool bAppSideDB = false);
	bool UpdateNVMDB(int nDevice, const CString& strDBPath, CString& strError, bool bAppSide = false);
	bool UpdateDSPDB(int nDevice, const CString& strDspPath, CString& strError);
	bool ImportDBFromText(int nDevice, const CString& strDbTextPath, CString& strError, bool bAppSide = false, bool blocking = true);
	CMessageSender * CreateMessageSender(const CString & strModuleName, const CString &strInstanceName=_T(""));
	void DeleteMessageSender(CMessageSender*& pSender);
	CICATMessageReceiverEx * CreateMessageReceiver(LPVOID pClass, BOOL bStartReceiving, LP_ICAT_MESSAGE_FUNC *pICATMessageFunc);
	void DeleteMessageReceiver(CICATMessageReceiverEx*& pReceiver);

protected:
	static UINT TerminateXDevFunc(LPVOID pParam);
	static UINT StopScriptsThread(LPVOID pParam);
	void RunSelectedScripts();
//	void ValidateEnvironmentParameters();
	static UINT RunAllScriptsFunc(LPVOID pParam);
	static UINT RunSelectedScriptsFunc(LPVOID pParam);
	void RunAllScripts();
	void StopScriptsActions();

public:	
	void StopTestEngine();
	void PatchInt3(BOOL bPatch) ;
	void ResetModified();
	void StopScripts(void);
	BOOL WaitForCleanUp();
	void ScriptEnded();
	//////////////////////////////////////////////////////////////////////////
	//Richard added for RF Cal	2011-12-31
	int GetCurrentBatchIteration();
	int GetCurrentScriptIteration();
	CStringA GetInstanceName();
	void SetInstanceName(CString& strInstanceName);
	int GetTotalCurrentScriptIterations();
	BOOL IsLastScriptAndIterInBatch();
	int GetCurrentScriptIndex();
	BOOL GetNightMode();
	CStringA GetCurrentTestBatchPath();
	BOOL SetEnvironmentParameter(const CString &strName, const CString &strValue);

	eScriptRunType m_eScRunType;

	//Richard added for RF Cal	2011-12-31
	//////////////////////////////////////////////////////////////////////////

public:
	CEvent* GetPauseEvent(){ return &m_PauseEvent; }
	CEvent* GetResumeEvent(){ return &m_ResumeEvent;}
};


struct TestInterface 
{
	CTestEngine *m_pTestEngine;

	TestInterface() { m_pTestEngine = NULL; }
	TestInterface(CTestEngine *pTestEngine) { m_pTestEngine = pTestEngine; }
};

//Richard add this function for RFCal Project	2012-02-07
//extern "C" __declspec (dllexport) BOOL RFC_TE_GetBatchParameter(CTestEngine* te, const CString &strName, CString &strValue);
//Richard add this function for RFCal Project	2012-02-07

#endif // !defined(AFX_TESTENGINE1_H__7FB3F70D_0641_4AAE_A7ED_95BCF3A7DEC6__INCLUDED_)
