#if !defined(AFX_SUBSCRIPTRESULTSDB_H__DDD4818A_B78B_4E1B_94DC_4A2B6AF0DF23__INCLUDED_)
#define AFX_SUBSCRIPTRESULTSDB_H__DDD4818A_B78B_4E1B_94DC_4A2B6AF0DF23__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SubScriptResultsDB.h : header file
//

#include <afxmt.h>
#include "../../Converter/DB/DisconnectedADORecordset.h"

/////////////////////////////////////////////////////////////////////////////
// CSubScriptResultsDB DAO recordset

class CSubScriptResultsDB : public CDisconnectedADORecordset
{
public:
	CSubScriptResultsDB();
	virtual ~CSubScriptResultsDB();
	long	m_Script_Result_ID;
	long	m_SubScript_Result_ID;
	long	m_Script_Iteration;
	CString	m_ms_Test_Name;
	CString	m_ms_Sub_Test_Name;
	CString	m_Sub_Script_Value;
	bool	m_Pass_Fail;
	CString	m_Criteria;
	CString	m_Reason_Of_Fail;
	long	m_Index;

	long AddRecord(long nScriptResultID, long nScriptIteration, const CString &msTestName, 
							const CString &msSubTestName, const CString &subScriptValue, 
							BOOL bPassFail, const CString &strCriteria, const CString &strFailureReason = _T(""),long nIndex = (-1));
	BOOL UpdateRecord(long nSubScriptResultID, const CString &subScriptValue, 
									   BOOL bPassFail, const CString &strCriteria, 
									   const CString &strFailureReason,long nIndex =(-1));

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSubScriptResultsDB)
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

#endif // !defined(AFX_SUBSCRIPTRESULTSDB_H__DDD4818A_B78B_4E1B_94DC_4A2B6AF0DF23__INCLUDED_)
