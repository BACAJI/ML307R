// DiagMessage.h: interface for the CDiagMessage class.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include "..\CATCore\Converter\Converter1.h"
#include "..\CATCore\Converter\ConverterManager.h"
#include "..\CATCore\Converter\FormatData.h"
#include "GeneralFunctions.h"
#include "ICATMessage.h"
#include <afxmt.h>

//these macros already defined in ..\catcore\converter\formatData.h
//#define RAW_DATA_FORMAT_BYTE	0
//#define RAW_DATA_FORMAT_WORD	1
//#define RAW_DATA_FORMAT_DWORD	2
//
//#define RAW_DATA_PRES_DEC		0
//#define RAW_DATA_PRES_HEX		1
//
//#define RAW_MESSAGE_PRES_ASCII	0
//#define RAW_MESSAGE_PRES_NUMERIC	1
//#define RAW_MESSAGE_PRES_BOTH	2
//
//#define STRUCT_PRES_NAME		0
//#define STRUCT_PRES_DATA		1
//
//#define TIME_STAMP_FORMAT_TICKS				0
//#define TIME_STAMP_FORMAT_COTULLA_TIME		1
//#define TIME_STAMP_FORMAT_WHITESAIL_SLOW	2
//#define TIME_STAMP_FORMAT_WHITESAIL_FAST	3
//
//#define TIME_STAMP_TEXT_FORMAT_MINUTES	0
//#define TIME_STAMP_TEXT_FORMAT_SECONDS	1
//
//#define ENUM_PRES_DEC			0
//#define ENUM_PRES_HEX			1
//#define ENUM_PRES_CHAR			2
//#define ENUM_PRES_NAME			3

////////////////////////////////////////////////
////////////////////////////////////////////////

#define FRAME_NUMBER_DATA_PRES_DEC		0
#define FRAME_NUMBER_DATA_PRES_HEX		1

class CDiagMessageEx;
class CICATMessage;

#ifdef _CATCORE_DLL
#define EXPORTED_API __declspec(dllexport)
#else
#define EXPORTED_API __declspec(dllimport)
#endif

////////////////////////////////////////////////////////////////////////
class EXPORTED_API CMessageReaderEx
{
	DECLARE_NO_COPY(CMessageReaderEx)

	CDiagMessageEx	* m_pDiagMessageEx;
	CICATMessage	* m_pMessage;

	DWORD			m_dwPrevAppTimeStamp;
	DWORD			m_dwPrevCommTimeStamp;
public:

	int				m_TimeStampFormat;
	// TIME_STAMP_FORMAT_TICKS			0
	// TIME_STAMP_FORMAT_COTULLA_TIME	1
	// TIME_STAMP_FORMAT_WHITESAIL_SLOW	2
	// TIME_STAMP_FORMAT_WHITESAIL_FAST	3

	int				m_TimeStampTextFormat;
	// TIME_STAMP_TEXT_FORMAT_MINUTES	0
	// TIME_STAMP_TEXT_FORMAT_SECONDS	1

	int				m_RawFormat;
	//	RAW_DATA_FORMAT_BYTE	0
	//	RAW_DATA_FORMAT_WORD	1
	//	RAW_DATA_FORMAT_DWORD	2
	int				m_RawPres;	//char			m_FormatLetter;
	// RAW_DATA_PRES_DEC	0	'u'
	// RAW_DATA_PRES_HEX	1	'X'

	int				m_StructPres;
	// STRUCT_PRES_NAME		0
	// STRUCT_PRES_DATA		1
	BOOL			m_bLeadingZeros;

	BOOL			m_bIsOffline;

	int				m_RawMessagePresentation;
	//#define RAW_MESSAGE_PRES_ASCII	0
	//#define RAW_MESSAGE_PRES_NUMERIC	1
	//#define RAW_MESSAGE_PRES_BOTH		2

	bool			m_bIsHexDisplayMode;

	int				m_bFrameNumberFormatDec;
	// FRAME_NUMBER_DATA_PRES_DEC	0	'u'
	// FRAME_NUMBER_DATA_PRES_HEX	1	'X'
public:

	CMessageReaderEx(CICATMessage* pMessage);
	CMessageReaderEx(MessageConversionData * pMessageConversionData);
	CMessageReaderEx();
	virtual ~CMessageReaderEx();

	void InitParams();
	void InitParamsFromIni();

	bool	IsMessageTypeDSP();
	bool	IsDSPReport();
	bool	IsPLPMsg();

	void	SetMessage(CICATMessage* pMessage);
	void	SetMessage(MessageConversionData * pMessageConversionData);

	void	SetTimeStampFormat(int nFormat = TIME_STAMP_FORMAT_TICKS)							{m_TimeStampFormat = nFormat;}
	void	SetTimeStampTextFormat(int nFormat = TIME_STAMP_TEXT_FORMAT_MINUTES)				{m_TimeStampTextFormat = nFormat;}
	void	SetRawFormat(int nFormat = RAW_DATA_FORMAT_BYTE)									{m_RawFormat = nFormat;}
	void	SetStructPresentation(int nFormat = STRUCT_PRES_NAME)								{m_StructPres = nFormat;}
	void	SetHexadecimalLeadingZerosState(BOOL bState = TRUE)									{m_bLeadingZeros = bState;}
	void	SetOfflineMode(BOOL bMode = FALSE)													{m_bIsOffline = bMode;}
	void    SetRawMessagePresentation( int RawMessagePresentation = RAW_MESSAGE_PRES_ASCII )	{m_RawMessagePresentation = RawMessagePresentation;}
	void	SetFrameNumberFormat(int val = FRAME_NUMBER_DATA_PRES_DEC)							{ m_bFrameNumberFormatDec = val; }
	void	SetRawPresentation(int nFormat = RAW_DATA_PRES_HEX)									{m_RawPres = nFormat;}

	void SetHexDisplayMode(bool val) { m_bIsHexDisplayMode = val; }

	int		GetTimeStampFormat()				{return m_TimeStampFormat;}
	int		GetTimeStampTextFormat()			{return m_TimeStampTextFormat;}
	int		GetRawFormat()						{return m_RawFormat;}
	int		GetRawPresentation()				{return m_RawPres;}
	int		GetStructPresentation()				{return m_StructPres;}
	BOOL	GetHexadecimalLeadingZerosState()	{return m_bLeadingZeros;}
	BOOL	GetOfflineMode()					{return m_bIsOffline;}
	int		GetRawMessagePresentation()			{return m_RawMessagePresentation;}

	bool	GetIsHexDisplayMode() const			{return m_bIsHexDisplayMode;}
	int		GetFrameNumberFormat() const		{return m_bFrameNumberFormatDec; }

	//////////////////////
	bool IsApp()							{return m_pMessage->IsApp();}
	bool IsFrame2Exist()					{return m_pMessage->IsFrame2Exist();}
	bool IsFromTarget()						{return m_pMessage->IsFromTarget();}

	virtual LPBYTE	GetDataBuffer()			{return m_pMessage->GetDataBuffer();}
	virtual WORD	GetDataBufferLen()		{return m_pMessage->GetDataBufferLen();}

	virtual LPBYTE	GetData(UINT nIdx = 0)	{return m_pMessage->GetData(nIdx);}
	virtual WORD	GetDataLen()			{return m_pMessage->GetDataLen();}

	BYTE	GetMsgType()					{return m_pMessage->GetMsgType();}
	BYTE	GetHeaderLen_DW()				{return m_pMessage->GetHeaderLen_DW();}
	BYTE	GetChannel()					{return m_pMessage->GetChannel();}
	BYTE	GetPriority()					{return m_pMessage->GetPriority();}
	BYTE	GetSrcId()						{return m_pMessage->GetSrcId();}
	BYTE	GetDstId()						{return m_pMessage->GetDstId();}
	DWORD	GetTargetTs()					{return m_pMessage->GetTargetTs();}
	WORD	GetMsgId()						{return m_pMessage->GetMsgId();}
	WORD	GetMsgCtr()						{return m_pMessage->GetMsgCtr();}
	DWORD	GetFrameNum();					
	DWORD	GetFrame2Num();					
	WORD	GetHeaderLen()					{return m_pMessage->GetHeaderLen();}

	BYTE	GetDiagSap()					{return m_pMessage->GetDiagSap();}
	BYTE	GetService()					{return m_pMessage->GetService();}
	BYTE	GetModuleID(bool bFromData = false)	{return m_pMessage->GetModuleID(bFromData);}
	WORD	GetFullDiagSap()				{return m_pMessage->GetFullDiagSap();}
	BYTE	GetDiagId()						{return m_pMessage->GetDiagId();}
	WORD    GetExtraData()					{return m_pMessage->GetExtraData();}

	bool	IsDiagProtocol()				{return m_pMessage->IsDiagProtocol() == TRUE;}

	bool	IsMessageTypeDiag()				{return m_pMessage->IsMessageTypeDiag();}
	bool	IsMessageTypeService()			{return m_pMessage->IsMessageTypeService();}
	bool	IsMessageTypeSignal()			{return m_pMessage->IsMessageTypeSignal();}
	bool	IsMessageTypeString()			{return m_pMessage->IsMessageTypeString();}
	int		GetDiagMessageType()			{return m_pMessage->GetDiagMessageType();}
	bool	IsAligned()						{return m_pMessage->IsAligned();}

	bool	IsValidMessage()				{return m_pMessage->IsValidMessage();}
	int		GetDevice()						{return m_pMessage->GetDevice();}
	UINT64	GetMessageNumber()				{return m_pMessage->GetMessageNumber();}
	const CSystemTime&	GetPCTimeStamp()		{return m_pMessage->GetPCTimeStamp();}
	bool	IsPrintMessage()				{return m_pMessage->IsPrintMessage();}
	bool	GetUserRemark(CString & strtemp){return m_pMessage->GetUserRemark(strtemp);}
	BYTE	GetClientID()					{return m_pMessage->GetClientID();}


	//////////////////////

	DWORD	GetDifTargetTS();
	DWORD	GetAppTS();
	DWORD	GetCommTS();
	DWORD	GetDifAppTS();
	DWORD	GetDifCommTS();

	//DSP
	BYTE	GetCopyType();
	BYTE	*GetDataPacket();
	WORD	GetDataPacketLen();
	WORD	GetDspOpCode();
	WORD	GetEntireDspOpCode();
	WORD	GetDspDataLen();
	WORD	GetDspSetId();
	WORD	GetDspSubOpCode();

	//GKI
	LPBYTE	GetDataEx(UINT nIdx = 0);
	WORD	GetDataExLen();

	DWORD	GetFrameTicks();			
	WORD	GetSourceTaskId();
	WORD	GetTargetTaskId();
	DWORD	GetSignalId();
	WORD	GetSignalLength();
	///////////////////////////

	bool	GetTargetTSStr(CString & strtemp);
	bool	GetDifTargetTSStr(CString & strtemp);
	bool	GetAppTSStr(CString & strtemp);
	bool	GetCommTSStr(CString & strtemp);
	bool	GetDifAppTSStr(CString & strtemp);
	bool	GetDifCommTSStr(CString & strtemp);
	bool	GetCat1Str(CString & strtemp);
	bool	GetCat2Str(CString & strtemp);
	bool	GetCat3Str(CString & strtemp);
	bool	GetChannelStr(CString & strtemp);
	bool	GetMessageNumberStr(CString & strtemp);
	bool	GetDeviceStr(CString & strtemp);
	bool	GetCopyTypeStr(CString & strtemp);
	bool	GetDataStr(CString & strtemp);
	bool	GetDataPacketStr(CString & strtemp);
	bool	GetMsgCtrStr(CString & strtemp);
	bool	GetFullDiagSapStr(CString & strtemp);
	bool	GetDspOpCodeStr(CString & strtemp);
	bool	GetFrameNumStr(CString & strtemp);
	bool	GetSFNStr(CString & strtemp);
//	bool	GetFrame2NumStr(CString & strtemp);
	bool	GetFrameTicksStr(CString & strtemp);
	bool	GetMsgIdStr(CString & strtemp);
	bool	GetModuleIDStr(CString & strtemp);
	bool	GetPCTimeStampStr(CString & strtemp);
	bool	GetServiceStr(CString & strtemp);
	bool	GetDspSetIdStr(CString & strtemp);
	bool	GetSignalGroupStr(CString & strtemp);
	bool	GetSourceTaskIdStr(CString & strtemp, BOOL bWithID = TRUE);
	bool	GetTargetTaskIdStr(CString & strtemp, BOOL bWithID = TRUE);
	bool	GetDspSubOpCodeStr(CString & strtemp);
	bool	GetUserDataStr(CString & strtemp);
	bool	GetUserRemarkStr(CString & strtemp);
	bool	GetSrcIdStr(CString & strtemp);
	bool	GetDstIdStr(CString & strtemp);
	bool	GetSrcNameStr(CString & strtemp);
	bool	GetDstNameStr(CString & strtemp);
	bool	GetDiagIdStr(CString & strtemp);
	bool	GetMsgTypeStr(CString & strtemp);
	bool	GetExtraDataStr(CString & strtemp);
	bool	GetDataExLenStr(CString & strtemp);
	bool	GetDataLenStr(CString & strtemp);
	bool	GetDataHexStr(CString & strtemp);
	
	bool GetCat123Str(CString & strtemp, bool bAddClientName = false);
	void FormatData( BYTE *pData, int len, CString &retStr );
	void GetCurrentRawData(CString &str);
	
};

/////////////////////////////////////
///  GKI Data reader
/////////////////////////////////////

class CGKIExData
{
	int			m_taskIDSize;
	int			m_nSignalIDSize;

	int			m_iSourceTaskIDIndex;
	int			m_iTargetTaskIDIndex;
	int			m_iFrameNumberIndex;
	int			m_iFrameTicksIndex;
	int			m_iSignalLengthIndex;
	int			m_iSignalIDIndex;
	int			m_iDataIndex;
	int			m_iSkipSize;
	DWORD		m_dwSkipSize;

	CICATMessage * m_pIcatMessage;
public:

	CGKIExData(CICATMessage * pIcatMessage);
	virtual ~CGKIExData(){}


	virtual LPBYTE	GetDataEx(UINT nIdx = 0)	{return m_pIcatMessage->GetData(nIdx + m_iDataIndex);}
	virtual WORD	GetDataExLen()				{return m_pIcatMessage->GetDataLen() - m_iDataIndex;}
	virtual DWORD	GetFrameNum();

	virtual DWORD	GetFrameTicks();
	virtual WORD	GetSourceTaskId();
	virtual WORD	GetTargetTaskId();
	virtual DWORD	GetSignalId();
	virtual WORD	GetSignalLength();

	virtual int		GetSignalIdSize()	{return m_nSignalIDSize;}
	virtual void	Delete()			{delete this;}
	
};

////////////////////////////////////////////////////////////////
//struct EnumValsRecord;


class CDiagMessageEx  
{

protected:

	MessageConversionData	* m_pMessageConversionData;
	CMessageReaderEx		* m_pMessageReaderEx;
	CString					 m_strCurrentRawData;
		
	CICATMessage			* m_pIcatMessage;

	virtual bool ConvertString(CString &retStr)		{return false;}
	virtual bool ConvertCCString(CString &retStr)	{return false;}

public:
	void	FormatData(BYTE *pData, int len, CString &retStr);
	void	FormatTimeStamp(DWORD timeStamp, CString &strFormat);

	virtual void SetMessageConversionData(MessageConversionData * pMessageConversionData);

public:
	CDiagMessageEx(CMessageReaderEx * pMessageReaderEx, CICATMessage * pIcatMessage);
	virtual ~CDiagMessageEx(){}

	void GetCurrentRawData(CString &str) const { str = m_strCurrentRawData; }

	EXPORTED_API static bool GetClientName(int nId, CString &strName);
	EXPORTED_API static bool GetClientID(const CString &strName , int &nId);

#if 0
	bool	IsApp()			{return m_pIcatMessage->IsApp();}
	bool	IsFrame2Exist()	{return m_pIcatMessage->IsFrame2Exist();}
	bool	IsFromTarget()	{return m_pIcatMessage->IsFromTarget();}
	bool	IsAligned()		{return m_pIcatMessage->IsAligned();}
	BYTE	GetService()	{return m_pIcatMessage->GetService();}
	BYTE	GetDiagSap()	{return m_pIcatMessage->GetDiagSap();}
	bool	IsPrintMessage(){return m_pIcatMessage->IsPrintMessage();}
	bool	GetUserRemark(CString & strtemp){return m_pIcatMessage->GetUserRemark(strtemp);}
	bool    IsClientMatch(eTargetType targetType)	{return m_pIcatMessage->IsClientMatch(targetType);}
#else
	bool	IsApp()			{return m_pIcatMessage && m_pIcatMessage->IsApp();}
	bool	IsFrame2Exist()	{return m_pIcatMessage && m_pIcatMessage->IsFrame2Exist();}
	bool	IsFromTarget()	{return m_pIcatMessage && m_pIcatMessage->IsFromTarget();}
	bool	IsAligned()		{return m_pIcatMessage && m_pIcatMessage->IsAligned();}
	BYTE	GetService()	{return m_pIcatMessage ? m_pIcatMessage->GetService() : 0xFF;}
	BYTE	GetDiagSap()	{return m_pIcatMessage ? m_pIcatMessage->GetDiagSap() : 0xFF;}
	bool	IsPrintMessage(){return m_pIcatMessage && m_pIcatMessage->IsPrintMessage();}
	bool	GetUserRemark(CString & strtemp){return m_pIcatMessage && m_pIcatMessage->GetUserRemark(strtemp);}
	bool    IsClientMatch(eTargetType targetType)	{return m_pIcatMessage && m_pIcatMessage->IsClientMatch(targetType);}
#endif

	virtual bool IsMessageTypeDSP()			{return false;}
	virtual bool IsDSPReport()				{return false;}
	virtual bool IsPLPMsg()					{return false;}

	virtual LPBYTE	GetDataBuffer()			{return m_pIcatMessage->GetDataBuffer();}
	virtual WORD	GetDataBufferLen()		{return m_pIcatMessage->GetDataBufferLen();}

	virtual LPBYTE	GetData(UINT nIdx = 0)	{return m_pIcatMessage->GetData(nIdx);}
	virtual WORD	GetDataLen()			{return m_pIcatMessage->GetDataLen();}

	virtual DWORD	GetFrameNum()			{return m_pIcatMessage->GetFrameNum();}
	virtual DWORD	GetFrame2Num()			{return m_pIcatMessage->GetFrame2Num();}

	virtual DWORD	GetTargetTs()			{return m_pIcatMessage->GetTargetTs();}

	virtual DWORD	GetAppTS();
	virtual DWORD	GetCommTS();
	
	virtual BYTE	GetCopyType()			{return 0;}
	virtual BYTE	*GetDataPacket()		{return 0;}
	virtual WORD	GetDataPacketLen()		{return 0;}
	virtual WORD	GetDspOpCode()			{return 0;}
	virtual WORD	GetEntireDspOpCode()	{return 0;}
	virtual WORD	GetDspDataLen()			{return 0;}
	virtual WORD	GetDspSetId()			{return 0;}
	virtual WORD	GetDspSubOpCode()		{return 0;}
	
	virtual LPBYTE	GetDataEx(UINT nIdx = 0){return GetData(nIdx);}
	virtual WORD	GetDataExLen()			{return GetDataLen();}

	virtual DWORD	GetFrameTicks()			{return 0;}
	virtual WORD	GetSourceTaskId()		{return 0;}
	virtual WORD	GetTargetTaskId()		{return 0;}
	virtual DWORD	GetSignalId()			{return 0;}
	virtual WORD	GetSignalLength()		{return 0;}
	
	virtual bool	GetTargetTSStr(CString & strtemp);
	virtual bool	GetAppTSStr(CString & strtemp);
	virtual bool	GetCommTSStr(CString & strtemp);
	virtual bool	GetCat1Str(CString & strtemp)			{strtemp.Empty(); return false;}
	virtual bool	GetCat2Str(CString & strtemp)			{strtemp.Empty(); return false;}
	virtual bool	GetCat3Str(CString & strtemp)			{strtemp.Empty(); return false;}
	virtual bool	GetChannelStr(CString & strtemp);
	virtual bool	GetMessageNumberStr(CString & strtemp);
	virtual bool	GetDeviceStr(CString & strtemp);
	virtual bool	GetCopyTypeStr(CString & strtemp)		{strtemp.Empty(); return false;}
	virtual bool	GetDataStr(CString & strtemp);
	virtual bool	GetDataPacketStr(CString & strtemp)		{strtemp.Empty(); return false;}
	virtual bool	GetMsgCtrStr(CString & strtemp)			{strtemp.Empty(); return false;}
	virtual bool	GetFullDiagSapStr(CString & strtemp);
	virtual bool	GetDspOpCodeStr(CString & strtemp)		{strtemp.Empty(); return false;}
	virtual bool	GetFrameNumStr(CString & strtemp)		{strtemp.Empty(); return false;}
	virtual bool	GetSFNStr(CString & strtemp)			{strtemp.Empty(); return false;}
//	virtual bool	GetFrame2NumStr(CString & strtemp)		{strtemp.Empty(); return false;}
	virtual bool	GetFrameTicksStr(CString & strtemp)		{strtemp.Empty(); return false;}
	virtual bool	GetMsgIdStr(CString & strtemp)			{strtemp.Empty(); return false;}
	virtual bool	GetModuleIDStr(CString & strtemp);
	virtual bool	GetPCTimeStampStr(CString & strtemp);
	virtual bool	GetServiceStr(CString & strtemp)		{strtemp.Empty(); return false;}
	virtual bool	GetDspSetIdStr(CString & strtemp)		{strtemp.Empty(); return false;}
	virtual bool	GetSignalGroupStr(CString & strtemp)	{strtemp.Empty(); return false;}
	virtual bool	GetSourceTaskIdStr(CString & strtemp, BOOL bWithID = TRUE)	{strtemp.Empty(); return false;}
	virtual bool	GetTargetTaskIdStr(CString & strtemp, BOOL bWithID = TRUE)	{strtemp.Empty(); return false;}
	virtual bool	GetDspSubOpCodeStr(CString & strtemp)	{strtemp.Empty(); return false;}
	virtual bool	GetUserDataStr(CString & strtemp)		{strtemp.Empty(); return false;}
	virtual bool	GetUserRemarkStr(CString & strtemp);
	virtual bool	GetSrcIdStr(CString & strtemp);
	virtual bool	GetDstIdStr(CString & strtemp);
	virtual bool	GetSrcNameStr(CString & strtemp);
	virtual bool	GetDstNameStr(CString & strtemp);
	virtual bool	GetDiagIdStr(CString & strtemp);
	virtual bool	GetMsgTypeStr(CString & strtemp);
	virtual bool	GetExtraDataStr(CString & strtemp)		{strtemp.Empty(); return false;}
	virtual bool	GetDataExLenStr(CString & strtemp);
	virtual bool	GetDataLenStr(CString & strtemp);
	virtual bool    GetDataHexStr(CString & strtemp);
};



class CdumyMessageEx : public CDiagMessageEx
{
public:
	CdumyMessageEx(CMessageReaderEx * pMessageReaderEx);
	virtual ~CdumyMessageEx(){}

	bool	IsApp()			{return false;}
	bool	IsFrame2Exist()	{return false;}
	bool	IsFromTarget()	{return false;}
	bool	IsAligned()		{return false;}
	BYTE	GetService()	{return 0;}
	BYTE	GetDiagSap()	{return 0;}
	bool	IsPrintMessage(){return false;}
	bool	GetUserRemark(CString & strtemp){strtemp.Empty(); return false;}

	virtual LPBYTE	GetDataBuffer()			{return NULL;}
	virtual WORD	GetDataBufferLen()		{return 0;}

	virtual LPBYTE	GetData(UINT nIdx = 0)	{return NULL;}
	virtual WORD	GetDataLen()			{return 0;}

	virtual DWORD	GetFrameNum()			{return 0;}
	virtual DWORD	GetFrame2Num()			{return 0;}

	virtual DWORD	GetTargetTs()			{return 0;}
	
	virtual bool	GetTargetTSStr(CString & strtemp)		{strtemp.Empty(); return false;}
	virtual bool	GetAppTSStr(CString & strtemp)			{strtemp.Empty(); return false;}
	virtual bool	GetCommTSStr(CString & strtemp)			{strtemp.Empty(); return false;}
	virtual bool	GetChannelStr(CString & strtemp)		{strtemp.Empty(); return false;}
	virtual bool	GetDeviceStr(CString & strtemp)			{strtemp.Empty(); return false;}
	virtual bool	GetDataStr(CString & strtemp)			{strtemp.Empty(); return false;}
	virtual bool	GetFullDiagSapStr(CString & strtemp)	{strtemp.Empty(); return false;}
	virtual bool	GetModuleIDStr(CString & strtemp)		{strtemp.Empty(); return false;}
	virtual bool	GetPCTimeStampStr(CString & strtemp)	{strtemp.Empty(); return false;}
	virtual bool	GetSrcIdStr(CString & strtemp)			{strtemp.Empty(); return false;}
	virtual bool	GetDstIdStr(CString & strtemp)			{strtemp.Empty(); return false;}
	virtual bool	GetSrcNameStr(CString & strtemp)		{strtemp.Empty(); return false;}
	virtual bool	GetDstNameStr(CString & strtemp)		{strtemp.Empty(); return false;}
	virtual bool	GetDiagIdStr(CString & strtemp)			{strtemp.Empty(); return false;}
	virtual bool	GetMsgTypeStr(CString & strtemp)		{strtemp.Empty(); return false;}
	virtual bool	GetUserRemarkStr(CString & strtemp)		{strtemp.Empty(); return false;}  
	virtual bool	GetDifAppTSStr(CString & strtemp)		{strtemp.Empty(); return false;}  
	virtual bool	GetDifCommTSStr(CString & strtemp)		{strtemp.Empty(); return false;}  
	virtual bool	GetMessageNumberStr(CString & strtemp)  {strtemp.Empty(); return false;}
};


class CStringMessageEx : public CDiagMessageEx
{
public:
	CStringMessageEx(CMessageReaderEx * pMessageReaderEx, CICATMessage * pIcatMessage);
	virtual ~CStringMessageEx(){}

	virtual bool	ConvertString(CString &retStr);
	virtual bool	ConvertCCString(CString &retStr);

	virtual bool	GetTargetTSStr(CString & strtemp)		{strtemp.Empty(); return false;}
	virtual bool	GetAppTSStr(CString & strtemp)			{strtemp.Empty(); return false;}
	virtual bool	GetCommTSStr(CString & strtemp)			{strtemp.Empty(); return false;}	
	virtual bool	GetChannelStr(CString & strtemp)		{strtemp.Empty(); return false;}
	virtual bool	GetFullDiagSapStr(CString & strtemp)	{strtemp.Empty(); return false;}
	virtual bool	GetModuleIDStr(CString & strtemp)		{strtemp.Empty(); return false;}
	virtual bool	GetSrcIdStr(CString & strtemp)			{strtemp.Empty(); return false;}
	virtual bool	GetDstIdStr(CString & strtemp)			{strtemp.Empty(); return false;}
	virtual bool	GetSrcNameStr(CString & strtemp)		{strtemp.Empty(); return false;}
	virtual bool	GetDstNameStr(CString & strtemp)		{strtemp.Empty(); return false;}
	virtual bool	GetDiagIdStr(CString & strtemp)			{strtemp.Empty(); return false;}
	virtual bool	GetMsgTypeStr(CString & strtemp)		{strtemp.Empty(); return false;}
};

class CDiagMessageHexEx : public CStringMessageEx
{
public:
	CDiagMessageHexEx(CMessageReaderEx * pMessageReaderEx, CICATMessage * pIcatMessage);
	virtual ~CDiagMessageHexEx(){}

	virtual bool	ConvertString(CString &retStr);
	virtual bool	ConvertCCString(CString &retStr);
};

class CErrorMessageEx : public CStringMessageEx
{
public:
	CErrorMessageEx(CMessageReaderEx * pMessageReaderEx, CICATMessage * pIcatMessage);
	virtual ~CErrorMessageEx(){}

	virtual bool	ConvertString(CString &retStr);
	virtual bool	ConvertCCString(CString &retStr);
};

class CDiagMessageDiagEx : public CDiagMessageEx
{
protected:
	EnumValsRecord *	m_pRec;

	CString		m_CurrentTableName;
	BYTE	*	m_pLastByteOfData;

	CString	ConvertParam(TCHAR type, bool longType, BYTE **ppParams, int nParamSize);
	bool	FormatExportedFunctionData(CString &retStr);

	virtual bool	ConvertString(CString &retStr);
	virtual bool	ConvertCCString(CString &retStr);
	virtual void	FormatLocalData(CString & retStr);

public:
	CDiagMessageDiagEx(CMessageReaderEx * pMessageReaderEx, CICATMessage * pIcatMessage, EnumValsRecord * pRec);
	virtual ~CDiagMessageDiagEx(){}
	
	virtual bool	GetCat1Str(CString & strtemp);
	virtual bool	GetCat2Str(CString & strtemp);
	virtual bool	GetCat3Str(CString & strtemp);
	virtual bool	GetMsgCtrStr(CString & strtemp);
	virtual bool	GetFrameNumStr(CString & strtemp);
	virtual bool	GetSFNStr(CString & strtemp);
//	virtual bool	GetFrame2NumStr(CString & strtemp);
	virtual bool	GetMsgIdStr(CString & strtemp);
	virtual bool	GetExtraDataStr(CString & strtemp);
};

class CDiagMessageISEx : public CDiagMessageEx
{
protected:
	virtual bool ConvertString(CString &retStr);
	virtual bool ConvertCCString(CString &retStr);

public:
	CDiagMessageISEx(CMessageReaderEx * pMessageReaderEx, CICATMessage * pIcatMessage);
	virtual ~CDiagMessageISEx(){}

	virtual bool	GetServiceStr(CString & strtemp);
};

class CDiagMessageGKIEx : public CDiagMessageEx
{
	DECLARE_NO_COPY(CDiagMessageGKIEx)

	CGKIExData* GetGKIExData();
	CGKIExData* m_pExData;

	CCriticalSection m_CritSec;

protected:
	virtual bool ConvertString(CString &retStr);
	virtual bool ConvertCCString(CString &retStr);

public:
	CDiagMessageGKIEx(CMessageReaderEx * pMessageReaderEx, CICATMessage * pIcatMessage);
	virtual ~CDiagMessageGKIEx();
	virtual void SetMessageConversionData(MessageConversionData * pMessageConversionData);

	virtual LPBYTE	GetDataEx(UINT nIdx = 0)	{return GetGKIExData()->GetDataEx(nIdx);}
	virtual WORD	GetDataExLen()				{return GetGKIExData()->GetDataExLen();}
	virtual DWORD	GetFrameNum();

	virtual DWORD	GetFrameTicks()				{return GetGKIExData()->GetFrameTicks();}				
	virtual WORD	GetSourceTaskId()			{return GetGKIExData()->GetSourceTaskId();}
	virtual WORD	GetTargetTaskId()			{return GetGKIExData()->GetTargetTaskId();}
	virtual DWORD	GetSignalId()				{return GetGKIExData()->GetSignalId();}
	virtual WORD	GetSignalLength()			{return GetGKIExData()->GetSignalLength();}
	virtual int		GetSignalIdSize()			{return GetGKIExData()->GetSignalIdSize();}

	virtual bool	GetMsgCtrStr(CString & strtemp);
	virtual bool	GetFrameNumStr(CString & strtemp);
	virtual bool	GetSFNStr(CString & strtemp);
	virtual bool	GetFrameTicksStr(CString & strtemp);
	virtual bool	GetSignalGroupStr(CString & strtemp);
	virtual bool	GetSourceTaskIdStr(CString & strtemp, BOOL bWithID = TRUE);
	virtual bool	GetTargetTaskIdStr(CString & strtemp, BOOL bWithID = TRUE);

};

class CDiagMessageDspEx : public CDiagMessageDiagEx
{
protected:
	virtual bool	ConvertString(CString &retStr);
	virtual bool	ConvertCCString(CString &retStr);
	virtual void	FormatLocalData(CString & retStr);

public:
	CDiagMessageDspEx(CMessageReaderEx * pMessageReaderEx, CICATMessage * pIcatMessage, EnumValsRecord * pRec);
	virtual ~CDiagMessageDspEx(){}

	virtual bool	IsMessageTypeDSP()		{return true;}
	virtual bool	IsDSPReport();
	virtual bool	IsPLPMsg();
	virtual LPBYTE	GetDataEx(UINT nIdx = 0);
	virtual WORD	GetDataExLen();

	virtual BYTE	GetCopyType();
	virtual BYTE	*GetDataPacket();
	virtual WORD	GetDataPacketLen();
	virtual WORD	GetDspOpCode();
	virtual WORD	GetEntireDspOpCode();
	virtual WORD	GetDspDataLen();
	virtual WORD	GetDspSetId();
	virtual WORD	GetDspSubOpCode();

	virtual bool	GetCopyTypeStr(CString & strtemp);
	virtual bool	GetDataPacketStr(CString & strtemp);
	virtual bool	GetDspOpCodeStr(CString & strtemp);
	virtual bool	GetDspSetIdStr(CString & strtemp);
	virtual bool	GetDspSubOpCodeStr(CString & strtemp);

};

class CDiagMessageDiagErrorEx : public CDiagMessageDiagEx
{
public:
	CDiagMessageDiagErrorEx(CMessageReaderEx * pMessageReaderEx, CICATMessage * pIcatMessage);
	virtual ~CDiagMessageDiagErrorEx(){}

	virtual bool	GetDataStr(CString & strtemp);
	virtual bool	GetCat1Str(CString & strtemp);
	virtual bool	GetCat2Str(CString & strtemp);
	virtual bool	GetCat3Str(CString & strtemp);
};
///////////////////////////////////////////////////////////////////////

#define MAX_DIAG_HEADER_EX_SIZE		(MAX_DIAG_HEADER_SIZE+16)


class EXPORTED_API CHeaderBuilderEx : public CHeaderBuilder
{
	int m_nType;
public:
	CHeaderBuilderEx(int nType);
	~CHeaderBuilderEx();

//	int BuildHeader(LPBYTE pData, int nBufLen, int nId, int nModule, DWORD dwDBVersion, int nDestination=0, bool bFixup=false);
	int	BuildTargetHeader(LPBYTE pData, int nBufLen, stDiagHeaderParams & param);
};


