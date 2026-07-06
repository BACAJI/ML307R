/*------------------------------------------------------------------------------------------*
 |(C) Copyright 2006,2007 Marvell Semiconductor Israel Ltd. All Rights Reserved				|
 *------------------------------------------------------------------------------------------*/
#if !defined(AFX_ALLFILTERS_H__C3772561_F6DB_475A_89E1_FB6066437F4F__INCLUDED_)
#define AFX_ALLFILTERS_H__C3772561_F6DB_475A_89E1_FB6066437F4F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <Afxtempl.h>

#define NUM_FILTER_TYPES	4

#define DIAG_FILTER_INDEX		0
#define APP_DIAG_FILTER_INDEX	1
#define GKI_FILTER_INDEX		2
#define DSP_FILTER_INDEX		3

class CFilterBase;
class CICATMessage;


class __declspec(dllexport) CAllFilters : public CArray <CFilterBase *, CFilterBase *>
{
public:
	void OpenEntireFilter();
	void OpenEntireFilterEx();
	void CloseEntireFilter(int nFilterIndex = -1);
	void CloseEntireFilterEx();
	CAllFilters(int nDevice, BOOL bOpenAll = FALSE);
	virtual ~CAllFilters();

	BOOL IsPassFilter(CICATMessage *pMessage);
	virtual void RefreshFilter() { ; }

	static CString m_strFilterTitles[NUM_FILTER_TYPES];

	BOOL	m_bInternalServices;
	BOOL	m_bAtCommands;


	// API Functions for setting the different filter-types
	// DIAG Filter
	BOOL SetDIAGFilter(const CString &strCat1, const CString &strCat2, const CString &strCat3, BYTE bPass); 
	// DIAG Filter
	BOOL SetAppDIAGFilter(const CString &strCat1, const CString &strCat2, const CString &strCat3, BYTE bPass); 
	// GKI/Signals Filter
	BOOL SetGKIFilter(const CString &strSignalName, BYTE bPass);
	// DSP Filter
	BOOL SetDSPFilter(WORD wOpcode, BOOL bReport, BYTE bPass);

	BOOL SetModuleFilter(const CString &strModuleName, BYTE bPass);

	void SetInternalServicesFilter(BYTE bPass){m_bInternalServices = bPass;}
	void SetATCommandsFilter(BYTE bPass){m_bAtCommands = bPass;}

	void LoadAllFilters();
	void SaveAllFilters();


};

#endif // !defined(AFX_ALLFILTERS_H__C3772561_F6DB_475A_89E1_FB6066437F4F__INCLUDED_)
