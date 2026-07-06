// SubScriptResultParamsDB.cpp : implementation file
//

#include "stdafx.h"
#include "SubScriptResultParamsDB.h"
#include "ApplicationINI.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CSubScriptResultParamsDB

CSubScriptResultParamsDB::CSubScriptResultParamsDB()
{
	//{{AFX_FIELD_INIT(CSubScriptResultParamsDB)
	m_SubScript_Result_ID = 0;
	m_SubScript_Parameter_Name = _T("");
	m_SubScript_Parameter_Value = _T("");
	//}}AFX_FIELD_INIT

}

CSubScriptResultParamsDB::~CSubScriptResultParamsDB()
{
	if ( IsOpen() )
		Close();
}

CString CSubScriptResultParamsDB::GetDefaultDBName()
{

	if ( AppIni()->GetProfileInt(_T("TestEngineSettings"), _T("DatabaseType"), 0) == 1 )
		return AppIni()->GetProfileString(_T("TestEngineSettings"), _T("DatabasePath"), _T(""));

	return AppPath() + _T("\\DB\\TestResults.mdb");
}

CString CSubScriptResultParamsDB::GetDefaultSQL()
{
	return _T("[TB_Sub_Script_Parameters]");
}

void CSubScriptResultParamsDB::DoFieldExchange(BOOL bLoad/*=TRUE*/)
{
	if ( bLoad )
	{
		GetFieldValue(_T("SubScript_Result_ID"), m_SubScript_Result_ID);
		GetFieldValue(_T("SubScript_Parameter_Name"), m_SubScript_Parameter_Name);
		GetFieldValue(_T("SubScript_Parameter_Value"), m_SubScript_Parameter_Value);
	}
	else
	{
		SetFieldValue(_T("SubScript_Result_ID"), m_SubScript_Result_ID);
		SetFieldValue(_T("SubScript_Parameter_Name"), m_SubScript_Parameter_Name);
		SetFieldValue(_T("SubScript_Parameter_Value"), m_SubScript_Parameter_Value);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSubScriptResultParamsDB diagnostics

BOOL CSubScriptResultParamsDB::AddRecord(long nSubScriptResultID, const CString &strParamName, const CString &strParamValue)
{
	CSingleLock sLock(&m_cSection);
	sLock.Lock();

	AddNew();
	m_SubScript_Result_ID = nSubScriptResultID;
	m_SubScript_Parameter_Name = strParamName;
	m_SubScript_Parameter_Value = strParamValue;
	Update();

	return TRUE;
}

BOOL CSubScriptResultParamsDB::GetSubScriptResultParams(long nSubScriptResultID, CParameterMap &map)
{
	CSingleLock sLock(&m_cSection);
	sLock.Lock();

	CString strFilter;
	strFilter.Format(_T("[SubScript_Result_ID] = %d"), nSubScriptResultID);
	SetFilter(strFilter);

	while ( !IsEOF() )
	{
		map.SetAt(m_SubScript_Parameter_Name, m_SubScript_Parameter_Value);
		MoveNext();
	}

	SetFilter(_T(""));
	
	return TRUE;
}
