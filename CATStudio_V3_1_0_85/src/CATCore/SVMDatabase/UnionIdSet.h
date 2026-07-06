#if !defined(AFX_UNIONIDSET_H__E75EDB0D_ADEF_4906_A40F_F8A8270EEAA9__INCLUDED_)
#define AFX_UNIONIDSET_H__E75EDB0D_ADEF_4906_A40F_F8A8270EEAA9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UnionIdentifiersDB.h : header file
//

#include "BaseNodeSet.h"

/////////////////////////////////////////////////////////////////////////////
// CUnionIdSet DAO recordset

class CUnionIdSet : public CBaseNodeSet
{
public:
	CUnionIdSet(int nDeviceIndex,int nStrType,CADODatabase* pdb = NULL);
	void CacheTableTxt(CMapStringToString& SvmUnionsId);
	void CacheTable(CMapStringToString& SvmUnionsId);
	bool Open(LPCTSTR lpstrExec = _T(""), int nOption = CADORecordset::openQuery);
	int  GetDbType(){return CSvmDb::kDbComm;}

	virtual void ParseTxtRec( CString strTempRec, int strType = CSvmDb::kNone );

	//	virtual void SetDBName(const CString& strFile);

	CString m_strUnionName;
	CString m_strIdentifiersName;
//	CString m_strDBFile;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUnionIdSet)
	public:
//	virtual CString GetDefaultDBName();		// Default database name
	virtual CString GetDefaultSQL();		// Default SQL for Recordset
	virtual void DoFieldExchange(BOOL bLoad = TRUE);
	//}}AFX_VIRTUAL

};

class CAppUnionIdSet : public CUnionIdSet
{
public:
	CAppUnionIdSet(int nDeviceIndex,int nStrType,CADODatabase* pDatabase = NULL)
		:CUnionIdSet(nDeviceIndex,nStrType,pDatabase){m_strDBFile=_T("");}
	
	CString m_strDBFile;
	int  GetDbType(){return CSvmDb::kDbApp;}
// 	virtual void SetDBName(const CString& strFile)
// 	{
// 		m_strDBFile = strFile;
// 	}

// 	virtual CString GetDefaultDBName()
// 	{
// //  		TCHAR szPath[MAX_PATH] = {0};
// //  		GetModuleFileName( NULL, szPath, MAX_PATH );
// //  		(_tcsrchr(szPath, _T('\\')))[1] = 0;
// // 		return CString(szPath) + _T("\\DB\\App_NVM.mdb");
// 		return m_strDBFile;
// 	}
};


class CAsn1UnionIdSet : public CUnionIdSet
{
public:
	CAsn1UnionIdSet(int nDeviceIndex,int nStrType,CADODatabase* pDatabase = NULL)
		:CUnionIdSet(nDeviceIndex,nStrType,pDatabase){}
	
	int  GetDbType(){return CSvmDb::kDbAsn1;}

	virtual CString GetDefaultDBName()
	{
  		TCHAR szPath[MAX_PATH] = {0};
  		GetModuleFileName( NULL, szPath, MAX_PATH );
  		(_tcsrchr(szPath, _T('\\')))[1] = 0;
 		return CString(szPath) + _T("\\DB\\asn1Messages.mdb");
	}

	virtual CString GetDefaultSQL(){return _T("[Asn1UnionsID]");};
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UNIONIDSET_H__E75EDB0D_ADEF_4906_A40F_F8A8270EEAA9__INCLUDED_)
