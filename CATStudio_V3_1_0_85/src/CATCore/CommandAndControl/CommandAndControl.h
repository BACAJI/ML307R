/*--------------------------------------------------------------------------------------------------------------------

 (C) Copyright 2006,2007 Marvell Semiconductor Israel Ltd. All Rights Reserved  

-------------------------------------------------------------------------------------------------------------------*/



#if !defined(AFX_COMMANDANDCONTROL_H__C21CA1F6_191D_11D5_8230_0006294FD6F7__INCLUDED_)
#define AFX_COMMANDANDCONTROL_H__C21CA1F6_191D_11D5_8230_0006294FD6F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>
//#include "StdAfx.h"   //Committed by hlguo 2012.2.21 to cancel the dependence on the special project files

#include "..\Converter\CommandAndMessageStructures.h"
//#include "MrvlCommon\CommonDefs.h"
#include "ICATMessage.h"

//////////////////////////////////////////////////////
// Trace filter ////////////////

#define DEFAULT_PARAMETER				0xFF

struct stFilterData
{
	BYTE		Action;
	BYTE		Priority;

	stFilterData(BYTE nAction = DEFAULT_PARAMETER, BYTE nPriority = DEFAULT_PARAMETER)
		:Action(nAction), Priority(nPriority){}
};

#define TRACE_SENT				stFilterData(0,DEFAULT_PARAMETER)
#define TRACE_NOT_SENT			stFilterData(1,DEFAULT_PARAMETER)
#define TRACE_PRIORITY_HIGH		stFilterData(0, 1)
#define TRACE_PRIORITY_NORMAL	stFilterData(0, 2)
#define TRACE_PRIORITY_LOW		stFilterData(0, 3)
#define TRACE_PRIORITY_INTERNAL	stFilterData(0, 0)


#define TRACE_SENDED		TRACE_SENT			
#define TRACE_NOT_SENDED	TRACE_NOT_SENT		
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////


#define USB_MESSAGE_HEADER_SIZE			4

#define DEFAULT_LOGGER_FIFO_SIZE		5000

// typedef enum
// {
// 	DIAG_NONE = 0,
// 	DIAG_FATAL_ERROR,
// 	DIAG_ERROR,
// 	DIAG_WARNING,
// 	DIAG_INFORMATION,
// 	DIAG_DEBUG_HIGH,
// 	DIAG_DEBUG_LOW,
// 	DIAG_ALL
// } DiagFilterLevel;

// struct tDeviceInfo 
// {
// 	int		nDevice;
// 	BOOL	bConnect;
// 	CString	strIMEI;
// 	CString	strCommOS;
// 	CString	strAppOS;
// };

class CWordList : public CList<WORD, WORD &>
{
public:
	CWordList() { ; }
	CWordList(CWordList &list) { AddTail(&list); }
	~CWordList() { RemoveAll(); }
	void operator = (CWordList &list) { RemoveAll(); AddTail(&list); }
};


typedef CMap<CString, LPCSTR, CWordList, CWordList &> CCatsToOpcodesMap;

class  __declspec(dllexport) CCommandAndControl
{
	int m_nCurrentDeviceID;

public:
	CCommandAndControl();
	virtual ~CCommandAndControl();

	void SetTargetDevice(CICATMessage::eDirection targetDev);
	CICATMessage::eDirection GetTargetDevice();

	static BOOL SetATCommandsMode(int nMode);
	static BOOL SetATCommandsOverDiag(CString strSendATCommandCat1, CString strSendATCommandCat2, CString strSendATCommandCat3, CString strRecvATCommandCat1, CString strRecvATCommandCat2, CString strRecvATCommandCat3, eTargetType trgetType);

	/*********************************************************************************/
	BOOL Cat123ToID(const CStringA &Cat123, USHORT &moduleID, USHORT &commandID, BOOL bReport = TRUE);
	BOOL Cat123ToID(const CStringA &Cat1, const CStringA &Cat2, const CStringA &Cat3, USHORT &moduleID, USHORT &commandID, BOOL bReport = TRUE);
	BOOL Cat123ToID(const CStringA &Cat123, USHORT &moduleID, USHORT &commandID, eTargetType TargetType,BOOL bReport = TRUE);
	BOOL Cat123ToID(const CStringA &Cat1, const CStringA &Cat2, const CStringA &Cat3, USHORT &moduleID, USHORT &commandID, eTargetType TargetType, BOOL bReport = TRUE);
	BOOL ReportLineToEnumStrings(const CStringA &reportLine, CStringA &Cat1,  CStringA &Cat2, CStringA &Cat3, BOOL bReport = TRUE);
	bool AppReportLineToEnumStrings(const CStringA &reportLine, CStringA &Cat1,  CStringA &Cat2, CStringA &Cat3, BOOL bReport = TRUE);

#ifdef _UNICODE
	BOOL ReportLineToEnumStrings(const CString &reportLine, CString &Cat1,  CString &Cat2, CString &Cat3, BOOL bReport = TRUE);
	bool AppReportLineToEnumStrings(const CString &reportLine, CString &Cat1,  CString &Cat2, CString &Cat3, BOOL bReport = TRUE);
	BOOL Cat123ToID(const CString &Cat123, USHORT &moduleID, USHORT &commandID, BOOL bReport = TRUE);
	BOOL Cat123ToID(const CString &Cat1, const CString &Cat2, const CString &Cat3, USHORT &moduleID, USHORT &commandID, BOOL bReport = TRUE);
	BOOL Cat123ToID(const CString &Cat123, USHORT &moduleID, USHORT &commandID, eTargetType TargetType, BOOL bReport = TRUE);
	BOOL Cat123ToID(const CString &Cat1, const CString &Cat2, const CString &Cat3, USHORT &moduleID, USHORT &commandID, eTargetType TargetType, BOOL bReport = TRUE);
	bool GetEnumStrings(USHORT moduleID, USHORT messageID, CString &Cat1, CString &Cat2, CString &Cat3, BOOL bReport = TRUE);
#endif

	bool GetEnumStrings(USHORT moduleID, USHORT messageID, CStringA &Cat1, CStringA &Cat2, CStringA &Cat3, BOOL bReport = TRUE);

	void SetCommandAndControlName(const CString &strName);
	BOOL PlayMacro(const CString& a_sMacroFileName, bool a_bInfiniteLoop = false, int a_iIterationsNumber = 1);
	static CICATMessage::eDirection GetAllOpenDevices();

	WORD GetGKITaskID(const CString &strTaskName);
	void StopWait();
	void SetDebugMode(bool bstate = true);

	/*******************************
	*                              *
	*      Send and Wait           *
	*                              *
	********************************/

	UE_errCode_t SendCommand(BYTE *data, int length, bool bToDiagOnly);
	UE_errCode_t SendCommand(UE_Message &command);
	UE_errCode_t SendCommand(UE_Message &command, DWORD dwWriteTimeout);
	UE_errCode_t SendCommand(const CStringA &Cat1, const CStringA &Cat2, const CStringA &Cat3, BYTE *pData = NULL, WORD dataLen = 0, bool fixup = false);
#ifdef _UNICODE
	UE_errCode_t SendCommand(const CString &Cat1, const CString &Cat2, const CString &Cat3, BYTE *pData = NULL, WORD dataLen = 0, bool fixup = false);
#endif

	UE_errCode_t WaitForMessage(UE_Message &report, UINT64 &messageNum, int timeout= DEFAULT_TIMEOUT, bool searchFIFO =false, bool useMsgNum =false);
	UE_errCode_t WaitForMessage(UE_FrameMessage &report, UINT64 &messageNum, int timeout= DEFAULT_TIMEOUT, bool searchFIFO =false, bool useMsgNum =false);
	UE_errCode_t WaitForMultipleMessage(UE_Message &report, const CStringList &strWaitList, UINT64 &messageNum, int timeout = DEFAULT_TIMEOUT);

	UE_errCode_t SendAndWait(UE_Message &command, UE_Message &report, UINT64 &messageNum, int timeout = DEFAULT_TIMEOUT);
	UE_errCode_t SendAndWaitMultiple(UE_Message &command, UE_Message &report, const CStringList &strWaitList, UINT64 &messageNum, int timeout = DEFAULT_TIMEOUT);

	///// Ext Command ///////////

	UE_errCode_t SendExtCommand(UE_ExtMessage &command);
	UE_errCode_t SendExtCommand(const CStringW &Cat1, const CStringW &Cat2, const CStringW &Cat3, WORD opCode, BYTE *pData = NULL, WORD dataLen = 0);
	UE_errCode_t WaitForExtMessage(UE_ExtMessage &report, UINT64 &messageNum, int timeout = DEFAULT_TIMEOUT, bool searchFIFO = false);
	UE_errCode_t SendExtAndWait(UE_ExtMessage &command, UE_Message &report, UINT64 &messageNum, int timeout = DEFAULT_TIMEOUT);
	UE_errCode_t SendExtAndWaitExt(UE_ExtMessage &command, UE_ExtMessage &report, UINT64 &messageNum, int timeout = DEFAULT_TIMEOUT);

	////// Internal Service ///

	UE_errCode_t SendInternalServiceCommand(BYTE serviceID, eTargetType targetType = UE_Comm_Side);
	UE_errCode_t WaitForInternalServiceCommand(USHORT serviceID, BYTE* messageBuf, int bufferLen, int timeout = DEFAULT_TIMEOUT);
	UE_errCode_t WaitForInternalServiceCommand(USHORT serviceID, eTargetType targetType, BYTE* messageBuf, int bufferLen, int timeout = DEFAULT_TIMEOUT);
	UE_errCode_t SendInternalServiceCommandAndWait(BYTE sendServiceID, USHORT waitServiceID, BYTE* messageBuf, int bufferLen, int timeout = DEFAULT_TIMEOUT);
	UE_errCode_t SendInternalServiceCommandAndWait(BYTE sendServiceID, eTargetType targetType, USHORT waitServiceID, eTargetType replyTargetType, BYTE* messageBuf, int bufferLen, int timeout = DEFAULT_TIMEOUT);

	///// AT Commands ///////////

	UE_errCode_t SendATCommand(const CString &strCommand, UINT nSuffix = SUFFIX_RETURN);

	UE_errCode_t WaitForATMessage(CStringW& strMessage = ANY_STRING, int timeout = DEFAULT_TIMEOUT);
	UE_errCode_t WaitForATMessage(CString& strMessage, UINT64 &messageNum, int timeout = DEFAULT_TIMEOUT);
	UE_errCode_t WaitForMultipleATMessage(CString &strMessage, const CStringList &strWaitList, UINT64 &messageNum, int timeout = DEFAULT_TIMEOUT);

	UE_errCode_t SendATAndWait(const CString& strCommand, UINT nSuffix = SUFFIX_RETURN, CStringW& strMessage = ANY_STRING, int timeout = DEFAULT_TIMEOUT);
	UE_errCode_t SendATAndWait(const CString& strCommand, UINT nSuffix, CString& strMessage, UINT64 &messageNum, int timeout = DEFAULT_TIMEOUT);
	UE_errCode_t SendATAndWaitMultiple(const CString &strCommand, UINT nSuffix, CString &strMessage, const CStringList &strWaitList, UINT64 &messageNum, int timeout = DEFAULT_TIMEOUT);

	//Michal - the following function support in waiting for more than one AT message to recived
	UE_errCode_t SendATAndWaitSeveral(const CString &strCommand, UINT nSuffix, CStringList &strMsgList, CStringList &strWaitList, CArray<UINT64,UINT64&> &messageNumArray, int timeout = DEFAULT_TIMEOUT);

	////// GKI Command //////////

	UE_errCode_t SendGKISignal(WORD sourceTaskID, WORD targetTaskID, const CString &strSignalName, BYTE *pData, WORD len);
	UE_errCode_t WaitForGKISignal(GKI_Signal &signal, UINT64 &messageNum, int timeout = DEFAULT_TIMEOUT, bool searchFIFO = false);
//	UE_errCode_t SendGKISignalAndWaitGKISignal(GKI_Signal &sendSignal, GKI_Signal &waitSignal, UINT64 &messageNum, int timeout = DEFAULT_TIMEOUT);

	///// Huge Command ////////

	UE_errCode_t SendHugeCommand(const CStringA &Cat1, const CStringA &Cat2, const CStringA &Cat3, BYTE *pData = NULL, WORD dataLen = 0, int nMaxLength = -1, bool fixup = false);
	UE_errCode_t SendHugeCommand(UE_Message &command, int nMaxLength = -1);

private:
	UE_errCode_t SendATCommandOverDiag(CString lpszCommand);
	UE_errCode_t SendATCommandOverGKI(CString lpszCommand);

public:

  	/*******************************
	*                              *
	*           F I F O            *
	*                              *
	********************************/

	void StartFIFO();
	void StopFIFO(BOOL bStopCompletely = TRUE);
	void SetFifoSize(int nSize, bool bClear = true);

	UINT64 DeleteMessage(UINT64 messageNum);
	void ClearMessageFIFO(UINT64 upToMessageNum = CLEAR_ALL);
	
	void GoToBeginningOfFIFO();

	UINT64 GetNextMessage(UE_Message &Report, UINT64 messageNum, const CString &Cat1 = ALL_MESSAGES, const CString &Cat2 = ALL_MESSAGES, const CString &Cat3 = ALL_MESSAGES, BOOL bDelete = FALSE);
	UINT64 GetNextMessage(UE_FrameMessage &Report, UINT64 messageNum, const CStringA &Cat1 = "", const CStringA &Cat2 = "", const CStringA &Cat3 = "", BOOL bDelete =FALSE);
	UINT64 GetNextExtMessage(UE_ExtMessage &Report, UINT64 messageNum, const CString &Cat1 = ALL_MESSAGES, const CString &Cat2 = ALL_MESSAGES, const CString &Cat3 = ALL_MESSAGES, WORD getOpcode = ALL_OPCODES, BOOL bDelete = FALSE);

	UINT64 GetNextATMessage(CString &strMessage, UINT64 messageNum, BOOL bDelete = FALSE);

	void RemoveMessagesFromFIFO(const CStringA &strCat1 = "", const CStringA &strCat2 = "", const CStringA &strCat3 = "", eTargetType targetType = UE_Comm_Side);
	void RemoveExtMessagesFromFIFO(const CStringA &strCat1 = "", const CStringA &strCat2 = "", const CStringA &strCat3 = "", WORD wOpcode = ALL_OPCODES);

	UINT64 GetCat123Message(UE_FrameMessage &Report, UINT64 messageNum, const CStringA &Cat1 = "", const CStringA &Cat2 = "", const CStringA &Cat3 = "", BOOL bDelete = FALSE);
	UINT64 GetCat123Message(UE_Message &Report, UINT64 messageNum, const CStringA &Cat1 = "", const CStringA &Cat2 = "", const CStringA &Cat3 = "", BOOL bDelete = FALSE);

	/*******************************
	*                              *
	*           Filter             *
	*                              *
	********************************/
	// Download Filter operations:
	UE_errCode_t SetDIAGTargetFilterArray(BYTE *pArray, int nLength, eTargetType targetType = UE_Comm_Side);
	UE_errCode_t GetDIAGTargetFilterArray(BYTE *pBuffer, int &nLength, eTargetType targetType = UE_App_Side, int timeout = DEFAULT_TIMEOUT);//hlguo added default value to support LNS.

	UE_errCode_t SetDIAGTargetFilterMessage(const CStringW &strCat1, const CStringW &strCat2, const CStringW &strCat3, BYTE bPass);
	UE_errCode_t SetDIAGTargetFilterMessage(const CStringA &strCat1, const CStringA &strCat2, const CStringA &strCat3, eTargetType TargetType, BYTE bPass);
	UE_errCode_t GetDIAGTargetFilterMessage(const CStringA &strCat1, const CStringA &strCat2, const CStringA &strCat3, eTargetType TargetType, BYTE &bFitlered, int timeout = DEFAULT_TIMEOUT);

	UE_errCode_t SetTraceFilter(eTargetType client, const CStringA & strCat1, const CStringA & strCat2, const CStringA & strCat3, const stFilterData & FilterData);
	UE_errCode_t SetTraceFilter(eTargetType client, const CStringA & strCat123, const stFilterData & FilterData);
	UE_errCode_t SetTraceFilter(eTargetType client, USHORT ModuleId, USHORT MessageId, const stFilterData & FilterData);

	UE_errCode_t SetGKITargetFilterSignal(const CStringA &strSignalName, BYTE bPass);
	UE_errCode_t GetGKITargetFilterSignal(const CStringA &strSignalName, BYTE &bFiltered, int timeout = DEFAULT_TIMEOUT);

	UE_errCode_t SetSignalFilter(const CStringA & strSignal, const stFilterData & FilterData);
	UE_errCode_t SetSignalFilter(DWORD SignalId, const stFilterData & FilterData);

#ifdef _UNICODE
	UE_errCode_t SetDIAGTargetFilterMessage(const CStringW &strCat1, const CStringW &strCat2, const CStringW &strCat3, eTargetType TargetType, BYTE bPass);
	UE_errCode_t GetDIAGTargetFilterMessage(const CStringW &strCat1, const CStringW &strCat2, const CStringW &strCat3, eTargetType TargetType, BYTE &bFitlered, int timeout = DEFAULT_TIMEOUT);
	UE_errCode_t SetTraceFilter(eTargetType client, const CStringW & strCat1, const CStringW & strCat2, const CStringW & strCat3, const stFilterData & FilterData);
	UE_errCode_t SetTraceFilter(eTargetType client, const CStringW & strCat123, const stFilterData & FilterData);
	UE_errCode_t SetGKITargetFilterSignal(const CStringW &strSignalName, BYTE bPass);
	UE_errCode_t GetGKITargetFilterSignal(const CStringW &strSignalName, BYTE &bFiltered, int timeout = DEFAULT_TIMEOUT);
	UE_errCode_t SetSignalFilter(const CStringW & strSignal, const stFilterData & FilterData);
#endif
};


#define SIM_SLEEP(ms, f) SleepEx((CCommandAndControl::m_bSimulationMode ? ms * CCommandAndControl::m_TimeoutMultiplyFactor : ms) , (f))




// DB update messages
#define WM_DB_UPDATE_ALL			(WM_USER+20)
#define WM_DB_UPDATE_COMM_DIAG		(WM_USER+21)
#define WM_DB_UPDATE_COMM_NVM		(WM_USER+22)
#define WM_DB_UPDATE_COMM_DSP		(WM_USER+23)
#define WM_DB_UPDATE_COMM_ASN1		(WM_USER+24)
#define WM_DB_UPDATE_APP_DIAG		(WM_USER+25)
#define WM_DB_UPDATE_APP_NVM		(WM_USER+26)


#endif // !defined(AFX_COMMANDANDCONTROL_H__C21CA1F6_191D_11D5_8230_0006294FD6F7__INCLUDED_)

