#if !defined(AFX_SCRIPTRESULTSDB_H__C90B9177_96DB_44F6_8D5D_23500950E209__INCLUDED_)
#define AFX_SCRIPTRESULTSDB_H__C90B9177_96DB_44F6_8D5D_23500950E209__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ScriptResultsDB.h : header file
//

#include <afxmt.h>
#include "../../Converter/DB/DisconnectedADORecordset.h"

/////////////////////////////////////////////////////////////////////////////
// CScriptResultsDB DAO recordset

class CScriptResultsDB : public CDisconnectedADORecordset
{
public:
	CScriptResultsDB();
	virtual ~CScriptResultsDB();
	long	m_Batch_Result_ID;
	long	m_Script_Result_ID;
	long	m_Script_Iteration;
	long	m_Batch_Iteration;
	long	m_Script_Param_Set_ID;
	CString	m_Script_Name;
	CString	m_Group_Name;
	CString	m_Script_Version;
	CString	m_Configuration_Name;
	bool	m_Pass_Fail;
	CString	m_Reason_of_Fail;
	COleDateTime	m_Script_Start_Time;
	short	m_Script_Start_Time_Milli;

	BOOL SetScriptResult(long nScriptResultID, long nScriptIteration, BOOL bPassed, const CString &strFailureReason = _T(""));
	long AddRecord(long nScriptIteration, long nBatchResultID, long nBatchIteration, 
							long nScriptParamSetID, const CString &strScriptName, const CString &strGroupName, 
							const CString &strScriptVersion, const CString &strHWConfig, int nResultID);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScriptResultsDB)
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

#endif // !defined(AFX_SCRIPTRESULTSDB_H__C90B9177_96DB_44F6_8D5D_23500950E209__INCLUDED_)
