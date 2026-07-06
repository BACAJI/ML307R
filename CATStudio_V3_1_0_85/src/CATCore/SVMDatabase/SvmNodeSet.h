#if !defined(AFX_SVMNODESET_H__BC47BE91_6377_4522_92C1_83BBF2C06A6D__INCLUDED_)
#define AFX_SVMNODESET_H__BC47BE91_6377_4522_92C1_83BBF2C06A6D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SvmNodeSet.h : header file
//
//#include <afxdao.h>
#include "SvmNode.h"
#include "BaseNodeSet.h"

/////////////////////////////////////////////////////////////////////////////
// CSvmNodeSet DAO recordset

enum EFieldIndices
{
	kIdx			= 0,
	kItemName		= 1,
	kPrntName		= 2,
	kParmArr		= 3,
	kParmName		= 4,
	kParmType		= 5,
	kTrnsType		= 6,
	kDescript		= 7,
	kMaxSetFld		= 7,
	kMaxSetExFld	= 8
};


class CSvmNodeSet : public CBaseNodeSet
{
public:
	//________________________________________________________________________________
	//cache a specific node by name.
	BOOL CacheNode(const CString& nodeName,CList<CSvmObject*>& svmStructTree
					,CObList& svmEnumsList,CObList& svmUnionsList);
	BOOL MoveToNode(const CString& itemName);

	BOOL CacheTable(CMapStringToOb& nvmStructMap,CMapStringToOb& svmEnumsList,CMapStringToOb& svmUnionsList);

	CEnum* FindEnumByName(const CString& enmName,CObList& EnumsList);
	CSvmNode* FindNode(CList<CSvmObject*> &list);
	void CacheTable(CSvmDb* SvmDb);
	void CacheTableTxt(CSvmDb* SvmDb);
	bool Open(LPCTSTR lpstrExec = _T(""), LPCTSTR lpstrFilter = _T(""), int nOption = CADORecordset::openQuery);
	BOOL IsExFormat(){return (kMaxSetExFld==GetFieldCount());}
	void CacheStrName(CSvmDb* pSvmDb);
	CSvmNodeSet(int nDeviceIndex,CADODatabase* pDatabase = NULL);

	void ParseTxtRec(CString strRec, int strType);
	
	virtual int GetStrType(){ return CSvmDb::kComNvm; }
	virtual int GetDbIdx(){ return CSvmDb::kDbComm; }
	virtual LPCTSTR GetStrTypeName(){ return _T("NVM"); }
	
//	virtual void SetDBName(const CString& strFile, const int nFileType);

	BOOL	m_bHasIndex;
	long	m_nIndex,
			m_nMaxIndex;
	CString	m_ItemName;
	CString	m_ParentName;
	int 	m_ParmArray;
	CString	m_ParmName;
	CString	m_ParmType;
	CString	m_TransferType;
	CString m_strDBFile;
	BOOL	m_bOnlyItem;
	///////// Extended Format Field /////////
	CString m_Description;
	/////////////////////////////////////////

// 	int		m_nFileType;
// 	CCacheStrTable/*CStdioFile*/ m_fTxtFile;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSvmNodeSet)
	public:
	//virtual CString GetDefaultDBName();		// Default database name
	virtual CString GetDefaultSQL();		// Default SQL for Recordset
	virtual void DoFieldExchange(BOOL bLoad = TRUE);
	//}}AFX_VIRTUAL

private:
	BOOL IsNodeMember(CSvmNode* pNode,CString& strItem);
	CUnion* FindUnionByName(const CString& unName,CObList& unionList);
	template <class Node>
    void FindByName(Node*& Node, LPCTSTR Name, CMapStringToOb& theMap);
};


class CGkiNodeSet : public CSvmNodeSet  
{
public:
	CGkiNodeSet(int nDeviceIndex,CADODatabase* pDatabase = NULL):CSvmNodeSet(nDeviceIndex,pDatabase){m_strDBFile=_T("");}
	virtual ~CGkiNodeSet(){};

	CString m_strDBFile;
	virtual CString GetDefaultSQL()
	{ 
		if ( m_nFileType == eMDB)
			return _T("[Signals]");
		else
			return _T("Signals");
	}		// Default SQL for Recordset
		
	virtual int GetStrType(){ return CSvmDb::kComGki; }
	virtual int GetDbIdx(){ return CSvmDb::kDbComm; }
	virtual LPCTSTR GetStrTypeName(){ return _T("GKI"); }
// 	virtual void SetDBName(const CString& strFile, const int nFileType)
// 	{
// 		m_strDBFile = strFile;
// 		m_nFileType = nFileType;
// 	}
// 	virtual CString GetDefaultDBName()
// 	{
// 		return m_strDBFile;
// // 		TCHAR szPath[MAX_PATH] = {0};
// // 		GetModuleFileName( NULL, szPath, MAX_PATH );
// // 		(_tcsrchr(szPath, _T('\\')))[1] = 0;
// // 		return CString(szPath) + _T("\\DB\\NVM.mdb");
// 	}
};


 class CAppGkiNodeSet : public CGkiNodeSet  
 {
 public:
	 CAppGkiNodeSet(int nDeviceIndex,CADODatabase* pDatabase = NULL):CGkiNodeSet(nDeviceIndex,pDatabase){m_strDBFile=_T("");}
 	virtual ~CAppGkiNodeSet(){if(IsOpen()) Close();};
	CString m_strDBFile;
// 	virtual void SetDBName(const CString& strFile, const int nFileType)
// 	{
// 		m_strDBFile = strFile;
// 		m_nFileType = nFileType;
// 	}
//  	// Default SQL for Recordset
//  	virtual CString GetDefaultDBName()
//  	{
// //  		TCHAR szPath[MAX_PATH] = {0};
// //  		GetModuleFileName( NULL, szPath, MAX_PATH );
// //  		(_tcsrchr(szPath, _T('\\')))[1] = 0;
// // 		return CString(szPath) + _T("\\DB\\App_NVM.mdb");
// 		return m_strDBFile;
//  	}
 	virtual int GetStrType(){ return CSvmDb::kAppGki; }
 	virtual int GetDbIdx(){ return CSvmDb::kDbApp; }
	virtual LPCTSTR GetStrTypeName(){ return _T("App.GKI"); }
 };


class CAppNvmNodeSet : public CSvmNodeSet  
{
public:
	CAppNvmNodeSet(int nDeviceIndex,CADODatabase* pDatabase = NULL):CSvmNodeSet(nDeviceIndex,pDatabase){}
	virtual ~CAppNvmNodeSet(){if(IsOpen()) Close();};

	CString m_strDBFile;
// 	virtual void SetDBName(const CString& strFile, const int nFileType)
// 	{
// 		m_strDBFile = strFile;
// 		m_nFileType = nFileType;
// 	}
// 	// Default SQL for Recordset
// 	virtual CString GetDefaultDBName()
// 	{
// 		//  		TCHAR szPath[MAX_PATH] = {0};
// 		//  		GetModuleFileName( NULL, szPath, MAX_PATH );
// 		//  		(_tcsrchr(szPath, _T('\\')))[1] = 0;
// 		// 		return CString(szPath) + _T("\\DB\\App_NVM.mdb");
// 		return m_strDBFile;
// 	}
	virtual int GetStrType(){ return CSvmDb::kAppNvm;};
	virtual int GetDbIdx(){ return CSvmDb::kDbApp; }
	virtual LPCTSTR GetStrTypeName(){ return _T("App.NVM"); }
};



class CAsn1NodeSet : public CSvmNodeSet  
{
public:
	CAsn1NodeSet(int nDeviceIndex,CADODatabase* pDatabase = NULL):CSvmNodeSet(nDeviceIndex,pDatabase){}
	virtual ~CAsn1NodeSet(){if(IsOpen()) Close();};
	// Default SQL for Recordset
	virtual CString GetDefaultSQL(){return _T("[Asn1Structs]");}
	virtual CString GetDefaultDBName()
	{
		TCHAR szPath[MAX_PATH] = {0};
		GetModuleFileName( NULL, szPath, MAX_PATH );
		(_tcsrchr(szPath, _T('\\')))[1] = 0;
		return CString(szPath) + _T("\\DB\\asn1Messages.mdb");
	}
	virtual int GetStrType(){ return CSvmDb::kAsn1;};
	virtual int GetDbIdx(){ return CSvmDb::kDbAsn1; }
	virtual LPCTSTR GetStrTypeName(){ return _T("ASN.1"); }
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SVMNODESET_H__BC47BE91_6377_4522_92C1_83BBF2C06A6D__INCLUDED_)
