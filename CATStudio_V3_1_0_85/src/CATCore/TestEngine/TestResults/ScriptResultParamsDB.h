#if !defined(AFX_SCRIPTRESULTPARAMSDB_H__381C763F_2C1A_451E_A687_CFA329FB7B2F__INCLUDED_)
#define AFX_SCRIPTRESULTPARAMSDB_H__381C763F_2C1A_451E_A687_CFA329FB7B2F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ScriptResultParamsDB.h : header file
//

#include <afxmt.h>
#include "../../Converter/DB/DisconnectedADORecordset.h"

class CParameterMap;

/////////////////////////////////////////////////////////////////////////////
// CScriptResultParamsDB DAO recordset

class CScriptResultParamsDB : public CDisconnectedADORecordset
{
public:
	CScriptResultParamsDB();
	virtual ~CScriptResultParamsDB();
	long	m_Script_Result_ID;
	long	m_Script_Iteration;
	CString	m_Script_Parameter_Name;
	CString	m_Script_Parameter_Value;
	long	m_Script_Param_Set_ID;

	BOOL AddRecords(long nScriptResultID, long nScriptIteration, long nScriptParamSetID, CParameterMap *pMap);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScriptResultParamsDB)
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

#endif // !defined(AFX_SCRIPTRESULTPARAMSDB_H__381C763F_2C1A_451E_A687_CFA329FB7B2F__INCLUDED_)
