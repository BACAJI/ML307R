#if !defined(AFX_SIGNALIDSET_H__E75EDB0D_ADEF_4906_A40F_F8A8270EEAA9__INCLUDED_)
#define AFX_SIGNALIDSET_H__E75EDB0D_ADEF_4906_A40F_F8A8270EEAA9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SignalIDSet.h : header file
//
#include <AFXTEMPL.H>
#include "../Converter/DB/AdoRecordsetEx.h"
#include "svmnode.h"

/////////////////////////////////////////////////////////////////////////////
// CSignalIdSet DAO recordset
 
class CSignalIdSet : public CADORecordsetEx
{
public:
	CSignalIdSet(CADODatabase* pdb = NULL);
	//BOOL CacheTable(CMapStringToOb& SignalMap);
	bool Open(LPCTSTR lpstrExec = _T(""), int nOption = CADORecordset::openQuery);
	void SetDBName(const CString& strDBFile);

	CString m_strSignalName,
			m_strTransferType;
	int		m_nSignalOpCode;
	CString m_strDBFile;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSignalIdSet)
	public:
	virtual CString GetDefaultDBName();		// Default database name
	virtual CString GetDefaultSQL();		// Default SQL for Recordset
	virtual void DoFieldExchange(BOOL bLoad = TRUE);
	//}}AFX_VIRTUAL

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SignalIdSet_H__E75EDB0D_ADEF_4906_A40F_F8A8270EEAA9__INCLUDED_)
