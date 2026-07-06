#if !defined(AFX_NVMDB_H__A61EDE5A_A7E5_4A9A_AF27_8C357D1FB51A__INCLUDED_)
#define AFX_NVMDB_H__A61EDE5A_A7E5_4A9A_AF27_8C357D1FB51A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NvmDB.h : header file

#include "adorecordsetex.h"
#include "./../DiagCommDef.h"
#include <map>
/////////////////////////////////////////////////////////////////////////////
// CNvmDB ADO recordset

#ifdef _CATCORE_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

class DLL_EXPORT CNvmDB : public CADORecordsetEx
{
public:
	CNvmDB(CADODatabase* pdb = NULL);

	long	m_nIndex;
	CString	m_ItemName;//
	CString	m_ParentName;
	int 	m_ParmArray;//
	CString	m_ParmName;//
	CString	m_ParmType;//
	CString	m_TransferType;//
	CString	m_Description;//

	CString m_strNVMDB;

	void SetDBName(CString strNVM);

	void AddRecord(int nIndex, CString strItemName, CString strParentName, CString strParmName, 
				   CString strParmType, CString strTransferType, int nParmArray, CString strDescription);


	public:
	virtual CString GetDefaultDBName();		// Default database name
	virtual CString GetDefaultSQL();		// Default SQL for Recordset
	virtual void DoFieldExchange(BOOL bLoad = TRUE);

};

class DLL_EXPORT CAppNvmDB : public CNvmDB
{
public:
	virtual CString GetDefaultDBName();		// Default database name

};


class DLL_EXPORT CCpNvmDB : public CADORecordsetEx
{
public:
	CCpNvmDB(CADODatabase* pdb = NULL);

	CString	m_strItemName;//
	CString	m_strParentName;
	int 	m_strParamArray;//
	CString	m_strParamName;//
	CString	m_strParamType;//
	CString	m_strTransferType;//
	CString	m_strDescription;//
	CString m_strCategory;
	CString m_strItemMode;
	CString m_strItemUnits;
	CString m_strDependency;
	BOOL    m_bIsAutoDoc;


	CString m_strNVMDB;

	void SetDBName(CString strNVM);

	void AddCpRecord(CString sttItemName, CString strParentName, CString strParamName,
		CString strParaType, CString strTransferType, int nParamArray, CString strDescription,
		CString strCategory, CString strItemMode, CString strItemUnits, CString strDependecy, BOOL bAutoDoc);
public:
	virtual CString GetDefaultDBName();		// Default database name
	virtual CString GetDefaultSQL();		// Default SQL for Recordset
	virtual void DoFieldExchange(BOOL bLoad = TRUE);

};

#endif