// MonitorParamsDB.h: interface for the CMonitorParamsDB class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MONITORPARAMSDB_H__1B1A0754_1408_4FA8_8384_B6D4C1FDFF1C__INCLUDED_)
#define AFX_MONITORPARAMSDB_H__1B1A0754_1408_4FA8_8384_B6D4C1FDFF1C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "adorecordsetex.h"
#include "./../DiagCommDef.h"
#include <map>


#ifdef _CATCORE_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

class DLL_EXPORT CMonitorParamsDB : public CADORecordsetEx  
{
public:
	CMonitorParamsDB(CADODatabase* pdb = NULL);

	long	m_ID;
	CString	m_Description;
	CString	m_Type;
	CString	m_SubCategory;
	BOOL 	m_IsModifiable;
	
	CString m_strMonitorDB;

	void SetDBName(CString strMonitor);

	void AddRecord(int nID, CString strDescription, CString strType, CString strSubCategory, BOOL bIsModifiable); 

public:
	virtual CString GetDefaultDBName();		// Default database name
	virtual CString GetDefaultSQL();		// Default SQL for Recordset
	virtual void DoFieldExchange(BOOL bLoad = TRUE);
};


class DLL_EXPORT CAppMonitorParamsDB : public CMonitorParamsDB
{
public:
	virtual CString GetDefaultDBName();		// Default database name

};  

#endif 
