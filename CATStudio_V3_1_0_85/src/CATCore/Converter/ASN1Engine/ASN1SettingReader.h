// ASN1SettingReader.h: interface for the CASN1SettingReader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ASN1SETTINGREADER_H__2471898E_D3B1_4C65_B4C6_799643DAE389__INCLUDED_)
#define AFX_ASN1SETTINGREADER_H__2471898E_D3B1_4C65_B4C6_799643DAE389__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>
#include "..\..\Converter\db\AdoRecordsetEx.h"

class CASN1SettingReader : public CADORecordsetEx  
{
public:
	CASN1SettingReader (CADODatabase* pDatabase = NULL);

	CString m_EntryName;
	CString m_EntryVal;

	virtual CString GetDefaultDBName ();		// Default database name
	virtual CString GetDefaultSQL ();		// Default SQL for Recordset
	virtual void DoFieldExchange (BOOL bLoad = TRUE);

	BOOL GetValueWhileDbIsOpen (const CString &strEntryName, CString &strEntryVal);

	static BOOL GetAsn1SettingValue (const CString &strEntryName, CString &strEntryVal);
	static BOOL SetAsn1SettingValue (const CString &strEntryName, const CString &strEntryVal);
};

#endif // !defined(AFX_ASN1SETTINGREADER_H__2471898E_D3B1_4C65_B4C6_799643DAE389__INCLUDED_)
