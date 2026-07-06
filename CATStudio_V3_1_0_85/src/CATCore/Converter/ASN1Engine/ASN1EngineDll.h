// ASN1Engine.h: interface for the CASN1Engine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(ASN1_ENGINE_DLL)
#define ASN1_ENGINE_DLL

#include "ASN1Wrapper.h"

extern "C" {

typedef enum 
{
	ASN1_ENGINE_ERR_DLL_NAME_IS_NULL = 0xFF00,
	ASN1_ENGINE_ERR_NULL_CONTENT = 0xFF01,
} Asn1EngineErr_t;

typedef UINT8 EutraLogicalChannelType;
typedef UINT8 EutraSrbId;

// ASN.1 engine API; init the ASN.1 engine DLL
extern __declspec(dllexport) int ASN1Engine_Init (const char * asn1EngineName);

// ASN.1 engine API; init the ASN.1 engine DLL
extern __declspec(dllexport) void ASN1Engine_InitParams ();

// ASN.1 engine API; Terminates the ASN.1 engine DLL
extern __declspec(dllexport) void ASN1Engine_Term();

// ASN.1 engine API: Get the ASN.1 message ID
extern __declspec(dllexport) bool ASN1Engine_GetASN1MessageID (RadioBearer radioBearer, TrafficDirection direction, 
								  TransportChannel trChType, BYTE *content, WORD contentLen, 
								  BYTE * nasMsgOutBufPtr, WORD * nasMsgOutBufLenPtr,WORD& asn1MsgID,bool &bIsEngineInit);

// ASN.1 engine API: Retrieve the include NAS message
extern __declspec(dllexport) BOOL ASN1Engine_GetNasMessage (RadioBearer radioBearer, TrafficDirection direction, 
						  TransportChannel trChType, BYTE *content, WORD contentLen, 
						  BYTE * nasMsgOutBufPtr, WORD * nasMsgOutBufLenPtr,bool &bIsEngineInit);

// ASN.1 engine API; decode a message
extern __declspec(dllexport) bool ASN1Engine_DecodeASN1Message (RadioBearer radioBearer, TrafficDirection direction, 
						  TransportChannel trChType, BYTE *content, WORD contentLen, 
						  BYTE * outBufPtr, WORD * outBufLenPtr,bool &bIsEngineInit,bool bPrintPDU = false,
						  BYTE * nasMsgOutBufPtr = NULL, WORD * nasMsgOutBufLenPtr = NULL);

// ASN.1 engine API; decode a message
extern __declspec(dllexport) bool ASN1Engine_DecodeLTEASN1Message (EutraSrbId radioBearer, TrafficDirection direction, 
							TransportChannel trChType/*EutraLogicalChannelType logChType*/, BYTE *content, WORD contentLen, 
							BYTE *& outBufPtr, WORD * outBufLenPtr,bool &bIsEngineInit,bool bPrintPDU = false,
							BYTE * nasMsgOutBufPtr = NULL, WORD * nasMsgOutBufLenPtr = NULL);


// ASN.1 engine API; decode a SIB
extern __declspec(dllexport) bool ASN1Engine_DecodeASN1Sib (BYTE sibType, BYTE *content, WORD contentLen,
						  BYTE * outBufPtr, WORD * outBufLenPtr,bool &bIsEngineInit,bool bPrintPDU = false, BYTE exSibType = 0);

extern __declspec(dllexport) bool ASN1Engine_DecodeASN1ExteSib (BYTE extType, BYTE extSibType, BYTE *content, WORD contentLen, 
							BYTE *outBufPtr, WORD *outBufLenPtr,bool &bIsEngineInit,bool bPrintPDU);


// ASN.1 engine API; decode a message by wireshark
extern __declspec(dllexport) bool ASN1Engine_DecodeASN1MessageWS (RadioBearer radioBearer, TrafficDirection direction, 
	TransportChannel trChType, BYTE *content, WORD contentLen, 
	BYTE * outBufPtr, WORD * outBufLenPtr,bool &bIsEngineInit,bool bPrintPDU = false,
	BYTE * nasMsgOutBufPtr = NULL, WORD * nasMsgOutBufLenPtr = NULL);

// ASN.1 engine API; decode a message by wireshark
extern __declspec(dllexport) bool ASN1Engine_DecodeLTEASN1MessageWS (EutraSrbId radioBearer, TrafficDirection direction, 
	TransportChannel trChType/*EutraLogicalChannelType logChType*/, BYTE *content, WORD contentLen, 
	BYTE *& outBufPtr, WORD * outBufLenPtr,bool &bIsEngineInit,bool bPrintPDU = false,
	BYTE * nasMsgOutBufPtr = NULL, WORD * nasMsgOutBufLenPtr = NULL);

// ASN.1 engine API; decode a message by wireshark
extern __declspec(dllexport) bool ASN1Engine_DecodeNBASN1MessageWS (EutraSrbId radioBearer, TrafficDirection direction, 
	TransportChannel trChType/*EutraLogicalChannelType logChType*/, BYTE *content, WORD contentLen, 
	BYTE *& outBufPtr, WORD * outBufLenPtr,bool &bIsEngineInit,bool bPrintPDU = false,
	BYTE * nasMsgOutBufPtr = NULL, WORD * nasMsgOutBufLenPtr = NULL);

// ASN.1 engine API; decode a message by wireshark
extern __declspec(dllexport) bool ASN1Engine_DecodeNRASN1MessageWS (EutraSrbId radioBearer, TrafficDirection direction, 
	TransportChannel trChType/*EutraLogicalChannelType logChType*/, BYTE *content, WORD contentLen, 
	BYTE *& outBufPtr, WORD * outBufLenPtr,bool &bIsEngineInit,bool bPrintPDU = false,
	BYTE * nasMsgOutBufPtr = NULL, WORD * nasMsgOutBufLenPtr = NULL);


// ASN.1 engine API; decode a SIB by wireshark
extern __declspec(dllexport) bool ASN1Engine_DecodeASN1SibWS (BYTE sibType, BYTE *content, WORD contentLen,
	BYTE * outBufPtr, WORD * outBufLenPtr,bool &bIsEngineInit,bool bPrintPDU = false, BYTE exSibType = 0);

//Empties the str that holds the content of the decoded ASN1.
extern __declspec(dllexport) void ASN1Engine_initASN1AsStrVar();

//gets the decoded ASN1 that was saved as CString.
extern __declspec(dllexport) char* ASN1Engine_getASN1AsStr();
extern __declspec(dllexport) void  ASN1Engine_SetASN1Str( char* str, int len );
extern __declspec(dllexport) int DirectProcessAsn1Message (int pduNum, BYTE *content, WORD contentLen, BYTE *& outBufPtrPtr, WORD * outBufLenPtr);

} // End of extern C

#endif // !defined(ASN1_ENGINE_DLL)
