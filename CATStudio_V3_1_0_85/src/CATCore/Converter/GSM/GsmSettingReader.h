// GSMSettingReader.h: interface for the CGSMSettingReader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GSMSETTINGREADER_H__2471898E_D3B1_4C65_B4C6_799643DAE389__INCLUDED_)
#define AFX_GSMSETTINGREADER_H__2471898E_D3B1_4C65_B4C6_799643DAE389__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>
#include "..\DB\AdoRecordsetEx.h"

class CGSMSettingReader : public CADORecordsetEx  
{
public:
	CGSMSettingReader (CADODatabase* pDatabase = NULL);

	CString m_EntryName;
	CString m_EntryVal;

	virtual CString GetDefaultDBName ();		// Default database name
	virtual CString GetDefaultSQL ();		// Default SQL for Recordset
	virtual void DoFieldExchange (BOOL bLoad = TRUE);

	BOOL GetCurrentAppPath(CString& strAppPath);
	BOOL GetValueWhileDbIsOpen (const CString &strEntryName, CString &strEntryVal);

	static BOOL GetSettingValue (const CString &strEntryName, CString &strEntryVal);
	static BOOL SetSettingValue (const CString &strEntryName, const CString &strEntryVal);
};

#endif // !defined(AFX_GSMSETTINGREADER_H__2471898E_D3B1_4C65_B4C6_799643DAE389__INCLUDED_)
