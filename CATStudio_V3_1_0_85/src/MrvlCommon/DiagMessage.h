// DiagMessage.h: interface for the CDiagMessage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIAGMESSAGE_H__99829ACB_6953_4424_9B30_CADD04858B2B__INCLUDED_)
#define AFX_DIAGMESSAGE_H__99829ACB_6953_4424_9B30_CADD04858B2B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IDiagMessage.h"
#include "GeneralFunctions.h"

class CICATMessage;
class CSystemTime;

enum EMsgTypesId
{
	//////////  Internal Service Messages //////////
	
	IS_DB_VERSION_SERVICE			= 0x00,	
	//IS_GET_CLOCK_RATE				= 0x02,
	IS_ICAT_DIAG_READY_NOTIFY		= 0x04,
	//IS_ENTER_BOOTLOADER_MODE		= 0x06,//Hermon
	//IS_SEND_FULL_FRAME_NUM			= 0x09,//L1-validation???
	IS_UE_CP_INFO						= 0x0B,
	IS_ACAT_DISCONNECT_NOTIFY			= 0x0C,//12,
	IS_ACAT_KEEP_ALIVE					= 0x0D,//13,
	ClientDB_REQ					= 0x0E,
	ClientDB_REQ_STATUS				= 0x0F,
	ClientDB_DATA					= 0x10,
	ClientDB_DATA_STATUS			= 0x11,
	IS_MAX_NUMBER					= 0x2F,
	///////////////////////////////////////////////
	//////////////  Control Messages //////////////
	
	CM_TX_COMMAND_EXPORT_FUNC		= 0x30, //DIAG SAP = 1,(3)
	CM_TX_SIGNAL_COMMAND			= 0x31, //DIAG SAP = 6
	
	///////////////////////////////////////////////
	//////////////// Data Messages ////////////////
	
	DM_RX_TRACE						= 0x80, //DIAG SAP = 0,4
	DM_RX_TRACE_AND_FN				= 0x81, //DIAG SAP = 0,4
	DM_RX_SIGNAL					= 0x82  //DIAG SAP = 5
	
	///////////////////////////////////////////////	
};

enum ESrcDstValues
{
	diag_entity_Comm	= 0x00,
	diag_entity_App		= 0x01,
	diag_entity_Acat	= 0xff
};

#define DIAG_MESSAGE_DIAG	1
#define DIAG_MESSAGE_IS		2
#define DIAG_MESSAGE_GKI	3
#define DIAG_MESSAGE_STRING	4

#define MAX_DIAG_HEADER_SIZE	20

struct stDiagHeaderParams
{
	int		nSource;

	int		nId; /*Message or service */
	int		nModulId;


	int		nPriority;

	int		nMsgCount;
	int		nFrame;
	int		nFrame2;

	bool	bFrame;
	bool	bFrame2;

	unsigned long	TimeStamp;

	bool			bExGKI;
	int				SourceTaskId;
	int				TargetTaskId;
	unsigned int	FrameTicks;
	unsigned int	SignalId;

	stDiagHeaderParams() : nSource(0), nPriority(1), nMsgCount(0), bFrame(false), bFrame2(false), TimeStamp(0), bExGKI(false),
				SourceTaskId(0), TargetTaskId(0), FrameTicks(0), SignalId(0){}
	stDiagHeaderParams(int source, int id, int module = 0): nSource(source), nId(id), nModulId(module),
		nPriority(1), nMsgCount(0), bFrame(false), bFrame2(false), TimeStamp(0), bExGKI(false) {}
	stDiagHeaderParams(unsigned int SigId, int SourceId, int TargetId, unsigned int Frame, unsigned int Tics): 
		nSource(0), nModulId(0), nPriority(1), nMsgCount(0), bFrame(true), bFrame2(false), TimeStamp(0), 
		bExGKI(true), SignalId(SigId), SourceTaskId(SourceId), TargetTaskId(TargetId), nFrame(Frame), FrameTicks(Tics) {}

	void SetPriority(int priority) {nPriority = priority;}
	void SetMessageCount(int MsgCnt) {nMsgCount = MsgCnt;}
	void SetFrame(int frame){nFrame = frame; bFrame = true;}
	void SetFrame2(int frame){nFrame2 = frame; bFrame2 = true;}
	void SetTimeStamp(unsigned long ts){TimeStamp = ts;}
	void SetSignalId(unsigned int SigId){SignalId = SigId; bExGKI = true;}
};


class CDiagMessage :public IDiagMessage  
{
protected:

	LPBYTE			m_pData;
	WORD			m_DataLen;
	CICATMessage*	m_pMessage;

	bool			m_bFromTarget;
	bool			m_bApp;
	bool			m_bFrame2Exist;

public:
	CDiagMessage(CICATMessage* pMessage);
	CDiagMessage();
	virtual ~CDiagMessage();

	void Delete(){delete this;};

	virtual bool IsApp() {return m_bApp;}
	virtual bool IsFromTarget() {return m_bFromTarget;}
	virtual bool IsFrame2Exist() {return m_bFrame2Exist;}

	virtual int BuildHeader(LPBYTE pData, int nBufLen, int nId, int nModule, DWORD dwDBVersion, int nDestination=0, bool bFixup=false){return 0;}
	virtual int	BuildTargetHeader(LPBYTE pData, int nBufLen, stDiagHeaderParams & param){return 0;}

	virtual LPBYTE	GetDataBuffer();
	virtual WORD	GetDataBufferLen();
	virtual BYTE	GetMsgType()		{return 0;}
	virtual BYTE	GetHeaderLen_DW()	{return 0;}
	virtual BYTE	GetChannel()		{return 0;}
	virtual BYTE	GetSrcId()			{return 0;}
	virtual BYTE	GetDstId()			{return 0;}
	virtual DWORD	GetTargetTs()		{return 0;}
	virtual WORD	GetMsgId()			{return 0;}
	virtual WORD	GetMsgCtr()			{return 0;}
	virtual DWORD	GetFrameNum()		{return 0;}
	virtual DWORD	GetFrame2Num()		{return 0;}
	virtual LPBYTE	GetData(UINT nIdx = 0);
	virtual WORD	GetHeaderLen()		{return 0;}
	virtual WORD	GetDataLen();
	virtual WORD	GetExtraData()		{return 0;}

	virtual BYTE	GetDiagSap()		{return 0;}
	virtual BYTE	GetService()		{return 0xFF;}
	virtual BYTE	GetModuleID(bool bFromData = false)		{return 0;}
	virtual WORD	GetFullDiagSap();

	virtual BYTE	GetDiagId()					{return 0;}
	virtual bool	IsDiagProtocol()			{return false;}
	virtual bool	IsMessageTypeDiag()			{return false;}
	virtual bool	IsMessageTypeService()		{return false;}
	virtual bool	IsMessageTypeSignal()		{return false;}
	virtual bool	IsMessageTypeString()		{return false;}
	virtual int		GetDiagMessageType()		{return 0;}
	virtual	bool	IsAligned()					{return false;}
	virtual WORD	GetDspOpCode()				{return 0;}
	virtual WORD	GetEntireDspOpCode()		{return 0;}


	virtual bool	IsValidMessage();
	virtual int		GetDevice();
	virtual	UINT64	GetMessageNumber();
	virtual const CSystemTime&	GetPCTimeStamp();
	virtual bool GetUserRemark(CString&);

	virtual bool    IsPrintMessage();
	virtual BYTE	GetClientID()				{return 0;}
};

class CDumyMessage : public CDiagMessage
{

public:
	CDumyMessage();
	virtual ~CDumyMessage();

	virtual bool	IsValidMessage()		{return false;}	
	virtual int		GetDevice()				{return 0;}
	virtual	UINT64	GetMessageNumber()		{return 0;}
	virtual const CSystemTime&	GetPCTimeStamp();
};



class CStringMessage : public CDiagMessage
{
public:
	CStringMessage(CICATMessage* pMessage);
	CStringMessage();
	virtual ~CStringMessage();
	virtual bool	IsMessageTypeString()	{return true;}
	virtual int		GetDiagMessageType()	{return DIAG_MESSAGE_STRING;}
};

class CDiag1Message : public CDiagMessage
{
protected:
	enum EMsgToTargetFormat
	{
		diag1To_SAP			= 0,
		diag1To_serviceID	= 1,
		diag1To_moduleID	= 2,
		diag1To_commandID	= 4,
		diag1To_sourceID	= 8
	};

	enum EMsgFromTargetFormat
	{
		diag1From_SAP		= 0,
		diag1From_MsgCount	= 2,
		diag1From_Frame		= 2,
		diag1From_moduleID	= 4,
		diag1From_FrameHigh = 5,
		diag1From_commandID	= 6,
		diag1From_serviceID	= 6,
		diag1GKIFrom_TimeStamp	= 4,
		diag1From_TimeStamp	= 8
	};

public:
	CDiag1Message(CICATMessage* pMessage);
	CDiag1Message();
	virtual ~CDiag1Message();

	virtual BYTE	GetMsgType();
	virtual BYTE	GetHeaderLen_DW();
	virtual BYTE	GetChannel();
	virtual BYTE	GetSrcId();
	virtual BYTE	GetDstId();
	virtual DWORD	GetTargetTs();
	virtual WORD	GetMsgId();
	virtual WORD	GetMsgCtr();
	virtual DWORD	GetFrameNum();
	virtual WORD	GetHeaderLen();

	virtual BYTE	GetDiagSap();
	virtual BYTE	GetModuleID(bool bFromData = false);

	virtual BYTE	GetDiagId()			{return 1;}
	virtual bool	IsDiagProtocol()	{return true;}

	virtual BYTE	GetClientID();
	virtual WORD	GetExtraData();
//	virtual bool	IsValidMessage();
};

class CTmpDiagMessage :public CDiag1Message  
{
protected:

	CDiagMessage* CreateDiagMsg();
public:
	CTmpDiagMessage(CICATMessage* pMessage);
	virtual ~CTmpDiagMessage(){};

	virtual bool IsApp()						{return CreateDiagMsg()->IsApp();			 }
	virtual bool IsFromTarget()					{return CreateDiagMsg()->IsFromTarget();	 }
	virtual bool IsFrame2Exist()				{return CreateDiagMsg()->IsFrame2Exist();	 }

	virtual int BuildHeader(LPBYTE pData, int nBufLen, int nId, int nModule, DWORD dwDBVersion, int nDestination=0, bool bFixup=false){return CreateDiagMsg()->BuildHeader(pData,nBufLen, nId, nModule, dwDBVersion, nDestination, bFixup);}
	virtual int	BuildTargetHeader(LPBYTE pData, int nBufLen, stDiagHeaderParams & param){return CreateDiagMsg()->BuildTargetHeader(pData, nBufLen, param);}

	virtual LPBYTE	GetDataBuffer();
 	virtual WORD	GetDataBufferLen();
	virtual BYTE	GetMsgType()		{return CreateDiagMsg()->GetMsgType()		;}
	virtual BYTE	GetHeaderLen_DW()	{return CreateDiagMsg()->GetHeaderLen_DW()	;}
	virtual BYTE	GetChannel()		{return CreateDiagMsg()->GetChannel()		;}
	virtual BYTE	GetSrcId()			{return CreateDiagMsg()->GetSrcId()			;}
	virtual BYTE	GetDstId()			{return CreateDiagMsg()->GetDstId()			;}
	virtual DWORD	GetTargetTs()		{return CreateDiagMsg()->GetTargetTs()		;}
	virtual WORD	GetMsgId()			{return CreateDiagMsg()->GetMsgId()			;}
	virtual WORD	GetMsgCtr()			{return CreateDiagMsg()->GetMsgCtr()		;}
	virtual DWORD	GetFrameNum()		{return CreateDiagMsg()->GetFrameNum()		;}
	virtual DWORD	GetFrame2Num()		{return CreateDiagMsg()->GetFrame2Num()		;}
	virtual LPBYTE	GetData(UINT nIdx = 0){return CreateDiagMsg()->GetData(nIdx)	;}
	virtual WORD	GetHeaderLen()		{return CreateDiagMsg()->GetHeaderLen()		;}
	virtual WORD	GetDataLen()		{return CreateDiagMsg()->GetDataLen()		;}
	virtual WORD	GetExtraData()		{return CreateDiagMsg()->GetExtraData()		;}

	virtual BYTE	GetDiagSap()		{return CreateDiagMsg()->GetDiagSap();		 }
	virtual BYTE	GetService()		{return CreateDiagMsg()->GetService();		 }
	virtual BYTE	GetModuleID(bool bFromData = false)		{return CreateDiagMsg()->GetModuleID(bFromData);}
//	virtual WORD	GetFullDiagSap();

//	virtual BYTE	GetDiagId()					{return 1;}
	virtual bool	IsDiagProtocol()			{return CreateDiagMsg()->IsDiagProtocol()		;}
	virtual bool	IsMessageTypeDiag()			{return CreateDiagMsg()->IsMessageTypeDiag()	;}
	virtual bool	IsMessageTypeService()		{return CreateDiagMsg()->IsMessageTypeService()	;}
	virtual bool	IsMessageTypeSignal()		{return CreateDiagMsg()->IsMessageTypeSignal()	;}
	virtual bool	IsMessageTypeString()		{return CreateDiagMsg()->IsMessageTypeString()	;}
	virtual int		GetDiagMessageType()		{return CreateDiagMsg()->GetDiagMessageType()	;}
	virtual	bool	IsAligned()					{return CreateDiagMsg()->IsAligned()			;}
	virtual WORD	GetDspOpCode()				{return CreateDiagMsg()->GetDspOpCode()			;}
	virtual WORD	GetEntireDspOpCode()		{return CreateDiagMsg()->GetEntireDspOpCode()	;}


//	virtual bool	IsValidMessage();
	virtual int		GetDevice()					{return CreateDiagMsg()->GetDevice()			;}
//	virtual	UINT64	GetMessageNumber();
//	virtual const CSystemTime&	GetPCTimeStamp();
//	virtual bool GetUserRemark(CString&);

//	virtual bool    IsPrintMessage();
//	virtual BYTE	GetClientID()				{return 0;}
};

class CDiag1MessageDiag : public CDiag1Message
{
public:
	CDiag1MessageDiag(CICATMessage* pMessage);
	CDiag1MessageDiag();
	virtual ~CDiag1MessageDiag();
	
	virtual int		BuildHeader(LPBYTE pData, int nBufLen, int nId, int nModule, DWORD dwDBVersion, int nDestination=0, bool bFixup=false);
	virtual int		BuildTargetHeader(LPBYTE pData, int nBufLen, stDiagHeaderParams & param);
	virtual bool	IsMessageTypeDiag()		{return true;}
	virtual bool	IsAligned();
	virtual int		GetDiagMessageType()	{return DIAG_MESSAGE_DIAG;}

	virtual WORD	GetDspOpCode();
	virtual WORD	GetEntireDspOpCode();	
	virtual DWORD	GetFrame2Num();
};

class CDiag1MessageIS : public CDiag1Message
{
public:
	CDiag1MessageIS(CICATMessage* pMessage);
	CDiag1MessageIS();
	virtual ~CDiag1MessageIS();
	
	virtual BYTE	GetService();
	virtual int		BuildHeader(LPBYTE pData, int nBufLen, int nId, int nModule, DWORD dwDBVersion, int nDestination=0, bool bFixup=false);
	virtual int		BuildTargetHeader(LPBYTE pData, int nBufLen, stDiagHeaderParams & param);
	virtual bool	IsMessageTypeService()	{return true;}
	virtual int		GetDiagMessageType()	{return DIAG_MESSAGE_IS;}
};


class CDiag1MessageGKI : public CDiag1Message
{

public:
	CDiag1MessageGKI(CICATMessage* pMessage);
	CDiag1MessageGKI();
	virtual ~CDiag1MessageGKI();
	
	virtual int		BuildHeader(LPBYTE pData, int nBufLen, int nId, int nModule, DWORD dwDBVersion, int nDestination=0, bool bFixup=false);
	virtual int		BuildTargetHeader(LPBYTE pData, int nBufLen, stDiagHeaderParams & param);
	virtual bool	IsMessageTypeSignal()	{return true;}
	virtual int		GetDiagMessageType()	{return DIAG_MESSAGE_GKI;}

	virtual DWORD	GetTargetTs();
	virtual WORD	GetHeaderLen();
	virtual BYTE	GetModuleID(bool bFromData = false) {return 0;}
};

///////////////////////////////////////////////////////////////////////

class CHeaderBuilder
{
	DECLARE_NO_COPY(CHeaderBuilder)

	CDiagMessage* m_pDiagMessage;

public:
	CHeaderBuilder(int nType);
	~CHeaderBuilder();

	int BuildHeader(LPBYTE pData, int nBufLen, int nId, int nModule, DWORD dwDBVersion, int nDestination=0, bool bFixup=false);
	int	BuildTargetHeader(LPBYTE pData, int nBufLen, stDiagHeaderParams & param);
};




#endif // !defined(AFX_DIAGMESSAGE_H__99829ACB_6953_4424_9B30_CADD04858B2B__INCLUDED_)
