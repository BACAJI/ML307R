/*--------------------------------------------------------------------------------------------------------------------

 (C) Copyright 2006,2007 Marvell Semiconductor Israel Ltd. All Rights Reserved  

-------------------------------------------------------------------------------------------------------------------*/

#if !defined(AFX_CONVERTER1_H__EE02C74A_FA56_4164_9CEC_92E91052B78E__INCLUDED_)
#define AFX_CONVERTER1_H__EE02C74A_FA56_4164_9CEC_92E91052B78E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "DataFormatDlg.h"
#include "ICATMessage.h"

#include <afxtempl.h>
#include "..\..\LogViewer\ColumnDataDef.h"


//Must be alphabetic sorted!!!!
//and must add to the static array below too
enum {
//  COL_ADVANCED_DATA,
  COL_APP_TIME_STAMP,	
  COL_APP_TS_DIFF,		
  COL_CAT1,				
  COL_CAT2,			
  COL_CAT3,
//  COL_CELL,
  COL_CHANNEL_ID,		
  COL_COMM_DEVICE,		
  COL_COMM_TIME_STAMP,	
  COL_COMM_TS_DIFF,		
  COL_COPY_TYPE,			
  COL_DATA,	
  COL_DATA_HEX,
  COL_DATA_PACKET,		
//  COL_DESTINATION_ID,	
  COL_DIAG_COUNTER,		
  COL_DIAG_SAP,			
  COL_DSP_OPCODE,	
  COL_EXTRA_DATA,
  COL_FRAME_NUMBER,
//  COL_FRAME_NUMBER2,
  COL_FRAME_TICKS,		
  COL_INDEX,
  COL_LENGTH,
//  COL_MESSAGETYPE,		
  COL_MESSAGEID,
  COL_MODULEID,			
  COL_PC_TIME_STAMP,		
  COL_SERVICEID,			
  COL_SET_ID,	
  COL_SFN,
  COL_SIGNAL_GROUP,	
  COL_SOURCE_TASK_ID,
  COL_SOURCE_ID,
  COL_SUB_OPCODE,
  COL_SYMBOL,
  COL_TARGET_TASK_ID,	
  COL_USER_DATA,
  COL_USER_REMARKS,
  NUM_OF_COL
};

//KEEP ALPHABETIC SORTED AND SYCH WITH THE ENUM ABOVE !!!!!!
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static CString ColumnName[NUM_OF_COL] = {/*_T("Advanced Data"),*/ _T("App. Time Stamp"), _T("App. TS Diff."), _T("Cat1"), _T("Cat2"), _T("Cat3"), /*_T("Cell"),*/ _T("Channel ID"), _T("Comm Device"), _T("Comm. Time Stamp"),
										_T("Comm. TS Diff."), _T("Copy Type"), _T("Data"),_T("Data Hex"), _T("Data Packet"), /*_T("Destination ID"), */_T("Diag Counter"), _T("Diag SAP"), _T("DSP Opcode"),
										_T("Extra Data"), _T("Frame Number"), /*_T("Frame Number2"),*/ _T("Frame Ticks"), _T("Index"),_T("Length"), /*_T("Message Type"),*/ _T("MessageID"), _T("ModuleID"), 
										_T("PC Time Stamp"), _T("ServiceID"), _T("Set ID"), _T("SFN"),_T("Signal Group"),  _T("Source Task ID"), _T("Source ID"), _T("Sub Opcode"), _T("Symbol"), _T("Target Task ID"), _T("User Data"), _T("User Remarks")};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
//Communication Indexes
//////////////////////////////////////////////////////////////////////////

#define  INDEX_APP_TIME_STAMP			4
#define  INDEX_COMM_TIME_STAMP			INDEX_APP_TIME_STAMP 
#define  INDEX_APP_TIME_STAMP_WITH_MI	8
#define  INDEX_COMM_TIME_STAMP_WITH_MI	INDEX_APP_TIME_STAMP_WITH_MI 
#define  INDEX_DIAG_COUNTER				2
#define  INDEX_DIAG_SAP					0
#define  INDEX_DSP_OPCODE				12
#define  INDEX_DSP_OPCODE_EXT_LEN		14
#define  INDEX_MESSAGEID_COMM			6
#define  INDEX_MODULEID_COMM			4
#define  INDEX_SOURCEID_COMM			12
#define  INDEX_RETURN_SERVICE_DATA_COMM			INDEX_SOURCEID_COMM

//////////////////////////////////////////////////////////////////////////
//C & C Indexes
//////////////////////////////////////////////////////////////////////////
#define  INDEX_CHANNEL_ID			18
#define  INDEX_COPY_TYPE			19
#define  INDEX_DATA_PACKET			16
#define  INDEX_SERVICEID			1
#define  INDEX_MESSAGEID_CC			4
#define  INDEX_MODULEID_CC			2
#define  INDEX_SOURCEID_CC			8


#define DIAG_ERROR_REPORT				0x7f


//////////////////////////////////////////////////////////////////////////////
#define DIAG_SAP_INDEX			0
#define PDU_HEADER_LEN			12

#define DIAG_HEADER_FOR_RECEIVING_MI_SIGNALS	8	// only Diag-SAP + Time-Stamp
#define DIAG_HEADER_FOR_RECEIVING_MI_SIGANLS	DIAG_HEADER_FOR_RECEIVING_MI_SIGNALS	// backwards compatibility

// lee 2012.4.1
// typedef enum {kComm, kApp, kMaxChipSetNum}EChipSet;

/////////////////////////// DiagSAP Definitions: /////////////////////////////
// lee 2012.4.1
// typedef enum {
// 	INTERNAL_SERVICE		= 0,
// 	COMMAND_SERVER			/*=1*/,        
// 	RSVP_COMMAND_SERVER		/*=2*/,
// 	FIXUPS_COMMAND_SERVER	/*=3*/,
// } DiagSAP;


#define APP_SIDE_MASK_FOR_SENDING		((BYTE)0x80)
#define APP_SIDE_MASK_FOR_RECEIVING		((WORD)0x8000)

#define APPLICATION_REPORT			0
#define RETURN_SERVICE				1
#define RSVP_SERVICE				2
//#define APPLICATION_REPORT_FIXUP	3
#define APPLICATION_REPORT_ALIGNED	4
#define DIAG_MI_LOGGED_SIGNAL			5
#define DIAG_MI_COMMAND					5
#define DIAG_MI_SIGNAL					6
#define DIAG_MI_SPECIAL_LOGGED_SIGNAL	7
#define DIAG_SAP_IML_LOG	9

#define INVALID_SIGID 0xffffffff

//////////////////////////////////////////////////////////////////////////////

////////////////////// Internal Service Definitions: /////////////////////////////

//ACAT READY parameters
#define DELETE_ALL_PENDING_TRACES	1
#define DISABLE_ALL_TRACES			2


//////////////////////////////////////////////////////////////////////////////

/************************ EMMI Protocol Specific ************************/
#define SIGNAL_MI			211
#define LOGGED_SIGNAL_MI	212
#define COMMAND_MI			213

#define EMMI_HEADER_LEN		1

//#define SIGNAL_BODY_OFFSET			(EMMI_HEADER_LEN + MI_SIGNAL_HEADER_LENGTH)
//#define LOGGED_SIGNAL_BODY_OFFSET	(EMMI_HEADER_LEN + MI_LOGGED_SIGNAL_HEADER_LENGTH)
//#define COMMAND_BODY_OFFSET			(EMMI_HEADER_LEN + MI_COMMAND_HEADER_LENGTH)
/************************************************************************/

typedef void (CONVERTER_CALLBACK_PROC)(LPVOID, LPCTSTR , const CString &,int);
typedef void (CONVERTER_CALLBACK_MUL_LN_PROC)(LPVOID, LPCTSTR , const CString &,int, int);
typedef bool (MINILOG_ENG_PARSER_PROC)(LPVOID, CICATMessage *, CString&, int&, CString&, CString&, COLORREF &color);


struct MessageConversionData {
	CICATMessage *pMessage;
	CONVERTER_CALLBACK_PROC *pCallbackProc;
	CONVERTER_CALLBACK_MUL_LN_PROC *pCallbackMulLnProc;
	MINILOG_ENG_PARSER_PROC *pMLAnalyzerProc;
	LPVOID pCaller;
	LPVOID pMLAnalyzerPtr;
	CString strStruct;
	CString strASN1MessageName;
	CString strASN1Details;
	bool	bIsOffline;
	DWORD   dwSourceTaskID;
	DWORD   dwTargetTaskID;
	COLORREF color;

	MessageConversionData()
	{
		bIsOffline = false;
		pCallbackProc = NULL;
		pCallbackMulLnProc = NULL;
		pCaller = NULL;
		pMLAnalyzerProc = NULL;
		pMLAnalyzerPtr	= NULL;
	};
};

typedef struct FieldStruct
{
	CString m_strFieldName;
	CString m_strFieldData;
	
// 	FieldStruct()
// 	{
// 		m_strFieldName	= "";
// 		m_strFieldData	= "";		
// 	};	

}sFieldStruct;

typedef CMap<CString, LPCTSTR, CString, LPCTSTR> m_MapFieldsData_t; 

enum EMessageType
{
	enmMsg_Others		= 0,
	enmMsg_Cat123		= 1,
	enmMsg_GKI			= 2,
	enmMsg_Dsp_Report	= 3,
	enmMsg_Dsp_Cmd		= 4,
};

#ifdef _CATCORE_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif
class  DLL_EXPORT CConverterEx
{

	/////Ziv
public:

	enum EnumModuleID{MODULE_COMMUNICATION			= 1,//Diag & App_Diag
					  MODULE_COMMANDAND_AND_CONTROL = 3};

	BOOL GetCommDevice(		sFieldStruct& CommDevice,	CString strDevice,		CMap <CString, LPCTSTR, int, int> &FieldsMap);
	BOOL GetDiagSap(		sFieldStruct& DiagSap,		WORD   dwDiagSAP,		CMap <CString, LPCTSTR, int, int> &FieldsMap);
	BOOL GetDiagCounter(	sFieldStruct& DiagCounter,	DWORD	dwDiagCounter,  CMap <CString, LPCTSTR, int, int> &FieldsMap);
	BOOL GetSFN(			sFieldStruct& SFN,			DWORD	dwSFN,			CMap <CString, LPCTSTR, int, int> &FieldsMap);
	BOOL GetModuleID(		sFieldStruct& ModuleID,		USHORT	moduleID,		CMap <CString, LPCTSTR, int, int> &FieldsMap);
	BOOL GetMessageID(		sFieldStruct& MessageID,	USHORT	messageID,		CMap <CString, LPCTSTR, int, int> &FieldsMap);
// 	BOOL GetMessageID(		sFieldStruct& MessageID,	DWORD	messageID,		CMap <CString, LPCSTR, int, int> &FieldsMap);
	BOOL GetDataLength(		sFieldStruct& sDataLength,  USHORT dataLength,       CMap <CString, LPCTSTR, int, int> &FieldsMap);//richard added for showing the column of "Length"
	BOOL GetExtraData(		sFieldStruct& sExtraData,	WORD	wDiagIndex,		CMap <CString, LPCTSTR, int, int> &FieldsMap); //sxwang added for showing the column of (Extra Data)
	BOOL GetCommTSDiff(		sFieldStruct& CommTSDiff,	DWORD	UE_TimeStamp,	CMap <CString, LPCTSTR, int, int> &FieldsMap);
	BOOL GetCommTimeStamp(	sFieldStruct& CommTimeStamp,DWORD	UE_TimeStamp,	CMap <CString, LPCTSTR, int, int> &FieldsMap);
	BOOL GetAppTimeStamp(	sFieldStruct& AppTimeStamp,	DWORD	UE_TimeStamp,	CMap <CString, LPCTSTR, int, int> &FieldsMap);
	BOOL GetAppTSDiff(		sFieldStruct& AppTSDiff,	DWORD	dwTemp,			CMap <CString, LPCTSTR, int, int> &FieldsMap);
	BOOL GetSourceID(		sFieldStruct& SourceID,		DWORD	dwSourceID,		CMap <CString, LPCTSTR, int, int> &FieldsMap);

	BOOL GetSetID(			sFieldStruct& SetID,		DWORD wSetID,	CString rec, CMap <CString, LPCTSTR, int, int> &FieldsMap);
	BOOL GetDSPOpcode(		sFieldStruct& DSPOpcode,	DWORD extLen, DWORD opCode, CMap <CString, LPCTSTR, int, int> &FieldsMap);
	BOOL GetSubOpcode(		sFieldStruct& SubOpcode,	CString rec, DWORD wSubOpcode, DWORD extLen, CMap <CString, LPCTSTR, int, int> &FieldsMap);

	BOOL GetUserRemarks(	sFieldStruct& UserRemarks,	DWORD UE_TimeStamp, DWORD moduleID, DWORD messageID, CMap <CString, LPCTSTR, int, int> &FieldsMap);
	BOOL GetUserRemarks(	sFieldStruct& UserRemarks,	CString strData, CMap <CString, LPCTSTR, int, int> &FieldsMap);

	BOOL GetData(			sFieldStruct& Data,			CString strTemp, CMap <CString, LPCTSTR, int, int> &FieldsMap);

	BOOL GetSourceTaskID(	sFieldStruct& sourceTaskID, BOOL bLookupGKITaskID, CString strTemp, DWORD wSourceTaskID, CMap <CString, LPCTSTR, int, int> &FieldsMap);
	BOOL GetTargetTaskID(	sFieldStruct& targetTaskID, BOOL bLookupGKITaskID, CString strTemp, DWORD wTargetTaskID, CMap <CString, LPCTSTR, int, int> &FieldsMap);

	BOOL GetFrameNumber(	sFieldStruct& frameNumber,	DWORD dwFrameNumber, CMap <CString, LPCTSTR, int, int> &FieldsMap);
	BOOL GetFrameTicks(		sFieldStruct& frameTicks,	DWORD dwFrameTicks, CMap <CString, LPCTSTR, int, int> &FieldsMap);
	
	BOOL GetSignalGroup(	sFieldStruct& signalGroup,  CString strSignalGroup, CMap <CString, LPCTSTR, int, int> &FieldsMap);
	
	BOOL GetServiceID(		sFieldStruct& serviceID,	DWORD dwServiceID, CMap <CString, LPCTSTR, int, int> &FieldsMap);

	BOOL GetChannelID(		sFieldStruct& ChannelID,	BYTE bChannelID, CMap <CString, LPCTSTR, int, int> &FieldsMap);
	BOOL GetCopyType(		sFieldStruct& CopyType,		CString strCopyType, CMap <CString, LPCTSTR, int, int> &FieldsMap);
	BOOL GetDataPacket(		sFieldStruct& DataPacket,	CString strTemp, CMap <CString, LPCTSTR, int, int> &FieldsMap);

	BOOL GetCat1(			sFieldStruct& Cat1,			CString strCat1, CMap <CString, LPCTSTR, int, int> &FieldsMap);
	BOOL GetCat2(			sFieldStruct& Cat2,			CString strCat2, CMap <CString, LPCTSTR, int, int> &FieldsMap);
	BOOL GetCat3(			sFieldStruct& Cat3,			CString strCat3, CMap <CString, LPCTSTR, int, int> &FieldsMap);

	BOOL GetPCTimeStamp(	sFieldStruct& PCTimeStamp,	CString strTimpStamp, CMap <CString, LPCTSTR, int, int> &FieldsMap);
	////////

public:
	CConverterEx(int nDeviceID = -1, CWnd *pParentWnd = NULL);
	virtual ~CConverterEx();
	
public:
	void ConvertRawDataMessage(CICATMessage *pMessage, CString &fmtMessage);
	static int GetTargetDeviceIndex(CICATMessage::eDirection dir);
	int GetRawMessagePresentation();
	bool ConvertMessage(MessageConversionData *pConversionData, m_MapFieldsData_t &MapFieldsData,/*CMap <CString, LPCTSTR, int, int>*/CArray<COneField,COneField&> &FieldsMap);
//	bool ConvertMessage(MessageConversionData *pConversionData, m_MapFieldsData_t &MapFieldsData,CMap <CString, LPCTSTR, int, int>&FieldsMap);
	void FormatTimeStamp(DWORD timeStamp, CString &strFormat);
	//void ShowDataFormatDlg();
    void FormatData(BYTE* pData, int len, CString &retStr);
	static void FormatDataEx(BYTE* pData, int len, CString &retStr);
	bool FormatExportedFunctionData(const CString &formatStr, BYTE *pParams, int dataLen, CString &retStr);
	static bool GetMsgIdGkiIdDspCode(CICATMessage* pMessage, EMessageType &iMsgType,
									 WORD &wCat123Id, bool bAppSide, DWORD &dwGkiId, WORD &wDspCode);
	
	//void SetDataForamtDlg(CDataFormatDlg* pDataFormatDlg);
private:
	//CDataFormatDlg *m_pDataFormatDlg;
	BYTE	*m_pLastByteOfData;
	CString m_CurrentTableName;
	CWnd *m_pParentWnd;
	DWORD m_dwPrevCommTimeStamp;
	DWORD m_dwPrevAppTimeStamp;
	int   m_nDeviceID;

	CString FormatDSPData(BYTE *pData, int dataLen);
	CString ConvertParam(TCHAR type, bool longType, BYTE **ppParams, bool bAligned, bool bAppSide, int nDeviceID);
	bool ConvertString(CString &formatStr, BYTE *pParams, int nPrmLen, bool bAligned, bool &structFlag, CString &strStruct, CString &retStr, bool bAppSide, int nDeviceID);
	bool ConvertMessage_DIAG(MessageConversionData *pConversionData, m_MapFieldsData_t &MapFieldsData, CMap <CString, LPCTSTR, int, int> &FieldsMap);
	bool ConvertMessage_EMMI(MessageConversionData *pConversionData, m_MapFieldsData_t &MapFieldsData);
	bool ConvertMessage_RAW(MessageConversionData *pConversionData, m_MapFieldsData_t &MapFieldsData, CMap <CString, LPCTSTR, int, int> &FieldsMap);
	
	
	static CString m_strCopyTypes[3]; 
	CMessageReaderEx * m_pMessageReader;
};

#endif // !defined(AFX_CONVERTER1_H__EE02C74A_FA56_4164_9CEC_92E91052B78E__INCLUDED_)
