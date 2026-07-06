#pragma once
#include <afxmt.h>

#include <map>
#include <set>
#include "..\Converter\MessageBuilder.h"
#include "IDispatcherBase.h"
#include "..\Converter\CommandAndMessageStructures.h"
#include "MrvlCommon\CommonDefs.h"
#include "MrvlCommon\Dispatcher.h"
#include "MrvlCommon\SmartShell.h"
#include "MrvlCommon\DeviceStatus.h"

#define VGMUX_CHANNEL_COMMAND_2		1
#define VGMUX_CHANNEL_UNSOLISITED	4
#define DIAG_MI_LOGGED_SIGNAL			5

#ifdef _CATCORE_DLL
#define _DLL_EXPORT_ __declspec(dllexport) 
#else
#define _DLL_EXPORT_ __declspec(dllimport) 
#endif


class _DLL_EXPORT_/*__declspec(dllexport)*/ CCommandChannel
{
private:
	CCommandChannel(int nDevice = 0);
public:
	~CCommandChannel(void);
	static CCommandChannel*  Instance(int nDevice=0);
	void DeleteInstance();

private:
	struct DiagSting 
	{
		CString Cat1;
		CString Cat2;
		CString Cat3;
		bool operator < (const DiagSting &p) const
		{
			if(Cat1 != p.Cat1)
				return Cat1 < p.Cat1;
			else
				if(Cat2 != p.Cat2)
					return Cat2 < p.Cat2;
				else
					return Cat3 < p.Cat3;
		}
	};
	struct DiagID
	{
		UINT moduleID;
		UINT commandID;
	};

	std::map<DiagSting,DiagID> m_mapDiagMeaaage;
	std::map<DiagSting,DiagID> ::iterator pos;

	const int m_nDevice;	

// 	class CICATMessage * m_pMessage;
// 	eTargetType m_WaitTargetType;
// 	CICATMessage::eDirection m_TargetDevice;
// 	CString m_WaitCat1;
// 	CString m_WaitCat2;
// 	CString m_WaitCat3;
// 	unsigned int m_iMessageCount;
// 	CEvent			m_MessageReadyEvent;
// 	const CStringList * m_pstrWaitList;
// 	int     m_WaitType;
//	WORD    m_WaitOpcode;
//	CEvent	m_WaitingForMessageEvent;

	CCriticalSection m_SendAndWaitSync;				//Richard added	2011-10-21		

//	HANDLE m_hFIFOSync;

	CCriticalSection m_LoggerFIFOSync;
	static	eOSType	m_nCommOSType[MAX_DEVICE_NUM];
	static	eOSType	m_nAppOSType[MAX_DEVICE_NUM];

private:
//	volatile BOOL m_bCatchMessage;			//Begin catch message or Stop catch message.
//	volatile LONG m_nCatchMessage;			//how many catch message requests.
	CICATMessageReceiverPTK m_MessageReceiver;
	CList<CICATMessage*, CICATMessage*> m_LoggerFIFO;
	POSITION m_Position;

	static CCriticalSection		m_InstanceCreationLock;
	static SmartShell<CCommandChannel> m_SmartShell;
	friend class SmartShell<CCommandChannel>;

public:
	BOOL ReleaseAll();
//	UE_errCode_t SetTargetDevice(CICATMessage::eDirection targetDev, int nDevice);
//	void SetTargetDevice(CICATMessage::eDirection targetDev);
	CICATMessage::eDirection GetTargetDevice();

	BOOL GetEnumStrings(USHORT moduleID, USHORT messageID, CString &Cat1, CString &Cat2, CString &Cat3, BOOL bReport = TRUE);
	BOOL GetEnumStrings( USHORT moduleID, USHORT messageID, CString &Cat1, CString &Cat2, CString &Cat3, BOOL *bIsExtMessage /*=NULL*/ );
	BOOL GetAppEnumStrings(USHORT moduleID, USHORT messageID, CString &Cat1, CString &Cat2, CString &Cat3, BOOL bReport = TRUE);
	BOOL AppCat123ToID(const CString &Cat1, const CString &Cat2, const CString &Cat3, USHORT &moduleID, USHORT &commandID, BOOL bReport = TRUE);
	BOOL AppCat123ToID(const CString &Cat123, USHORT &moduleID, USHORT &commandID, BOOL bReport = TRUE);
	BOOL Cat123ToID(const CString &Cat1, const CString &Cat2, const CString &Cat3, USHORT &moduleID, USHORT &commandID, BOOL bReport = TRUE);
	BOOL Cat123ToID(const CString &Cat123, USHORT &moduleID, USHORT &commandID, BOOL bReport = TRUE);

	BOOL PlayMacro(const CString& a_sMacroFileName, BOOL a_bInfiniteLoop = false, int a_iIterationsNumber = 1);
	static BOOL IsAlive(int nDevice);
	static BOOL IsRawData(int nDevice);
	static BOOL IsDIAG(int nDevice);
	static BOOL IsADB(int nDevice);
	static CICATMessage::eDirection  GetAllOpenDevices();

public:
	static void GetICATPath(CString& strPath);
	//eOSType	GetOSType(eTargetType TargetType);
	static CString& GetICATPath();
	static BOOL DiagPackMessage(const char* inBuf, char* outBuf, int inlen, int& outLen);


	//eOSType	GetOSTypeOnDevice(eTargetType TargetType, int nDevice);	
	static void DeleteCmdAndCtrlInstance(int nDevice);

	static BOOL SetATCommandsMode(int nMode);
	static BOOL SetATCommandsOverDiag(CString strSendATCommandCat1, CString strSendATCommandCat2, CString strSendATCommandCat3, CString strRecvATCommandCat1, CString strRecvATCommandCat2, CString strRecvATCommandCat3, eTargetType targetType);

public:
	// AT Commands Settings
	static int m_ATCommandsMode;
	class CMessageBuilder	*m_pMessageBuilder;
	static CString m_strSendATCommandCat1;
	static CString m_strSendATCommandCat2;
	static CString m_strSendATCommandCat3;
	static CString m_strRecvATCommandCat1;
	static CString m_strRecvATCommandCat2;
	static CString m_strRecvATCommandCat3;
	static eTargetType m_DiagATCommandsTargetType;

   public:
	BOOL LockSendAndWaitSync(CString str = _T(""));
	void UnLockSendAndWaitSync(CString str  = _T(""));

   static void GetTestTime(UINT& t1, UINT&t2, UINT& t3);
   static void SetTestTime(UINT t1, UINT t2, UINT t3);

   CEvent m_FIFONotEmptyEvent;

public:



	int SetCommandHeader(BYTE * buffer, CString strCat1, CString strCat2, CString strCat3, eTargetType TargetType = UE_Comm_Side, bool fixup = false);
	int	BuildHeader(LPBYTE pData, int nBufLen, int nId, int nModule, DWORD dwDBVersion, int nDestination=0, bool bFixup=false);


	/*******************************
	*      Update filter ???       *
	********************************/
private:
	std::set<USHORT> m_ReportIdSet;
	std::set<USHORT> m_AppReportIdSet;

public:
//	bool  UpdateFilter(eTargetType targetType, USHORT messageId );
//	bool  UpdateFilter(eTargetType targetType, const CArray<USHORT,USHORT>& messageIdArray );

	////////////////////////////////
	////////////////////////////////

	bool GetModuleMessageId(const UE_Message& report, USHORT& moduleId, USHORT& messageId );
	bool GetMultipleModuleMessageId(const UE_Message& report, const CStringList& strWaitList, CArray<USHORT, USHORT>& moduleIdArray, CArray<USHORT, USHORT>& messageIdArray);
	BOOL ParseCommand(UE_MessageWithId &command);
//	static void RecordDiagMessageProcedure(CICATMessage* pMessage, CString strFuncName);
//	static void RecordRead_BeginEnd(BOOL bBegin, char* pBuffer = NULL, UINT uLen = 0);

	/*******************************
	*                              *
	*      Send and Wait           *
	*                              *
	********************************/
	void SetDebugMode(bool bstate = true) {m_bDebugMode = bstate;}
	void StopWait() { m_bStopWait = true; }
	void EmptyMessageList();

	void CatchMessages(bool start = true, bool clear = true);

	UE_errCode_t SendCommand(UE_Message &command, DWORD timeout = DEFAULT_TIMEOUT);
	UE_errCode_t SendCommand(UE_MessageWithId &command, DWORD timeout = DEFAULT_TIMEOUT);
	UE_errCode_t SendCommand(BYTE *data, int length , BOOL bToDiagOnly);
	UE_errCode_t SendCommandWithTimeout(BYTE *data, int length , BOOL bToDiagOnly, int nTimeout);
	UE_errCode_t SendCommand(const CString &Cat1, const CString &Cat2, const CString &Cat3, BYTE *pData = NULL, WORD dataLen = 0, BOOL fixup = false);
	UE_errCode_t SendCommand(UE_Message &command, int nDevice);

	UE_errCode_t WaitForMessage(UE_Message &report, UINT64 &messageNum, int timeout = DEFAULT_TIMEOUT, BOOL searchFIFO = false);
	UE_errCode_t WaitForMessage(UE_Message &report, UINT64 &messageNum, int timeout, BOOL searchFIFO, int nDevice);
	UE_errCode_t WaitForMessagePTK(UE_Message &report, UINT64 &messageNum, int timeout= DEFAULT_TIMEOUT, bool searchFIFO =false, bool useMsgNum =false);
	UE_errCode_t WaitForMessagePTK(UE_FrameMessage &report, UINT64 &messageNum, int timeout= DEFAULT_TIMEOUT, bool searchFIFO =false, bool useMsgNum =false);
	UE_errCode_t WaitForMultipleMessage(UE_Message &report, const CStringList &strWaitList, UINT64 &messageNum, int timeout = DEFAULT_TIMEOUT);
	UE_errCode_t WaitForMultipleMessage(UE_Message &report, const CStringList &strWaitList, UINT64 &messageNum, int timeout, int nDevice);
	UE_errCode_t WaitForMultipleMessage(UE_Message &report, CArray<USHORT,USHORT>& arModuleId, CArray<USHORT,USHORT>& arMessageId, UINT64 &messageNum, int timeout =DEFAULT_TIMEOUT);
	UE_errCode_t WaitForGKISignal(GKI_Signal& signal, UINT64& messageNumber, int timeout, bool searchFifo = false, bool useMessageNumber = false);


	UE_errCode_t SendAndWait(UE_Message &command, UE_Message &report, UINT64 &messageNum, int timeout = DEFAULT_TIMEOUT);
	UE_errCode_t SendAndWait(UE_Message &command, UE_Message &report, UINT64 &messageNum, int timeout, int nDevice);

	UE_errCode_t SendAndWaitMultiple(UE_Message &command, UE_Message &report, const CStringList &strWaitList, UINT64 &messageNum, int timeout = DEFAULT_TIMEOUT);
	UE_errCode_t SendAndWaitMultiple(UE_Message &command, UE_Message &report, CArray<USHORT,USHORT>& arModuleId, CArray<USHORT,USHORT>& arMessageId, UINT64 &messageNum, int timeout = DEFAULT_TIMEOUT);
	static UE_errCode_t SendAndWaitMultiple(UE_Message &command, UE_Message &report, const CStringList &strWaitList, UINT64 &messageNum, int timeout, int nDevice);

	///// Ext Command ///////////

	UE_errCode_t SendExtCommand(UE_ExtMessage &command);
	UE_errCode_t SendExtCommand(const CString &Cat1, const CString &Cat2, const CString &Cat3, WORD opCode, BYTE *pData = NULL, WORD dataLen = 0);
	UE_errCode_t SendExtCommand(UE_ExtMessage &command, int nDevice);

	UE_errCode_t WaitForExtMessage(UE_ExtMessage &report, UINT64 &messageNum, int timeout, BOOL searchFIFO, int nDevice);
	UE_errCode_t WaitForExtMessage(UE_ExtMessage &report, UINT64 &messageNum, int timeout = DEFAULT_TIMEOUT, BOOL searchFIFO = false);
	UE_errCode_t SendAndExtWait(UE_Message &command, UE_ExtMessage &report, UINT64 &messageNum, int timeout = DEFAULT_TIMEOUT);
	UE_errCode_t SendExtAndWait(UE_ExtMessage &command, UE_Message &report, UINT64 &messageNum, int timeout, int nDevice);
	UE_errCode_t SendExtAndWait(UE_ExtMessage &command, UE_Message &report, UINT64 &messageNum, int timeout = DEFAULT_TIMEOUT);
	UE_errCode_t SendExtAndWaitExt(UE_ExtMessage &command, UE_ExtMessage &report, UINT64 &messageNum, int timeout, int nDevice);//Michal
	UE_errCode_t SendExtAndWaitExt(UE_ExtMessage &command, UE_ExtMessage &report, UINT64 &messageNum, int timeout = DEFAULT_TIMEOUT);

	///// AT Commands ///////////

	UE_errCode_t SendATCommand(const CString &strCommand, UINT nSuffix, int nDevice);
	UE_errCode_t SendATCommand(const CString &strCommand, UINT nSuffix = SUFFIX_RETURN);
	UE_errCode_t SendATCommandOverGKI(CString lpszCommand); //sxwang add 2011-09-21
	UE_errCode_t SendATCommandOverDiag(CString lpszCommand);
	UE_errCode_t SendATCommandOverString(CString lpszCommand);		//Send string directly.

	UE_errCode_t WaitForATMessage(CString& strMessage, UINT64 &messageNum, int timeout, int nDevice);//Michal
	UE_errCode_t WaitForATMessage(CString &strMessage /*=ANY_STRING*/, UINT64 &messageNum, int timeout =DEFAULT_TIMEOUT);
	UE_errCode_t WaitForMultipleATMessage(CString &strMessage, const CStringList &strWaitList, UINT64 &messageNum, int timeout, int nDevice);
	UE_errCode_t WaitForMultipleATMessage(CString &strMessage, const CStringList &strWaitList, UINT64 &messageNum, int timeout =DEFAULT_TIMEOUT);
	UE_errCode_t WaitForSeveralATMessage(CStringList &strMsgList, CStringList &strWaitList, CArray<UINT64,UINT64&> &messageNumArray, int timeout = DEFAULT_TIMEOUT);
	UE_errCode_t WaitForATMessageOverDiag(CString &strMessage /*=ANY_STRING*/, UINT64 &messageNum, int timeout =DEFAULT_TIMEOUT);
	UE_errCode_t WaitForMultipleATMessageOverDiag(CString &strMessage, const CStringList &strWaitList, UINT64 &messageNum, int timeout =DEFAULT_TIMEOUT);
	UE_errCode_t WaitForSeveralATMessageOverDiag(CStringList &strMsgList, CStringList &strWaitList, CArray<UINT64,UINT64&> &messageNum, int timeout = DEFAULT_TIMEOUT);
	UE_errCode_t WaitForATMessageOverGKI(CString &strMessage, UINT64 &messageNum, int timeout = DEFAULT_TIMEOUT);
	UE_errCode_t WaitForMultipleATMessageOverGKI(CString &strMessage, const CStringList &strWaitList, UINT64 &messageNum, int timeout = DEFAULT_TIMEOUT);
	UE_errCode_t WaitForSeveralATMessageOverGKI(CStringList &strMsgList, CStringList &strWaitList, CArray<UINT64,UINT64&> &messageNum, int timeout = DEFAULT_TIMEOUT);

	UE_errCode_t SendATAndWait(const CString &strCommand, UINT nSuffix, CString &strMessage, UINT64 &messageNum, int timeout, int nDevice);
	UE_errCode_t SendATAndWait(const CString &strCommand, UINT nSuffix, CString &strMessage, UINT64 &messageNum, int timeout = DEFAULT_TIMEOUT);
	UE_errCode_t SendATAndWaitMultiple(const CString &strCommand, UINT nSuffix, CString &strMessage, const CStringList &strWaitList, UINT64 &messageNum, int timeout, int nDevice);
	UE_errCode_t SendATAndWaitMultiple(const CString &strCommand, UINT nSuffix, CString &strMessage, const CStringList &strWaitList, UINT64 &messageNum, int timeout = DEFAULT_TIMEOUT);
	UE_errCode_t SendATAndWaitSeveral(const CString &strCommand, UINT nSuffix, CStringList &strMsgList, CStringList &strWaitList, CArray<UINT64,UINT64&> &messageNumArray, int timeout = DEFAULT_TIMEOUT);

	////// GKI Command //////////

	UE_errCode_t SendGKICommand(/*class*/ GKI_Command &command);
	UE_errCode_t SendGKISignal(/*class*/ GKI_Signal &signal);
	UE_errCode_t SendGKISignal(WORD sourceTaskID, WORD targetTaskID, const CString &strSignalName, BYTE *pData, WORD len);
	
	////// Internal Service ///

	HANDLE GetKillWriteHandle();
	UE_errCode_t SendInternalServiceCommand(BYTE serviceID, eTargetType targetType);
	UE_errCode_t SendInternalServiceCommand(BYTE serviceID, eTargetType targetType, int nTimeout);

	///// Huge Command ////////

	UE_errCode_t SendHugeCommandPTK(const CString &Cat1, const CString &Cat2, const CString &Cat3, BYTE *pData = NULL, WORD dataLen = 0, int nMaxLength = -1, bool fixup = false);
	UE_errCode_t SendHugeCommandPTK(UE_Message &command, int nMaxLength = -1);

	///// ADB ////////////////

	UE_errCode_t SendADBCommand(const CString &strCommand);
	UE_errCode_t WaitForADBMessage(CString &strMessage /*=ANY_STRING*/, UINT64 &messageNum, int timeout =DEFAULT_TIMEOUT);
	UE_errCode_t SendADBAndWait(const CString &strCommand, CString &strMessage, UINT64 &messageNum, int timeout, int nDevice);
	UE_errCode_t StopADBCommand();

	/*******************************
	*                              *
	*           F I F O            *
	*                              *
	********************************/

	void StartFIFO();
	void StopFIFO(BOOL bStopCompletely =TRUE);

	static void HandleICATMessage(void* pObj, CICATMessage* pMessage);
	void  HandleMessage(CICATMessage* pMessage);
	void SetFifoSize(int nSize, bool bClear = true);
	void ClearFIFO(UINT64 upToMessageNum =CLEAR_ALL);

	UINT64 DeleteMessage(UINT64 messageNum);
	void GoToBeginningOfFIFO();
	void RemoveMessagesFromFIFO(const CString &strCat1=ALL_MESSAGES, const CString &strCat2=ALL_MESSAGES, const CString &strCat3=ALL_MESSAGES, eTargetType targetType=UE_Comm_Side);
	void RemoveExtMessagesFromFIFO(const CString &strCat1=ALL_MESSAGES, const CString &strCat2=ALL_MESSAGES, const CString &strCat3=ALL_MESSAGES, WORD wOpcode=ALL_OPCODES);

	UINT64 GetExtMessage(UE_ExtMessage &Report, UINT64 messageNum, const CString &Cat1 = ALL_MESSAGES, const CString &Cat2 = ALL_MESSAGES, const CString &Cat3 = ALL_MESSAGES, WORD getOpcode = ALL_OPCODES, BOOL bDelete = FALSE);
	UINT64 GetExtMessage(UE_ExtMessage &Report, UINT64 messageNum, const CString &Cat1, const CString &Cat2, const CString &Cat3, WORD getOpcode, BOOL bDelete, int nDevice);//Micahl
	UINT64 GetNextExtMessage(UE_ExtMessage &Report, UINT64 messageNum, const CString &Cat1 = ALL_MESSAGES, const CString &Cat2 = ALL_MESSAGES, const CString &Cat3 = ALL_MESSAGES, WORD getOpcode = ALL_OPCODES, BOOL bDelete = FALSE);
	UINT64 GetNextExtMessage(UE_ExtMessage &Report, UINT64 messageNum, const CString &Cat1, const CString &Cat2, const CString &Cat3, WORD getOpcode, BOOL bDelete, int nDevice);//Michal	
	UINT64 GetNextATMessage(CString &strMessage, UINT64 messageNum, BOOL bDelete = FALSE);
	UINT64 GetNextATMessage(CString &strMessage, UINT64 messageNum, BOOL bDelete, int nDevice);//Michal
	UINT64 GetNextMessage(UE_Message &Report, UINT64 messageNum, const CString &Cat1 = ALL_MESSAGES, const CString &Cat2 = ALL_MESSAGES, const CString &Cat3 = ALL_MESSAGES, BOOL bDelete = FALSE);
	UINT64 GetNextMessage(UE_Message &Report, UINT64 messageNum, const CString &Cat1, const CString &Cat2, const CString &Cat3, BOOL bDelete, int nDevice);//Michal	


	UINT64 GetCat123Message(UE_Message &Report, UINT64 messageNum, const CString &Cat1 /*ALL_MESSAGES*/, const CString &Cat2 /*ALL_MESSAGES*/, const CString &Cat3 /*ALL_MESSAGES*/, BOOL bDelete = FALSE);
	UINT64 GetNextMessagePTK(UE_FrameMessage &Report, UINT64 messageNum, const CString &Cat1 = ALL_MESSAGES, const CString &Cat2 = ALL_MESSAGES, const CString &Cat3 = ALL_MESSAGES, BOOL bDelete =FALSE);
	UINT64 GetCat123MessagePTK(UE_FrameMessage &Report, UINT64 messageNum, const CString &Cat1 = ALL_MESSAGES, const CString &Cat2 = ALL_MESSAGES, const CString &Cat3 = ALL_MESSAGES, BOOL bDelete = FALSE);
	UINT64 GetCat123MessagePTK(UE_Message &Report, UINT64 messageNum, const CString &Cat1 = ALL_MESSAGES, const CString &Cat2 = ALL_MESSAGES, const CString &Cat3 = ALL_MESSAGES, BOOL bDelete = FALSE);
	UINT64 GetGkiMessage(GKI_Signal& signal, UINT64 messageNumber, BOOL doDelete = FALSE);
    CICATMessage * GetNextMessagePTK();

private:
	UINT64 GetNextATMessageOverDiag(CString &strMessage, UINT64 messageNum, BOOL bDelete = FALSE);
	UINT64 GetNextATMessageOverGKI(CString &strMessage, UINT64 messageNum, BOOL bDelete = FALSE);

	/*******************************
	*                              *
	*           Filter             *
	*                              *
	********************************/
public:
	UE_errCode_t SetDIAGTargetFilterMessage(const CString &strCat1, const CString &strCat2, const CString &strCat3, BYTE bPass);
	UE_errCode_t SetDIAGTargetFilterMessage(const CString &strCat1, const CString &strCat2, const CString &strCat3, eTargetType targetType, BYTE bPass);
	UE_errCode_t SetDIAGTargetFilterMessage(const USHORT moduleID, const USHORT messageID, BYTE bPass);	
	UE_errCode_t SetDIAGTargetFilterMessage(const USHORT moduleID, const USHORT messageID, eTargetType targetType, BYTE bPass);	
	UE_errCode_t GetDIAGTargetFilterMessage(const CString &strCat1, const CString &strCat2, const CString &strCat3, eTargetType TargetType, BYTE &bFitlered, int timeout = DEFAULT_TIMEOUT);
	UE_errCode_t GetDIAGTargetFilterArray(BYTE *pBuffer, int &nLength, eTargetType targetType, int timeout = DEFAULT_TIMEOUT);
	UE_errCode_t SetDIAGTargetFilterArray(BYTE *pArray, int nLength, eTargetType targetType = UE_Comm_Side);

	/**************************************/

	void	SendICATMessage(const CString & strMsg);

private:

	bool	m_bStopWait;

	bool	m_bDebugMode;
	static const  int m_default_fifo_size = 5000;
	int				m_nLoggerFifoSize;
	
	static UINT m_SendAndWaitRetries;
	CICATMessage::eDirection m_TargetDevice;
};
