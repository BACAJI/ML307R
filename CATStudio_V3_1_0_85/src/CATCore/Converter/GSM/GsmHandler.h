/*--------------------------------------------------------------------------------------------------------------------

 (C) Copyright 2006,2007 Marvell Semiconductor Israel Ltd. All Rights Reserved  

-------------------------------------------------------------------------------------------------------------------*/

// GsmHandler.h: interface for the CGsmHandler class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GSMHANDLER_H__9DB5892F_740F_43C6_AB97_2C14A18AD203__INCLUDED_)
#define AFX_GSMHANDLER_H__9DB5892F_740F_43C6_AB97_2C14A18AD203__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>
#include "..\..\BasicComponents\StringArrayEx.h"

#define NAS_MSG_TYPE_OFFSET				(1)
#define NAS_MSG_TYPE_MASK				(0x7F)

/*
// Enum for protocol discriminator
typedef enum 
{
    PD_CC                       =   0x03,
    PD_MM                       =   0x05,
    PD_RR                       =   0x06,
    PD_GMM                      =   0x08, 
    PD_SMS                      =   0x09,
    PD_SM                       =   0x0A, 
    PD_SS                       =   0x0B, 
    PD_TEST                     =   0x0F,
    PD_INVALID                  =   0x7F
}
ProtocolDiscriminator_te;
*/

class CGsmHandler  
{
public:
	CGsmHandler(int nDevice);
	virtual ~CGsmHandler();

private:

    CMap<DWORD, DWORD, BOOL, BOOL>						m_IsGsmMsg;
	CMap <DWORD, DWORD, CStringArrayEx, CStringArrayEx&>	m_GsmMsgMap;

	CString	m_GrrMsgsCarrierName;
	CString m_NasMsgsCarrierName;
	DWORD	m_GrrMsgsGkiId;
	DWORD	m_NasMsgsGkiId;
	BOOL	m_GkiSignalIdSet;
	int		m_nDevice;

private:

	void ClearCachedTable();
	void CacheGsmTable();
	int  GetGsmMessageKey(DWORD signalID, LPBYTE pBuffer);

	BOOL ReadSettings ();
	BOOL ReadSignalIds ();

	void CreatePacket(CString nasMessage,int nasSize,CString &outPacket);
	CString getLineNumber(int& currentLineNum);
	BOOL RunCMDLine(const CString &appName,const CString &command,CString &outDecodedNAS);
	BOOL readFileToString(const CString & fileName, CString &text);
	bool RunExecFile(CString strCommand, CString& strOutput);
	void readStreamToString(CString strDecoded, CString& strOut);
public:

	BOOL IsGsmMessage(DWORD sigID);
	BOOL GetGsmMessageName(DWORD signalID, LPBYTE pBuffer, CString& signalName);
	BOOL GetGsmMessageType(DWORD signalID, LPBYTE pBuffer, CString& signalType);
	BOOL DecodeGsmMessage (DWORD signalID, LPBYTE pBuffer, LPBYTE dMsg, DWORD& dLen);
	
	BOOL DecodeNASMessages (LPBYTE pBuffer, WORD& dwProtocolDiscriminator, WORD& dwNasMessageType);
	BOOL GetNasMessageName (WORD dwProtocolDiscriminator, WORD dwNasMessageType, CString& strNasMsgName, int nDir);

	BOOL DecodeStrNASMessage(CString NASMessage,CString &outDecodedNAS,int nRatMode,int SecHeaderType);
	BOOL FindSharkPath(CString &sPath);
};

#endif // !defined(AFX_GSMHANDLER_H__9DB5892F_740F_43C6_AB97_2C14A18AD203__INCLUDED_)
