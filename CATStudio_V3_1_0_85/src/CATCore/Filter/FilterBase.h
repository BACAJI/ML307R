/*--------------------------------------------------------------------------------------------------------------------

 (C) Copyright 2006,2007 Marvell Semiconductor Israel Ltd. All Rights Reserved  

-------------------------------------------------------------------------------------------------------------------*/

 
#if !defined(AFX_FILTERBASE_H__6A88513D_9488_4082_BDE4_3ADCDDF9EE32__INCLUDED_)
#define AFX_FILTERBASE_H__6A88513D_9488_4082_BDE4_3ADCDDF9EE32__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CICATMessage;
class CAllFilters;

class  CFilterBase  
{
public:
	CFilterBase(CAllFilters *pAllFilters);
	virtual ~CFilterBase();

	virtual BOOL CreateDlg(CWnd *pParent) = 0;
	virtual CDialog * GetDlg() = 0;
	virtual BOOL IsPassFilter(CICATMessage *pMessage) = 0;
	virtual void RefreshFilterTree() = 0;
	virtual void RenewFilter() = 0;
	virtual void OpenEntireFilter() = 0;
	virtual void CloseEntireFilter() = 0;
	virtual void UpdateFilterTree() = 0;
	

	// Save and Load functions
	virtual void SaveToFile(BOOL bDefaultFile = false) { ; }
	virtual void LoadFromFile(BOOL bDefaultFile = false) { ; }
	virtual void Load(const CString &strFileName, BOOL bDefaultFile = false) { ; }
	virtual void Save(const CString &strFileName) { ; }
	virtual BYTE * GetFilter(BOOL bCommands = true){return NULL;}
	

	static CString GetFilterFilesDir();

	CAllFilters *m_pAllFilters;
	virtual void RefreshFitler();

};

#endif // !defined(AFX_FILTERBASE_H__6A88513D_9488_4082_BDE4_3ADCDDF9EE32__INCLUDED_)
