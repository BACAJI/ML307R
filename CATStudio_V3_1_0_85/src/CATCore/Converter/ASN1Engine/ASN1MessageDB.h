// ASN1MessageDB.h: interface for the CASN1MessageDB class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ASN1MESSAGEDB_H__41A5FDEB_9638_435D_B22B_972F19631B68__INCLUDED_)
#define AFX_ASN1MESSAGEDB_H__41A5FDEB_9638_435D_B22B_972F19631B68__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>
#include "..\..\converter\db\AdoRecordsetEx.h"
#include "Asn1MsgNameAndStruct.h"

class CASN1MessageDB : public CADORecordsetEx  
{
public:
	CASN1MessageDB (CADODatabase* pDatabase = NULL);

	short m_RadioBearer;
	short m_Direction;
	short m_TransportChannel;
	short m_Asn1ID;
	CString m_MessageName;
	CString m_MessageStruct;

public:
	virtual CString GetDefaultDBName ();		// Default database name
	virtual CString GetDefaultSQL ();		// Default SQL for Recordset
	virtual void DoFieldExchange (BOOL bLoad = TRUE);

public:
	static BOOL LoadToMap (CMap<UINT64, UINT64, CASN1MsgNameAndStruct, CASN1MsgNameAndStruct&> &map);
};

#endif // !defined(AFX_ASN1MESSAGEDB_H__41A5FDEB_9638_435D_B22B_972F19631B68__INCLUDED_)
