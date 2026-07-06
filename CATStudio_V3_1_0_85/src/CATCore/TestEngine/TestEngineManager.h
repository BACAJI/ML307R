#pragma once
#include "ScriptsDB.h"
#include "ScriptParamsDB.h"
#include "TestEngine.h"
#include "TestResults/BatchResultsDB.h"
#include "TestResults/UeHwComponentsDB.h"
#include "TestResults/MinimumStandardDB.h"
#include "TestResults/BatchResultParamsDB.h"
#include "SingletonDestroyer.h"
#include "TestResults/ScriptResultsDB.h"
#include "TestResults/SubScriptResultsDB.h"
#include "TestResults/ScriptResultParamsDB.h"
#include "TestResults/SubScriptResultParamsDB.h"
#include <map>

#define MAX_NUM_TESTENGINES 5
#define WM_ADD_TESTENGINE (WM_USER+3)

class CATCORE_DLLEXPORT CTestEngineManager
{
public:
	CTestEngineManager();
	static CTestEngineManager * Instance();
	static BOOL IsAlive();
	static BOOL IsAlive(CTestEngine *pTestEngine);
	void OnOpenTestEngine(CTestEngine *pTestEngine);
	void CloseTestEngine(CTestEngine *pTestEngine);
	BOOL IsTestRunning();
	void Terminate();
	CList <CTestEngine *, CTestEngine *> & GetTestEngineList(){return m_TestEngineList;}
	//Script Databases:
	CScriptsDB		m_ScriptsDB;
	CScriptParamsDB m_ScriptParamsDB;
	UINT	m_nClipBoardFormatID;
private:
	static CTestEngineManager *m_pThis;
	virtual ~CTestEngineManager();
	static CSingletonDestroyer<CTestEngineManager> m_Destroyer;
	friend class CSingletonDestroyer<CTestEngineManager>;
	////////////////////////////////////////////////////
	//Parameters For Remote Testings: See CT Spector////
//	CTestEngine *m_pThreadTestEngine;
	CString m_strFileName;
	CBatchResultsDB				m_BatchResultsDB;
	CBatchResultParamsDB		m_BatchResultParamsDB;
	CScriptResultsDB			m_ScriptResultsDB;
	CScriptResultParamsDB		m_ScriptResultParamsDB;
	CSubScriptResultsDB			m_SubScriptResultsDB;
	CSubScriptResultParamsDB	m_SubScriptResultParamsDB;
	CMinimumStandardDB			m_MinimumStandardDB;
	CUeHwComponentsDB			m_UeHwComponentsDB;

	friend class CTestEngine;
	friend class CScriptData;
	friend class CEnvironmentParamsTab;

	void OpenDatabases();
	void CloseDatabases();
	void CloseAllTestEngines(); //Gregory

	static UINT UpdateTestResultsFunc(LPVOID pParam);
	CEvent m_hCanRunEvent;
protected:
	CList <CTestEngine *, CTestEngine *> m_TestEngineList; // List of Test-Engines.
	CList <CTestEngine *, CTestEngine *> m_AllTestEngineList;
	LRESULT OnUpdateTestResults(WPARAM wParam, LPARAM lParam);
	void AddToList(CTestEngine *pTestEngine);
	void RemoveFromList(CTestEngine *pTestEngine);
	CCriticalSection m_ListSync;
};
#define theTEManager	CTestEngineManager::Instance()
#define WM_UPDATE_TEST_RESULTS	(WM_USER+10)