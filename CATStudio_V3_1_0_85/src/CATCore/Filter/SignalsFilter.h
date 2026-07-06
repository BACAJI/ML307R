/*--------------------------------------------------------------------------------------------------------------------

 (C) Copyright 2006,2007 Marvell Semiconductor Israel Ltd. All Rights Reserved  

-------------------------------------------------------------------------------------------------------------------*/

 
#if !defined(AFX_SIGNALSFILTER_H__AB9F6EF9_87EC_48ED_88A8_67F811F81B52__INCLUDED_)
#define AFX_SIGNALSFILTER_H__AB9F6EF9_87EC_48ED_88A8_67F811F81B52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FilterBase.h"

class CSignalsFilterDlg;
class CICATMessage;
class CAllFilters;


class  CSignalsFilter : public CFilterBase  
{
public:
	CSignalsFilter(CAllFilters *pAllFilters, BOOL bOpenAll, int nDevice);
	virtual ~CSignalsFilter();

	void RenewFilter();
	BOOL IsPassFilter(CICATMessage *pMessage);
 	CDialog * GetDlg();
 	BOOL CreateDlg(CWnd *pParent);
// 	void LoadFromFile(BOOL bDefaultFile = false);
// 	void SaveToFile(BOOL bDefaultFile = false);
	void Save(const CString &strFileName);
	void Load(const CString &strFileName, BOOL bDefaultFile = false);
	void RefreshFilterTree();
	BOOL SetPassFilter(const CString &strSignalName, BYTE bPass);
	void OpenEntireFilter();
	void CloseEntireFilter();
	void UpdateFilterTree();
	BYTE * GetFilter(BOOL bCommands = true){return m_pFilter;}
	
private:
	int m_nDevice;
	CSignalsFilterDlg *m_pSignalsFilterDlg;
	BYTE *m_pFilter;
	DWORD m_nFilterSize;

	friend class CSignalsFilterDlg;

};

#endif // !defined(AFX_SIGNALSFILTER_H__AB9F6EF9_87EC_48ED_88A8_67F811F81B52__INCLUDED_)
