#if !defined(AFX_SCRIPTSDB_H__1447D192_5EB3_41D4_891D_3C6A2A80DD75__INCLUDED_)
#define AFX_SCRIPTSDB_H__1447D192_5EB3_41D4_891D_3C6A2A80DD75__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ScriptsDB.h : header file
//

#include <afxmt.h>
#include "../Converter/db/DisconnectedADORecordset.h"
#if !(_MSC_VER >= 1400)
#include <afxtempl.h>
#endif


#define NO_CONFIG _T("No Configuration")

class CScriptData;

/////////////////////////////////////////////////////////////////////////////
// CScriptsDB DAO recordset

class  CATCORE_DLLEXPORT CScriptsDB : public CDisconnectedADORecordset
{
public:
	CScriptsDB();
	virtual ~CScriptsDB();
	long	m_ScriptID;
	CString m_ScriptName;
	CString m_GroupName;
	CString m_DllName;
	CString m_ScriptVersion;
	CString m_Configs;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScriptsDB)
	public:
	virtual CString GetDefaultDBName();		// Default database name
	virtual CString GetDefaultSQL();		// Default SQL for Recordset
	virtual void DoFieldExchange(BOOL bLoad = TRUE);
	//}}AFX_VIRTUAL

public:
	static BOOL GetScriptListByDll(const CString &strDllName, CStringList *pScriptList);
	static BOOL RemoveScripts(CStringList &strScriptList);
	static BOOL GetScriptList(const CString &strGroupName, CStringList *pScriptList);
	static long RemoveScript(const CString &strGroup, const CString &strScript);
	static BOOL SetScriptVersion(const CString &strGroup, const CString &strScript, const CString &strVersion);
	static BOOL GetHWConfigurations(const CString &strGroup, const CString &strScript, CStringList &strListConfigs);
	static BOOL GetHWConfigurations(long nScriptId,CStringList &strListConfigs);
	static BOOL SetHWConfigurations(long nScriptId, CString strConfigs/*CStringList &strListConfigs*/);
	static BOOL AddRelatedHWConfiguration(CStringList &strGroupList, CStringList &strScriptList, const CString &strConfigName);
	static CString GetScriptVersion(const CString &strGroup, const CString &strScript);
	static CString GetDllName(const CString &strGroup, const CString &strScript);
	static CString GetGroupName(long nScriptID);
	static long GetScriptID(const CString &strGroup, const CString &strScript);
	static void LoadDB(CTreeCtrl *pTree, const CString &strHWConfig = NO_CONFIG, BOOL bShowAll = FALSE, const CString &strGroup = _T(""),int iItemImage = 0,int iGroupImage = 0);
	static void LoadDBWithConfig(CTreeCtrl *pTree, const CString &strHWConfig);
	static void UpdateGroupsForScripts(CTreeCtrl *pTree, CList<HTREEITEM,HTREEITEM>& lstItemsToUpdate);
	static void LoadDBToList(CList<CScriptData*, CScriptData *>& lstScriptList, const CString &strHWConfig =NO_CONFIG, BOOL bShowAll =FALSE, const CString &strGroup =_T(""));
	static BOOL UpdateScriptProperties(const CScriptData * pData,CString strConfigs =_T(""));

private:
	BOOL IsHWConfigOK(const CString &strHWConfig);

	static CCriticalSection m_cSection;
	CSingleLock m_sLock;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCRIPTSDB_H__1447D192_5EB3_41D4_891D_3C6A2A80DD75__INCLUDED_)
