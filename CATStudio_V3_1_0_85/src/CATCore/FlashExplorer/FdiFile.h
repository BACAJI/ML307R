/*--------------------------------------------------------------------------------------------------------------------

 (C) Copyright 2006,2007 Marvell Semiconductor Israel Ltd. All Rights Reserved  

-------------------------------------------------------------------------------------------------------------------*/


#if !defined(AFX_FDIFILE_H__991FA5DC_C870_404B_932C_A0188280033B__INCLUDED_)
#define AFX_FDIFILE_H__991FA5DC_C870_404B_932C_A0188280033B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MB	1048576
#define KB	1024


class __declspec (dllexport) CFdiFile: CObject
{
public:
	void SetTime(UINT32 a_iTimeVal);
	void SetDate(UINT32 a_iDateVal);
	void SetTimeProperties(UINT32 a_unCreationTime, UINT32 a_unModificationTime);
	CString m_sName;
	CString m_sCreationTime;
	CString	m_sCreationDate;

	CString m_sModificationTime;
	CString	m_sModificationDate;

	DWORD	m_dwSize;
	CString m_sSize;
	WORD	m_wAttributes;
	
	DECLARE_DYNCREATE(CFdiFile)

	CFdiFile(const CStringW& a_sName = CStringW(_T("")), const CStringW& a_sCreationTime =CStringW(_T("")),const CStringW& a_sCreationDate =CStringW(_T("")), DWORD a_dwSize=0,WORD a_wAttributes=0);//

	CFdiFile(const CFdiFile& a_oFdiFile);
	virtual ~CFdiFile();
	BOOL	operator == (const CFdiFile& a_oFdiFile) const;
	void	operator=(const CFdiFile& a_oFdiFile);
private:
	BOOL ConvertByteSizeToKorMstr(UINT32 a_nByteSize, CString &a_sFormatedSize, BOOL a_bRound = false);
};

#endif // !defined(AFX_FDIFILE_H__991FA5DC_C870_404B_932C_A0188280033B__INCLUDED_)
