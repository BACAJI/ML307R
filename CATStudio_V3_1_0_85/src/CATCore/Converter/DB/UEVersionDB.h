#if !defined(AFX_UEVERSIONDB_H__710279D9_C399_4D8A_A7FC_E2F8776EF275__INCLUDED_)
#define AFX_UEVERSIONDB_H__710279D9_C399_4D8A_A7FC_E2F8776EF275__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UEVersionDB.h : header file
//

#include "./AdoRecordsetEx.h"


/////////////////////////////////////////////////////////////////////////////
// CUEVersionDB DAO recordset


#ifdef _CATCORE_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

class  DLL_EXPORT CUEVersionDB : public CADORecordsetEx
{
public:
	CString GetUEVersion();
	BOOL SetUEVersion(long lVer);
	long GetDBVersion();
	CUEVersionDB(CADODatabase* pDatabase = NULL);
	void AddRecord(long lVer);
	void SetDBName(const CString& strDBFile);

	CString m_strDBFile;
	long m_UEVersion;
	int  m_IntSize;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUEVersionDB)
	public:
	virtual CString GetDefaultDBName();		// Default database name
	virtual CString GetDefaultSQL();		// Default SQL for Recordset
	virtual void DoFieldExchange(BOOL bLoad = TRUE);
	//}}AFX_VIRTUAL

};

class  DLL_EXPORT CUEVersionAppDB : public CADORecordsetEx
{
public:
	CString GetUEVersion();
	BOOL SetUEVersion(long lVer);
	long GetDBVersion();
	CUEVersionAppDB(CADODatabase* pDatabase = NULL);
	void AddRecord(long lVer);
	void SetDBName(const CString& strDBFile);

	CString m_strDBFile;
	long m_UEVersion;
	int  m_IntSize;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUEVersionDB)
	public:
	virtual CString GetDefaultDBName();		// Default database name
	virtual CString GetDefaultSQL();		// Default SQL for Recordset
	virtual void DoFieldExchange(BOOL bLoad = TRUE);
	//}}AFX_VIRTUAL

};

class DLL_EXPORT CNvmDbVersion : public CADORecordsetEx
{
public:
	BOOL SetUEVersion(long lVer);
	long GetDBVersion();
	CNvmDbVersion(CADODatabase* pDatabase = NULL);
	void AddRecord(long lVer);
	void SetDBName(const CString& strDBFile);

	CString m_strDBFile;
	long	m_DbVersion;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNvmDbVersion)
	public:
	virtual CString GetDefaultDBName();		// Default database name
	virtual CString GetDefaultSQL();		// Default SQL for Recordset
	virtual void DoFieldExchange(BOOL bLoad = TRUE);
	//}}AFX_VIRTUAL

};


class DLL_EXPORT CNvmAppDbVersion : public CADORecordsetEx
{
public:
	BOOL SetUEVersion(long lVer);
	long GetDBVersion();
	CNvmAppDbVersion(CADODatabase* pDatabase = NULL);
	void AddRecord(long lVer);
	void SetDBName(const CString& strDBFile);

	CString m_strDBFile;
	long	m_DbVersion;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNvmDbVersion)
	public:
	virtual CString GetDefaultDBName();		// Default database name
	virtual CString GetDefaultSQL();		// Default SQL for Recordset
	virtual void DoFieldExchange(BOOL bLoad = TRUE);
	//}}AFX_VIRTUAL

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UEVERSIONDB_H__710279D9_C399_4D8A_A7FC_E2F8776EF275__INCLUDED_)
