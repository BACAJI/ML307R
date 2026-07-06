/*--------------------------------------------------------------------------------------------------------------------

 (C) Copyright 2006,2007 Marvell Semiconductor Israel Ltd. All Rights Reserved  

-------------------------------------------------------------------------------------------------------------------*/

#ifndef __COMMAND_AND_MESSAGE_STRUCTURES_H__
#define __COMMAND_AND_MESSAGE_STRUCTURES_H__

#include "MrvlCommon/CommonDefs.h"

#define ALL						L""
#define ALL_MESSAGES			ALL
#define ALL_SIGNALS			ALL
#define ALL_OPCODES			((WORD)(-1))
#define CLEAR_ALL				((UINT64)(-1))
#define ANY_STRING			CStringW("")

#define DEFAULT_TIMEOUT		8000

#define NO_SUFFIX				0
#define SUFFIX_RETURN		1
#define SUFFIX_CTRLZ			2
#define SUFFIX_CRLN				3

#define AT_COMMANDS_RAW_DATA	         0
#define AT_COMMANDS_OVER_DIAG	         1
#define AT_COMMANDS_OVER_GKI	         2
#define AT_COMMANDS_OVER_STRING			3

enum eTargetType {
   UE_None        = -1,
   UE_Comm_Side   = 0x00,
   UE_App_Side    = 0x01,
   UE_MTSD_cid    = 0x02,
   UE_Audio_cid   = 0x03,
   UE_Error_Handler_cid    = 0x04,
   UE_VAL_IF_cid           = 0x05,
   UE_Apps_Diag_Server_cid = 0x08,
   UE_AP_Diag_Server_cid   = 0x09,
   UE_RF_Bin_cid           = 0xE,
   UE_DSP_cid              = 0x0F,
   UE_ALL_Clients          = 0x7F,
   UE_Diag_Server_cid      = 0x80
};

#define MAX_COM_CLIENTS UE_Comm_Side+1
#define FIRST_COM_ID UE_Comm_Side

#define MAX_APP_CLIENTS UE_VAL_IF_cid
#define FIRST_APP_ID UE_App_Side


#define IS_COMM_SIDE(x)		(((eTargetType)x==UE_Comm_Side))
#define IS_APP_SIDE(x)		((eTargetType)x>=FIRST_APP_ID && (eTargetType)x<= MAX_APP_CLIENTS)
#define IS_MSA_SIDE(x)		(((eTargetType)x==UE_DSP_cid))
#define IS_RF_BIN_SIDE(x)	(((eTargetType)x==UE_RF_Bin_cid))

enum eOSType
{
   eOSTypeNone,
   eOSTypeRTOS,
   eOSTypeWinCE,
   eOSTypeLinux,
   eOSTypeAndroid
};
//Add PTK's Target DB Type definition. 
enum eTargetDBType
{
	eTargetDBTypeNone = -1,
	eFirstTargetDBType = 0,

	eTargetDBTypeCom = eFirstTargetDBType,
	eTargetDBTypeApp,
	eTargetDBTypeMsa,
	eTargetDBTypeRFBin,

	eNumTargetDBTypes
};
#define OS_TYPE_STR_RTOS	"RTOS"
#define OS_TYPE_STR_WINCE	"WinCE"
#define OS_TYPE_STR_LINUX	"Linux"
#define OS_TYPE_STR_ANDROID	"Android"


#define DB_STATUS	WM_USER+450
#define DB_COMM_MATCH	0x0001
#define DB_APP_MATCH	0x0002

class UE_Message 
{
public:
   CStringW		m_Cat1;
   CStringW		m_Cat2;
   CStringW		m_Cat3;
   BYTE		*m_pData;
   WORD		m_DataLen;
   DWORD		m_TimeStamp;
   BOOL		m_Fixup;
   eTargetType	m_TargetType;
   int			m_Device;
   bool		m_bPack;
   bool		m_bIsAlign4;


   DWORD		m_MaxDataLen;

   friend class CCommandAndControl;
   friend class UE_FrameMessage;


   friend class CCommandChannel;
   friend class UE_FrameMessage;

public:

   UE_Message(const CStringW &Cat1 = ALL, const CStringW &Cat2 = ALL, const CStringW &Cat3 = ALL, BYTE *pData = NULL, WORD dataLen = 0, BOOL fixup = false, DWORD timeStamp = -1, eTargetType	targetType = UE_Comm_Side)
   {
      m_Cat1 = Cat1;
      m_Cat2 = Cat2;
      m_Cat3 = Cat3;
      m_pData = pData;
      m_DataLen = dataLen;
      m_Fixup = fixup;
      m_TimeStamp = timeStamp;
      m_TargetType = targetType;
      m_MaxDataLen = (DWORD)(-1);
      m_Device = -1;
   }
};


class UE_FrameMessage : public UE_Message
{
public:
	DWORD	m_dwMsgFrame;
	DWORD	m_dwMsgFrame2;

	UE_FrameMessage(const CStringW &Cat1 = ALL, const CStringW &Cat2 = ALL, const CStringW &Cat3 = ALL, BYTE *pData = NULL, WORD dataLen = 0, bool fixup = false, DWORD timeStamp = -1):
	UE_Message(Cat1, Cat2, Cat3, pData, dataLen, fixup, timeStamp)
	{
		m_dwMsgFrame = 0;
		m_dwMsgFrame2 = 0;
	}

	UE_FrameMessage(UE_Message& rep)
	{
		m_Cat1 = rep.m_Cat1;
		m_Cat2 = rep.m_Cat2;
		m_Cat3 = rep.m_Cat3;
		m_pData = rep.m_pData;
		m_DataLen = rep.m_DataLen;
		m_Fixup = rep.m_Fixup;
		m_TimeStamp = rep.m_TimeStamp;
		m_TargetType = rep.m_TargetType;
		m_MaxDataLen = rep.m_MaxDataLen;

		m_bPack	= rep.m_bPack;
		m_bIsAlign4 = rep.m_bIsAlign4;

	}
};

class UE_MessageWithId : public UE_Message{
public:
  	 USHORT m_ModuleID;
	 USHORT m_MessageID;

   UE_MessageWithId(const CStringW &Cat1 = ALL, const CStringW &Cat2 = ALL, const CStringW &Cat3 = ALL, USHORT ModuleId = 0,USHORT MessageId = 0, BYTE *pData = NULL, WORD dataLen = 0, bool fixup = false,  DWORD timeStamp = -1, eTargetType	targetType = UE_Comm_Side) :
   UE_Message(Cat1, Cat2, Cat3, pData, dataLen, fixup, timeStamp, targetType)
   {
		m_ModuleID = ModuleId;
		m_MessageID = MessageId;
   }
};

class ASN1_Parameter
{
public:
	BYTE	m_radioBearer;
	BYTE	m_direction;
	BYTE	m_trCh;
	BYTE	m_rlcmode;
	BYTE	m_SibType;
	WORD	m_asnMsgLen;
	BYTE*	m_asn1ContentPtr;
	UINT64	m_messageid;
	int		m_deviceid;
private:
	friend class CCommandAndControl;
public:
	ASN1_Parameter(BYTE radioBearer = 0xFF/*RBID_INVALID*/,BYTE direction = 0/*NEUTRAL*/,BYTE trCh = 0xFF/*TC_INVALID*/, BYTE rlcmode = 0xFF/*RLC_MODE_INVALID*/,
				BYTE SibType = 0,WORD asnMsgLen = 0,BYTE* asn1ContentPtr = NULL,UINT64 messageid = 0,int  deviceid = -1)
	{
		m_radioBearer = radioBearer;
		m_direction = direction;
		m_trCh = trCh;
		m_rlcmode = rlcmode;
		m_SibType = SibType;
		m_asnMsgLen = asnMsgLen;
		m_asn1ContentPtr = asn1ContentPtr;
		m_messageid = messageid;
		m_deviceid = deviceid;
	}
};
// static void SetTargetType(UE_Message *command)
// {
// #if 1
// 	command->m_TargetType = UE_Comm_Side;
// #else
// 	if (DialogAudioCalibrationTab::GetTargetType() == ONE_CHIP_CONFIGURATION)
// 		command->m_TargetType = UE_Comm_Side;
// 	else
// 		command->m_TargetType = UE_App_Side;
// #endif
// }
// class UE_FrameMessage : public UE_Message
// {
// 	public:
// 	DWORD	m_dwMsgFrame;
// 
// 	UE_FrameMessage(const CString &Cat1 = ALL, const CString &Cat2 = ALL, const CString &Cat3 = ALL, BYTE *pData = NULL, WORD dataLen = 0, bool fixup = false, DWORD timeStamp = -1):
// 		UE_Message(Cat1, Cat2, Cat3, pData, dataLen, fixup, timeStamp)
// 		{
// 			m_dwMsgFrame = 0;
// 		}
// 
// 	UE_FrameMessage(UE_Message& rep)
// 	{
// 		m_Cat1 = rep.m_Cat1;
// 		m_Cat2 = rep.m_Cat2;
// 		m_Cat3 = rep.m_Cat3;
// 		m_pData = rep.m_pData;
// 		m_DataLen = rep.m_DataLen;
// 		m_Fixup = rep.m_Fixup;
// 		m_TimeStamp = rep.m_TimeStamp;
// 		m_TargetType = rep.m_TargetType;
// 		m_MaxDataLen = (DWORD)(-1);
// 
// 	}
// };


class UE_ExtMessage : public UE_Message{
public:
   WORD	m_Opcode;
   DWORD	m_dwMsgFrame;
   UE_ExtMessage(const CStringW &Cat1 = ALL, const CStringW &Cat2 = ALL, const CStringW &Cat3 = ALL, WORD opCode = ALL_OPCODES, BYTE *pData = NULL, WORD dataLen = 0, bool fixup = false,  DWORD timeStamp = -1, eTargetType	targetType = UE_Comm_Side) :
   UE_Message(Cat1, Cat2, Cat3, pData, dataLen, fixup, timeStamp, targetType)
   {
      m_Opcode = opCode;
	  m_dwMsgFrame = 0;
   }


};


typedef enum {NO_COPY=0, COPY_KNOWN=1, COPY_UNKNOWN=2} eCopyType;

 class UE_IpcMessage : public UE_ExtMessage
 {
 public:
 	BYTE	*m_pDataPacket;
 	WORD	m_DataPacketLength;	// Note: data-packet length and data-parameters in Bytes
 	DWORD	m_Pointer;
 	BYTE	m_CopyType;
 	BYTE	m_ChannelID;
 
 	UE_IpcMessage(const CStringW &Cat1 = ALL, const CStringW &Cat2 = ALL, const CStringW &Cat3 = ALL, WORD opCode = ALL_OPCODES, BYTE *pData = NULL, WORD dataLen = 0, BYTE *pDataPacket = NULL, WORD dataPacketLen = 0, DWORD pointer = 0, BYTE copyType = 0, BYTE channelID = 0, bool fixup = false,  DWORD timeStamp = -1, eTargetType	targetType = UE_Comm_Side ) :
 		UE_ExtMessage(Cat1, Cat2, Cat3, opCode, pData ,dataLen , fixup , timeStamp, targetType)
 	{
 		m_pDataPacket		= pDataPacket;
 		m_DataPacketLength	= dataPacketLen;	
 		m_Pointer			= pointer;		
 		m_CopyType			= copyType;		
 		m_ChannelID			= channelID;				
 	}
 
 };
 
class GKI_Signal
{
public:
   BOOL	m_bLoggedSignal;
   WORD	m_SourceTaskID;
   WORD	m_TargetTaskID;
   DWORD	m_FrameNumber;
   DWORD	m_FrameTicks;
   WORD	m_SignalLength;
   DWORD	m_SignalID;
   CStringW m_SignalName;
   BYTE	*m_pSignalBody;
private:
   DWORD	m_MaxDataLen;

   friend class CCommandChannel;

public:
   GKI_Signal(const CStringW &a_SignalName=_T(""), BYTE* a_pSignalBody=NULL, WORD a_SignalLength=0, WORD a_SourceTaskID=0, WORD	a_TargetTaskID=0): 
      m_pSignalBody (a_pSignalBody),
         m_SignalLength (a_SignalLength),
         m_SourceTaskID (a_SourceTaskID),
         m_TargetTaskID (a_TargetTaskID),
         m_FrameNumber (0),
         m_FrameTicks (0),
         m_MaxDataLen ((DWORD)(-1))
      {
         m_SignalName = a_SignalName;
      }
};

// This class is for sending GKI Signals to the App. side.
// It is for backwards compatibility (instead of adding another field to the GKI_Signal class). 
class GKI_App_Signal : public GKI_Signal
{
public :
	GKI_App_Signal(const CStringW &a_SignalName=_T(""), BYTE* a_pSignalBody=NULL, WORD a_SignalLength=0, WORD a_SourceTaskID=0, WORD	a_TargetTaskID=0) :
		GKI_Signal(a_SignalName, a_pSignalBody, a_SignalLength, a_SourceTaskID, a_TargetTaskID)
	{

	}

	virtual void DoNothing() { ; } 
};


class GKI_Command
{
public:
   WORD	m_CommandID;
   CStringW m_CommandName;
   BYTE	*m_pCommandBody;
   int		m_BodyLength;

public:
   GKI_Command(const CStringW &a_CommandName = _T(""), BYTE *a_pCommandBody = NULL, int a_nBodyLength = 0) : 
      m_pCommandBody(a_pCommandBody),
         m_BodyLength(a_nBodyLength)
      { 
         m_CommandName = a_CommandName;
      }
};


// This class is for sending GKI Commands to the App. side.
// It is for backwards compatibility (instead of adding another field to the GKI_Command class). 
class GKI_App_Command : public GKI_Command
{
public:
	GKI_App_Command(const CStringW &a_CommandName = _T(""), BYTE *a_pCommandBody = NULL, int a_nBodyLength = 0) :
		GKI_Command(a_CommandName, a_pCommandBody, a_nBodyLength)
	{

	}

	virtual void DoNothing() { ; } 
};


#endif // __COMMAND_AND_MESSAGE_STRUCTURES_H__