// UnionsDB.h: interface for the CUnionsDB class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UNIONSDB_H__C04E4C77_D12D_4A10_A70A_103A02BB6F3C__INCLUDED_)
#define AFX_UNIONSDB_H__C04E4C77_D12D_4A10_A70A_103A02BB6F3C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif 

#include "adorecordsetex.h"
#include "./../DiagCommDef.h"
#include <map>

class CADORecordsetEx;

#ifdef _CATCORE_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

class DLL_EXPORT CUnionsDB : public CADORecordsetEx  
{
public:
	CUnionsDB(CADODatabase* pdb = NULL);
	
	CString	m_ItemName;
	int 	m_ParmArray;
	CString	m_ParmName;
	CString	m_ParmType;
	CString	m_TransferType;
	int		m_IdentifierVal;

	CString m_strUionoDB;
	void SetDBName(CString strDB);
	
	void AddRecord(CString strItemName, CString strParmName, CString strParmType, 
		CString strTransferType, int nParmArray, int nIdentifierVal);
	
	
public:
	virtual CString GetDefaultDBName();		// Default database name
	virtual CString GetDefaultSQL();		// Default SQL for Recordset
	virtual void DoFieldExchange(BOOL bLoad = TRUE);
};

class DLL_EXPORT CAppUnionsDB : public CUnionsDB
{
public:
	virtual CString GetDefaultDBName();		// Default database name
	
};

#endif 