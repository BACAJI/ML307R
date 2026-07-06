#if !defined(AFX_SUBSCRIPTRESULTPARAMSDB_H__569BB76F_2501_4F15_896D_3BA82218CD06__INCLUDED_)
#define AFX_SUBSCRIPTRESULTPARAMSDB_H__569BB76F_2501_4F15_896D_3BA82218CD06__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SubScriptResultParamsDB.h : header file
//

#include <afxmt.h>
#include "../ParameterMap.h"
#include "../../Converter/DB/DisconnectedADORecordset.h"

/////////////////////////////////////////////////////////////////////////////
// CSubScriptResultParamsDB DAO recordset

class CSubScriptResultParamsDB : public CDisconnectedADORecordset
{
public:
	BOOL GetSubScriptResultParams(long nSubScriptResultID, CParameterMap &map);
	BOOL AddRecord(long nSubScriptResultID, const CString &strParamName, const CString &strParamValue);
	CSubScriptResultParamsDB();
	virtual ~CSubScriptResultParamsDB();
	long	m_SubScript_Result_ID;
	CString	m_SubScript_Parameter_Name;
	CString	m_SubScript_Parameter_Value;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSubScriptResultParamsDB)
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

#endif // !defined(AFX_SUBSCRIPTRESULTPARAMSDB_H__569BB76F_2501_4F15_896D_3BA82218CD06__INCLUDED_)
