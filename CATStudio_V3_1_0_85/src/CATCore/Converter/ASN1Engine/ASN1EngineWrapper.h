/* ASN1EngineWrapper.h: interface for the ASN1 engine. */

#if !defined(ASN1_ENGINE_WRAPPER)
#define ASN1_ENGINE_WRAPPER

#include "ASN1EngineDll.h"
#include "ASN1Wrapper.h"

#include "./OSSFiles/ossdll.h"
#include "rrcSpecVer.h"

#ifdef RRC7D0
#include "rrc7d0.h"
#elif defined RRC7D0_ERRC8A0
#include "rrc7d0_errc8a0.h"
#elif defined RRC8K0_ERRC9C0
#include "rrc8k0_errc9c0.h"
#elif defined ERRCB40_RRC9D0
#include "rrc9d0_errcb40.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
// Internal decoding member functions. Used as an interface to the ASN.1 engine:
int ProcessBcchBchMessage (OssGlobal *world, BYTE *content, WORD contentLen,
							BYTE * outBufPtrPtr, WORD * outBufLenPtr);

int ProcessBcchFachMessage (OssGlobal *world, BYTE *content, WORD contentLen,
						    BYTE * outBufPtrPtr, WORD * outBufLenPtr);

int ProcessBcchDLSchMessage (OssGlobal *world, BYTE *content, WORD contentLen,
			     BYTE *outBufPtr, WORD *outBufLenPtr);

int ProcessPcchMessage (OssGlobal *world, BYTE *content, WORD contentLen,
						    BYTE * outBufPtrPtr, WORD * outBufLenPtr);

int ProcessDlCcchMessage (OssGlobal *world, BYTE *content, WORD contentLen,
						    BYTE * outBufPtrPtr, WORD * outBufLenPtr);

int ProcessUlCcchMessage (OssGlobal *world, BYTE *content, WORD contentLen,
						    BYTE * outBufPtrPtr, WORD * outBufLenPtr);

int ProcessDlDcchMessage (OssGlobal *world, BYTE *content, WORD contentLen,
						    BYTE * outBufPtrPtr, WORD * outBufLenPtr, unsigned short &choice);

int ProcessUlDcchMessage (OssGlobal *world, BYTE *content, WORD contentLen,
						    BYTE * outBufPtrPtr, WORD * outBufLenPtr, unsigned short &choice);

int ProcessMcchMessage (OssGlobal *world, BYTE *content, WORD contentLen,
						BYTE * outBufPtrPtr, WORD * outBufLenPtr);
int ProcessMasterInfoBlock (OssGlobal *world, BYTE *content, WORD contentLen,
						    BYTE * outBufPtrPtr, WORD * outBufLenPtr);

int ProcessSysInfoType1 (OssGlobal *world, BYTE *content, WORD contentLen,
						    BYTE * outBufPtrPtr, WORD * outBufLenPtr);

int ProcessSysInfoType2 (OssGlobal *world, BYTE *content, WORD contentLen,
						    BYTE * outBufPtrPtr, WORD * outBufLenPtr);

int ProcessSysInfoType3 (OssGlobal *world, BYTE *content, WORD contentLen,
						    BYTE * outBufPtrPtr, WORD * outBufLenPtr);

int ProcessSysInfoType4 (OssGlobal *world, BYTE *content, WORD contentLen,
						    BYTE * outBufPtrPtr, WORD * outBufLenPtr);

int ProcessSysInfoType5 (OssGlobal *world, BYTE *content, WORD contentLen,
						    BYTE * outBufPtrPtr, WORD * outBufLenPtr);

int ProcessSysInfoType6 (OssGlobal *world, BYTE *content, WORD contentLen,
						    BYTE * outBufPtrPtr, WORD * outBufLenPtr);

int ProcessSysInfoType7 (OssGlobal *world, BYTE *content, WORD contentLen,
						    BYTE * outBufPtrPtr, WORD * outBufLenPtr);

int ProcessSysInfoType8 (OssGlobal *world, BYTE *content, WORD contentLen,
						    BYTE * outBufPtrPtr, WORD * outBufLenPtr);

int ProcessSysInfoType9 (OssGlobal *world, BYTE *content, WORD contentLen,
						    BYTE * outBufPtrPtr, WORD * outBufLenPtr);

int ProcessSysInfoType10 (OssGlobal *world, BYTE *content, WORD contentLen,
						    BYTE * outBufPtrPtr, WORD * outBufLenPtr);

int ProcessSysInfoType11 (OssGlobal *world, BYTE *content, WORD contentLen,
						    BYTE * outBufPtrPtr, WORD * outBufLenPtr);

int ProcessSysInfoType12 (OssGlobal *world, BYTE *content, WORD contentLen,
						    BYTE * outBufPtrPtr, WORD * outBufLenPtr);

int ProcessSysInfoType13 (OssGlobal *world, BYTE *content, WORD contentLen,
						    BYTE * outBufPtrPtr, WORD * outBufLenPtr);

int ProcessSysInfoType13_1 (OssGlobal *world, BYTE *content, WORD contentLen,
						    BYTE * outBufPtrPtr, WORD * outBufLenPtr);

int ProcessSysInfoType13_2 (OssGlobal *world, BYTE *content, WORD contentLen,
						    BYTE * outBufPtrPtr, WORD * outBufLenPtr);

int ProcessSysInfoType13_3 (OssGlobal *world, BYTE *content, WORD contentLen,
						    BYTE * outBufPtrPtr, WORD * outBufLenPtr);

int ProcessSysInfoType13_4 (OssGlobal *world, BYTE *content, WORD contentLen,
						    BYTE * outBufPtrPtr, WORD * outBufLenPtr);

int ProcessSysInfoType14 (OssGlobal *world, BYTE *content, WORD contentLen,
						    BYTE * outBufPtrPtr, WORD * outBufLenPtr);

int ProcessSysInfoType15 (OssGlobal *world, BYTE *content, WORD contentLen,
						    BYTE * outBufPtrPtr, WORD * outBufLenPtr);

int ProcessSysInfoType15_1 (OssGlobal *world, BYTE *content, WORD contentLen,
						    BYTE * outBufPtrPtr, WORD * outBufLenPtr);

int ProcessSysInfoType15_2 (OssGlobal *world, BYTE *content, WORD contentLen,
						    BYTE * outBufPtrPtr, WORD * outBufLenPtr);

int ProcessSysInfoType15_3 (OssGlobal *world, BYTE *content, WORD contentLen,
						    BYTE * outBufPtrPtr, WORD * outBufLenPtr);

int ProcessSysInfoType15_4 (OssGlobal *world, BYTE *content, WORD contentLen,
						    BYTE * outBufPtrPtr, WORD * outBufLenPtr);

int ProcessSysInfoType15_5 (OssGlobal *world, BYTE *content, WORD contentLen,
						    BYTE * outBufPtrPtr, WORD * outBufLenPtr);

int ProcessSysInfoType16 (OssGlobal *world, BYTE *content, WORD contentLen,
						   BYTE * outBufPtrPtr, WORD * outBufLenPtr);

int ProcessSysInfoType17 (OssGlobal *world, BYTE *content, WORD contentLen,
						   BYTE * outBufPtrPtr, WORD * outBufLenPtr);

int ProcessSysInfoType18 (OssGlobal *world, BYTE *content, WORD contentLen,
						    BYTE * outBufPtrPtr, WORD * outBufLenPtr);

int ProcessSysInfoTypeSB1 (OssGlobal *world, BYTE *content, WORD contentLen,
							BYTE * outBufPtrPtr, WORD * outBufLenPtr);

int ProcessSysInfoTypeSB2 (OssGlobal *world, BYTE *content, WORD contentLen,
							BYTE * outBufPtrPtr, WORD * outBufLenPtr);

int ProcessAsn1Message (OssGlobal *world, int pduNum, BYTE *content, WORD contentLen, BYTE *& outBufPtrPtr, WORD * outBufLenPtr);
int DirectProcessAsn1Message (int pduNum, BYTE *content, WORD contentLen, BYTE *& outBufPtrPtr, WORD * outBufLenPtr);

int ProcessRRCMessageWS(CString strRRCProt, BYTE* content, WORD wLen,  CString& outDecodedNAS);
int OSSTraceFunc(FILE *pFile, const char *format, ...);

void readStreamToString(CString strDecoded, CString& strOut);
bool RunExecFile(CString strCommand, CString& strOutput);
BOOL FindSharkPath(CString &sPath);
BOOL RunCMDLine(const CString &appName,const CString &command,CString &outDecodedNAS);
CString getLineNumber(int& currentLineNum);

#ifdef __cplusplus
} // extern "C"
#endif /* __cplusplus */

#endif // !defined(ASN1_ENGINE_WRAPPER)
