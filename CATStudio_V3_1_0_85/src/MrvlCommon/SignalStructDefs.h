// SignalStructDefs.h
// 
#ifndef _SIGNAL_STRUCT_DEFS_
#define _SIGNAL_STRUCT_DEFS_


/// ///////////////////////////////////////////////////////////////////////
/// Signal definition
enum EMessageType
{
   eGki     = 0,
   eRlc     = 1,
   eDspMsg  = 2,
   eDspCmd  = 3,
   eCat123  = 4,
   eAppDiag = 5,
   eAsn1    = 6
};

struct SignalGroupStruct
{
   WORD	codeID;
   TCHAR	itemName[MAX_PATH];
   BYTE	level;
   COLORREF color;
   BYTE	displayed;
};


struct CGkiMessage
{
   SignalGroupStruct val;
   WORD    wTargetTaskId;
   int     nDataLength;
   BYTE*   pData;
};

struct CRlcMessage
{
   DWORD val;
   DWORD dwUETimeStamp;
   WORD  sfn;
   BOOL  IsOffline;
   BYTE* pData;
};

struct CDspMessage
{
   WORD  wOpCode;
   WORD  wDspDataLen;
   WORD* pDspData;
};

struct CDspCommand
{
   WORD  wOpCode;
   WORD  wDspDataLen;
   WORD* pDspData;
};

struct CCat123Message
{
   SignalGroupStruct val;
   int   nDataLength;
   BYTE* pData;
};

struct CAppDiagMessage
{
   WORD  wSigValue;
   BYTE* pData;
};

struct CAsn1Message
{
   DWORD dwSigId;
   WORD  wTargetTaskId;
   int   nDataLen;
   BYTE* pData;
};









#endif
