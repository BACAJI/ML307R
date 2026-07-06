#pragma once
#include "adorecordsetex.h"
#include <afxtempl.h>
#include <map>

#ifdef _CATCORE_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

struct SignalTableRecord 
{
	CString m_SignalName;
	unsigned long	m_SignalVal;

	SignalTableRecord(const CString &sigName = _T(""), long sigVal = 0) 
	{ 
		m_SignalName = sigName; 
		m_SignalVal = sigVal;
	}

	SignalTableRecord(SignalTableRecord &rec) 
	{
		m_SignalName = rec.m_SignalName;
		m_SignalVal = rec.m_SignalVal;
	}

	void operator= (SignalTableRecord &rec)
	{
		m_SignalName = rec.m_SignalName;
		m_SignalVal = rec.m_SignalVal;
	}

};

class DLL_EXPORT CSignalTableDB : public CADORecordsetEx
{
public:
	CSignalTableDB(CADODatabase* pDatabase = NULL);

	CString m_SignalName;
	unsigned long	m_SignalVal;
	CString m_strDBFile;

	BOOL LoadToMap(std::map<DWORD, CString>& map);
	BOOL LoadToMap(std::map<CString, DWORD>& map);
	void SetDBName(const CString strDBFile);
	void AddRecord(CString strVarName, long lVarValue);
	
	/*static*/ BOOL LoadToMap(CMap</*LPCTSTR*/CString, LPCTSTR, DWORD, DWORD>& map);
// 	BOOL LoadToList(CList<SignalTableRecord, SignalTableRecord&>& list);

	
public:
	virtual CString GetDefaultDBName();		// Default database name
	virtual CString GetDefaultSQL();		// Default SQL for Recordset
	virtual void DoFieldExchange(BOOL bLoad = TRUE);

};