#pragma once
#include "afxwin.h"
#include "../../CATCore/Converter/ConverterManager.h"
#include <queue>
#include "Imc.h"
using namespace std;

#define	BLOCK_SIZE 100
#define WM_TABLE_LOADED		WM_USER + 1

#define		ALIGN_2(a)			((a)%2)?(2-((a)%2)):0
#define		ALIGN_4(a)			((a)%4)?(4-((a)%4)):0
#define		ALIGN_8(a)			((a)%8)?(8-((a)%8)):0
#define     ALIGN_AT(a,l)		((a)%(l))?((l)-((a)%(l))):0

#define		SWAP_SHORT(x)		((x)>>8)|((x)<<8)
#define		SWAP_LONG(x)		(((x)>>24)|(((x)<<8)&0x00FF0000)|(((x)>>8)&0x0000FF00)|((x)<<24))
#define		SWAP_LONG64(x)		(((x)>>56)|(((x)<<40)&0x00FF000000000000)|(((x)<<24)&0x0000FF0000000000)|(((x)<<8)&0x000000FF00000000)|\
								(((x)>>8)&0x00000000FF000000)|(((x)>>24)&0x0000000000FF0000)|(((x)>>40)&0x000000000000FF00)|((x)<<56))
#define		SWAP(a)				(sizeof(a)!=1)?((sizeof(a)==2)?SWAP_SHORT(a):(sizeof(a)==4)?SWAP_LONG(a):SWAP_LONG64(a)):(a)



typedef enum
{
	VT_CHAR,
	VT_UCHAR,
	VT_SHORT,
	VT_USHORT,
	VT_LONG,
	VT_ULONG,
	VT_FLOAT,
	VT_LONG64,
	VT_ULONG64
}vartypes;

typedef enum
{
	ET_UCHAR,
	ET_SCHAR,
	ET_USHORT,
	ET_SSHORT,
	ET_ULONG,
	ET_LONG,
	ET_ULONG64,
	ET_LONG64,
	ET_FLOAT,
	ET_ERROR
}enumtypes;

typedef enum
{
	PRESENT,
	ARRAY,
	VAR_ARRAY,
	STRING,
	UNION
} EAssociationVars;

class CSvm;
class CEnum;
class CUnion;
class CSvmNode;
class CSvmObject;
class CSvmNodeSet;
class CEnumNodeSet;
class CUnionNodeSet;
class CUnionIdSet;
//class CSignalIdSet;

class CExcept
{
	CString m_ErrMsg;
public:

	CExcept(LPCTSTR lpszFormat, ...)
	{
		ASSERT(AfxIsValidString(lpszFormat));

		va_list argList;
		va_start(argList, lpszFormat);
		m_ErrMsg.FormatV(lpszFormat, argList);
		va_end(argList);
	}
	~CExcept(){};

	const TCHAR *ShowReason() const { return LPCTSTR(m_ErrMsg); }
};


typedef CMapStringToOb	CStructureRuleMap;

//typedef CMap<CString, LPCTSTR, CObject*, CObject*> CMyMapStrToObj;

#ifdef _CATCORE_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT 
#endif

class DLL_EXPORT CSvmDb  : public CWinThread , public ImcListener
{
//	friend class CUnionVar;

public:
	CSvmDb(int nDevice, BOOL bCacheTablesFlag = false);

	enum ERadix
	{
		kDec	= 0,
		kHexDec	= 1
	};

	enum EFileFormat
	{
		kTxt	= 0,
		kXls	= 1
	};

	enum EDbUpdateData
	{
		kIN		 = 0,
		kOUT     = 1,
		kINVC	 = 2,			
		kOUTVC	 = 3			
	};

	enum EStructIndices
	{
		kNone	 = -1,
		kComNvm	 =  0,
		kComGki	 =  1,
		kAppNvm	 =	2,
		kAppGki	 =  3,
		kAsn1	 =  4,
		kStrAll	 =  5
	};

	enum EDbTableIndices
	{
		kDbNone		= -1,
		kDbComm		=  0,
		kDbApp		=  1,
		kDbAsn1		=  2,
		kDbNvmAll	=  2,
		kDbAll		=  3
	};

	enum EDbEvents
	{

		KILL_EVENT		= 0,
		START_EVENT		= 1,
		MAX_TH_EVENTS	= 2
	};


private:
//	static CSvmDb*	m_pThis;

	HANDLE			m_hInitEvent,
					m_hAbortEvent,
					m_hStopEvent,
					m_hExitEvent,
					m_hDbEvents[MAX_TH_EVENTS];
	int				m_nLoadType, 
					m_nStrType,
					m_nCurDbIdx,
					m_nDelayedType;
	BOOL			m_bSuccess,
					m_bCurrUpdate,
					m_bNewTask,
					m_bLoadDefault,
					m_bCurRulMapFound,
					m_bReload;
	CString			m_ErrorMsg,
					m_CurrStructName,
					m_cDatabaseName;

	CSvmNodeSet*	m_pDelayedTask;

	CMapStringToString				m_SvmUnionsId[kDbNvmAll];
	CMapStringToOb					m_SvmEnums[kDbAll],
									m_SvmUnions[kDbAll],
									m_StrMapArray[kStrAll];
	CStringList						m_StrMapNameList[kStrAll];
	CMapStringToOb					m_StrRuleMap;
	CStructureRuleMap				*m_pCurrentRuleMap;

	CString					m_strCpNvmFile;
	CString					m_strApNvmFile;

	BOOL m_bCacheTablesFlag;

	int				m_nDbVer; // 0: old, 1: new version?
	int				m_nCpFileType;
	int				m_nApFileType;
	
	int				m_nDeviceIndex;
    
	CImcReceiver	m_ImcReceiver;

	CCriticalSection m_Cs;	

	static SmartShell<CSvmDb> m_SmartShell;
	friend class SmartShell<CSvmDb>;

protected:
	void	ShowProgress(int nType, CWnd* pWnd, BOOL bWait);
	virtual ~CSvmDb();
private:
	void LoadDataSets(int nStrType);
	void CacheTables(int nStrType, const CString& = _T(""));
	void CacheSvmEnums(int nStrType);
	void CacheSvmUnions(int nStrType);
	void CacheSvmUnionsId(int nStrType);
	void CacheAssociations();
	void	StopTask();
	void	SvmNotify();
	BOOL IsDigit(CString& strNum);

	CWinThread* GetActiveThread(int&);
	void		AddThread(CWinThread*&, int);
	CSvmNode*   FindSvmNodeInNode(const CString &nodeName, const CList<CSvmObject*>* pList) const ; 
	CUnion*		FindUnionNodeInNode(const CObList* pList, const CString &nodeName, const CString &parentNodeName) const;
//	void		UpdateParent(const CObject*& pObj, int nMinAlignment, int nSize,bool bAlignOntByte = false) const;
public:
	virtual int Run();
	virtual BOOL InitInstance();
  UINT ThreadFunc();
public:
	BOOL IsInited();
	BOOL IsAborted();
	BOOL IsFinished();
	BOOL IsProcessed();

	static CCriticalSection		m_InstanceCreationLock;
	static BOOL IsInstanceAlive(int nDeviceID);
	static void DeleteInstance(int nDevice);
	static void InitSmartShell(int nSize);
	static void DestructSmartShell();

	static	CSvmDb* Instance(int nDevice,int nStrType = kNone, BOOL bReload = false, BOOL bCacheTablesFlag= false);
	static  void StructListRelease(CList<CSvmObject*>* pList);

//	static	void	DestroyThis();
	static  int     GetPrimitiveType(const CString& type, const CString& = CString());
	static  BOOL    IsPrimitive(const CString &type);

	int				GetDbIdx(int nStrType)const { return (nStrType==kComNvm||nStrType==kComGki)? kDbComm:(nStrType==kAppNvm||nStrType==kAppGki)?kDbApp:kDbAsn1;}
	BOOL            DbLoader(int nIdx, CWnd* pWnd = NULL, BOOL bWait = true, BOOL bReload = false);
	BOOL			IsTableLoaded(int nIdx);
	
	BOOL			GetUnionVars(int nDbIdx, LPCTSTR lpTitleName, CStringList &list);
	BOOL			GetStructureNames(int nIdx, CStringList &list);
	
	CSvmNode* FindSvmNodeByName(const CString &ndName, const CList<CSvmObject*>* = NULL);
	CSvmNode*   FindSvmNodeInNode(const CString &nodeName, const CObList* pList) const ; 
	CObject*  FindObjectByName(int nType, const CString &strName, CList<CSvmObject*> &list, BOOL bWholName = false);

   //  Add two function for decoding CSN1 message.
	int  GetNvmContent(int nNvm, LPCTSTR fpath, LPBYTE value, int arrlen, int* pOffset = NULL);
	int  SetNvmContent(int nNvm, LPCTSTR fpath, LPBYTE value, int arrlen, int* pOffset = NULL);
   void SetNvmDbPath(CString strCpNvmDbPath, CString strApNvmDbPath, int nCpType, int nApType, int nUnionVer);

	CMapStringToOb*	GetStrMapByIdx(int nIdx){ return &m_StrMapArray[nIdx];}
	CMapStringToOb*	GetCurrStrMap(){ return &m_StrMapArray[m_nStrType];}
	CMapStringToOb*	GetEnumsMap(int nDbType){ return &m_SvmEnums[nDbType];}
	CMapStringToOb*	GetUnionsMap(int nDbType){ return &m_SvmUnions[nDbType];}
	CMapStringToString* GetUnionIDsMap(int nDbType){return &m_SvmUnionsId[nDbType];}
	CStringList* GetStrMapName(int nIdx){ return &m_StrMapNameList[nIdx];}

	BOOL			GetSide(){ return (m_nCurDbIdx==kDbApp)?true:false;}
	CUnion*	  FindUnionByName(const CString&);
	CEnum*    FindEnumByName(const CString&);
	CObject*  FindObject( int& VarType, CObject *pParentObj, CList<CSvmObject*>& Node, const CString& ItemName, const CString& ParentName = CString("") );
	CSvmNode* FindStructure(int nType, const CString &nodeName, BOOL bCopy = TRUE);
	CSvmNode* FindGKIStructureType(int nType,const CString &nodeName, CString& newnodeName);

	int  FindEnumSize(CEnum* pEn);
	void AbortTask();

	void ClearCachedUnions(int);
	void ClearCachedEnums(int);
	void ClearCachedUnionsId();
	void ClearCachedTables(int);
	void ClearAssociationTable();
	void ClearAllCashedTables();
	void CopyObjList(CList<CSvmObject*>* pSrcNode,CList<CSvmObject*>* pDstNode);

	int  FindSignalType(const CString & name, CObject*&) const;
	int  FindSignalType(const int nIdx, const CString &nodeName, CObject*& Obj) const;
	BOOL InitializeDb();

	int  UpdateStructure(int nIdx, const CString& lpStrName, CList<CSvmObject*> &Branch, LPBYTE pBuf, int& Len, BOOL eDir, BOOL bDef = 0,bool bUsePCEnumSize = false,bool bShowException = true);
//	int  UpdateData(CObList* pList, LPBYTE pBuf, int& idx, int iLen, int = kIN);
//	int  UpdateData(CObList* pNode, CString& fpath, LPBYTE pVal, int len, int = kIN);
//   BOOL BuildMultiStruct(int nIdx, CObList& Node, CObject*& pParent);
	int	 PrintStructData(int nIdx, LPCTSTR lpSigName, LPBYTE pBuf, int nBufLen, LPCTSTR pFilePath, int nFileFormat = kTxt, int nRadix = kDec, int nArrayIdx = -1);
	

	void PrintData(CList<CSvmObject*>* pNode, const CObject* pParent, CString& SigPath, CStdioFile* OutFile, int nFormat, int nRadix);

	bool LookupRulMap( CString& strKey,CStructureRuleMap *&pRuleMap );
	bool IsCurrUpdate()  {return m_bCurrUpdate  == TRUE;};
	bool IsLoadDefault() {return m_bLoadDefault == TRUE;};
	int GetStrType() {return m_nStrType;};

	virtual LRESULT OnMessageReceived( CMessage* pMessage );
	int GetCurrentUnionsVer(DbArchitecture dbArch);
};

inline BOOL CSvmDb::IsInited(){ return   (::WaitForSingleObject(m_hInitEvent, 0)  == WAIT_OBJECT_0);}
inline BOOL CSvmDb::IsProcessed(){ return (::WaitForSingleObject(m_hDbEvents[START_EVENT], 0) == WAIT_OBJECT_0);}
inline BOOL CSvmDb::IsAborted(){ return (::WaitForSingleObject(m_hAbortEvent, 0) == WAIT_OBJECT_0);}
inline BOOL CSvmDb::IsFinished(){ return (::WaitForSingleObject(m_hStopEvent, 0)  == WAIT_OBJECT_0);}
// inline void CSvmDb::endian_swap(unsigned short& x){	x = (x>>8)|(x<<8);}
// inline void CSvmDb::endian_swap(unsigned long& x){ x = (x>>24)|((x<<8)&0x00FF0000)|((x>>8)&0x0000FF00)|(x<<24);}
// inline void CSvmDb::endian_swap(unsigned __int64& x){ x = (x>>56)|((x<<40)&0x00FF000000000000)|((x<<24)&0x0000FF0000000000)|((x<<8)  & 0x000000FF00000000)|
//													((x>>8)&0x00000000FF000000)|((x>>24)&0x0000000000FF0000)|((x>>40)&0x000000000000FF00)|(x<<56);}
