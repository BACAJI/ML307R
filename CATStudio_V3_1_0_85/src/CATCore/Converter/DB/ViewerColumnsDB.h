#if !defined(AFX_VIEWERCOLUMNSDB_H__1000A72C_949A_4D4E_B0CD_A0CFF4236239__INCLUDED_)
#define AFX_VIEWERCOLUMNSDB_H__1000A72C_949A_4D4E_B0CD_A0CFF4236239__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "..\..\CATCore\CATCore\Modules\Converter\DB\AdoRecordsetEx.h"
#include "ADORecordsetEx.h"

#ifdef _CATCORE_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

class DLL_EXPORT CViewerColumnsDB : public CADORecordsetEx
{
public:
	CViewerColumnsDB(CADODatabase* pDatabase = NULL);

	CString m_strDBName;

	CString m_ColumnName;
	CString m_GroupName;
	int		m_ColumnIndex;
	int		m_ColumnWidth;

public:
	void SetDBName(CString strDBName);

	static BOOL InitTree(CTreeCtrl *pTree);
	static BOOL GetColumnsList(CStringList *pList);

	public:
	virtual CString GetDefaultDBName();		// Default database name
	virtual CString GetDefaultSQL();		// Default SQL for Recordset
	virtual void DoFieldExchange(BOOL bLoad = TRUE);


};


#endif 