#pragma once

#include "adorecordsetex.h"
#include "./../DiagCommDef.h"
#include <map>

#ifdef _CATCORE_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

class DLL_EXPORT CEnumsTitleDB : public CADORecordsetEx
{
public:
	CEnumsTitleDB(CADODatabase* pDatabase = NULL);

	void SetDBName(CString strDB);
	void AddRecord(CString strEnumName, CString strDescription, BOOL bIsAutoDoc, CString strCategory);
	
public:
	virtual CString GetDefaultDBName(); 
	virtual CString GetDefaultSQL();  
	virtual void DoFieldExchange(BOOL bLoad = TRUE); 


public:
	CString m_EnumName;
	CString m_Description;
	BOOL m_IsAutoDoc;
	CString m_Category;
	CString m_strDBPath;
};

class DLL_EXPORT CAppEnumsTitleDB : public CEnumsTitleDB
{
public:
	virtual CString GetDefaultDBName();
};