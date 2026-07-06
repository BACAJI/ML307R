/*===============================================================================
* Copyright (C) 2008-2011 Marvell Technology Shanghai Ltd., HEFEI Branch.
* All right reserved.
*             
* File Name : CICATMessage.h
* Brief     : Header file of
* Version   : 1.0.0.1
* Author    : 
=================================================================================*/
#pragma once
#include <afxmt.h>
#include "SystemTime.h"
#include "DiagMessage.h"

#ifndef MAKEUINT64
	#define MAKEUINT64(low, hi)    ((UINT64)(((DWORD)(low)) | ((UINT64)((DWORD)(hi))) << 32))
#endif // MAKEUINT64
#ifndef LODWORD
	#define LODWORD(l)          ((DWORD)(l))
#endif // LODWORD
#ifndef HIDWORD
	#define HIDWORD(l)			((DWORD)(((UINT64)(l) >> 32) & 0xFFFFFFFF))
#endif // HIDWORD


//DIAG Sap
/////////////////////////////////////////////////////////////////////////

/////////////////////////// DiagSAP Definitions: /////////////////////////////

#define DIAG_SAP_INDEX			0
#define PDU_HEADER_LEN			12

#define DIAG_HEADER_FOR_RECEIVING_MI_SIGNALS	8	// only Diag-SAP + Time-Stamp
#define DIAG_HEADER_FOR_RECEIVING_MI_SIGANLS	DIAG_HEADER_FOR_RECEIVING_MI_SIGNALS	// backwards compatibility

#define APP_SIDE_MASK_FOR_SENDING		((BYTE)0x80)
#define APP_SIDE_MASK_FOR_RECEIVING		((WORD)0x8000)

#define SECOND_FRAME_MASK				((WORD)0x4000)

#define APPLICATION_REPORT			0
#define RETURN_SERVICE				1
#define RSVP_SERVICE				2
//#define APPLICATION_REPORT_FIXUP	3
#define APPLICATION_REPORT_ALIGNED	4
#define DIAG_MI_LOGGED_SIGNAL			5
#define DIAG_MI_COMMAND					5
#define DIAG_MI_SIGNAL					6
#define DIAG_MI_SPECIAL_LOGGED_SIGNAL	7
//////////////////////////////////////////////////////////////////////////

#define MAX_ALIGN_STRUCT	4

enum EMsgError
{
   kNoError				= 0,
   //HOST_ERROR				= 1,        
   //HOST_NO_RX_DATA		= 2,
   //HOST_TOO_MUCH_DATA	= 3,
   //HOST_DEVICE_CLOSED	= 4,
   kInvalidMessageSize		= 5,
   kInvalidLongMessageSize	= 6,
   kLRCCalculationFailed	= 7,
   kParityError			= 8,
   kWrongMessageSequence   = 9,
   kInvalidProtocolID		= 10
};

enum EProtocolType 
{
	eStringProtocol = 0,
	eDIAGProtocol	/*=1*/,
	eEMMIProtocol	/*=2*/,
	eProtocolStrings /*=3*/,
   eNMEAProtocol /*=4*/,
   eMEEDProtocol /*=5*/,
   eADBProtocol /*=6*/,
};

class IDiagMessage;

#pragma pack(push,1)
class CSerialzeData
{
public:

	enum eDirection {
		MessageIN = 0,
		MessageOUT = 1,
		MessageOUT_Device1 = 2,
		MessageOUT_Device2 = 4,
		MessageOUT_Device3 = 8,
		MessageOUT_Device4 = 16,
		MessageOUT_Device5 = 32,
		MessageOUT_ALL = 2046,

		MessageIN_Device1 = MessageOUT_Device1,
		MessageIN_Device2 = MessageOUT_Device2,
		MessageIN_Device3 = MessageOUT_Device3,
		MessageIN_Device4 = MessageOUT_Device4,
		MessageIN_Device5 = MessageOUT_Device5,
		MessageIN_ALL = MessageOUT_ALL
	};


//private:
	int				m_DataLen;

public:
	int				m_ModuleID;
	int				m_InstanceID;

	eDirection		m_Direction;
	
	UINT			m_bConvertable;
	UINT64			m_MessageNumber;
	BYTE			m_UserRemark;

	friend class CICATMessage;
	friend class CMessageSender;
	friend class CDiagMessage;
	friend class CCommInterface;
};
#pragma pack(pop)




#ifdef _CATCORE_DLL
class __declspec(dllexport) CICATMessage : public CSerialzeData
#else
class __declspec(dllimport) CICATMessage : public CSerialzeData
#endif
{
public:
  static enum EDiagCmdIndices
  {
    kCmdSap		= 0,
    kSrvId		= 1,
    kCmdModId	= 2,
    kCmdId		= 4,
    kCmdSrcId	= 8,
    kCmdData	= 12
  };

  static enum EDiagMsgIndices
  {
    kMsgSap		= 0,
    kMsgLCount	= 2,
    kMsgModId	= 4,
    kMsgHCount	= 5,
    kMsgId		= 6,
    kMsgArmTS	= 8,
    kMsgData	= 12
  };

  static enum EDiagRsvpMsgIndices
  {
    kRMsgSap	= 0,
    kRMsgLCount	= 2,
    kRMsgModId  = 4,
    kRMsgHCount	= 5,
    kRMsgMsgId	= 6,
    kRMsgArmTS	= 8,
    kRMsgSrcId	= 12,
    kRMsgData	= 16
  };

//   enum eDirection {
//     MessageIN = 0,
//     MessageOUT = 1,
//     MessageOUT_Device1 = 2,
//     MessageOUT_Device2 = 4,
//     MessageOUT_Device3 = 8,
//     MessageOUT_Device4 = 16,
//     MessageOUT_Device5 = 32,
//     MessageOUT_ALL = 2046,
// 
//     MessageIN_Device1 = MessageOUT_Device1,
//     MessageIN_Device2 = MessageOUT_Device2,
//     MessageIN_Device3 = MessageOUT_Device3,
//     MessageIN_Device4 = MessageOUT_Device4,
//     MessageIN_Device5 = MessageOUT_Device5,
//     MessageIN_ALL = MessageOUT_ALL
//   };

public:
//	  int				m_ModuleID;
//	  int				m_InstanceID;
	  CSystemTime		m_Time;
//    int				    m_DataLen;
	  BYTE			   *m_pData;
// 	  eDirection		m_Direction;
//    UINT64			m_MessageNumber;
//    UINT			    m_bConvertable; // Actually of enum type EProtocolType; says how this message should be interpreted.
      BYTE			    m_nDiagHCounter;
// 	  BYTE			    m_UserRemark;
	  EMsgError		    m_Error;
	  static UINT64	    m_MessageCounter;
	  int		        m_ReceiversCounter;
	  static CCriticalSection	m_NumberLock;
	  static CCriticalSection   m_ReceiversCounterLock;
	  CCriticalSection			m_LockDiagmsg;
	  int						m_DiagIndex;

private:
#ifdef DEBUG
	static bool s_firstLoggingForSession;
	static int Log(const CString* trace = NULL);
#endif

public:
  void AddRef(const CString* callerName = NULL);
  CICATMessage();
  CICATMessage(int m, int i, BYTE *pd = NULL, int dl = 0, BOOL bMemAlocation = true);
  CICATMessage(int Prot, int m, int i, BYTE *pd =NULL, int dl=0, BOOL bMemAllocation = true); 
  CICATMessage(int m, int i, BYTE *pd , int dl , BYTE *pd2 , int dl2);  
  CICATMessage(CICATMessage &message);
  ~CICATMessage();
  void operator = (CICATMessage &message);

  bool IsFromTarget();

  unsigned long long Delete(const CString* callerName = NULL);
  void GetNumber();
  void Serialize(CArchive& ar);
  int GetMsgSize(bool bIncludeDataLength = true);
  friend class CTmpDiagMessage;
  //////////////////////////////////////////////////////////////////////////
protected:
  IDiagMessage* CreateDiagMsg();
  IDiagMessage* m_pDiagMessage;
  CTmpDiagMessage	 m_tmpMsg;
  bool			m_bIsMsgInit;
  void InitDiagMsg();

  void SetMessage()
  {
	  if (m_pDiagMessage != NULL)
	  {
		  return;
	  }

	  CreateDiagMsg();
  };

public:
  BOOL IsEmpty();
  BOOL IsDiagProtocol();
  bool IsValid()
  {
	  return (m_DataLen > 0);
  }

  virtual bool IsApp()
  {
  	return m_pDiagMessage->IsApp();
  }
    
  UINT  GetLengthInFile();
  virtual bool IsFrame2Exist()
  {
  	return m_pDiagMessage->IsFrame2Exist();
  }

  virtual bool IsClientMatch(int targetType); 
  virtual int  GetClientID();
  virtual WORD	GetMsgId();
  // BYTE	GetModuleID();
  virtual WORD GetEntireDspOpCode();
  virtual WORD	GetDataLen();
  virtual BYTE* GetData(UINT idx=0);
  virtual int   GetDevice();
  virtual DWORD GetTargetTs();
  virtual LPBYTE	GetDataBuffer();
  virtual WORD	GetDataBufferLen();
  
  virtual BYTE	GetMsgType();
  virtual BYTE	GetHeaderLen_DW();
  virtual BYTE	GetPriority();
  virtual BYTE	GetChannel();
  virtual BYTE	GetSrcId();
  virtual BYTE	GetDstId();
  virtual WORD	GetMsgCtr();
  virtual DWORD	GetFrameNum();
  virtual DWORD	GetFrame2Num();
  virtual WORD	GetHeaderLen();
  
  virtual BYTE	GetDiagSap();
  virtual BYTE	GetService();
  virtual BYTE	GetModuleID(bool bFromData = false);
  virtual WORD	GetFullDiagSap();
  virtual BYTE	GetDiagId();
  virtual WORD  GetExtraData();
  virtual WORD	GetDspOpCode();
  
  virtual bool	IsMessageTypeDiag();
  virtual bool	IsMessageTypeService();
  virtual bool	IsMessageTypeSignal();
  virtual bool	IsMessageTypeString();
  virtual int		GetDiagMessageType();
  virtual bool	IsAligned();
  
  virtual bool	IsValidMessage();
  virtual UINT64	GetMessageNumber();
  virtual const CSystemTime&	GetPCTimeStamp();
  virtual bool GetUserRemark(CString&);
  
  virtual bool    IsPrintMessage();
  
  /////////////////////////////////////////////////////////////////////////
  
  friend class CMessageSender;
  friend class CDiagMessage;
  friend class CCommInterface;
  friend class CMessageReaderEx;
};

#define eMessageIN			CICATMessage::MessageIN
#define eMessageOUT			CICATMessage::MessageOUT
#define eMessageOUT_Device1	CICATMessage::MessageOUT_Device1
#define eMessageOUT_Device2	CICATMessage::MessageOUT_Device2
#define eMessageOUT_Device3	CICATMessage::MessageOUT_Device3
#define eMessageOUT_Device4	CICATMessage::MessageOUT_Device4
#define eMessageOUT_Device5	CICATMessage::MessageOUT_Device5
#define eMessageOUT_ALL		CICATMessage::MessageOUT_ALL

