// UE_Rec.h: interface for the CUE_Rec class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UE_REC_H__DDC8C462_3965_11D5_8230_0006294FD6F7__INCLUDED_)
#define AFX_UE_REC_H__DDC8C462_3965_11D5_8230_0006294FD6F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUECommandsDB;


class CUE_Rec  
{
public:
	long	m_FileId;
	long	m_EnumVal;
	BYTE	m_EnumType;
	CString	m_ReportLine;
	CString m_Cat1;
	CString m_Cat2;
	CString m_Cat3;
	CString m_DefaultData;
	BOOL	m_bIsExtCommand;
	CString	m_DefaultExtOpcode;

	CUE_Rec();
	CUE_Rec(CUECommandsDB *db);

	virtual ~CUE_Rec();
};

#endif // !defined(AFX_UE_REC_H__DDC8C462_3965_11D5_8230_0006294FD6F7__INCLUDED_)
