#pragma once
#include <afxmt.h>
#include <afxtempl.h>
#include "MrvlCommon/CommonDefs.h"
#include "MrvlCommon/RWLock.h"
#include "singletondestroyer.h"
#include "gsm\GsmHandler.h"
#include "SignalData.h"
#include "TokensMap.h"
#include "UE_Rec.h"
#include "DSPRecord.h"
#include "ASN1Engine\ASN1Handler.h"
#include "CSN1Handler.h"
#include "SmartShell.h"
#include "MessageIDToRecMap.h"
#include "DiagCommDef.h"
#include "CommandAndMessageStructures.h"
#include "MrvlCommon/ICATMessage.h"

#define theConverterManager(s) CConverterManager::Instance(s)
#define LOCK_CONVERTER		CSingleLock csConverterLock(&m_CSection); csConverterLock.Lock();
#define UNLOCK_CONVERTER	csConverterLock.Unlock();

class CCat2ToCat3Map;
class CCat3ToRecMap;

class CLockDBToRead
{
public:
	CLockDBToRead(CRWLock* lock)
	{
		m_RWLock = lock;
		m_RWLock->WaitToRead();
	}
	~CLockDBToRead()
	{
		m_RWLock->Done();
	}
private:
	CRWLock* m_RWLock;
};

class CLockDBToWrite
{
public:
	CLockDBToWrite(CRWLock* lock)
	{
		m_RWLock = lock;
		m_RWLock->WaitToWrite();
	}
	~CLockDBToWrite()
	{
		m_RWLock->Done();
	}
private:
	CRWLock* m_RWLock;
};

#define READ_LOCKER   CLockDBToRead  lockRead(&m_mapLock)
#define WRITE_LOCKER  CLockDBToWrite lockWrite(&m_mapLock)

#define LOCK_TO_READ     m_mapLock.WaitToRead()
#define LOCK_TO_WRITE    m_mapLock.WaitToWrite()
#define UNLOCK           m_mapLock.Done()

#define MAX_ALIGN_STRUCT	4
#define ALIGN(counter, align) ((counter) += ((UINT)(counter) % (align)) ? ((align)-(((UINT)(counter)) % (align))) : 0)

typedef enum DbArchitectureTag
{
	UnionsTableWithIndex  =    0,
	UnionsTableWithoutIndex  =    1
}DbArchitecture;

#define EMMI_HEADER_LEN		1
#define APP_SIDE_MASK_FOR_SENDING		((BYTE)0x80)

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

#define DIAG_HEADER_FOR_RECEIVING_MI_SIGNALS	8	// only Diag-SAP + Time-Stamp
#define DIAG_HEADER_FOR_RECEIVING_MI_SIGANLS	DIAG_HEADER_FOR_RECEIVING_MI_SIGNALS	// backwards compatibility

#define SIGNAL_MI			211
#define COMMAND_MI			213

#define MI_LOGGED_SIGNAL_HEADER_LENGTH(s)	CConverterManager::Instance(s)->GetGKILoggedSignalHeaderSize(kComm)

#define MI_COMMAND_HEADER_LENGTH(s)			CConverterManager::Instance(s)->GetGKICommandHeaderSize(kComm)

#define APP_MI_LOGGED_SIGNAL_HEADER_LENGTH(s)	CConverterManager::Instance(s)->GetGKILoggedSignalHeaderSize(kApp)

#define APP_MI_COMMAND_HEADER_LENGTH(s)		CConverterManager::Instance(s)->GetGKICommandHeaderSize(kApp)


#define MI_SIGNAL_HEADER_LENGTH			CConverterManager::Instance()->GetGKISignalHeaderSize(kComm)
#define APP_MI_SIGNAL_HEADER_LENGTH			CConverterManager::Instance()->GetGKISignalHeaderSize(kApp)
//for SIM0/1 window division
#define MAX_NUM_OF_TASKS    3000  //check m_mapGKITaskIdMap to find the end task id
#define SIM0_TASK_FLAG      0
#define SIM1_TASK_FLAG      1
#define COMM_TASK_FLAG      2

// CConverterManager command target
#if STATIC_BUILD
class CConverterManager
#else
class __declspec(dllexport) CConverterManager
#endif
{
public:
	virtual ~CConverterManager();

private:
	CConverterManager(int nDevice = 0);
	CRWLock				m_mapLock;
	CCriticalSection	m_CSection;
	CCriticalSection	m_DecodeNasCSection;
	CCriticalSection	m_NasMsgNameCSection;
	CCriticalSection	m_DecodeASN1AsStrCSection;
	CCriticalSection	m_DecodeNASWithASN1CSection;
	CCriticalSection   m_DecodeNasStreamCSection;
 	CCriticalSection	m_DecodeNasStrCSection;
	CCriticalSection	m_ASN1MsgNameCSection;
	CCriticalSection	m_ASN1MsgDetailsStrCSection;
	CCriticalSection	m_ASN1MsgDetailsStrArrCSection;
 	CCriticalSection   m_DecodeCSN1AsStrCSection;


   CCriticalSection  m_csASN1HandlerLock;
   CCriticalSection  m_csCSN1HandlerLock;

	static SmartShell<CConverterManager> m_SmartShell;
	friend class SmartShell<CConverterManager>;

	const int m_nDevice;
	CASN1Handler m_ASN1Handler;
	CCSN1Handler  m_CSN1Handler;
	CGsmHandler*  m_pGsmHandler;
	CMap<DWORD, DWORD, CStringArrayEx, CStringArrayEx&> m_SignalMap; //sxwang added for sending gki command. 08/26/2011
	CMap<DWORD, DWORD, DWORD, DWORD> m_mapAsnID;
	CMap<DWORD, DWORD, DWORD, DWORD> m_mapNasID;
	CMap<DWORD, DWORD, DWORD, DWORD> m_mapImsID;
	CMap<DWORD, DWORD, DWORD, DWORD> m_mapLwipLteID;
	CMap<DWORD, DWORD, DWORD, DWORD> m_mapLwipWifiID;
	// add by wenjie
	CMap <int, int, CMessageIDToRecMap *, CMessageIDToRecMap *> m_AppsModuleIDToMessageIDCommandMap;
	CMap<int, int, CMessageIDToRecMap *, CMessageIDToRecMap*> m_AppsModuleIDToMessageIDReportMap;
	CMap<int, int, CMessageIDToRecMap *, CMessageIDToRecMap*> m_ModuleIDToMessageIDReportMap;
	CMap <int, int, CMessageIDToRecMap *, CMessageIDToRecMap *> m_ModuleIDToMessageIDCommandMap;

	CMap <int, int, int , int> m_ClientIDToMaxMsgIDMap;


	CDSPRecordMap m_DSPCommandMap;
	CDSPRecordMap m_DSPReportMap;
	MapOpName2DSPItem m_mapDspReport;
	MapOpName2DSPItem m_mapDspCommand;

	
   volatile long ms_bIsLoaded;
   volatile long ms_bIsLoading;
   DWORD  m_dwCPVer;
   DWORD  m_dwAPVer;
   DWORD  m_dwCpNvmVer;
   DWORD  m_dwApNvmVer;
   static CCriticalSection m_Lock;
   static CString ms_strDBPath;  
   static CCriticalSection ms_csLockDBPath;
   

   void LoadSignalMap(const CString strFile);
	void RefreshAsn1ID();
	void RefreshNasMsgID();
	void RefreshImsMsgID();
	void RefreshLwipMsgID();

	CMap <USHORT, USHORT, CString, LPCTSTR> m_GKICommandMap;
	CMap <CString, LPCTSTR, CTokensMap *, CTokensMap *> m_AppEnumTypesMap;
	CMap <CString, LPCTSTR, CTokensMap *, CTokensMap *> m_EnumTypesMap;
	//CMap <LPCWSTR, LPCWSTR, DWORD, DWORD> m_SignalNameToSignalIDMap;
	CMap <CString, LPCTSTR, DWORD, DWORD> m_SignalNameToSignalIDMap;

	CMap <CString, LPCTSTR, CCat2ToCat3Map *, CCat2ToCat3Map *> m_Cat1ToCat2CommandMap;
	CMap <CString, LPCTSTR, CCat2ToCat3Map *, CCat2ToCat3Map *> m_Cat1ToCat2ReportMap;
	// All data-structures for DIAG commands/reports are duplicated for the Apps side.
	CList <CUE_Rec *, CUE_Rec *> m_AppsUERecs;
	CMap <CString, LPCTSTR, CCat2ToCat3Map *, CCat2ToCat3Map *> m_AppsCat1ToCat2CommandMap;
	CMap <CString, LPCTSTR, CCat2ToCat3Map *, CCat2ToCat3Map *> m_AppsCat1ToCat2ReportMap;

	int	m_StructAlignment[kMaxChipSetNum];
	int	m_EnumSize[kMaxChipSetNum];

public:
	void GetMaxDiagIDsMap(CMap <int, int, int , int> *&pMaxDiagIDsMap);	

	static CCriticalSection		m_InstanceCreationLock;
	static BOOL IsInstanceAlive(int nDeviceID);
	static CConverterManager* Instance(int nDevice/* = 0*/);
	static void DeleteInstance(int nDevice);
   static void InitSmartShell(int nSize);
	int BuildSignalArray(SignalGroupArray &aSignalArray);
	tSignalGroup * FindSignalGroup(SignalGroupArray &aSignalArray, DWORD dwSigId);
	BOOL GetEnumFromTable(const CString &EnumType, USHORT key, CString &strToken);
	BOOL GetEnumFromTable(const CString &EnumType, INT64 key, CString &strToken, BOOL bAppSide);
#ifdef _UNICODE
	BOOL GetEnumFromTable(const CString &EnumType, INT64 key, CString &strToken, eTargetDBType TargetDBType);
	bool GetEnumValueByName(const CString &EnumType, INT64& key,const CString &strToken, eTargetDBType TargetDBType);
#endif // _UNICODE
	BOOL GetEnumFromTable(const CStringA &EnumType, INT64 key, CStringA &strToken, eTargetDBType TargetDBType);	
	bool GetEnumValueByName(const CStringA &EnumType, INT64& key,const CStringA &strToken, eTargetDBType TargetDBType);
	//////////////////////////////////////////////////////////////////////////
	BOOL Cat123ToID(const CString &Cat1, const CString &Cat2, const CString &Cat3, USHORT &nModuleID, USHORT &nMessageID, BOOL bReport = TRUE);
	BOOL Cat123ToID(const CString& cat123 ,USHORT &nModuleID, USHORT &nMessageID, BOOL bReport = FALSE);
	BOOL Cat123ToID(const CString& cat123 ,USHORT *nModuleID, USHORT *nMessageID,int &nLength, BOOL bReport = FALSE);
	BOOL Cat123ToIDEx(const CString& cat123 ,USHORT &nModuleID, USHORT &nMessageID, BOOL bReport = TRUE);
	BOOL APCat123ToID(const CString& cat123, USHORT &nModuleID, USHORT &nMessageID, BOOL bAppSide = FALSE);				//AP: cat123->msgID+ModuleID
	BOOL APCat123ToID(const CString& cat123 ,USHORT *nModuleID, USHORT *nMessageID,int &nLength, BOOL bReport = FALSE);
	BOOL APCat123ToID(const CString& cat1, const CString& cat2, const CString& cat3, USHORT &nModuleID, USHORT &nMessageID, BOOL bAppSide = FALSE);				//AP: cat123->msgID+ModuleID
	BOOL APCat123ToIDEx(const CString& cat123, USHORT &nModuleID, USHORT &nMessageID, BOOL bReport = TRUE);
	BOOL GetReportEnumStrings(USHORT moduleID, USHORT messageID, CString &Cat1, CString &Cat2, CString &Cat3, BOOL bReport = TRUE);		//CP: msgID+ModuleID->cat123
	BOOL APGetReportEnumStrings(USHORT moduleID, USHORT messageID, CString &Cat1, CString &Cat2, CString &Cat3, BOOL bReport = TRUE);		//AP: msgID+ModuleID->cat123
	bool AppReportLineToEnumStrings(const CString &reportLine, CString &Cat1, CString &Cat2, CString &Cat3, BOOL bReport = TRUE);
	bool GetReportStringParamTranslation(long messageID, const CString &strParam, CString &strTranslation);
	//////////////////////////////////////////////////////////////////////////
	BOOL DecodeNASMessages (LPBYTE pBuffer, WORD& dwProtocolDiscriminator, WORD& dwNasMessageType);
	BOOL GetNasMessageName (WORD dwProtocolDiscriminator, WORD dwNasMessageType, CString& strNasMsgName, int nDir = 0);
	DWORD GetSignalID(const CString &strSignalName);
 	BOOL LookupSignal(DWORD nSignalID, CString &strSignalName);
 	BOOL LookupSignal(DWORD nSignalID, CString &strSignalName, CString &strSignalGroup);
	EEnumSize GetEnumerationSize(BOOL bSide=kComm); //sxwang add 07/01/2011
	EStructureAlignment GetStructureAlignment(BOOL bSide=kComm); //sxwang add 07/05/2011
	
	char * DecodeNAS(char *Inbuff);
	bool DecodeASN1MessageAsStr (DWORD sigId, BYTE * pBuffer, CString &asnAsStr);
	BOOL DecodeStrNASMessage (CString NASMessage,CString &outDecodedNAS, int nRatMode, int SecHeaderType  = 1);
	BOOL DecodeNasStreamMessage(BYTE * pBuffer, int iNasMsgLen, CString &asnAsStr, int nRatMode, int SecHeaderType);
	BOOL DecodeNASMessageAsStr(DWORD dwSigID, BYTE* pBuffer, int nLen, CString& NasAsStr);

	void InitCategoryTreeCtrl(CTreeCtrl* pTreeCtrl, int type = 1 /*0=Report, 1=Command*/, bool bAddNodeAll = true, bool bAddSubTreeComm = true, bool bAddSubTreeApp = true, bool omitDspItems = false, CMap<int, int, HTREEITEM, HTREEITEM> * pIdxItemMap = NULL);
	//void InitCatTreeCtrl(CTreeCtrl *pTreeCtrl, int type = 1, BOOL bAddAllNode = false); //sxwang add 08/16/2011
	//void InitAppCatTreeCtrl(CTreeCtrl *pTreeCtrl, int type = 1, BOOL bAddAllNode = false); //sxwang add 08/16/2011
	void ParseCat123String(const CString &Cat123, CString &Cat1, CString &Cat2, CString &Cat3); //sxwang add 08/17/2011
	BOOL GetCommandRecordReportLine(CString &reportline, const CString &cat1, const CString &cat2, const CString &cat3, BOOL bAppSide = false);//sxwang add 08/17/2011 
	BOOL GetExtendedCommand(CString &Cat1, CString &Cat2, CString &Cat3);//sxwang add 08/19/2011 
	void BuildSignalsTree(CTreeCtrl &tree, BOOL bSide = kComm, BOOL bAddAllNode = FALSE, BOOL bWithIDs = TRUE);//sxwang add 08/36/2011
	void GetMaxDiagIDs(BOOL bAppSide, int nType,/* int &nMaxModuleID,*/ int &nMaxMessageID); //sxwang add 10/13/2011
//	int BuildSignalArray(const CString& strDBFile, SignalGroupArray &aSignalArray);	//sxwang add 10/17/2011
	BOOL LoadDataBase(const CString& strCpNvmFile,const CString& strCpDiagFile, const CString& strApNvmFile, const CString& strApDiagFile);//sxwang add 03/23/2012
	BOOL LoadCpDatabase(CString strCpText);
	BOOL LoadApDatabase(CString strApText);
	BOOL LoadDatabase();
   void SetCpDatabaseFileType(EDatabaseFileType iType);
   void SetApDatabaseFileType(EDatabaseFileType iType);
   EDatabaseFileType  GetCpDatabaseFileType();// 0:TXT, 1:MDB
   EDatabaseFileType  GetApDatabaseFileType();// 0:TXT, 1:MDB
   BOOL UpdateDatabaseFile(CString srcFullPathName, int iDevice, CString strDatabaseFileName, bool bOnline=true);
   void CopyDatabaseFiles(CString strTargetDir, int iDevice);
   void SizeOfDatabaseFiles( int iDevice, CStringList& lstFilename, CList<DWORD>& lstSize, DWORD* pTotalSize=NULL);
	double GetDbVersion();
	DbArchitecture GetDbArchitecture();
   long GetCpVersion(); //sxwang 05/08/2012
   DWORD GetCpNvmVersion();
   DWORD GetApNvmVersion();
   DWORD GetCpVersionFromFile();
   long  GetCpVersionFromFile_(DWORD& dwCpVersion);
   DWORD GetApVersionFromFile();
   long  GetApVersionFromFile_(DWORD& dwApVersion);
   DWORD GetCpNvmVersionFromFile_();
   DWORD GetApNvmVersionFromFile_();
   DWORD GetApVersion();
	DWORD GetGKITargetTaskID(); //sxwang 05/15/2012
   DWORD GKINameToID(const CString name);
   void LockToRead();
   void LockToWrite();
   void Unlock();
   static void SetDBPath(CString& strDBPath);
   static CString GetDBPath();
   static BOOL IsAlive(int iDevice);
   

   // add by wenjie for converter1.h/.cpp
	void LoadDSPOpcodeMaps();
	BOOL FindDSPItem(const CString strKey, int nType, DSPMsgItem& oneItem);

	EnumValsRecord * GetReportRecord(int moduleID, int messageID, bool bAppSide = false);
	EnumValsRecord * GetCommandRecord(int moduleID, int messageID, bool bAppSide = false);
	BOOL LookupDSPCommand(WORD wOpcode, CDSPRecord &dspRec);
	BOOL LookupDSPReport(WORD wOpcode, CDSPRecord &dspRec);
	BOOL LookupGKICommand(USHORT nCommandID, CString &strCommandName);
	bool IsAsn1Message (DWORD sigId);
	bool IsAsn1Message (DWORD sigId, int &nRatMode);
	bool GetASN1MessageName (DWORD sigId, BYTE * pBuffer, CString & strName);
	bool GetASN1MsgDetails (DWORD sigId, BYTE *pBuffer, CString &strDetails);
	bool GetASN1MsgDetails (DWORD sigId, BYTE *pBuffer, CStringArray &strArr);
	int  GetASN1MsgDirection(DWORD sigId);
	BOOL IsGsmMessage(DWORD sigID);
	BOOL GetGsmMessageName(DWORD signalID, LPBYTE pBuffer, CString& signalName);
	DWORD GetHighestSignalGroup();
	//CSN.1 Messages
	bool IsCSN1Message (DWORD sigId);
	bool DecodeCSN1MessageAsStr (int nDevice,DWORD dwSigId,BYTE *pDataBuffer,int bufferLen,CString &strDecodedMsg);
	bool GetCSN1MessageName (DWORD sigId, BYTE * pBuffer, CString & strName);
	bool GetCSN1MsgDetails(int nDevice, DWORD sigId, BYTE *pBuffer, CString &strDetails);
	int  GetCSN1MsgDirection(DWORD sigId);
   //void SetNvmDbPath(CString& strCpNvm, CString& strApNvm);
	//2012.4.18
	void BuildSignalMsgTree(CTreeCtrl &tree, BOOL bSide = kComm, BOOL bAddAllNode =FALSE, BOOL bWithIDs =TRUE);
	
	BOOL FindSharkInfo(CString& strPath);
	BOOL GetDatabaseFile(CString& strCpDiagFile, CString& strCpNvmFile, CString& strApDiagFile, CString& strApNvmFile);
	//2014.5.29
	bool IsNasMessage(DWORD sigID, int& nDir);
	bool GetNasMessageType(DWORD sigId, int& nType);
	//2020.10.29
	bool IsImsMessage(DWORD msgID);
	bool IsLwipLteMessage(DWORD msgID);
	bool IsLwipWifiMessage(DWORD msgID);

	BOOL GetCat3Array(const CString &Cat1, const CString &Cat2, CStringArray & Cat3Array, CArray<USHORT, USHORT&> &moduleIDArray, CArray<USHORT, USHORT&> &commandIDArray, eTargetType clientID = UE_Comm_Side, BOOL bReport = TRUE);
	void RefreshCompilerOptions();
private:
	DWORD GetSignalID_(const CString &strSignalName);//for temp use, will be removed.
	BOOL Cat123ToID_(const CString& cat123 ,USHORT &nModuleID, USHORT &nMessageID, BOOL bAppSide = FALSE);
	BOOL APCat123ToID_(const CString& cat123, USHORT &nModuleID, USHORT &nMessageID, BOOL bAppSide = FALSE);
   int GetEnumSizeByName_LockFree(const CString &strEnumName, bool bAppSide);
	
private:
	int m_GKISignalIDSize;
	int m_GKITaskIDSize;
public:
	void LoadSingalMapEx(CString strNvmFile);
	void LoadGKICommandMap();
	void UnloadGKICommandMap();
	int GetGKICommandHeaderSize(BOOL=kComm);
	int GetGKITaskIDSize(BOOL=kComm);
	int GetGKISignalIDSize(BOOL=kComm);
	int GetGKISignalHeaderSize(BOOL=kComm);
	int GetGKILoggedSignalHeaderSize(BOOL=kComm);
	int GetEnumSizeByName(const CString &strEnumName);
	int GetEnumSizeByName(const CString &strEnumName, bool bAppSide);// add by wenjie
	WORD GetGKICommandID(const CString &strCommandName);
	WORD GetGKITaskID(const CString &strTaskName);
	BOOL IsGKITaskIDExist(WORD nTaskID);
	BOOL LookupGKITaskID(WORD nTaskID, CString &strTaskName);
    BOOL Cat123ToIDArray(const CString &Cat1, const CString &Cat2, const CString &Cat3, CArray<USHORT, USHORT&> &moduleIDArray, CArray<USHORT, USHORT&> &commandIDArray, BOOL bAppSide = FALSE, BOOL bReport = TRUE);
// 	bool Cat23ToIDArray(CCat2ToCat3Map *pCat2ToCat3Map, const CString &Cat2, const CString &Cat3, CArray<USHORT, USHORT&> &moduleIDArray, CArray<USHORT, USHORT&> &commandIDArray);
// 	bool Cat3ToIDArray(CCat3ToRecMap *pCat3ToRecMap, const CString &Cat3, CArray<USHORT, USHORT&> &moduleIDArray, CArray<USHORT, USHORT&> &commandIDArray);
	int Pack(BYTE* pOutput, int outSize, const BYTE* pInput, int inSize, const CString& strControl, eTargetType client);
	bool GetMessageInfo(UE_Message * pReport, CICATMessage *pMessage);
	
	//for SIM0/1 window division
	BYTE m_Sim1TaskFlag[MAX_NUM_OF_TASKS];
	void BuildSim1TaskFlgTbl(BYTE *FlgTbl);
	BOOL IsCommTaskId(WORD wTaskID);
	BOOL IsSim1TaskId(WORD wTaskID);
	/************************************************************************/
	/*                       GKI 命令相关的代码  -- End                     */
	/************************************************************************/

};