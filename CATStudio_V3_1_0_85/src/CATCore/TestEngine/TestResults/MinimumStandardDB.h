#if !defined(AFX_MinimumSTANDARDDB_H__2FE72034_3E4D_4F01_9DEE_73B28A27E8D8__INCLUDED_)
#define AFX_MinimumSTANDARDDB_H__2FE72034_3E4D_4F01_9DEE_73B28A27E8D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MinimumStandardDB.h : header file
//

#include <afxmt.h>
#include "../../Converter/DB/DisconnectedADORecordset.h"

/////////////////////////////////////////////////////////////////////////////
// CMinimumStandardDB DAO recordset

class CATCORE_DLLEXPORT CMinimumStandardDB : public CDisconnectedADORecordset
{
public:
	CMinimumStandardDB();
	virtual ~CMinimumStandardDB();
	CString	m_Minimum_Standard_Name;
	CString	m_ms_Test_Name;
	CString	m_ms_Sub_Test_Name;
	CString	m_Minimum_standard_sub;
	double	m_Min;
	double	m_Max;
	int 	m_Range_ID;
	CString	m_Notes;
	CString	m_Section;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMinimumStandardDB)
	public:
	virtual CString GetDefaultDBName();		// Default database name
	virtual CString GetDefaultSQL();		// Default SQL for Recordset
	virtual void DoFieldExchange(BOOL bLoad = TRUE);
	//}}AFX_VIRTUAL

private:
	CCriticalSection m_cSection;
	friend class CTestEngine;
	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MinimumSTANDARDDB_H__2FE72034_3E4D_4F01_9DEE_73B28A27E8D8__INCLUDED_)
