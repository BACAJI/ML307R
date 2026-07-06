#if !defined(AFX_BATCHRESULTSDB_H__741861A3_B72F_438E_ADDB_F56E77F643D5__INCLUDED_)
#define AFX_BATCHRESULTSDB_H__741861A3_B72F_438E_ADDB_F56E77F643D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BatchResultsDB.h : header file
//

#include <afxmt.h>
#include "../../Converter/DB/DisconnectedADORecordset.h"


class CParameterMap;

/////////////////////////////////////////////////////////////////////////////
// CBatchResultsDB DAO recordset

class CBatchResultsDB : public CDisconnectedADORecordset
{
public:
	CBatchResultsDB();
	virtual ~CBatchResultsDB();
	long	m_Batch_Result_ID;
	long	m_Batch_Iteration;
	long	m_Batch_Param_Set_ID;
	CString m_Batch_Name;
	CString	m_UE_Number;
	COleDateTime	m_Date;
	CString	m_UE_SW_Ver;
	long	m_UE_Conf_ID;
	CString	m_Purpose;
	bool	m_Pass_Fail;
	CString	m_Station_Number;
	CString	m_Lab_Number;
	CString	m_Minimum_Standard_Name;
	CString	m_Minimum_standard_sub;
	CString	m_UE_FW_Ver;
	CString	m_UE_HW_Ver;
	CString	m_Reason_of_Fail;

	long AddRecord(const CString &strBatchName, long nBatchIteration, long nBatchParamSetID, CParameterMap *pEnvironmentParams, CParameterMap *pUeHwParams, int nResultID);
	BOOL SetBatchResults(long nBatchResultID, long nBatchIteration, BOOL bPassed, CStringList *pFailedScripts);
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBatchResultsDB)
	public:
	virtual CString GetDefaultDBName();		// Default database name
	virtual CString GetDefaultSQL();		// Default SQL for Recordset
	virtual void DoFieldExchange(BOOL bLoad = TRUE);
	//}}AFX_VIRTUAL

private:
	CCriticalSection m_cSection;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BATCHRESULTSDB_H__741861A3_B72F_438E_ADDB_F56E77F643D5__INCLUDED_)
