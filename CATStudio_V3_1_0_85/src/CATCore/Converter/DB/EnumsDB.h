#pragma once
#include <afxtempl.h>
#include <map>
#include "adorecordsetex.h"


#ifdef _CATCORE_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

class DLL_EXPORT CEnumsDB :
	public CADORecordsetEx
{
public:
	CEnumsDB(CADODatabase* pDatabase = NULL);
	
	CString m_strEnumName;
	CString m_strVarName;
	long    m_lVarValue;
	CString m_strDBFile;

	BOOL LoadToMap(std::map<CString,UINT>& map);
	BOOL GetEnumValue(const CString &strEnumType, const CString &strEnum, long &nEnumValue);
	BOOL GetMinEnumValue(const CString &strEnumType, long &nMaxEnumValue);
	BOOL GetMaxEnumValue(const CString &strEnumType, long &nMinEnumValue);

//#if !MICL_BUILD
	BOOL LoadToMap(const CString &strEnumName, std::multimap<long,CString> &map);
//#endif

	BOOL Open(LPCTSTR lpstrExec = _T(""), int nOption = CADORecordset::openQuery);

	void AddRecord(CString strEnumName, CString strVarName, long lVarValue);
	void SetDBName(const CString strDBFile);

public:
	virtual CString GetDefaultDBName();		// Default database name
	virtual CString GetDefaultSQL();		// Default SQL for Recordset
	virtual void DoFieldExchange(BOOL bLoad = TRUE);

};


class  DLL_EXPORT CAppEnumsDB : public CEnumsDB
{
public:
	virtual CString GetDefaultDBName();

	static BOOL LoadToMap(CMap<CString,LPCTSTR,UINT,UINT>& map);
	static BOOL GetEnumValue(const CString &strEnumType, const CString &strEnum, long &nEnumValue);
};

class DLL_EXPORT CCpEnumsDB : public CADORecordsetEx
{
public:
	CCpEnumsDB(CADODatabase* pDatabase = NULL);

	CString m_strEnumName;
	CString m_strVarName;
	CString m_strDescription;
	long    m_lVarValue;

	CString m_strDBFile;

	void AddRecord(CString strEnumName, CString strVarName, long lVarValue, CString strDescription);
	void SetDBName(const CString strDBFile);

public:
	virtual CString GetDefaultDBName();		// Default database name
	virtual CString GetDefaultSQL();		// Default SQL for Recordset
	virtual void DoFieldExchange(BOOL bLoad = TRUE);
};
