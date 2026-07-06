// UnionsDB.h: interface for the CUnionsDB class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARAMETERSDB_H__C04E4C77_D12D_4A10_A70A_103A02BB6F3C__INCLUDED_)
#define AFX_PARAMETERSDB_H__C04E4C77_D12D_4A10_A70A_103A02BB6F3C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif 

#include "adorecordsetex.h"
#include "./../DiagCommDef.h"
#include <map>


#ifdef _CATCORE_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

class DLL_EXPORT CParametersDB : public CADORecordsetEx  
{
public:
	CParametersDB(CADODatabase* pdb = NULL);
	
	CString	m_Type;
	CString	m_Value;
	
	CString m_strParaDB;
	void SetDBName(CString strParaDB);

	void AddRecord(CString strType, CString strValue);
	

public:
	virtual CString GetDefaultDBName();		
	virtual CString GetDefaultSQL();		
	virtual void DoFieldExchange(BOOL bLoad = TRUE);

};

class DLL_EXPORT CAppParametersDB : public CParametersDB
{
public:
	virtual CString GetDefaultDBName();		// Default database name
	
};

#endif 
