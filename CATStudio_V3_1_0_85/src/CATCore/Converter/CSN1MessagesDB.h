// CSN1MessagesDB.h: interface for the CCSN1MessagesDB class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CSN1MESSAGESDB_H__12498604_A67B_4421_851B_61988E820CC4__INCLUDED_)
#define AFX_CSN1MESSAGESDB_H__12498604_A67B_4421_851B_61988E820CC4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>
#include "DB\ADORecordsetEx.h"
#include "CSN1MsgNameAndStruct.h"

class CCSN1MessagesDB : public CADORecordsetEx  
{
public:
	CCSN1MessagesDB(CADODatabase* pDatabase = NULL);
	virtual ~CCSN1MessagesDB();

	CString	m_Signal_Name;
	CString	m_SignalType;
	CString	m_Direction;
	CString	m_Param_Path_1;
	CString m_Param_Path_2;

	BOOL GetCurrentAppPath(CString& strAppPath);

public:
	virtual CString GetDefaultDBName ();		// Default database name
	virtual CString GetDefaultSQL ();		// Default SQL for Recordset
	virtual void DoFieldExchange (BOOL bLoad = TRUE);
	
public:
	static BOOL LoadToArr (CArray<CCSN1MsgDetails, CCSN1MsgDetails&> &arr);

private:
	static SignalsType_Enum StrToSignalType(CString strSignalType);
	static SignalsDirection_Enum StrToSignalsDirection(CString strSignalsDirection);
};

#endif // !defined(AFX_CSN1MESSAGESDB_H__12498604_A67B_4421_851B_61988E820CC4__INCLUDED_)

