// ScriptResultsDB.cpp : implementation file
//

#include "stdafx.h"
#include "ScriptResultsDB.h"
#include "ApplicationINI.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScriptResultsDB

CScriptResultsDB::CScriptResultsDB()
{
	//{{AFX_FIELD_INIT(CScriptResultsDB)
	m_Batch_Result_ID = 0;
	m_Script_Result_ID = 0;
	m_Script_Iteration = 0;
	m_Batch_Iteration = 0;
	m_Script_Param_Set_ID = 0;
	m_Script_Name = _T("");
	m_Group_Name = _T("");
	m_Script_Version = _T("");
	m_Configuration_Name = _T("");
	m_Pass_Fail = FALSE;
	m_Reason_of_Fail = _T("");
	m_Script_Start_Time = (DATE)0;
	m_Script_Start_Time_Milli = 0;
	//}}AFX_FIELD_INIT
}

CScriptResultsDB::~CScriptResultsDB()
{
	if ( IsOpen() )
		Close();
}

CString CScriptResultsDB::GetDefaultDBName()
{

	if ( AppIni()->GetProfileInt(_T("TestEngineSettings"), _T("DatabaseType"), 0) == 1 )
		return AppIni()->GetProfileString(_T("TestEngineSettings"), _T("DatabasePath"), _T(""));

	return AppPath() + _T("\\DB\\TestResults.mdb");
}

CString CScriptResultsDB::GetDefaultSQL()
{
	return _T("[TB_Script_Results]");
}

void CScriptResultsDB::DoFieldExchange(BOOL bLoad/*=TRUE*/)
{
	if ( bLoad )
	{
		GetFieldValue(_T("Batch_Result_ID"), m_Batch_Result_ID);
		GetFieldValue(_T("Script_Result_ID"), m_Script_Result_ID);
		GetFieldValue(_T("Script_Iteration"), m_Script_Iteration);
		GetFieldValue(_T("Batch_Iteration"), m_Batch_Iteration);
		GetFieldValue(_T("Script_Parameter_Set_ID"), m_Script_Param_Set_ID);
		GetFieldValue(_T("Script_Name"), m_Script_Name);
		GetFieldValue(_T("Group_Name"), m_Group_Name);
		GetFieldValue(_T("Script_Version"), m_Script_Version);
		GetFieldValue(_T("Configuration_Name"), m_Configuration_Name);
		GetFieldValue(_T("Pass/Fail"), m_Pass_Fail);
		GetFieldValue(_T("Reason_of_Fail"), m_Reason_of_Fail);
		GetFieldValue(_T("Script_Start_Time"), m_Script_Start_Time);
		GetFieldValue(_T("Script_Start_Time_Milli"), m_Script_Start_Time_Milli);
	}
	else
	{
		SetFieldValue(_T("Batch_Result_ID"), m_Batch_Result_ID);
		SetFieldValue(_T("Script_Result_ID"), m_Script_Result_ID);
		SetFieldValue(_T("Script_Iteration"), m_Script_Iteration);
		SetFieldValue(_T("Batch_Iteration"), m_Batch_Iteration);
		SetFieldValue(_T("Script_Parameter_Set_ID"), m_Script_Param_Set_ID);
		SetFieldValue(_T("Script_Name"), m_Script_Name);
		SetFieldValue(_T("Group_Name"), m_Group_Name);
		SetFieldValue(_T("Script_Version"), m_Script_Version);
		SetFieldValue(_T("Configuration_Name"), m_Configuration_Name);
		SetFieldValue(_T("Pass/Fail"), m_Pass_Fail);
		SetFieldValue(_T("Reason_of_Fail"), m_Reason_of_Fail);
		SetFieldValue(_T("Script_Start_Time"), m_Script_Start_Time);
		SetFieldValue(_T("Script_Start_Time_Milli"), m_Script_Start_Time_Milli);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CScriptResultsDB diagnostics

long CScriptResultsDB::AddRecord(long nScriptIteration, long nBatchResultID, 
		long nBatchIteration, long nScriptParamSetID, const CString &strScriptName, const CString &strGroupName, 
		const CString &strScriptVersion, const CString &strHWConfig, int nResultID)
{
	CSingleLock sLock(&m_cSection);
	sLock.Lock();

	if ( nResultID == 0 )
	{
		if ( GetRecordCount() > 0 )
		{
			MoveLast();
			nResultID = m_Script_Result_ID + 1;
		}
		else
			nResultID = 1;	
	}

	AddNew();
	m_Script_Result_ID = nResultID;
	m_Script_Iteration = nScriptIteration;
	m_Batch_Result_ID = nBatchResultID;
	m_Batch_Iteration = nBatchIteration;
	m_Script_Param_Set_ID = nScriptParamSetID;
	m_Script_Name = strScriptName;
	m_Group_Name = strGroupName;
	m_Script_Version = strScriptVersion;
	m_Configuration_Name = strHWConfig;
	m_Script_Start_Time = COleDateTime::GetCurrentTime();
	SYSTEMTIME sysTime;
	::GetLocalTime(&sysTime);
	m_Script_Start_Time_Milli = (short)sysTime.wMilliseconds;
	Update();

	return nResultID;
}


BOOL CScriptResultsDB::SetScriptResult(long nScriptResultID, long nScriptIteration, 
								BOOL bPassed, const CString &strFailureReason /*=_T("")*/)
{
	CSingleLock sLock(&m_cSection);
	sLock.Lock();

	CString strFilter;
	strFilter.Format(_T("[Script_Result_ID] = %d AND [Script_Iteration] = %d"), nScriptResultID, nScriptIteration);
	SetFilter(strFilter);

	if ( GetRecordCount() > 0 )
	{
		Edit();
		m_Pass_Fail = bPassed ? true : false;
		m_Reason_of_Fail = strFailureReason;
		Update();
	}

	SetFilter(_T(""));

	return TRUE;
}
