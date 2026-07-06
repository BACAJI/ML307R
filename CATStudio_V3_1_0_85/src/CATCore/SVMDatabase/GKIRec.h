/******************************************************
*                       GKIRec.h
*
* Project : LogFileConverter              Ver : 1.0
* Programmer : Ohad Peled        Date : 03/02/2003  10:52:47 AM
* Language : VC 6.0              Target : Win32
* Purpose : Structure of MI_COMMAND Header
*****************************************************/
//@DOC

//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GKIRec_H__9754428F_F8B9_409E_A6B9_41E482E1C595__INCLUDED_)
#define AFX_GKIRec_H__9754428F_F8B9_409E_A6B9_41E482E1C595__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CICATMessage;

class CEnumSizeConverter;
class CGKIRec : public CObject  
{
public:
	virtual ~CGKIRec() 
	{
		if(m_pData)
			delete [] m_pData; 
		if(m_tempFullData)
			delete [] m_tempFullData;
	}

	CGKIRec& operator = (const CGKIRec& rec);
	void Serialize(CArchive& ar) = 0;
	virtual BOOL FormatRec(BYTE* data,int nDataLength,CEnumSizeConverter* pConverter) = 0;//{AfxMessageBox("Your'e in the wrong place");return FALSE;}
	virtual void CreateDataArr()=0;
	virtual CString GetLastError(){return m_strLastError;}

	virtual BYTE* GetSignalData(){return m_tempFullData;};
	virtual int	GetDataLength(){return m_FullDataLength;};
protected:
	CGKIRec(int nDeviceIndex)
	{
		m_nDeviceIndex = nDeviceIndex;
		m_dwMI = 0;
		m_pData = NULL;
		m_tempFullData = NULL;
	}

	int		m_nDeviceIndex;
public:
	DWORD  m_dwMI;
	USHORT m_shSize;
	DWORD m_shID;
	BYTE*  m_pData;
	CString m_strLastError;

	BYTE *m_tempFullData;//The all data of the signal for recovering it from *.tlg file
	int  m_FullDataLength;//The all data length of the signal for recovering it from *.tlg file
	int  m_pSignalWithoutDataLength;//The length of only the signal without data so we can convert it properly 
};

class CGKICommandRec : public CGKIRec
{
public:
	CGKICommandRec(int nDeviceIndex);
	void Serialize(CArchive& ar);
	BOOL FormatRec(BYTE* data,int nDataLength,CEnumSizeConverter* pConverter);
	virtual void CreateDataArr();
};

class CGKILoggedSignalRec : public CGKIRec
{
public:
	CGKILoggedSignalRec(int nDeviceIndex,BOOL bSpecial = FALSE);
	CGKILoggedSignalRec& operator = (const CGKILoggedSignalRec& rec);
	void Serialize(CArchive& ar);
	virtual BOOL FormatRec(BYTE* data,int nDataLength,CEnumSizeConverter* pConverter);
	virtual void CreateDataArr();

private:
	BOOL FormatRec_Regular(BYTE* data,int nDataLength,CEnumSizeConverter* pConverter);
	BOOL FormatRec_Special(BYTE* data,int nDataLength,CEnumSizeConverter* pConverter);

public:
	DWORD  m_dwSource;
	DWORD  m_dwDest;
	DWORD  m_dwFrameNum;
	DWORD  m_dwTime;
	USHORT m_shSignalLength;
	USHORT m_shPad;
	BOOL m_bSpecial;	// Support DIAGM Logged-Signal Format
};

class CGKISignalRec : public CGKIRec
{
public:
	CGKISignalRec(int nDeviceIndex);
	CGKISignalRec& operator = (const CGKISignalRec& rec);
	void Serialize(CArchive& ar);
	virtual BOOL FormatRec(BYTE* data,int nDataLength,CEnumSizeConverter* pConverter);
	virtual void CreateDataArr();
public:
	DWORD  m_dwSource;
	DWORD  m_dwDest;
	USHORT m_shSignalLength;
	USHORT m_shPad;
	
};

class CGKISignalRecReader : public CObject
{
public:
	CGKISignalRecReader();
//	void operator = (CGKISignalRec& rec);
	void Serialize(CArchive& ar);
	CICATMessage * GetCICATMessage();
	
private:
	DWORD					m_dwMI;
	WORD					m_diagSAP;
	
	int						m_tempMessaegeNumber;
	CICATMessage			*m_pTempICATMessage;

	CEnumSizeConverter		m_pConverter;

// 	CGKILoggedSignalRec		*m_pGKILoggedSignalRec;
// 	CGKICommandRec			*m_pCGKICommandRec;
// 	CGKISignalRec			*m_pCGKISignalRec;
	CGKIRec					*m_pGKIRec;
};

#endif // !defined(AFX_GKIRec_H__9754428F_F8B9_409E_A6B9_41E482E1C595__INCLUDED_)
