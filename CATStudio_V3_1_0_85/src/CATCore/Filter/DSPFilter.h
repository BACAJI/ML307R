/*------------------------------------------------------------------------------------------*
 |(C) Copyright 2006,2007 Marvell Semiconductor Israel Ltd. All Rights Reserved				|
 *------------------------------------------------------------------------------------------*/
#if !defined(AFX_DSPFILTER_H__A2C973DB_0EA1_4F41_8F0F_3C6BD230310F__INCLUDED_)
#define AFX_DSPFILTER_H__A2C973DB_0EA1_4F41_8F0F_3C6BD230310F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FilterBase.h"

#define MAX_DSP_OPCODE	0x200


class CDSPFiltersDlg;
class CAllFilters;

class  CDSPFilter : public CFilterBase  
{
public:
	BOOL SetPassFilter(WORD wOpcode, BOOL bReport, BYTE bPass);
	void OpenEntireFilter();
	void CloseEntireFilter();
	CDSPFilter(CAllFilters *pAllFilters, BOOL bOpenAll, int nDevice);
	virtual ~CDSPFilter();

	void RenewFilter();
	BOOL IsPassFilter(CICATMessage *pMessage);
	CDialog * GetDlg();
	BOOL CreateDlg(CWnd *pParent);
//	void LoadFromFile(BOOL bDefaultFile = false);
//	void SaveToFile(BOOL bDefaultFile = false);
	void Save(const CString &strFileName);
	void Load(const CString &strFileName, BOOL bDefaultFile = false);
 	void RefreshFilterTree();
 	void UpdateFilterTree();
	BYTE * GetFilter(BOOL bCommands = true);

private:
	int m_nDevice;				//Richard added 2012-06-18
	CDSPFiltersDlg *m_pDSPFiltersDlg;
	BYTE m_CommandsFilter[MAX_DSP_OPCODE];
	BYTE m_ReportsFilter[MAX_DSP_OPCODE];

	USHORT m_DSPReportModuleID;
	USHORT m_DSPReportMessageID;
	USHORT m_DSPCommandModuleID;
	USHORT m_DSPCommandMessageID;

	friend class CDSPFiltersDlg;

};

#endif // !defined(AFX_DSPFILTER_H__A2C973DB_0EA1_4F41_8F0F_3C6BD230310F__INCLUDED_)
