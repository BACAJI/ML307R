#pragma once

#include "adorecordsetex.h"
#include "NvmDB.h"
#include "./../DiagCommDef.h"
#include <map>


#ifdef _CATCORE_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

class DLL_EXPORT CSignalsDB : public CADORecordsetEx
{
public:
	CSignalsDB(CADODatabase* pdb = NULL);

	CString	m_ItemName;//
	CString	m_ParentName;
	int 	m_ParmArray;//
	CString	m_ParmName;//
	CString	m_ParmType;//
	CString	m_TransferType;//

	CString m_strNVMDB;

	void SetDBName(CString strNVM);

	void AddRecord(CString strItemName, CString strParentName, CString strParmName, 
					CString strParmType, CString strTransferType, int nParmArray);


public:
	virtual CString GetDefaultDBName();		// Default database name
	virtual CString GetDefaultSQL();		// Default SQL for Recordset
	virtual void DoFieldExchange(BOOL bLoad = TRUE);

};
