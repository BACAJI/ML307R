// ADORecordsetEx.h: interface for the CADORecordsetEx class.
//
//////////////////////////////////////////////////////////////////////
/*--------------------------------------------------------------------------------------------------------------------

 (C) Copyright 2006,2007 Marvell Semiconductor Israel Ltd. All Rights Reserved  

-------------------------------------------------------------------------------------------------------------------*/


#if !defined(AFX_ADORECORDSETEX_H__36D3408F_F125_41A3_85A4_198568AAE846__INCLUDED_)
#define AFX_ADORECORDSETEX_H__36D3408F_F125_41A3_85A4_198568AAE846__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Ado.h"

#ifdef _CATCORE_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif
class DLL_EXPORT CADORecordsetEx : public CADORecordset  
{
public:
	CADORecordsetEx(CADODatabase *pDB = NULL);
	virtual ~CADORecordsetEx();

	virtual CString GetDefaultDBName()=0;
	virtual CString GetDefaultSQL()=0;
	virtual void DoFieldExchange(BOOL bLoad = TRUE)=0;
	
	BOOL Open(LPCTSTR lpstrExec = _T(""), int nOption = CADORecordset::openQuery);

	BOOL AddNew();
	BOOL Update();

	BOOL Find(LPCTSTR lpFind, int nSearchDirection = CADORecordset::searchForward);
	BOOL FindFirst(LPCTSTR lpFind);
	BOOL FindLast(LPCTSTR lpFind);
	BOOL FindNext(LPCTSTR lpFind);
	BOOL FindPrev(LPCTSTR lpFind);
	BOOL FindNext();

	void MoveFirst();
	void MoveNext();
	void MovePrevious();
	void MoveLast();
	void MovePrev() { MovePrevious(); }	// For DAO Compatibility
	void Move(long nMove);

	void SetAbsolutePosition(int nPosition);

	BOOL SetFilter(LPCTSTR strFilter);

	CString m_strSort;
	CString m_strFilter;

private:
	BOOL m_bDeleteDB;

protected:
	CString BuildSQL();
	CADODatabase *m_pAdoDb;
	CString m_strExecute;

};

#endif // !defined(AFX_ADORECORDSETEX_H__36D3408F_F125_41A3_85A4_198568AAE846__INCLUDED_)
