// BatchResultsDB.cpp : implementation file
//

#include "stdafx.h"
#include "BatchResultsDB.h"

#include "../ParameterMap.h"
#include "ApplicationINI.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBatchResultsDB

CBatchResultsDB::CBatchResultsDB()
{
	//{{AFX_FIELD_INIT(CBatchResultsDB)
	m_Batch_Result_ID = 0;
	m_Batch_Iteration = 0;
	m_Batch_Param_Set_ID = 0;
	m_Batch_Name = _T("");
	m_UE_Number = _T("");
	m_Date = (DATE)0;
	m_UE_SW_Ver = _T("");
	m_UE_Conf_ID = 0;
	m_Purpose = _T("");
	m_Pass_Fail = FALSE;
	m_Station_Number = _T("");
	m_Lab_Number = _T("");
	m_Minimum_Standard_Name = _T("");
	m_Minimum_standard_sub = _T("");
	m_UE_FW_Ver = _T("");
	m_Reason_of_Fail = _T("");
	m_UE_HW_Ver = _T("");
	//}}AFX_FIELD_INIT
}

CBatchResultsDB::~CBatchResultsDB()
{
	if ( IsOpen() )
		Close();
}

CString CBatchResultsDB::GetDefaultDBName()
{

	if ( AppIni()->GetProfileInt(_T("TestEngineSettings"), _T("DatabaseType"), 0) == 1 )
		return AppIni()->GetProfileString(_T("TestEngineSettings"), _T("DatabasePath"), _T(""));

	return AppPath() + _T("\\DB\\TestResults.mdb");
}

CString CBatchResultsDB::GetDefaultSQL()
{
	return _T("[TB_Batch_Results]");
}

void CBatchResultsDB::DoFieldExchange(BOOL bLoad/*=TRUE*/)
{
	if ( bLoad )
	{
		GetFieldValue(_T("Batch_Result_ID"), m_Batch_Result_ID);
		GetFieldValue(_T("Batch_Iteration"), m_Batch_Iteration);
		GetFieldValue(_T("Batch_Parameter_Set_ID"), m_Batch_Param_Set_ID);
		GetFieldValue(_T("Batch_Name"), m_Batch_Name);
		GetFieldValue(_T("UE_Number"), m_UE_Number);
		GetFieldValue(_T("Date"), m_Date);
		GetFieldValue(_T("UE_SW_Ver"), m_UE_SW_Ver);
		GetFieldValue(_T("UE_Conf_ID"), m_UE_Conf_ID);
		GetFieldValue(_T("Purpose"), m_Purpose);
		GetFieldValue(_T("Pass/Fail"), m_Pass_Fail);
		GetFieldValue(_T("Station_Number"), m_Station_Number);
		GetFieldValue(_T("Lab_Number"), m_Lab_Number);
		GetFieldValue(_T("Minimum_Standard_Name"), m_Minimum_Standard_Name);
		GetFieldValue(_T("Minimum_standard_sub"), m_Minimum_standard_sub);
		GetFieldValue(_T("UE_FW_Ver"), m_UE_FW_Ver);
		GetFieldValue(_T("UE_HW_Ver"), m_UE_HW_Ver);
		GetFieldValue(_T("Reason_of_Fail"), m_Reason_of_Fail);
	}
	else
	{
		SetFieldValue(_T("Batch_Result_ID"), m_Batch_Result_ID);
		SetFieldValue(_T("Batch_Iteration"), m_Batch_Iteration);
		SetFieldValue(_T("Batch_Parameter_Set_ID"), m_Batch_Param_Set_ID);
		SetFieldValue(_T("Batch_Name"), m_Batch_Name);
		SetFieldValue(_T("UE_Number"), m_UE_Number);
		SetFieldValue(_T("Date"), m_Date);
		SetFieldValue(_T("UE_SW_Ver"), m_UE_SW_Ver);
		SetFieldValue(_T("UE_Conf_ID"), m_UE_Conf_ID);
		SetFieldValue(_T("Purpose"), m_Purpose);
		SetFieldValue(_T("Pass/Fail"), m_Pass_Fail);
		SetFieldValue(_T("Station_Number"), m_Station_Number);
		SetFieldValue(_T("Lab_Number"), m_Lab_Number);
		SetFieldValue(_T("Minimum_Standard_Name"), m_Minimum_Standard_Name);
		SetFieldValue(_T("Minimum_standard_sub"), m_Minimum_standard_sub);
		SetFieldValue(_T("UE_FW_Ver"), m_UE_FW_Ver);
		SetFieldValue(_T("UE_HW_Ver"), m_UE_HW_Ver);
		SetFieldValue(_T("Reason_of_Fail"), m_Reason_of_Fail);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CBatchResultsDB diagnostics

long CBatchResultsDB::AddRecord(const CString &strBatchName, long nBatchIteration, long nBatchParamSetID, CParameterMap *pEnvironmentParams, CParameterMap *pUeHwParams, int nResultID)
{
	CSingleLock sLock(&m_cSection);
	sLock.Lock();

	if ( nResultID == 0 )
	{
		if ( GetRecordCount() > 0 )
		{
			MoveLast();
			nResultID = m_Batch_Result_ID + 1;
		}
		else
			nResultID = 1;	
	}

	CString tempstr;
	AddNew();
	m_Batch_Result_ID = nResultID;
	m_Batch_Iteration = nBatchIteration;
	m_Batch_Param_Set_ID = nBatchParamSetID;
	m_Batch_Name = strBatchName;

	if ( pEnvironmentParams->Lookup(_T("UE Number"), tempstr) )
		m_UE_Number = tempstr;
	if ( pEnvironmentParams->Lookup(_T("UE SW Version"), tempstr) )
		m_UE_SW_Ver = tempstr;
	if ( pEnvironmentParams->Lookup(_T("UE Config ID"), tempstr) )
	{
	#ifdef UNICODE
		m_UE_Conf_ID = _wtoi(tempstr);
	#else
		m_UE_Conf_ID = atoi(tempstr);
	#endif		
	}
	if ( pEnvironmentParams->Lookup(_T("Testing Purpose"), tempstr) )
		m_Purpose = tempstr;
	if ( pEnvironmentParams->Lookup(_T("Station Number"), tempstr) )
		m_Station_Number = tempstr;
	if ( pEnvironmentParams->Lookup(_T("Lab Number"), tempstr) )
		m_Lab_Number = tempstr;
	if ( pEnvironmentParams->Lookup(_T("Min. Standard Name"), tempstr) )
		m_Minimum_Standard_Name = tempstr;
	if ( pEnvironmentParams->Lookup(_T("Min. Standard Sub"), tempstr) )
		m_Minimum_standard_sub= tempstr;
	if ( pEnvironmentParams->Lookup(_T("UE FW Version"), tempstr) )
		m_UE_FW_Ver = tempstr;

	if (pUeHwParams->Lookup(_T("System Version"), tempstr) )
		m_UE_HW_Ver = tempstr;
	
	m_Date = COleDateTime::GetCurrentTime();

	Update();
	
	return nResultID;	
}

BOOL CBatchResultsDB::SetBatchResults(long nBatchResultID, long nBatchIteration, BOOL bPassed, CStringList *pFailedScripts)
{
	CSingleLock sLock(&m_cSection);
	sLock.Lock();

	CString strFilter;
	strFilter.Format(_T("Batch_Result_ID = %d AND Batch_Iteration = %d"), nBatchResultID, nBatchIteration);
	SetFilter(strFilter);
	
	if ( GetRecordCount() > 0 )
	{
		Edit();
		m_Pass_Fail = bPassed ? true : false;
		if( !bPassed )
		{
			m_Reason_of_Fail = "The following scripts failed: ";
			for (POSITION pos = pFailedScripts->GetHeadPosition(); pos != NULL; )
				m_Reason_of_Fail += pFailedScripts->GetNext(pos) + _T(",");
			m_Reason_of_Fail = m_Reason_of_Fail.Left(m_Reason_of_Fail.GetLength()-1);
		}
		
		Update();
	}
	
	SetFilter(_T(""));

	return TRUE;
}
