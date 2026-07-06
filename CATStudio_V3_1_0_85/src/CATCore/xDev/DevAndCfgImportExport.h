#pragma once
#include "GeneralMacroDefine.h"

class CDBLayer;
class CDevParams;
class CConfigParams;

class CATCORE_DLLEXPORT CDevAndCfgImportExport  
{
public:
	CDevAndCfgImportExport();
	virtual ~CDevAndCfgImportExport();
//	BOOL ExportDevices(CStringList &devList, LPCTSTR strFileName = NULL);
//	BOOL ExportConfigurations(CStringList &configList, LPCTSTR strFileName = NULL);
//	BOOL ImportDevices();
//	BOOL ImportConfigurations();
	BOOL ImportDevicesOrConfiguration(const CString &strFilePath, CString &strErrMsg);

private:
		
	BOOL ExportDev(const CString &strDevName, CArchive &ar);
	BOOL ImportDev(CArchive &ar);
	BOOL ExportConfig(const CString &strConfigName, CArchive &ar);
	BOOL ImportConfig(CArchive &ar);

	CDBLayer *m_pDbLayer;
	CDevParams *m_pDevParams;
	CConfigParams *m_pConfigParams;

	int m_iMode;
	BOOL m_bApiFunc;

};

/*





// ScriptImportExport.h: interface for the CScriptImportExport class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCRIPTIMPORTEXPORT_H__1E2CEABC_7878_41A8_9B42_6FB50025E4C0__INCLUDED_)
#define AFX_SCRIPTIMPORTEXPORT_H__1E2CEABC_7878_41A8_9B42_6FB50025E4C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CScriptImportExport  
{
public:
	static BOOL ConvertBatchToExport();
	static BOOL	ExportScripts(CStringList &scriptList, LPCSTR strFileName = NULL);
	static BOOL	ImportScripts();
	
private:
	CScriptImportExport();
	virtual ~CScriptImportExport();
	
	static BOOL ExportScript(const CString &strGroupName, const CString &strScriptName, CArchive &ar);
	static BOOL ImportScript(CArchive &ar);
};

#endif // !defined(AFX_SCRIPTIMPORTEXPORT_H__1E2CEABC_7878_41A8_9B42_6FB50025E4C0__INCLUDED_)
*/