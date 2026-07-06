#if !defined(AFX_SCRIPTPARAMSDB_H__AEAF3EE8_ABEB_4088_8D72_C9BD7847F3BE__INCLUDED_)
#define AFX_SCRIPTPARAMSDB_H__AEAF3EE8_ABEB_4088_8D72_C9BD7847F3BE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ScriptParamsDB.h : header file
#include "ParameterMap.h"
#include "ParameterProperties.h"
#include <afxtempl.h>
#include <afxmt.h>
#include "../Converter/db/DisconnectedADORecordset.h"
#include "../Converter/db/EventForMultiLock.h"
#include "GeneralMacroDefine.h"

typedef enum {
	noParamType		= -1,
	paramTypeString	= 0,
	paramTypeInt,
	paramTypeUint,
	paramTypeDouble,
	paramTypeBOOLean,
	paramTypeEnum,
	paramTypeFile,
} ParamType;

/////////////////////////////////////////////////////////////////////////////
// CScriptParamsDB DAO recordset

class CATCORE_DLL_STATIC_EXPORT CScriptParamsDB : public CDisconnectedADORecordset
{
public:
	CScriptParamsDB();
	virtual ~CScriptParamsDB();
	static CString m_ParamTypeStrings[];

	long	m_nScriptID;
	CString m_ParamName;
	CString m_DefaultValue;
	CString m_LastValue;
	long	m_ParamType;
	CString m_MaxValue;
	CString m_MinValue;
	CString m_StringValues;
	CString m_Description;
	int 	m_ParamIndex;

	BOOL IsValidParameter(const CString & strValue);

	static CSyncObject* GetLockEvent() { return &m_cLockEvent;}
	
	static BOOL GetStringValues(long nScriptID, const CString &strParamName, CString &strValArray);
	static BOOL GetEnumNames(long nScriptID, const CString &strParamName, CString &strValArray);
	static BOOL GetEnumValue(long nScriptID, const CString& strParamName,const CString& strEnumVal,CString& strIntVal);
	static BOOL RemoveScriptParameters(long nScriptID);
	static BOOL GetParameterDescription(long nScriptID, const CString &strName, CString &strDescription);
	static ParamType GetParameterType(long nScriptID, const CString &strName);
	static BOOL CheckValidParameter(long scriptID, const CString &strName, const CString &strValue);
	static BOOL SetScriptLastParameters(long nScriptID, CParameterMap *pMap);
	static BOOL SetScriptDefaultParameters(long nScriptID, CParameterMap *pMap);
	static BOOL GetScriptParameters(long nScriptID, CStringList *pList);
	static BOOL GetScriptParameters(long nScriptID, CParameterMap *pMap);
	static BOOL GetScriptDefaultParameters(long nScriptID, CParameterMap *pMap);
	static BOOL GetScriptParametersProperties(long nScriptID, CList <CParameterProperties, CParameterProperties&> *paramList);
	
	static BOOL IsIntString(const CString &strParam);
	static BOOL IsUIntString(const CString &strParam);
	static BOOL IsDoubleString(const CString &strParam);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScriptParamsDB)
	public:
	virtual CString GetDefaultDBName();		// Default database name
	virtual CString GetDefaultSQL();		// Default SQL for Recordset
	virtual void DoFieldExchange(BOOL bLoad = TRUE);
	//}}AFX_VIRTUAL

private:
	CString m_strAppPath;
	static CEventForMultiLock m_cLockEvent;	

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCRIPTPARAMSDB_H__AEAF3EE8_ABEB_4088_8D72_C9BD7847F3BE__INCLUDED_)
