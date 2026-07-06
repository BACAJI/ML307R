/*--------------------------------------------------------------------------------------------------------------------

 (C) Copyright 2006,2007 Marvell Semiconductor Israel Ltd. All Rights Reserved  

-------------------------------------------------------------------------------------------------------------------*/

// ASN1Handler.h: interface for the CASN1Handler class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ASN1HANDLER_H__48537BDE_DC48_4DC1_8FC9_9FEDBC1B9009__INCLUDED_)
#define AFX_ASN1HANDLER_H__48537BDE_DC48_4DC1_8FC9_9FEDBC1B9009__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>
#include "ASN1Engine.h"
#include "Asn1MsgNameAndStruct.h"

// Offsets of ASN.1 GKI Signal Headers:
//======================================
// All offsets are in bytes.
 
// Rx ASN.1 Signal offsets:
//--------------------------
#define DL_RLC_MODE_OFFSET					(0)
#define UARFCN_DL_OFFSET					(DL_RLC_MODE_OFFSET + 2)
#define PRIMARY_SCRAMBLING_CODE_OFFSET		(UARFCN_DL_OFFSET + 2)
#define FRAME_NUMBER_SFN_OFFSET				(PRIMARY_SCRAMBLING_CODE_OFFSET + 2)
#define FRAME_NUMBER_CFN_OFFSET				(FRAME_NUMBER_SFN_OFFSET + 2)
#define RX_RADIO_BEARER_ID_OFFSET			(FRAME_NUMBER_CFN_OFFSET + 2)
#define TRANSPORT_CH_OFFSET					(RX_RADIO_BEARER_ID_OFFSET + 1)
#define RX_BYTE_LEN_OFFSET					(TRANSPORT_CH_OFFSET + 1)
#define RX_DATA_OFFSET						(RX_BYTE_LEN_OFFSET + 2)

#define GET_DL_RLC_MODE(ptr)				((BYTE)(*((ptr) + DL_RLC_MODE_OFFSET)))
#define GET_DL_UARFCN(ptr)					(*((WORD *)((ptr) + UARFCN_DL_OFFSET)))
#define GET_PRIMARY_SCRAMBLING_CODE(ptr)	(*((WORD *)((ptr) + PRIMARY_SCRAMBLING_CODE_OFFSET)))
#define GET_FRAME_NUMBER_SFN(ptr)			(*((WORD *)((ptr) + FRAME_NUMBER_SFN_OFFSET)))
#define GET_FRAME_NUMBER_CFN(ptr)			(*((WORD *)((ptr) + FRAME_NUMBER_CFN_OFFSET)))
#define GET_RADIO_BEARER_OF_DL(ptr) 		((WORD)(*((ptr) + RX_RADIO_BEARER_ID_OFFSET)))
#define GET_TR_CH(ptr) 						((WORD)(*((ptr) + TRANSPORT_CH_OFFSET)))
#define GET_ASN1_CONTENT_LEN_OF_DL(ptr)		(*((WORD *)((ptr) + RX_BYTE_LEN_OFFSET)))
// #define GET_ASN1_CONTENT_LEN_OF_DL(ptr)		MAX_LEN(GET_ASN1_CONTENT_LEN_OF_DL_(ptr),200) //Changed to 200 to avoid problem of padding 
												//zeros at the end of encoded PDUs. 
//#define MAX_LEN(x,y)						(((x) > (y)) ? (x) : (y))
#define GET_ASN1_CONTENT_PTR_OF_DL(ptr)		((BYTE *)((ptr) + RX_DATA_OFFSET))

// Tx ASN.1 Signal offsets:
//--------------------------
#define UL_RLC_MODE_OFFSET					(0)
#define TX_RADIO_BEARER_ID_OFFSET			(UL_RLC_MODE_OFFSET + 1)
#define TX_BYTE_LEN_OFFSET					(TX_RADIO_BEARER_ID_OFFSET + 1)
#define TX_DATA_OFFSET						(TX_BYTE_LEN_OFFSET + 2)
#define MAX_SYS_INFO_OCTETS					1000

#define GET_UL_RLC_MODE(ptr)				((BYTE)(*((ptr) + UL_RLC_MODE_OFFSET)))
#define GET_RADIO_BEARER_OF_UL(ptr) 		((WORD)(*((ptr) + TX_RADIO_BEARER_ID_OFFSET)))
#define GET_ASN1_CONTENT_LEN_OF_UL(ptr)		(*((WORD *)((ptr) + TX_BYTE_LEN_OFFSET)))
//#define GET_ASN1_CONTENT_LEN_OF_UL(ptr)		MAX_LEN(GET_ASN1_CONTENT_LEN_OF_UL_(ptr),200) //Changed to 200 to avoid problem of padding 
												//zeros at the end of encoded PDUs.
#define GET_ASN1_CONTENT_PTR_OF_UL(ptr)		((BYTE *)((ptr) + TX_DATA_OFFSET))
#define GET_ASN1_SIB_EXT_TYPE(ptr)			(*((BYTE *)((ptr) + SIB_DATA_OFFSET + MAX_SYS_INFO_OCTETS)))

// SIB ASN.1 Signal offsets:
//---------------------------
#define SIB_TYPE_OFFSET						(0)
#define SIB_BYTE_LEN_OFFSET					(SIB_TYPE_OFFSET + 2)
#define SIB_DATA_OFFSET						(SIB_BYTE_LEN_OFFSET + 2)

#define GET_ASN1_SIB_TYPE(ptr)				((WORD)(*(ptr + SIB_TYPE_OFFSET)))
#define GET_ASN1_CONTENT_LEN_OF_SIB(ptr)	(*((WORD *)((ptr) + SIB_BYTE_LEN_OFFSET)))
// #define GET_ASN1_CONTENT_LEN_OF_SIB(ptr)	MAX_LEN(GET_ASN1_CONTENT_LEN_OF_SIB_(ptr),200) //Changed to 200 to avoid problem of padding 
												//zeros at the end of encoded PDUs.
#define GET_ASN1_CONTENT_PTR_OF_SIB(ptr)	((BYTE *)((ptr) + SIB_DATA_OFFSET))


#define	GET_RADIO_BEARER_FROM_KEY(k)		((UINT64(k) & 0xFFFF000000000000) >> 48)
#define	GET_DIRECTION_FROM_KEY(k)			((UINT64(k) & 0x0000FFFF00000000) >> 32)
#define	GET_TR_CH_FROM_KEY(k)				((UINT64(k) & 0x00000000FFFF0000) >> 16)
#define	GET_ASN1_ID_FROM_KEY(k)				((UINT64(k) & 0x000000000000FFFF))


#define _1_MSB_SHIFT						(7)
#define _2_MSB_SHIFT						(6)
#define _3_MSB_SHIFT						(5)
#define _5_MSB_SHIFT						(3)

#define _2_MSB_SHIFT_EXLUDING_I_BIT			(6 - 1)
#define _3_MSB_SHIFT_EXLUDING_I_BIT			(5 - 1)
#define _5_MSB_SHIFT_EXLUDING_I_BIT			(3 - 1)

#define GET_INTEGRITY_BIT(b)				((BYTE)(((BYTE)(b) & 0x80) >> 7))
#define MASK_INTEGRITY_BIT(b)				((BYTE)(((BYTE)(b) & 0x7F)))
#define DECODE_ASN1_ID(b,s)					((WORD)((BYTE)(b) >> (s)))


// If IntegrityCheckInfo is present, its length is 1 bit for flag, 
// 32 bit of authentication code and 4 bits for msg sequence number:
#define ENCODED_INTEGRITY_INFO_LEN_IN_BITS	(37)
#define ASN1_MSG_ID_OFFSET_IN_BITS			(ENCODED_INTEGRITY_INFO_LEN_IN_BITS)
#define ASN1_MSG_ID_OFFSET_IN_BYTES			(ENCODED_INTEGRITY_INFO_LEN_IN_BITS / 8)
#define _2_BITS_MASK_AFTER_INTEG_INFO(w)	((BYTE)(((WORD)(w) & 0x0600) >> 9))
#define _3_BITS_MASK_AFTER_INTEG_INFO(w)	((BYTE)(((WORD)(w) & 0x0700) >> 8))
#define _5_BITS_MASK_AFTER_INTEG_INFO(w)	((BYTE)(((WORD)(w) & 0x07C0) >> 6))

#ifdef _CATCORE_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif
class DLL_EXPORT CASN1Handler  
{
public:
	CASN1Handler(int nDevice);
	virtual ~CASN1Handler();

	void Init();

	void LoadSibExtType();

	// ASN.1 Handler API; retrieve the ASN.1 message name
	BOOL GetASN1MessageName (DWORD dwSigId, BYTE *pBuffer, CString &strName);

	// ASN.1 Handler API; retrieve the ASN.1 struct name
	BOOL GetASN1StructName (DWORD dwSigId, BYTE *pBuffer, CString &strStructName);

	// ASN.1 Handler API; retrieve the ASN.1 message group details
	BOOL GetASN1MsgGroupDetails (DWORD dwSigId, BYTE *pBuffer, CString &strRB, 
					CString &strDirection, CString& strTrCh, CString &strRlcMode);

	// ASN.1 Handler API; retrieve the ASN.1 message group details --sxwang
	BOOL GetASN1MsgGroupDetails (DWORD dwSigId, BYTE *pBuffer, RadioBearerId& radioBearer,TrafficDirection&	direction,
			TransportChannel& trCh,DlRlcMode& rlcmode,BYTE&	SibType,WORD& asnMsgLen,BYTE** asn1ContentPtr);

	BOOL GetASN1MsgDirection(DWORD dwSigId, TrafficDirection &direction);

	// ASN.1 Handler API; retrieve the ASN.1 message details:
	BOOL GetASN1MsgDetails (DWORD dwSigId, BYTE *pBuffer, CStringArray &strArr);

	// ASN.1 Handler API; retrieve the ASN.1 message details into a formated string:
	BOOL GetASN1MsgDetails (DWORD dwSigId, BYTE *pBuffer, CString &strDetails);
	
	// ASN.1 Handler API; retrieve the ASN.1 message details in short form:
	BOOL GetASN1ShortFormDetails(DWORD dwSigId, BYTE *pBuffer, CString &strDetails, int *pAsn1HeaderSize = NULL);

	// ASN.1 Handler API; retrieve the ASN.1 message content
	BOOL DecodeASN1Message (DWORD dwSigId, BYTE *pBuffer, BYTE *pOutBufPtr, WORD *pOutBufLenPtr,
							BOOL bPrintPDU = false,BYTE * nasMsgOutBufPtr = NULL, WORD * nasMsgOutBufLenPtr = NULL,int * nRatMode = NULL);

	// ASN.1 Handler API; retrieve the ASN.1 message content by wireshark
	BOOL DecodeASN1MessageWS (DWORD dwSigId, BYTE *pBuffer, BYTE *pOutBufPtr, WORD *pOutBufLenPtr,
		BOOL bPrintPDU = false,BYTE * nasMsgOutBufPtr = NULL, WORD * nasMsgOutBufLenPtr = NULL,int * nRatMode = NULL);

	// ASN.1 Handler API; check whether a GKI signal contains ASN.1 message
	BOOL IsAsn1Message (DWORD dwSigId);

	// ASN.1 Handler API; return the ID of a signal which contains ASN.1 message:
	DWORD GetAsn1SignalID (const CString &strAsn1MsgName);

	//Empties the str that holds the content of the decoded ASN1.
	//void initASN1Str();

	//gets the decoded ASN1 that was saved as CString.
	CString getASN1AsStr();
	
	// ASN.1 Handler API; return a CStringList containing the GKI-Signals that wrap ASN.1 messages:
	const CStringList * GetGKISignalsForASN1();

	//Set refreshed id list
	void RefreshAsn1IDList(DWORD rrcRxID, DWORD rrcTxID, DWORD rrcSIBID, DWORD rrcLteRxID, DWORD rrcLteTxID, DWORD rrcLteLongRxID, DWORD rrcNbRxID, DWORD rrcNbTxID,
						   DWORD rrcNrRxID = 0, DWORD rrcNrTxID = 0);

	BOOL DecodeNASMessageAsStr(DWORD dwSigID, BYTE* pBuffer, int nLen, CString& NasAsStr);

	CString GetHexRawData();
private:
	// Read the ASN.1 GKI signal IDs from the setting table:
	BOOL ReadAsn1Settings ();

	// ASN.1 Handler API; retrieve the ASN.1 message & struct name
	BOOL GetName (DWORD dwSigId, BYTE *pBuffer, RequiredDataType eMsgNameOrStructName, CString &strName);

	// Get the key for a specific message name
	BOOL GetMessageKey (DWORD dwSigId, BYTE *pBuffer, BOOL * bIsNasMsgIncluded, UINT64 &key, CString& strNasMsg);

	// Get ASN.1 ID out of the ASN.1 message
	BOOL GetASN1Id (WORD wRadioBearer, WORD wDirection, WORD wTrCh, BYTE * pBuffer, WORD wBuffLen, BOOL * bIsNasMsgIncluded, WORD& asn1Id, CString& strNasMsg);

	// Get ASN.1 ID out of the ASN.1 message which includes integrity info
	WORD GetASN1IdAfterInterityInfo (WORD wRadioBearer, WORD wDirection, WORD wTrCh, BYTE * pBuffer, WORD wBuffLen);

	BOOL LoadToSignalsMap ();

	void PadWithLeadingZero (CString &str);

	BOOL GetRBProt(int radioBearer, int trCh, CString& strRb);
	BOOL GetLteRBProt(int radioBearer, int trCh, CString& strRb);
	BOOL GetSIBProt( int sibType, int extSibType, CString& strRb);
	/* Data Members */
	/*---------------*/
	// Maps for the ASN.1 message names
	CMap<UINT64, UINT64, CASN1MsgNameAndStruct, CASN1MsgNameAndStruct&>	m_ASN1MessageMap;
    CMap<WORD, WORD, CASN1MsgNameAndStruct, CASN1MsgNameAndStruct&>		m_ASN1SibMap;
	CMap<WORD, WORD, CASN1MsgNameAndStruct, CASN1MsgNameAndStruct&>		m_ASN1SibExtMap;
	CMap<UINT64, UINT64, CASN1MsgNameAndStruct, CASN1MsgNameAndStruct&>	m_ASN1GsmMsgMap;

#ifdef UNICODE
	// Map for the GKI signals which contains ASN.1 messages:
	CMap<CString, LPCWSTR, DWORD, DWORD>		m_SignalsAndAsn1MsgsMap;
#else
	// Map for the GKI signals which contains ASN.1 messages:
	CMap<CString, LPCSTR, DWORD, DWORD>		m_SignalsAndAsn1MsgsMap;
#endif	

	// List of GKI signal IDs that wrap ASN.1 messages
	CList<DWORD, DWORD>						m_Asn1SigIdList;

	// Mapping of the GKI signals:
    DWORD	m_RxSignalId;
	DWORD	m_TxSignalId;
	DWORD	m_SibSignalId;
	DWORD	m_GsmRxSignalId;
	DWORD	m_LteRxSignalId;
	DWORD	m_LteTxSignalId;
	DWORD	m_LteRxLongSignalId;
	DWORD	m_NbRxSignalId;
	DWORD	m_NbTxSignalId;
	DWORD	m_NrRxSignalId;
	DWORD	m_NrTxSignalId;

	CStringList m_ASN1WrapperNames; 

	// NAS message
	// The NAS message is a field of some ASN.1 messages. Nevertheless, it need
	// to be displayed along the ASN.1 message name, therefor, it has special 
	// treatment.
	CString		m_NASMsg;

	// ASN.1 Engine
	CString				m_Asn1EngineName;
	CASN1Engine			m_Asn1Engine;
	BOOL				   m_Asn1EngineReady;
   CCriticalSection  m_csAsn1EngineLock;

	int m_nDevice;
	CString			m_strRawHexdata;
    BOOL  m_isTTCN;
};

#endif // !defined(AFX_ASN1HANDLER_H__48537BDE_DC48_4DC1_8FC9_9FEDBC1B9009__INCLUDED_)
