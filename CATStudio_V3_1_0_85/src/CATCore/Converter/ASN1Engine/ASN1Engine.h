/*--------------------------------------------------------------------------------------------------------------------

 (C) Copyright 2006,2007 Marvell Semiconductor Israel Ltd. All Rights Reserved  

-------------------------------------------------------------------------------------------------------------------*/

// ASN1Engine.h: interface for the CASN1Engine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ASN1ENGINE_H__9F32D94E_6074_411C_A154_978463CF399F__INCLUDED_)
#define AFX_ASN1ENGINE_H__9F32D94E_6074_411C_A154_978463CF399F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ASN1Wrapper.h"

class CASN1Engine  
{
public:
	CASN1Engine();
	virtual ~CASN1Engine();
	
	HMODULE	hASN1EngineDll;
	//LTE/4G engine handle
	HMODULE	hLteASN1EngineDll;

	// Init the ASN.1 engine DLL:
	BOOL InitEngine (CString& strEngineName);
	
	// ASN.1 engine API; Get the ASN.1 message ID
	BOOL GetAsn1MEssageID (RadioBearerId radioBearer = RBID_INVALID, TrafficDirection direction = NEUTRAL, 
						  TransportChannel trChType = TC_INVALID, BYTE *content = NULL, WORD len = 0,
						  BYTE * nasMsgOutBufPtr = NULL, WORD * nasMsgOutBufLenPtr = NULL, WORD *asn1MsgID = NULL);

	// ASN.1 engine API: Retrieve the include NAS message
	BOOL GetNasMessage (RadioBearerId radioBearer = RBID_INVALID, TrafficDirection direction = NEUTRAL, 
						  TransportChannel trChType = TC_INVALID, BYTE *content = NULL, WORD len = 0,
						  BYTE * nasMsgOutBufPtr = NULL, WORD * nasMsgOutBufLenPtr = NULL);

	// ASN.1 engine API; decode a message
	BOOL DecodeASN1Message (RadioBearerId radioBearer = RBID_INVALID, TrafficDirection direction = NEUTRAL, 
						  TransportChannel trChType = TC_INVALID, BYTE *content = NULL, WORD len = 0,
						  BYTE *outBufPtr = NULL, WORD *outBufLenPtr = NULL,BOOL bPrintPDU = false,
						  BYTE * nasMsgOutBufPtr = NULL, WORD * nasMsgOutBufLenPtr = NULL,bool bLte = false);

	// ASN.1 engine API; decode a SIB
	BOOL DecodeASN1Sib (BYTE sibType, BYTE *content = NULL, WORD len = 0,
						  BYTE *outBufPtr = NULL, WORD *outBufLenPtr = NULL,BOOL bPrintPDU = false, BYTE sibExtType = 0);

	// ASN.1 engine API; decode a message by wireshark
	BOOL DecodeASN1MessageWS (RadioBearerId radioBearer = RBID_INVALID, TrafficDirection direction = NEUTRAL, 
		TransportChannel trChType = TC_INVALID, BYTE *content = NULL, WORD len = 0,
		BYTE *outBufPtr = NULL, WORD *outBufLenPtr = NULL,BOOL bPrintPDU = false,
		BYTE * nasMsgOutBufPtr = NULL, WORD * nasMsgOutBufLenPtr = NULL,bool bLte = false, bool bNb = false,
		BYTE bNr = 0);

	// ASN.1 engine API; decode a SIB by wireshark
	BOOL DecodeASN1SibWS (BYTE sibType, BYTE *content = NULL, WORD len = 0,
		BYTE *outBufPtr = NULL, WORD *outBufLenPtr = NULL,BOOL bPrintPDU = false, BYTE sibExtType = 0);

	//Empties the str that holds the content of the decoded ASN1.
	void initASN1Str(bool bLte = false);

	//gets the decoded ASN1 that was saved as CString.
	CString getASN1AsStr();
private:
	CString m_strAsn1Str;
};

#endif // !defined(AFX_ASN1ENGINE_H__9F32D94E_6074_411C_A154_978463CF399F__INCLUDED_)
