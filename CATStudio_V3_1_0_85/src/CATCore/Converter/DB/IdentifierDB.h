#pragma once

#include "adorecordsetex.h"
#include "./../DiagCommDef.h"
#include <map>


#ifdef _CATCORE_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

class DLL_EXPORT CIdentifierDB : public CADORecordsetEx
{
public:
	CIdentifierDB(CADODatabase* pdb = NULL);

	CString	m_strUnionName;
	CString	m_strIdentifierName;

	CString m_strNVMDB;

	void SetDBName(CString strNVM);

	void AddRecord(CString strUnionName, CString strIdentifierName);


public:
	virtual CString GetDefaultDBName();		// Default database name
	virtual CString GetDefaultSQL();		// Default SQL for Recordset
	virtual void DoFieldExchange(BOOL bLoad = TRUE);

};
