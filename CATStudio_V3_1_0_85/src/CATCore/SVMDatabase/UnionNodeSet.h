#if !defined(AFX_UNIONNODESET_H__371E77A7_3BBA_4DCD_AB62_4304EC44EE61__INCLUDED_)
#define AFX_UNIONNODESET_H__371E77A7_3BBA_4DCD_AB62_4304EC44EE61__INCLUDED_



#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// UnionsDB.h : header file
//

#include "BaseNodeSet.h"

/////////////////////////////////////////////////////////////////////////////
// CUnionNodeSet DAO recordset

class DLL_EXPORT CUnionNodeSet : public CBaseNodeSet
{
public:
	CUnionNodeSet(int nDeviceIndex,int nStrType,CADODatabase* pDatabase = NULL);	

	BOOL CacheTable(CMapStringToOb& UnionMap);
	BOOL CacheTableTxt(CMapStringToOb& UnionMap);
	
	bool Open(LPCTSTR lpstrExec = _T(""), int nOption = CADORecordset::openQuery);
	virtual int GetDbIdx(){ return CSvmDb::kDbComm;};
	
	bool GetUnionVars(CString strFilter, CStringList& lstCommand);
	bool GetUnionVarsTxt(CString strFilter, CStringList& lstCommand);
	void ParseTxtRec(CString strTmp, int strType = CSvmDb::kNone);

	CString m_strUnionName;
	CString m_strVarName;
	CString m_strTransferType;
	CString m_strVarType;
	long    m_lVarArrayLen;
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUnionNodeSet)
	public:
	
	virtual CString GetDefaultSQL();		// Default SQL for Recordset
	virtual void DoFieldExchange(BOOL bLoad = TRUE);
	//}}AFX_VIRTUAL
};


class CAppUnionNodeSet : public CUnionNodeSet
{
public:
	CAppUnionNodeSet(int nDeviceIndex,int nStrType,CADODatabase* pDatabase = NULL)
		:CUnionNodeSet(nDeviceIndex,nStrType,pDatabase){m_strDBFile=_T("");}	
	
	virtual int GetDbIdx(){ return CSvmDb::kDbApp;};
	virtual CString GetDefaultSQL(){return _T("[Unions]");};
};


class CAsn1UnionNodeSet : public CUnionNodeSet
{
public:
	CAsn1UnionNodeSet(int nDeviceIndex,int nStrType,CADODatabase* pDatabase = NULL)
		:CUnionNodeSet(nDeviceIndex,nStrType,pDatabase){}	

	virtual int GetDbIdx(){ return CSvmDb::kDbAsn1;};

	virtual CString GetDefaultDBName()
	{
  		TCHAR szPath[MAX_PATH] = {0};
  		GetModuleFileName( NULL, szPath, MAX_PATH );
  		(_tcsrchr(szPath, _T('\\')))[1] = 0;
 		return CString(szPath) + _T("\\DB\\asn1Messages.mdb");
	}

	virtual CString GetDefaultSQL(){return _T("[Asn1Unions]");};
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UNIONNODESET_H__371E77A7_3BBA_4DCD_AB62_4304EC44EE61__INCLUDED_)
