#if !defined(AFX_ENUMNODESET_H__83532901_B92C_49B9_A260_E07578C2FD66__INCLUDED_)
#define AFX_ENUMNODESET_H__83532901_B92C_49B9_A260_E07578C2FD66__INCLUDED_



#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EnumsDB.h : header file
//
//#include "afxtempl.h"
#include "BaseNodeSet.h"

/////////////////////////////////////////////////////////////////////////////
// CEnumNodeSet DAO recordset

class DLL_EXPORT CEnumNodeSet : public CBaseNodeSet
{
public:
	///static BOOL LoadToMap(CMap<CString,LPCSTR,USHORT,USHORT>& map);
	void CacheTable(CMapStringToOb& EnumsList);
	void CacheTableTxt(CMapStringToOb& EnumsList);
	CEnumNodeSet(int nDeviceIndex,int nStrType,CADODatabase* pDatabase = NULL);
	bool Open(LPCTSTR lpstrExec = _T(""), int nOption = CADORecordset::openQuery);
	virtual int GetDbIdx(){ return CSvmDb::kDbComm;};
//	virtual void SetDBName(const CString strDBFile);
	bool GetEnumTuples(CString strFilter, CStringList& lstCommand);
	bool GetEnumTuplesTxt(CString strFilter, CStringList& lstCommand);

	virtual void ParseTxtRec( CString strTempRec, int strType = CSvmDb::kNone );

	CString m_strEnumName;
	CString m_strVarName;
	long    m_lVarValue;
//	CString m_strDBFile;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEnumNodeSet)
	public:
//	virtual CString GetDefaultDBName();		// Default database name
	virtual CString GetDefaultSQL();		// Default SQL for Recordset
	virtual void DoFieldExchange(BOOL bLoad = TRUE);
	//}}AFX_VIRTUAL
};


class CAppEnumNodeSet : public CEnumNodeSet
{
public:
	CAppEnumNodeSet(int nDeviceIndex,int nStrType,CADODatabase* pDatabase = NULL)
		:CEnumNodeSet(nDeviceIndex,nStrType,pDatabase){}	
	virtual int GetDbIdx(){ return CSvmDb::kDbApp;};
//	CString m_strDBFile;

// 	virtual void SetDBName(const CString strDBFile)
// 	{
// 		m_strDBFile = strDBFile;
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

class CAsn1EnumNodeSet : public CEnumNodeSet
{
public:
	CAsn1EnumNodeSet(int nDeviceIndex,int nStrType,CADODatabase* pDatabase = NULL)
		:CEnumNodeSet(nDeviceIndex,nStrType,pDatabase){}	
	virtual int GetDbIdx(){ return CSvmDb::kDbAsn1;};

	virtual CString GetDefaultDBName()
	{
 		CString path;
 		TCHAR szPath[MAX_PATH] = {0};
 		GetModuleFileName( NULL, szPath, MAX_PATH );
 		(_tcsrchr(szPath, _T('\\')))[1] = 0;
		path = CString(szPath) +  _T("\\DB\\asn1Messages.mdb");
		return path;
	}

	virtual CString GetDefaultSQL(){return _T("[Asn1Enums]");};
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ENUMNODESET_H__83532901_B92C_49B9_A260_E07578C2FD66__INCLUDED_)
