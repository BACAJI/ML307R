// DisconenctedADORecorset.h: interface for the CDisconenctedADORecorset class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DISCONENCTEDADORECORSET_H__4D3E166E_67C3_4177_AAFF_CE399DC135BC__INCLUDED_)
#define AFX_DISCONENCTEDADORECORSET_H__4D3E166E_67C3_4177_AAFF_CE399DC135BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ado.h"

class CATCORE_DLLEXPORT CDisconnectedADORecordset
{
public:
	enum cadoSearchEnum
	{	
		searchForward = 1,
		searchBackward = -1
	};

public:
	CDisconnectedADORecordset();
	virtual ~CDisconnectedADORecordset();
	
	virtual CString GetDefaultDBName()=0;
	virtual CString GetDefaultSQL()=0;
	virtual void DoFieldExchange(BOOL bLoad = TRUE)=0;
	
	bool Open(LPCTSTR lpstrExec = _T(""));
	void Close();
	bool IsOpen();

	DWORD GetRecordCount();
	
	bool UpdateBatch(bool bDisconnect = false);
	bool AddNew();
	bool Edit();
	bool Delete();
	bool Update();

	bool FindFirst(LPCTSTR lpFind);
	bool FindLast(LPCTSTR lpFind);
	bool FindNext(LPCTSTR lpFind);
	bool FindPrev(LPCTSTR lpFind);

	bool IsEof()
		{ return m_spRS->EndOfFile == VARIANT_TRUE; }
	bool IsEOF()
		{ return m_spRS->EndOfFile == VARIANT_TRUE;}
	bool IsBof()
		{ return m_spRS->BOF == VARIANT_TRUE; }
	bool IsBOF()
		{ return m_spRS->BOF == VARIANT_TRUE; }

	void MoveFirst();
	void MoveNext();
	void MovePrevious();
	void MoveLast();
	void MovePrev() { MovePrevious(); }	// For DAO Compatibility
	void Move(long nMove);

	void SetAbsolutePosition(int nPosition);

	bool SetFilter(LPCTSTR strFilter);

	CString m_strSort;
	CString m_strFilter;

	bool GetFieldValue(LPCTSTR lpFieldName, double& dbValue);
	bool GetFieldValue(int nIndex, double& dbValue);
	bool GetFieldValue(LPCTSTR lpFieldName, long& lValue);
	bool GetFieldValue(int nIndex, long& lValue);
	bool GetFieldValue(LPCTSTR lpFieldName, int& nValue);
	bool GetFieldValue(int nIndex, int& nValue);
	bool GetFieldValue(LPCTSTR lpFieldName, short& nValue);
	bool GetFieldValue(int nIndex, short& nValue);
	bool GetFieldValue(LPCTSTR lpFieldName, BYTE& nValue);
	bool GetFieldValue(int nIndex, BYTE& nValue);	
	bool GetFieldValue(LPCTSTR lpFieldName, bool& bValue);
	bool GetFieldValue(int nIndex, bool& bValue);
	bool GetFieldValue(LPCTSTR lpFieldName, CString& strValue, CString strDateFormat = _T(""));
	bool GetFieldValue(int nIndex, CString& strValue, CString strDateFormat = _T(""));
	bool GetFieldValue(LPCTSTR lpFieldName, COleDateTime& time);
	bool GetFieldValue(int nIndex, COleDateTime& time);
	bool GetFieldValue(LPCTSTR lpFieldName, _variant_t& varValue);
	bool GetFieldValue(int nIndex, _variant_t& varValue);

	bool SetFieldValue(int nIndex, CString strValue);
	bool SetFieldValue(LPCTSTR lpFieldName, CString strValue);
	bool SetFieldValue(int nIndex, bool bValue);
	bool SetFieldValue(LPCTSTR lpFieldName, bool bValue);
	bool SetFieldValue(int nIndex, BYTE nValue);
	bool SetFieldValue(LPCTSTR lpFieldName, BYTE nValue);
	bool SetFieldValue(int nIndex, short nValue);
	bool SetFieldValue(LPCTSTR lpFieldName, short nValue);
	bool SetFieldValue(int nIndex, int nValue);
	bool SetFieldValue(LPCTSTR lpFieldName, int nValue);
	bool SetFieldValue(int nIndex, long lValue);
	bool SetFieldValue(LPCTSTR lpFieldName, long lValue);
	bool SetFieldValue(int nIndex, double dblValue);
	bool SetFieldValue(LPCTSTR lpFieldName, double dblValue);
	bool SetFieldValue(int nIndex, COleDateTime time);
	bool SetFieldValue(LPCTSTR lpFieldName, COleDateTime time);
	bool SetFieldValue(int nIndex, _variant_t varValue);
	bool SetFieldValue(LPCTSTR lpFieldName, _variant_t varValue);

	bool GetFieldInfo(LPCTSTR lpFieldName, CADOFieldInfo* fldInfo);
	bool GetFieldInfo(int nIndex, CADOFieldInfo* fldInfo);

private:
	_RecordsetPtr m_spRS;
	_ConnectionPtr m_spConn;

	CString BuildSQL();

	void dump_com_error(_com_error &e);

	bool Find(LPCTSTR lpFind, int nSearchDirection = searchForward); 

	int m_nSearchDirection;
	CString m_strFind;

	bool PutFieldValue(LPCTSTR lpFieldName, _variant_t vtFld);
	bool PutFieldValue(_variant_t vtIndex, _variant_t vtFld);
	bool GetFieldInfo(FieldPtr pField, CADOFieldInfo* fldInfo);
};

#endif // !defined(AFX_DISCONENCTEDADORECORSET_H__4D3E166E_67C3_4177_AAFF_CE399DC135BC__INCLUDED_)
