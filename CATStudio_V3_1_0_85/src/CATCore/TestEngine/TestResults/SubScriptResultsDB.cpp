// SubScriptResultsDB.cpp : implementation file
//

#include "stdafx.h"
#include "SubScriptResultsDB.h"
#include "ApplicationINI.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSubScriptResultsDB

CSubScriptResultsDB::CSubScriptResultsDB()
{
	//{{AFX_FIELD_INIT(CSubScriptResultsDB)
	m_Script_Result_ID = 0;
	m_SubScript_Result_ID = 0;
	m_Script_Iteration = 0;
	m_ms_Test_Name = _T("");
	m_ms_Sub_Test_Name = _T("");
	m_Sub_Script_Value = _T("");
	m_Pass_Fail = FALSE;
	m_Criteria = _T("");
	m_Reason_Of_Fail = _T("");
	m_Index = -1;
	//}}AFX_FIELD_INIT
}

CSubScriptResultsDB::~CSubScriptResultsDB()
{
	if ( IsOpen() )
		Close();
}

CString CSubScriptResultsDB::GetDefaultDBName()
{
	if ( AppIni()->GetProfileInt(_T("TestEngineSettings"), _T("DatabaseType"), 0) == 1 )
		return AppIni()->GetProfileString(_T("TestEngineSettings"), _T("DatabasePath"), _T(""));

	return AppPath() + _T("\\DB\\TestResults.mdb");
}

CString CSubScriptResultsDB::GetDefaultSQL()
{
	return _T("[TB_Sub_Script_Results]");
}

void CSubScriptResultsDB::DoFieldExchange(BOOL bLoad/*=TRUE*/)
{
	if ( bLoad )
	{
		GetFieldValue(_T("Script_Result_ID"), m_Script_Result_ID);
		GetFieldValue(_T("SubScript_Result_ID"), m_SubScript_Result_ID);
		GetFieldValue(_T("Script_Iteration"), m_Script_Iteration);
		GetFieldValue(_T("ms_Test_Name"), m_ms_Test_Name);
		GetFieldValue(_T("ms_Sub_Test_Name"), m_ms_Sub_Test_Name);
		GetFieldValue(_T("Sub_Script_Value"), m_Sub_Script_Value);
		GetFieldValue(_T("Pass_Fail"), m_Pass_Fail);
		GetFieldValue(_T("Criteria"), m_Criteria);
		GetFieldValue(_T("Reason_Of_Fail"), m_Reason_Of_Fail);
		GetFieldValue(_T("Index"), m_Index);
	}
	else
	{
		SetFieldValue(_T("Script_Result_ID"), m_Script_Result_ID);
		SetFieldValue(_T("SubScript_Result_ID"), m_SubScript_Result_ID);
		SetFieldValue(_T("Script_Iteration"), m_Script_Iteration);
		SetFieldValue(_T("ms_Test_Name"), m_ms_Test_Name);
		SetFieldValue(_T("ms_Sub_Test_Name"), m_ms_Sub_Test_Name);
		SetFieldValue(_T("Sub_Script_Value"), m_Sub_Script_Value);
		SetFieldValue(_T("Pass_Fail"), m_Pass_Fail);
		SetFieldValue(_T("Criteria"), m_Criteria);
		SetFieldValue(_T("Reason_Of_Fail"), m_Reason_Of_Fail);
		SetFieldValue(_T("Index"), m_Index);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSubScriptResultsDB diagnostics

long CSubScriptResultsDB::AddRecord(long nScriptResultID, long nScriptIteration,
									const CString &msTestName, const CString &msSubTestName,
									const CString &subScriptValue, BOOL bPassFail,const CString &strCriteria, 
									const CString &strFailureReason, long nIndex/*=(-1)*/)
{
	CSingleLock sLock(&m_cSection);
	sLock.Lock();

	long nResultID = 1; 
	if ( GetRecordCount() > 0 )
	{
		MoveLast();
		nResultID = m_SubScript_Result_ID + 1;
	}
	
	AddNew();
	m_Script_Result_ID = nScriptResultID;
	m_SubScript_Result_ID = nResultID;
	m_Script_Iteration = nScriptIteration;
	m_ms_Test_Name = msTestName;
	m_ms_Sub_Test_Name = msSubTestName;
	m_Sub_Script_Value = subScriptValue;
	m_Pass_Fail = bPassFail ? true : false;
	m_Criteria = strCriteria;
	m_Index = nIndex;
	if ( (!bPassFail) && (!strFailureReason.IsEmpty()) )
		m_Reason_Of_Fail = strFailureReason;
	else
		m_Reason_Of_Fail.Empty();

	Update();
	
	return nResultID;
}


BOOL CSubScriptResultsDB::UpdateRecord(long nSubScriptResultID, const CString &subScriptValue, 
									   BOOL bPassFail, const CString &strCriteria, 
									   const CString &strFailureReason, long nIndex/*=(-1)*/)
{
	CSingleLock sLock(&m_cSection);
	sLock.Lock();

	CString strQuery;
	strQuery.Format(_T("[SubScript_Result_ID] = %d"), nSubScriptResultID);
	if ( !FindFirst(strQuery) )
	{
		return FALSE;
	}

	Edit();
	m_Sub_Script_Value = subScriptValue;
	m_Pass_Fail = bPassFail ? true : false;
	m_Criteria = strCriteria;
	m_Reason_Of_Fail = strFailureReason;
	m_Index = nIndex;
	Update();

	return TRUE;
}
									