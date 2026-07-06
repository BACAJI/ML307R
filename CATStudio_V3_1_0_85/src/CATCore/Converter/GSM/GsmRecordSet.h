// GsmRecordSet.h: interface for the CGsmRecordSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GSMRECORDSET_H__2FC8E4DF_3128_4BFC_A775_ECE23B485B90__INCLUDED_)
#define AFX_GSMRECORDSET_H__2FC8E4DF_3128_4BFC_A775_ECE23B485B90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>
#include "..\DB\AdoRecordsetEx.h"
#include "..\..\BasicComponents\StringArrayEx.h"


class CGsmRecordSet : public CADORecordsetEx    
{
public:
	CGsmRecordSet(CADODatabase* pdb = NULL);
	virtual ~CGsmRecordSet();

	BOOL GetCurrentAppPath(CString& strAppPath);

	BOOL CacheTable( CMap<DWORD, DWORD, BOOL, BOOL>& IsGsmMsg, 
					 CMap <DWORD, DWORD, CStringArrayEx, CStringArrayEx&>& GsmMsgMap);
	BOOL Open(LPCTSTR lpstrExec = _T(""), int nOption = CADORecordset::openQuery);

	LONG    m_lgSignalId,
			m_lgProtDiscr,
			m_lgExtendType,
			m_lgMsgType;
	CString m_strStrType,
		    m_strStrName;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSignalIdSet)
	public:
	virtual CString GetDefaultDBName();		// Default database name
	virtual CString GetDefaultSQL();		// Default SQL for Recordset
	virtual void DoFieldExchange(BOOL bLoad = TRUE);
	//}}AFX_VIRTUAL

};

#endif // !defined(AFX_GSMRECORDSET_H__2FC8E4DF_3128_4BFC_A775_ECE23B485B90__INCLUDED_)
