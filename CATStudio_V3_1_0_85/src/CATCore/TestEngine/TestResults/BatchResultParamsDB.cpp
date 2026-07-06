// BatchResultParamsDB.cpp : implementation file
//

#include "stdafx.h"
#include "BatchResultParamsDB.h"

#include "../ParameterMap.h"
#include "ApplicationINI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBatchResultParamsDB

CBatchResultParamsDB::CBatchResultParamsDB()
{
	//{{AFX_FIELD_INIT(CBatchResultParamsDB)
	m_Batch_Result_ID = 0;
	m_Batch_Iteration = 0;
	m_Batch_Parameter_Name = _T("");
	m_Batch_Parameter_Value = _T("");
	m_Batch_Param_Set_ID = 0;
	//}}AFX_FIELD_INIT
}

CBatchResultParamsDB::~CBatchResultParamsDB()
{
	if ( IsOpen() )
		Close();
}

CString CBatchResultParamsDB::GetDefaultDBName()
{

	if ( AppIni()->GetProfileInt(_T("TestEngineSettings"), _T("DatabaseType"), 0) == 1 )
		return AppIni()->GetProfileString(_T("TestEngineSettings"), _T("DatabasePath"), _T(""));
	
	return AppPath() + _T("\\DB\\TestResults.mdb");
}

CString CBatchResultParamsDB::GetDefaultSQL()
{
	return _T("[TB_Batch_Parameters]");
}

void CBatchResultParamsDB::DoFieldExchange(BOOL bLoad/*=TRUE*/)
{
	if ( bLoad )
	{
		GetFieldValue(_T("Batch_Result_ID"), m_Batch_Result_ID);
		GetFieldValue(_T("Batch_Iteration"), m_Batch_Iteration);
		GetFieldValue(_T("Batch_Parameter_Name"), m_Batch_Parameter_Name);
		GetFieldValue(_T("Batch_Parameter_Value"), m_Batch_Parameter_Value);
		GetFieldValue(_T("Batch_Parameter_Set_ID"), m_Batch_Param_Set_ID);
	}
	else
	{
		SetFieldValue(_T("Batch_Result_ID"), m_Batch_Result_ID);
		SetFieldValue(_T("Batch_Iteration"), m_Batch_Iteration);
		SetFieldValue(_T("Batch_Parameter_Name"), m_Batch_Parameter_Name);
		SetFieldValue(_T("Batch_Parameter_Value"), m_Batch_Parameter_Value);
		SetFieldValue(_T("Batch_Parameter_Set_ID"), m_Batch_Param_Set_ID);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CBatchResultParamsDB diagnostics


BOOL CBatchResultParamsDB::AddRecords(long nBatchResultID, long nBatchIteration, long nBatchParamSetID, CParameterMap *pParamMap)
{
	CSingleLock sLock(&m_cSection);
	sLock.Lock();

	CString strName, strValue;
	for (POSITION pos = pParamMap->GetStartPosition(); pos != NULL; )
	{
		pParamMap->GetNextAssoc(pos, strName, strValue);

		AddNew();
		m_Batch_Result_ID = nBatchResultID;
		m_Batch_Iteration = nBatchIteration;
		m_Batch_Parameter_Name = strName;
		m_Batch_Parameter_Value = strValue;
		m_Batch_Param_Set_ID = nBatchParamSetID;
		Update();
	}
	
	return TRUE;
}
