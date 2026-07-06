// UeHwComponentsDB.h: interface for the CUeHwComponentsDB class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UEHWCOMPONENTSDB_H__BA7BA3EC_F6F7_48B7_89CA_3EFFDED1759B__INCLUDED_)
#define AFX_UEHWCOMPONENTSDB_H__BA7BA3EC_F6F7_48B7_89CA_3EFFDED1759B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxmt.h>
#include "../../Converter/DB/DisconnectedADORecordset.h"


class CUeHwComponentsDB : public CDisconnectedADORecordset  
{
public:
	CUeHwComponentsDB();
	virtual ~CUeHwComponentsDB();
	long m_Component_Serial_ID;
	long m_Batch_Result_ID;
	long m_Batch_Iteration;
	CString m_Conf_Name;
	CString m_Board_Serial_Number;
	CString m_Board_Name;
	CString m_Board_Version;
	CString m_Board_ECO;
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUeHwComponentsDB)
	public:
	virtual CString GetDefaultDBName();		// Default database name
	virtual CString GetDefaultSQL();		// Default SQL for Recordset
	virtual void DoFieldExchange(BOOL bLoad = TRUE); 
	//}}AFX_VIRTUAL

private:
	CCriticalSection m_cSection;
	friend class CTestEngine;

};

#endif // !defined(AFX_UEHWCOMPONENTSDB_H__BA7BA3EC_F6F7_48B7_89CA_3EFFDED1759B__INCLUDED_)
