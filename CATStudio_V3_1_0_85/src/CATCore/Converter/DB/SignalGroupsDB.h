#pragma once
#include "adorecordsetex.h"
#include <afxtempl.h>
#include <map>

#ifdef _CATCORE_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif


class DLL_EXPORT CSignalGroupsDB : public CADORecordsetEx
{
public:
	CSignalGroupsDB(CADODatabase* pDatabase = NULL);

	CString m_strGroupName;
	unsigned long 	m_nGroupBase; 

	CString m_strDBFile;
	void SetDBName(const CString strDBName);
	void AddRecord(CString strGroupName, unsigned long ulGroupBase);
	BOOL LoadSignalGroupMapbyBase(std::map<long, CString>& map);
public:
	virtual CString GetDefaultDBName();		// Default database name
	virtual CString GetDefaultSQL();		// Default SQL for Recordset
	virtual void DoFieldExchange(BOOL bLoad = TRUE);

};
