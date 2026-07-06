#if !defined(AFX_DSPRECORDSDB_H__3A5B1922_9217_4BD1_848D_72FDFC8849E1__INCLUDED_)
#define AFX_DSPRECORDSDB_H__3A5B1922_9217_4BD1_848D_72FDFC8849E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DSPRecordsDB.h : header file
//

#include "DSPRecord.h"
#include "DB\AdoRecordsetEx.h"


#define TYPE_REPORTS	0
#define TYPE_COMMANDS	1

#define SORT_BY_OPCODE	0
#define SORT_BY_NAME	1


/////////////////////////////////////////////////////////////////////////////
// CDSPRecordsDB DAO recordset

#ifdef _CATCORE_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

class DLL_EXPORT CDSPRecordsDB : public CADORecordsetEx
{
public:
	CDSPRecordsDB(CADODatabase* pDatabase = NULL);

	CString m_SetID;
	CString m_SubOpcode;
	CString m_SetName;
	CString m_SubOpName;

	BOOL GetCurrentAppPath(CString& strAppPath);
	
public:
	//static CString m_strDBName;

public:
	//static void SetDBName(CString strDBName);
	static void InitTree(CTreeCtrl *pTreeCtrl);
	static void	InitReportsTree(CTreeCtrl *pTreeCtrl);
	static void InitCommandsTree(CTreeCtrl *pTreeCtrl, int sortMode = SORT_BY_NAME);
	static BOOL LoadToMap(CDSPRecordMap &map, int type = TYPE_COMMANDS);
	static BOOL LoadToMapEx(MapOpName2DSPItem& map, int type = TYPE_COMMANDS);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDSPRecordsDB)
	public:
	virtual CString GetDefaultDBName();		// Default database name
	virtual CString GetDefaultSQL();		// Default SQL for Recordset
	virtual void DoFieldExchange(BOOL bLoad = TRUE);
	//}}AFX_VIRTUAL

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DSPRECORDSDB_H__3A5B1922_9217_4BD1_848D_72FDFC8849E1__INCLUDED_)
