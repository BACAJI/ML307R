#pragma once
#include "SystemTime.h"

////////////////////////////////////////////////////////////////////////
class  IDiagMessage
{
public:
	virtual ~IDiagMessage() {;}

	virtual void Delete()=0;


	virtual bool IsApp()=0;
	virtual bool IsFrame2Exist()=0;

	virtual LPBYTE	GetDataBuffer()=0;
	virtual WORD	GetDataBufferLen()=0;

	virtual LPBYTE	GetData(UINT = 0)=0;
	virtual WORD	GetDataLen()=0;

	virtual BYTE	GetMsgType()=0;
	virtual BYTE	GetHeaderLen_DW()=0;
	virtual BYTE	GetChannel()=0;
	virtual BYTE	GetSrcId()=0;
	virtual BYTE	GetDstId()=0;
	virtual DWORD	GetTargetTs()=0;
	virtual WORD	GetMsgId()=0;
	virtual WORD	GetMsgCtr()=0;
	virtual DWORD	GetFrameNum()=0;
	virtual DWORD	GetFrame2Num()=0;
	virtual WORD	GetHeaderLen()=0;

	virtual BYTE	GetDiagSap()=0;
	virtual BYTE	GetService()=0;
	virtual BYTE	GetModuleID(bool bFromData = false)=0;
	virtual WORD	GetFullDiagSap()=0;
	virtual BYTE	GetDiagId()=0;
	virtual WORD	GetExtraData()=0;

	virtual WORD	GetDspOpCode()=0;
	virtual WORD	GetEntireDspOpCode()=0;

	virtual bool	IsMessageTypeDiag()=0;
	virtual bool	IsMessageTypeService()=0;
	virtual bool	IsMessageTypeSignal()=0;
	virtual bool	IsMessageTypeString()=0;
	virtual int		GetDiagMessageType()=0;
	virtual bool	IsAligned()=0;

	virtual bool	IsValidMessage()=0;
	virtual int		GetDevice()=0;
	virtual UINT64	GetMessageNumber()=0;
	virtual const CSystemTime&	GetPCTimeStamp()=0;
	virtual bool GetUserRemark(CString&)=0;

	virtual bool    IsPrintMessage()=0;
	virtual BYTE	GetClientID()=0;
};

