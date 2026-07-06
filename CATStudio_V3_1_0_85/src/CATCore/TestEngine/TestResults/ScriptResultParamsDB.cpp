// ScriptResultParamsDB.cpp : implementation file
//

#include "stdafx.h"
#include "ScriptResultParamsDB.h"

#include "../ParameterMap.h"
#include "ApplicationINI.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CScriptResultParamsDB

CScriptResultParamsDB::CScriptResultParamsDB()
{
	//{{AFX_FIELD_INIT(CScriptResultParamsDB)
	m_Script_Result_ID = 0;
	m_Script_Iteration = 0;
	m_Script_Parameter_Name = _T("");
	m_Script_Parameter_Value = _T("");
	m_Script_Param_Set_ID = 0;
	//}}AFX_FIELD_INIT
}

CScriptResultParamsDB::~CScriptResultParamsDB()
{
	if ( IsOpen() )
		Close();
}

CString CScriptResultParamsDB::GetDefaultDBName()
{

	if ( AppIni()->GetProfileInt(_T("TestEngineSettings"), _T("DatabaseType"), 0) == 1 )
		return AppIni()->GetProfileString(_T("TestEngineSettings"), _T("DatabasePath"), _T(""));

	return AppPath() + _T("\\DB\\TestResults.mdb");
}

CString CScriptResultParamsDB::GetDefaultSQL()
{
	return _T("[TB_Script_Parameters]");
}

void CScriptResultParamsDB::DoFieldExchange(BOOL bLoad/*=TRUE*/)
{
	if ( bLoad )
	{
		GetFieldValue(_T("Script_Result_ID"), m_Script_Result_ID);
		GetFieldValue(_T("Script_Iteration"), m_Script_Iteration);
		GetFieldValue(_T("Script_Parameter_Name"), m_Script_Parameter_Name);
		GetFieldValue(_T("Script_Parameter_Value"), m_Script_Parameter_Value);
		GetFieldValue(_T("Script_Parameter_Set_ID"), m_Script_Param_Set_ID);
	}
	else
	{
		SetFieldValue(_T("Script_Result_ID"), m_Script_Result_ID);
		SetFieldValue(_T("Script_Iteration"), m_Script_Iteration);
		SetFieldValue(_T("Script_Parameter_Name"), m_Script_Parameter_Name);
		SetFieldValue(_T("Script_Parameter_Value"), m_Script_Parameter_Value);
		SetFieldValue(_T("Script_Parameter_Set_ID"), m_Script_Param_Set_ID);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CScriptResultParamsDB diagnostics


BOOL CScriptResultParamsDB::AddRecords(long nScriptResultID, long nScriptIteration, long nScriptParamSetID, CParameterMap *pMap)
{
	CSingleLock sLock(&m_cSection);
	sLock.Lock();

	CString strName, strValue;
	for (POSITION pos = pMap->GetStartPosition(); pos != NULL; )
	{
		pMap->GetNextAssoc(pos, strName, strValue);

		AddNew();
		m_Script_Result_ID = nScriptResultID;
		m_Script_Iteration = nScriptIteration;
		m_Script_Parameter_Name = strName;
		m_Script_Parameter_Value = strValue;
		m_Script_Param_Set_ID = nScriptParamSetID;
		Update();
	}
	
	return TRUE;
}
