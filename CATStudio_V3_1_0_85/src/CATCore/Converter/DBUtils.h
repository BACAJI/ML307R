#pragma once
#include <afxtempl.h>
#include <afxmt.h>
#include "./DiagCommDef.h"
#include <map>
#include "mrvlCommon/singletondestroyer.h"
#include "..\BasicComponents\StringArrayEx.h"
#include "mrvlCommon/SmartShell.h"
#include "MrvlCommon/CommonDefs.h"
#include "Cat1ToCat2Map.h"
#include "Cat2ToCat3Map.h"
#include "Cat3ToRecMap.h"
#include "CommandAndMessageStructures.h"
using namespace std;

#define HI_3BYTES(dw)	( ((DWORD)(dw) >> 8) )

class __declspec(dllexport) CDBUtils
{
public:
	CDBUtils(int nDevice = 0);
	~CDBUtils(void);

   enum EErrorCode
   {
      eNoError = 0,
      eInvalidArgument  = 1,
      eFileNotExists    = 2,
      eOpenFileFailed   = 3,
      eTableNotExists   = 4,
      eUnknownError     = 5
   };

   static const CString ErrorCodeString[/*eUnknownError+1*/];

   struct TranslateRules
   {
       CString  m_strSeparator;
       CString  m_strDelimiter;
       map<int, CString> m_mapRuleIDToFormat;
   };

private:
	int m_iFileType;
	map<long, TranslateRules *> m_mapTranslateRules; // added for IMS debug info by Dian
	map<CString, CString> m_mapUnionIdfiers;
	map<DWORD, CString> m_mapSignalTable;
	map<CString, DWORD> m_mapSignalTableRev;
	map<long, CString> m_mapSignalGroup;
	map<DWORD, DWORD> m_mapASN1Signal;
	multimap<long,EnumValsRecord*> m_mapUeCp;
	multimap<long,EnumValsRecord*> m_mapUeAp;		//Richard added. 2011-06-14
	multimap<CString, EnumValsRecord*> m_mapCpCAT123ToRecord;	//add by wenjie
	multimap<CString, EnumValsRecord*> m_mapApCAT123ToRecord;	//add by wenjie
	CCat1ToCat2Map m_mapCpCommandCat1ToCat2; // A signal info tree for the "command" signals of the Comm client that's hierarchically leveled root > CAT1 > CAT2 > CAT3 > CAT1-2-3 signal info structure
	CCat1ToCat2Map m_mapApCommandCat1ToCat2; // A signal info tree for the "command" signals of the App client that's hierarchically leveled root > CAT1 > CAT2 > CAT3 > CAT1-2-3 signal info structure
	CCat1ToCat2Map m_mapCpReportCat1ToCat2; // A signal info tree for the "report" signals of the Comm client that's hierarchically leveled root > CAT1 > CAT2 > CAT3 > CAT1-2-3 signal info structure
	CCat1ToCat2Map m_mapApReportCat1ToCat2; // A signal info tree for the "report" signals of the App client that's hierarchically leveled root > CAT1 > CAT2 > CAT3 > CAT1-2-3 signal info structure
// #if !MICL_BUILD
// 	multimap<long,CString>	m_mapGKITaskIdMap;		//sxwang added 2011-09-21
// #endif
	multimap<long,CString>	m_mapGKITaskIdMap;		//sxwang added 2011-09-21
	CString m_strCpNvmDBFile;
	map<CString, int> m_EnumSizeMap;
	multimap<CString, EnumValPair> m_EnumTypesMap;
	//int m_GKITaskIDSize;
	int m_GKISignalIDSize;
	int m_nMaxDiagMessageID;
	DWORD m_nGKITargetTaskID;
	long m_lCpVersion;
	long m_lApVersion;
    DWORD m_dwCpNvmVersion;
    DWORD m_dwApNvmVersion;
	const int m_nDevice;
	CString m_strOSType;
	CString m_strDBVersion;
	CString m_strPPCVersion;
	CString m_strPPLVersion;
	CString m_strPPManCMDVersion;
	CString m_strAppOSType;
	static SmartShell<CDBUtils> m_SmartShell;
	friend class SmartShell<CDBUtils>;
	static CCriticalSection		m_InstanceCreationLock;
   CCriticalSection m_csNvmPathLock;
   EDatabaseFileType   m_iCpFileType;
   EDatabaseFileType   m_iApFileType;
   //for getenumsize
   int m_nMaxVal;
   int m_nMaxNegVal;
   BOOL m_nContainNegativeNum;

   int m_nSizeofEnum;
private:
	void UpdateSizeofEnum(long nVal);
	void ResetEnumSizeVariable();
protected:
	BOOL LoadASN1Setting(map<CString, DWORD> &mapTmp);
	DWORD ReadApVersion(CString& strApText);
	DWORD ReadCpVersion(CString& strCpText);
   EErrorCode ReadCpVersion(CString& strCpText, DWORD& dwCpVersion);
   EErrorCode ReadApVersion(CString& strApText, DWORD& dwApVersion);
	BOOL BuildOldCpFormatDB(const CString &strTextDBPath, CString &strError);
	
public:
	BOOL ImportDBFromText(const CString &strCpPath, const CString& strApPath, CString &strError);
	BOOL BuildApDBFromText(const CString& strAPPath, CString& strError);
	BOOL BuildCpDBFromText(const CString& strCpPath, CString &strError);
	BOOL IsOldFormatTxt(const CString& strCpText);
	
	//HTREEITEM finditem(CTreeCtrl *pTreeCtrl, HTREEITEM  item, CString strtext);

public:
	static CDBUtils* Instance(int nDevice/* = 0*/);
	static void DeleteInstance(int nDevice);
	BOOL LoadDataBase(const CString& strCpNvmFile,const CString& strCpDiagFile, const CString& strApNvmFile, const CString& strApDiagFile);
	void SetNvmMDBPath(const CString& strNvmFile);
    void BuildEnumsMaps(CString strDBFile);
	void LoadParameters(CString strDBFile);
	void LoadAppParameters(CString strDBFile);
	void LoadParameters(CString& strType, CString& strValue);//new api.
	void LoadAppParameters(CString& strType, CString& strValue);//new api.
	int GetEnumSizeByName(const CString& strEnumName , BOOL bAppSide);//new api.
	void GetMaxDiagIDs(BOOL bAppSide, int nType,/* int &nMaxModuleID,*/ int &nMaxMessageID);
	DWORD GKINameToID(const CString name);	
// 	int GetGKITaskIDSize(BOOL bSide);
// 	int GetGKISignalIDSize(BOOL bSide);
	void ParseCat123String(const CString &Cat123, CString &Cat1, CString &Cat2, CString &Cat3);	
	EnumValsRecord* GetRecord(USHORT moduleid, USHORT messageid, BOOL bReport = TRUE);
	EnumValsRecord* APGetRecord(USHORT moduleid, USHORT messageid, BOOL bReport = TRUE);
	long GetCpVersion();
	long GetApVersion();
	CString GetDbVersion();
   DWORD GetCpNvmVersion();
   DWORD GetApNvmVersion();
   DWORD GetCpVersionFromFile(CString strCpDiagFile);
   EErrorCode  GetCpVersionFromFile(CString strCpDiagFile, DWORD& dwCpVersion);
   EErrorCode  GetApVersionFromFile(CString strCpDiagFile, DWORD& dwCpVersion);
    DWORD GetApVersionFromFile(CString strCpDiagFile);
    DWORD GetCpNvmVersionFromFile(CString strCpNvmFile);
    DWORD GetApNvmVersionFromFile(CString strApNvmFile);
	DWORD GetGKITargetTaskID();
   void  SetCpDatabaseFileType(EDatabaseFileType iType);
   void  SetApDatabaseFileType(EDatabaseFileType iType);
   EDatabaseFileType GetCpDatabaseFileType();
   EDatabaseFileType GetApDatabaseFileType();

	//////////////////////////////////////////////////////////////////////////
	BOOL Cat123ToID(const CString& cat123, USHORT &nModuleID, USHORT &nMessageID, BOOL bReport = FALSE);				//CP: cat123->msgID+ModuleID
	BOOL Cat123ToID(const CString& cat123 ,USHORT *nModuleID, USHORT *nMessageID,int &nLength, BOOL bReport = FALSE);
	BOOL Cat123ToID(const CString& cat1, const CString& cat2, const CString& cat3, USHORT &nModuleID, USHORT &nMessageID, BOOL bReport = FALSE);				//CP: cat123->msgID+ModuleID
	BOOL Cat123ToIDEx(const CString& cat123 ,USHORT &nModuleID, USHORT &nMessageID, BOOL bReport = TRUE);
	BOOL GetReportEnumStrings(USHORT moduleID, USHORT messageID, CString &Cat1, CString &Cat2, CString &Cat3, BOOL bReport = TRUE);		//CP: msgID+ModuleID->cat123
	BOOL GetReportEnumStrings(USHORT moduleID, USHORT messageID, CString &Cat1, CString &Cat2, CString &Cat3, BOOL *bIsExtMessage /*=NULL*/);
	BOOL APCat123ToID(const CString& cat123, USHORT &nModuleID, USHORT &nMessageID, BOOL bReport = FALSE);				//AP: cat123->msgID+ModuleID
	BOOL APCat123ToID(const CString& cat123 ,USHORT *nModuleID, USHORT *nMessageID,int &nLength, BOOL bReport = FALSE);//09282012 Add for read message id sequence, by peter.
	BOOL APCat123ToID(const CString& cat1, const CString& cat2, const CString& cat3, USHORT &nModuleID, USHORT &nMessageID, BOOL bReport = FALSE);				//AP: cat123->msgID+ModuleID
	BOOL APCat123ToIDEx(const CString& cat123, USHORT &nModuleID, USHORT &nMessageID, BOOL bReport = TRUE);
	BOOL APGetReportEnumStrings(USHORT moduleID, USHORT messageID, CString &Cat1, CString &Cat2, CString &Cat3, BOOL bReport = TRUE);		//AP: msgID+ModuleID->cat123
	
//#if MICL_BUILD
	BOOL ReportLineToEnumString(const CString reportLine , CString& strCat1, CString& strCat2, CString& strCat3, BOOL bReport = TRUE);

	TranslateRules *GetReportTranslateRules(long messageID);


	bool WereDeviceSignalsLoaded();

	void InitCategoryTreeCtrl(CTreeCtrl* pTreeCtrl, int type = 1 /*0=Report, 1=Command*/, bool bAddNodeAll = true, bool bAddSubTreeComm = true, bool bAddSubTreeApp = true, bool omitDspItems = false, CMap<int, int, HTREEITEM, HTREEITEM> * pIdxItemMap = NULL);
	static void InitClientSignalCategoryTreeCtrl(CTreeCtrl* pTreeCtrl, HTREEITEM hRoot, CCat1ToCat2Map* mapCat1ToCat2, eTargetType client = UE_Comm_Side, bool omitDspItems = false, CMap<int, int, HTREEITEM, HTREEITEM> * pIdxItemMap = NULL);
	static inline DWORD GetMessageIndexFromTreeItemData(DWORD itemData)	{ return (DWORD)(0x0000FFFF & itemData); }; // The message# is stored in the LSW of the item data, which is made up (LSB-to-HSB) of message# (word), don't-care (byte), and client# (byte); for further details see the built-in documentation in method CDBUtils::InitClientSignalCategoryTreeCtrl.
	static inline eTargetType GetClientFromTreeItemData(DWORD itemData)	{ return (eTargetType)(0x000000FF & (itemData >> 24)); }; // The client is stored in the MSB of the item data, which is made up (LSB-to-HSB) of message# (word), don't-care (byte), and client# (byte); for further details see the built-in documentation in method CDBUtils::InitClientSignalCategoryTreeCtrl.

	BOOL GetCommandRecordReportLine(CString &reportline, const CString &cat1, const CString &cat2, const CString &cat3);
	BOOL GetAppCommandRecordReportLine(CString &reportline, const CString &cat1, const CString &cat2, const CString &cat3);
	BOOL GetExtendedCommand(CString& cat1, CString& cat2, CString& cat3);	
	void LoadSignalMap(const CString strFile, CMap<DWORD, DWORD, CStringArrayEx, CStringArrayEx&>& mapSignal);
	void LoadSignalMapEx(CMap<DWORD, DWORD, CStringArrayEx, CStringArrayEx&>& mapSignal);
	WORD GetGKITaskID(const CString &strTaskName);
	BOOL IsGKITaskIDExist(WORD nTaskID);	
	BOOL LookupGKITaskID(WORD nTaskID, CString &strTaskName);
	WORD GetMaxGKITaskID(void);
// #else
// #endif
	BOOL GetEnumFromTable(const CString &EnumType, INT64 key, CString &strToken, BOOL bAppSide);
	bool GetEnumValueFromTable( const CString & EnumType, INT64& key,const CString & strToken, bool bAppSide );
	void LoadSignalTable(CMap<CString, LPCTSTR, DWORD, DWORD>& map);

	void SetDatabaseFileType(EDatabaseFileType iType);
	EDatabaseFileType  GetDatabaseFileType();// 0:TXT, 1:MDB
   
	BOOL GetCat3Array(const CString &Cat1, const CString &Cat2, CStringArray & Cat3Array, CArray<USHORT, USHORT&> &moduleIDArray, CArray<USHORT, USHORT&> &commandIDArray, BOOL bReport =TRUE);
	EnumValsRecord * GetCommandRecord( const CString &cat1, const CString &cat2, const CString &cat3,eTargetType clientID = UE_Comm_Side );
	eOSType GetOSType(eTargetType targetType =  UE_App_Side) const;
	BOOL Cat123ToIDArray(const CString &Cat1, const CString &Cat2, const CString &Cat3, CArray<USHORT, USHORT&> &moduleIDArray, CArray<USHORT, USHORT&> &commandIDArray, BOOL bAppSide/*=FALSE*/, BOOL bReport /*=TRUE*/);
	bool Cat23ToIDArray(CCat2ToCat3Map *pCat2ToCat3Map, const CString &Cat2, const CString &Cat3, CArray<USHORT, USHORT&> &moduleIDArray, CArray<USHORT, USHORT&> &commandIDArray);
	bool Cat3ToIDArray(CCat3ToRecMap *pCat3ToRecMap, const CString &Cat3, CArray<USHORT, USHORT&> &moduleIDArray, CArray<USHORT, USHORT&> &commandIDArray);
};