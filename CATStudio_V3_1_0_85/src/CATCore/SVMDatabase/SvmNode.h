// SvmNode.h: interface for the CSvmNode class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#define	MAX_VALS 50

#include "afxtempl.h"
#include "new.h"
#include "SvmDatabase.h"
#include "CommonDefs.h"

typedef enum
{
	eAlignment1Byte = 1,
	eAlignment2Byte = 2,
	eAlignment4Byte = 4,
	eAlignment8Byte = 8
}Alignment;

typedef enum
{
	eSvmNodeType_None = -1,

	eSvmNodeType_Parms = 0,
	eSvmNodeType_SvmNode,
	eSvmNodeType_ParamArray,
	eSvmNodeType_Union,
	eSvmNodeType_UnionVar,
	eSvmNodeType_Enum,
	eSvmNodeType_EnumParm,
	eSvmNodeType_Tuple,
}eSvmNodeType;

class CSvmNodeSet;
class CSignalIdSet;

class DLL_EXPORT CSvmObject: public CObject
{
	DECLARE_DYNAMIC(CSvmObject);
protected:
public:
	BOOL			m_bEnable;
	eSvmNodeType	m_eSvmNodeType;
	int				m_nStrType, m_nDbIdx;
	int				m_nSize;
	int				m_nDeviceIndex;
    bool            m_bIsTTCN;/*modify add "import ttcn log" menu CQ00110470 20180522 */

public:
	CSvmObject(CSvmObject& SvmObj);
	CSvmObject(CSvmObject* pSvmObj);
	CSvmObject(eSvmNodeType _eSvmNodeType,int nDeviceIndex,int nStrType);
	virtual ~CSvmObject();

	eSvmNodeType GetNodeType(){return m_eSvmNodeType;};
	virtual int GetStrType(){ return m_nStrType; }

	virtual BOOL BuildMultiStruct(CSvmObject* pParentNode,bool bRebuiledAnyway = false)=0;

	virtual int	UpdateData(CSvmObject* pParentNode, LPBYTE pBuf, int nBufLen, int& idx, int eDir = CSvmDb::kIN,BOOL bPrntEnable = TRUE,bool bUsePCEnumSize = false)=0;
	virtual int UpdateData(CString& fpath, LPBYTE pVal, int len, int& nActualLen, int eDir = CSvmDb::kIN)=0;
	virtual bool GetSubRuleMap(CMapStringToString*& pSubRuleMap){return false;}
	virtual bool GetStructureRuleMap(CStructureRuleMap*& pCurrentRuleMap){return false;}
	virtual void UpdateParent( int nMinAlignment, int nSize,bool bAlignOneByte ){return;};

	virtual EStructureAlignment GetStructureAlignment();//{return eAlignMinimum; /*replaces "theConverterManager->GetStructureAlignment((eTargetDBType)m_nDbIdx);" just to make it posible in the future to change it very easly*/};
	virtual EEnumSize GetEnumerationSize();//{return eEnumSizeAsNeeded; /*replaces "theConverterManager->GetEnumerationSize(m_nDbIdx)" just to make it posible in the future to change it very easly*/};\

	virtual void PrintParamData(CString& strParamData)=0;
};
/****************************************/
/*            class  CTuple             */
/*  defines a tuple in the enum object */
/****************************************/

class DLL_EXPORT  CTuple : public CSvmObject
{
	DECLARE_DYNAMIC(CTuple);
public:
	CString key;
	long val;
public:
	CTuple(int nDeviceIndex,int nStrType):CSvmObject(eSvmNodeType_Tuple,nDeviceIndex,nStrType){};
	CTuple(CSignalIdSet*,int nDeviceIndex,int nStrType);	

	virtual void PrintParamData(CString& strParamData){};
private:
	virtual int UpdateData( CString& fpath, LPBYTE pVal, int len, int& nOffset, int eDir = CSvmDb::kIN ){return 0;};
	virtual BOOL BuildMultiStruct( CSvmObject* pParentNode,bool bRebuiledAnyway = false ){return TRUE;};
	virtual int	UpdateData(CSvmObject* pParentNode, LPBYTE pBuf, int nBufLen, int& idx, int eDir = CSvmDb::kIN,BOOL bPrntEnable = TRUE,bool bUsePCEnumSize = false){return 0;};


};


/****************************************/
/*            class CEnum               */
/*        defines the structure         */ 
/*        of a specific enum            */
/****************************************/

class CEnumNodeSet;
class DLL_EXPORT  CEnum : public CSvmObject
{
	DECLARE_DYNAMIC(CEnum);
public:
	BOOL	 m_bError, m_bInit;
	CString  m_strName;//name of enum
	CString  m_strCurrentParmName;
	CPtrList m_lParams;//list of Tuples
	CTuple*  m_pCurrentTuple;
	long     m_lMaxValue;
	long     m_lMinValue;

public:
	CEnum(const CString& strName,int nDeviceIndex,int nStrType);
	int ValToIndex(int nVal);
	CEnum(CEnumNodeSet* eDB);
	CEnum(CEnum* pEn);
	virtual ~CEnum();
	
	void AddTuple(CEnumNodeSet* pSet);
	void AddTuple(const CString& strVarName,long lVarValue);
	//________________________________________________________________________________
	//returns the possible values (strings) of this enum.
	CStringList* GetVals();
	BOOL GetVals(CStringArray& strArr);
	//________________________________________________________________________________
	//returns the value of definition in this enum.
	int GetDefVal(const CString& definition);
	//________________________________________________________________________________
	//returns the specified string value for val
	CString GetStrVal(const int val);
	//________________________________________________________________________________
	//sets the m_pCurrentTuple to the one containing definition.
	BOOL SetCurrentValue(const CString& definition, BOOL bInit = false);
	//________________________________________________________________________________
	//returns the appropriate tuple.
	CTuple* GetTupleByName(const CString& definition);
	CTuple* GetTupleByVal(const int& definition);
	//________________________________________________________________________________
	//gets the current enum value(string) and inserts it to val.
	long GetCurrentValue(CString& val);
	CTuple* GetDefaultValue(){return (CTuple*)m_lParams.GetHead();}

	virtual int UpdateData( CString& fpath, LPBYTE pVal, int len, int& nOffset, int eDir = CSvmDb::kIN ){return 0;};
	virtual BOOL BuildMultiStruct( CSvmObject* pParentNode,bool bRebuiledAnyway = false ){return TRUE;};
	virtual int	UpdateData(CSvmObject* pParentNode, LPBYTE pBuf, int nBufLen, int& idx, int eDir = CSvmDb::kIN,BOOL bPrntEnable = TRUE,bool bUsePCEnumSize = false){return 0;};

	virtual void PrintParamData(CString& strParamData);
};

/****************************************/
/*            class CEnumParm           */
/*        defines an enum entry         */ 
/*        in a CSvmNode object          */
/****************************************/

class DLL_EXPORT  CEnumParm : public CSvmObject
{
	DECLARE_DYNAMIC(CEnumParm);

public:
	
	BOOL	  m_bError, m_bInit;
	CString   m_strName;
	CTuple*   m_pCurrentTuple;
	CEnum*    m_pEnumStructure;
	INT64     m_nGarbageVal;
	
public:
	CEnumParm(CEnum* pEn,const CString& name,int nDbIdx,int nStrType);
	CEnumParm(CEnumParm* pEn,int nDbIdx,int nStrType);
	virtual ~CEnumParm(){};
	BOOL SetValue(int val, BOOL bInit = false);
	BOOL SetValue(const CString& val, BOOL bInit = false);
	void SetDefaultValue();
	long GetTupleValue(CString& val);

	virtual int UpdateData( CString& fpath, LPBYTE pVal, int len, int& nOffset, int eDir = CSvmDb::kIN );
	virtual BOOL BuildMultiStruct( CSvmObject* pParentNode,bool bRebuiledAnyway = false );
	virtual int UpdateData( CSvmObject* pParentNode, LPBYTE pBuf, int nBufLen, int& idx, int eDir = CSvmDb::kIN,BOOL bPrntEnable = TRUE,bool bUsePCEnumSize = false );

	virtual void PrintParamData(CString& strParamData);
};


//________________________________________________________________________________
//defines the var types of the union.
typedef enum
{
	VT_UNKNWN		= -1,
	VT_STRUCT		=  0,
	VT_ENUM			=  1,
	VT_PRIMITIVE	=  2,
	VT_UNION		=  3,
	VT_ARR			=  4
}VarTypes;


//Chaim - No need for UnionVar we can use directly the Object type instead of this wrapper 
/*******************************************/
/*            class  CUnionVar             */
/*  defines a variable in the union object */
/*******************************************/
// class  CUnionVar: public CSvmObject
// {
// 	DECLARE_DYNAMIC(CUnionVar);
// public:
// 	
// 	CString       m_strVarName;
// 	CString       m_strTransferType;
// 	int           m_nType;
// 	int			  m_nSize;
// 	long          m_lArrayLen;
// 	unsigned char m_ucharValue;
// 	unsigned long m_ulongValue;
// public:
// 
// 	CUnionVar(int nDbIdx):CSvmObject(eSvmNodeType_UnionVar), m_nDbIdx(nDbIdx), m_strVarName(_T("")),  m_strTransferType(_T("")), m_nType(0),
// 		         m_nSize(0), m_lArrayLen(0), m_ucharValue(0), m_ulongValue(0){};
// 	CUnionVar(CUnionVar*);
// 	//________________________________________________________________________________
// 	//returns true if succeeded in setting the value of that var to val
// 	//value type will be casted according to m_strTransferType.
// 	BOOL SetValue(int val);
// 	void SetParams(VarTypes, const CString& VarName = CString(""));
// };

/*******************************************/
/*            class  CUnion                */
/*        defines a union entry            */ 
/*        in a CSvmNode object             */
/*******************************************/
class CUnionNodeSet;
class CParms;

class DLL_EXPORT  CUnion: public CSvmObject
{
	DECLARE_DYNAMIC(CUnion);
public:

	CString					m_strUnionName, m_strParentName;
	CStringArray			m_arPossibleValues;
	CList<CSvmObject*>		m_lVars;
	CSvmObject*				m_pCurVar;
	int						m_ArrayLen;
	BOOL					m_bError, m_bInit;
	BOOL					m_bOwnOrigBuf;
	Alignment				m_nMinAlignment;
	CString					m_strFieldName;
	LPBYTE					m_pOrigBuf;
	LPBYTE					m_pDataBuf;
	int						m_nDataLen;
public:
	//________________________________________________________________________________
	//Construction/Destruction
	CUnion(CString strUnionName,int nStrType,int nDeviceIndex);
	CUnion(CUnionNodeSet* uDB,int nStrType);
	CUnion(CUnion* un);
	CUnion& operator = (const CUnion& Item);
	virtual ~CUnion();

	BOOL AddParams(CUnionNodeSet* pUSet);
	//Alignment SetAlignmentMax(Alignment nMinAlignment);

	//________________________________________________________________________________
	//Sets The current value to be the var in the <nIndex> place in the vars list
	BOOL SetCurrentValue(int nIndex);

	//________________________________________________________________________________
	//Returns a list of all the variables in this union
	//CStringList* GetPossibleValuesList(){return &m_lPossibleValues;}
	//________________________________________________________________________________
	//returns the CUnionVar object that matches varName.
//	CObject* GetVar(const CString& varName);
	eSvmNodeType GetVar(const CString& varName, CSvmObject*& pCurObj);

	//________________________________________________________________________________
	//returns true if succeeds in setting the current value of the union to that of var name.
	BOOL SetCurrentValue(const CString& varName);
	const CString& GetCurItemText();
	BOOL SetUnData(LPBYTE pBuf, int nLen);
	void ResetUnData();

	virtual int UpdateData( CString& fpath, LPBYTE pVal, int len, int& nOffset, int eDir = CSvmDb::kIN );
	virtual BOOL BuildMultiStruct( CSvmObject* pParentNode,bool bRebuiledAnyway = false );
	virtual int UpdateData( CSvmObject* pParentNode, LPBYTE pBuf, int nBufLen, int& idx, int eDir = CSvmDb::kIN,BOOL bPrntEnable = TRUE,bool bUsePCEnumSize = false );
	void UpdateParent( int nMinAlignment, int nSize,bool bAlignOneByte );
	
	virtual void PrintParamData(CString& strParamData);
private:
	//void UpdateUnionVarsAlignment(Alignment nMinAlignment);	
	void ReleaseUnionVars();
};

/*******************************************/
/*          class CParamArray              */
/*        defines an array of params       */ 
/*        in a CSvmNode object             */
/*******************************************/
class CParms;
class CSvmNode;

class DLL_EXPORT  CParamArray: public CSvmObject
{
	DECLARE_DYNAMIC(CParamArray);
public:

	enum EnArrayLimits
	{
		kMinLimitSize	=	1,
		kMaxLimitSize	=	100000
	};

	CString   m_strArrayName;
	CString   m_strPureArrayName;
	CString   m_strType;
	CStringList m_ValsList;
	CArray<CSvmObject*>  m_Array;//array of CParms or CSvmNodes ,CEnums etc.
	int       m_nType;//type of objects in m_Array.
	CParamArray * m_pParentArray;
	int		  m_nIndexInParent;
	int		  m_nActualSize;
	CString   m_Description;
	
public:
	CParamArray(CSvmNodeSet* set , CParamArray *pParentArr = NULL, int nIdxInParent = -1);
	CParamArray(CUnionNodeSet* set , CParamArray *pParentArr =NULL, int nIdxInParent =-1);
	CParamArray(CParamArray* pArr);
	//dedicated constructor to build CSvmNodes array.
	CParamArray(int nSize,CSvmObject* pNode,const CString& arrName);
	virtual ~CParamArray();
	//returns the index of the element inserted
	int AddTailParam(CSvmObject* newParam);
	BOOL operator == (const CParamArray& ParmArr);
	void BuildArrayTitle(/*CString &strTitle*/);

	virtual int UpdateData( CString& fpath, LPBYTE pVal, int len, int& nOffset, int eDir = CSvmDb::kIN );
	virtual BOOL BuildMultiStruct( CSvmObject* pParentNode,bool bRebuiledAnyway = false );
	virtual int UpdateData( CSvmObject* pParentNode, LPBYTE pBuf, int nBufLen, int& idx, int eDir = CSvmDb::kIN,BOOL bPrntEnable = TRUE,bool bUsePCEnumSize = false );

	virtual void PrintParamData(CString& strParamData);
};

class DLL_EXPORT CSvmNode : public CSvmObject  
{
	DECLARE_DYNAMIC(CSvmNode);
public:
	BOOL AddStructTailParam(CSvmNode* pNode);
	CSvmNode(int nDeviceIndex,int nStrType);
	CSvmNode(CSvmNode* pItem);
	CSvmNode(CSvmNodeSet* svmNodeSet);
	CSvmNode(CUnionNodeSet* unNodeSet);
	CSvmNode(CString& ItemName,int nDeviceIndex,int nStrType, const CString& ParentName = CString(""), BOOL bShell = 0);
	CSvmNode& operator = (const CSvmNode& Item);
	BOOL operator == (const CSvmNode& Item );

	//void PASCAL operator delete(void* ptr);
	//void PASCAL operator delete(void* ptr, void*);
	//void PASCAL operator delete(void *ptr, LPCSTR, int);

	//void AddRef(CSvmNodeSet*);
	//int  Release(){return m_nReference--;};
	BOOL IsEmpty(){ return m_Parms.IsEmpty();};
	virtual ~CSvmNode();
	BOOL AddTailParam( CObject* newElement );
	BOOL IsMember(CObject* pObj);
	BOOL IsStructureAttach(CSvmNodeSet*);

	virtual int UpdateData( CString& fpath, LPBYTE pVal, int len, int& nOffset, int eDir = CSvmDb::kIN );
	virtual BOOL BuildMultiStruct( CSvmObject* pParentNode,bool bRebuiledAnyway = false );
	virtual int UpdateData( CSvmObject* pParentNode, LPBYTE pBuf, int nBufLen, int& idx, int eDir = CSvmDb::kIN,BOOL bPrntEnable = TRUE,bool bUsePCEnumSize = false );
	virtual bool GetSubRuleMap(CMapStringToString*& pSubRuleMap);
	virtual bool GetStructureRuleMap(CStructureRuleMap*& pCurrentRuleMap);
	void UpdateParent( int nMinAlignment, int nSize,bool bAlignOneByte );

	virtual void PrintParamData(CString& strParamData);
public:

	BOOL					m_bError, m_bInit, m_bShell;
	long					m_Index;
	int						m_nParmsCount;
	int						m_nArrayLen;//length of this node's array inside another node.
	CString					m_ItemName;
	CString					m_ParentName;
	CString					m_TransferType;
	CString					m_Description;
	Alignment				m_nMinAlignment;

	HTREEITEM				m_hHandle;
	CList<CSvmObject*>		m_Parms;
	CMapStringToString		m_SubRuleMap;
	CStructureRuleMap		*m_pCurrentRuleMap;

protected:
	EStructureAlignment		m_nStructAlignment;
};

/*
class CSvmNodeParm : public CObject  
{
	DECLARE_DYNAMIC(CSvmNodeParm);
	CSvmNodeParm();
	CSvmNodeParm(CSvmNode* pStruct,CString strName);
	void SetParams(CObList& paramsList);

public:
	CString m_strParmName;
	CSvmNode* m_pStructure;
	CObList   m_Parms;

};
*/
class DLL_EXPORT CParms : public CSvmObject
{
	DECLARE_DYNAMIC(CParms);
public:
	//CParms();
	CParms(CParms* pParams,int nStrType,int nDeviceIndex);
	CParms(CSvmNodeSet* svmNodeSet);
	CParms(CUnionNodeSet* svmNodeSet,int nStrType);
	CParms(CString& ParamName, CString& TranferType, CString& ParamType, CString& _vals,int nDbIdx,int nStrType,int nDeviceIndex);
	BOOL operator == (const CParms& Parm);

	virtual ~CParms();

	virtual int UpdateData( CString& fpath, LPBYTE pVal, int len, int& nOffset, int eDir = CSvmDb::kIN );
	virtual BOOL BuildMultiStruct( CSvmObject* pParentNode,bool bRebuiledAnyway = false );
	virtual int UpdateData( CSvmObject* pParentNode, LPBYTE pBuf, int nBufLen, int& idx, int eDir = CSvmDb::kIN,BOOL bPrntEnable = TRUE,bool bUsePCEnumSize = false );
	
	virtual void PrintParamData(CString& strParamData);

	BOOL			m_bInit;
	CString			m_ParmName;
	CString			m_ParmType;
	long			m_ParmArray;
	CString			m_TransferType;
	CString			m_Description;
	CString			m_strVal;
	CUIntArray		ValID;
	CStringArray	vals;
	CStringArray	NewVals;
	bool			m_bIsArray;
	CString			m_strPureParmName;
	int				m_nParamSize;
	bool			m_bIsSigned;
	CString			m_strFormat;
protected:
	void Init();
};

