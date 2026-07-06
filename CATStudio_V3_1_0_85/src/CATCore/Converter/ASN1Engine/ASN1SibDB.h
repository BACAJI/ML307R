// ASN1SibDB.h: interface for the CASN1SibDB class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ASN1SIBDB_H__57259E75_4C1B_4E01_ADE7_4750981D8CCE__INCLUDED_)
#define AFX_ASN1SIBDB_H__57259E75_4C1B_4E01_ADE7_4750981D8CCE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>
#include "..\..\converter\db\AdoRecordsetEx.h"
#include "Asn1MsgNameAndStruct.h"

class CASN1SibDB : public CADORecordsetEx  
{
public:
	CASN1SibDB (CADODatabase* pDatabase = NULL);

	short m_Asn1ID;
	CString m_MessageName;
	CString m_MessageStruct;

public:
	virtual CString GetDefaultDBName ();		// Default database name
	virtual CString GetDefaultSQL ();		// Default SQL for Recordset
	virtual void DoFieldExchange (BOOL bLoad = TRUE);

public:
	static BOOL LoadToMap (CMap<WORD, WORD, CASN1MsgNameAndStruct, CASN1MsgNameAndStruct&> &map);

};

#endif // !defined(AFX_ASN1SIBDB_H__57259E75_4C1B_4E01_ADE7_4750981D8CCE__INCLUDED_)
