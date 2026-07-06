#if !defined(AFX_BATCHRESULTPARAMSDB_H__AFFBF151_772B_4F13_8875_C968708605FA__INCLUDED_)
#define AFX_BATCHRESULTPARAMSDB_H__AFFBF151_772B_4F13_8875_C968708605FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BatchResultParamsDB.h : header file
//

#include <afxmt.h>
#include "../../Converter/DB/DisconnectedADORecordset.h"

class CParameterMap;

/////////////////////////////////////////////////////////////////////////////
// CBatchResultParamsDB DAO recordset

class CBatchResultParamsDB : public CDisconnectedADORecordset
{
public:
	CBatchResultParamsDB();
	virtual ~CBatchResultParamsDB();
	long	m_Batch_Result_ID;
	long	m_Batch_Iteration;
	CString	m_Batch_Parameter_Name;
	CString	m_Batch_Parameter_Value;
	long	m_Batch_Param_Set_ID;

	BOOL AddRecords(long nBatchResultID, long nBatchIteration, long nBatchParamSetID, CParameterMap *pParamMap);
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBatchResultParamsDB)
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

#endif // !defined(AFX_BATCHRESULTPARAMSDB_H__AFFBF151_772B_4F13_8875_C968708605FA__INCLUDED_)
