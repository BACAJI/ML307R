/*--------------------------------------------------------------------------------------------------------------------

 (C) Copyright 2006,2007 Marvell Semiconductor Israel Ltd. All Rights Reserved  

-------------------------------------------------------------------------------------------------------------------*/


// LoggerManager.h: interface for the CLoggerManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGGERMANAGER_H__E7D314C1_1233_11D5_8230_0006294FD6F7__INCLUDED_)
#define AFX_LOGGERMANAGER_H__E7D314C1_1233_11D5_8230_0006294FD6F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <map>
#include <afxtempl.h>
#include "SingletonDestroyer.h"
//#include "LoggerDefines.h"
//#include "Logger1.h"

class CLogger;

// struct LoggerOwnerRecord {
// 	void	*m_pOwner;
// 	CLogger *m_pLogger;
// 
// 	LoggerOwnerRecord (CLogger *pLogger=NULL, void *pOwner=NULL)
// 	{
// 		m_pOwner = pOwner;
// 		m_pLogger = pLogger;
// 	}
// };


class __declspec(dllexport)  CLoggerManager : public CCmdTarget 
{
	DECLARE_DYNCREATE(CLoggerManager)

public:
	static CLoggerManager * Instance();
	
private:
	static CLoggerManager *m_pThis;
	
	CLoggerManager();
	virtual ~CLoggerManager();
	static CSingletonDestroyer<CLoggerManager> m_Destroyer;
	friend class CSingletonDestroyer<CLoggerManager>;
	
public:
// 	BOOL IsScriptLogger(CLogger *pLogger);
// 	void ClearScriptLoggerList(void *pOwner);
// 	void CloseAllScriptLoggers(void *pOwner);
//	void DeleteAll();
	BOOL CloseLogger();
	BOOL CloseLogger(CString fileName /*= CString(_T(""))*/);
//	void OpenSpecificLogger(LPARAM lParam);
	//CList <CLogger *, CLogger *> * GetLoggerList();
//	void RemoveLogger(CLogger *pLogger);
	void OpenNewLog(const CString & fileNameIcl);
	BOOL AddNewLogger(const CString & fileName = CString(_T(""))/*, bool bTruncate = true, bool bStarted = true, int iDeviceNum = AllDevices, DWORD dwLogFileSize = 0, BOOL bAddAssertBookmarks = FALSE, BOOL bCutLogInAssert = FALSE*/);
//	CLogger * AddScriptLogger(CString fileName, bool bTruncate, bool bStarted, const CString &strPath, void *pOwner);
//	bool SetLoggerFile(CString fileName);
	long GetFileSize(CString strFilePathName);
	BOOL DeleteDirectory(CString strFilePath);
	CString GetIclLogName(CString strLogPathName);
	BOOL ExportLogFile(const CString &strZipFilePath, BOOL bDelLogAfterComplete = FALSE);	
	int CompressFiles(CString & strProcess, const CString strExportLogPath);
	BOOL CopyFolder(const CString &desc,const CString &source, TCHAR* strFuncLine);
	BOOL OpenFile(CFile & file, LPCTSTR lpszFileName, UINT nOpenFlags, TCHAR* strFuncLine);
	void GetLogNames(CStringArray & strFilesArray, std::map<CString,long> & mapFileNameSize);
	BOOL CopyAndRenameExportFile(const CString &oldPath, const CString &newPath, TCHAR* strFuncLine);
	BOOL MergeLogFiles(CStringArray &strArray,CString &tmpFolderPath, std::map<CString,long> mapFileNameSize,int nDevice = 0);
	void GetDBPathNames(CStringArray & strArrayPathNames, CArray<DWORD>& lArraySize, CArray<int>& nArrayActiveDevice, CString & strFirstActiveDeviceDBPath);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoggerManager)
	//}}AFX_VIRTUAL


private:
//	CList <CLogger *, CLogger *> m_LoggerList;
//	CList <LoggerOwnerRecord, LoggerOwnerRecord &> m_ScriptLoggerList;
//	int m_LoggerCounter;

protected:
	// Generated message map functions
	//{{AFX_MSG(CLoggerManager)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_LOGGERMANAGER_H__E7D314C1_1233_11D5_8230_0006294FD6F7__INCLUDED_)
