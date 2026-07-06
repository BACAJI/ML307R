#pragma once
#include "ViewerDefs.h"
//#include "../Filter/AllFilters.h"
//#include "../../IMLViewer/IPtkRecorder/IMLLoggerInterface.h"
#include "../IMLViewer/IPtkRecorder/IPtkRecorderStructures.h"
#include "../CommandAndControl/CommandChannel.h"
//#include "Tests-Dlls/generaldefs.h"

typedef BOOL (*PFN_IMLTSTARTFUNC)(const CString &,DWORD,int,CString &, DWORD,int);
typedef PFN_IMLTSTARTFUNC LPFN_IMLTSTARTFUNC;
typedef void (*PFN_IMLTSTOPFUNC)();
typedef PFN_IMLTSTOPFUNC LPFN_IMLTSTOPFUNC;
typedef BOOL (*PFN_IMLTRECORDERSETTINGFUNC)(SRecorderAPIParams& RecorderAPIParams,CString &strErrMsg);
typedef PFN_IMLTRECORDERSETTINGFUNC LPFN_IMLTRECORDERSETTINGFUNC;

#define RECORD_STRESS_NON_CYCLIC	2
#ifdef _UNICODE
BOOL __declspec(dllexport) IMLStartRecord(const CString & strTargetFile,DWORD dwFileSizeInMB,int iRecordingMode = RECORD_STRESS_NON_CYCLIC,CString &strErrMsg = CString(""), DWORD dwTriggerOpcode = 0x0000,int iTriggerPosition = 0);
#endif
BOOL __declspec(dllexport) IMLStartRecord(const CStringA & strTargetFile,DWORD dwFileSizeInMB,int iRecordingMode = RECORD_STRESS_NON_CYCLIC,CStringA &strErrMsg = CStringA(""), DWORD dwTriggerOpcode = 0x0000,int iTriggerPosition = 0);
void __declspec(dllexport) IMLStopRecord();
void __declspec(dllexport) IMLStopRecordAndWait();
void __declspec(dllexport) IMLAbortRecord();
BOOL __declspec(dllexport) IMLSetIMLRecorderSettings(SRecorderAPIParams& RecorderAPIParams,CString &strErrMsg);

typedef bool (*PFN_MINIVIEWERSAVEASTEXTFUNC)(LPCTSTR);
typedef PFN_MINIVIEWERSAVEASTEXTFUNC LPFN_MINIVIEWERSAVEASTEXTFUNC;
typedef bool (*PFN_ASN1VIEWERSAVEASTEXTFUNC)(LPCTSTR);
typedef PFN_ASN1VIEWERSAVEASTEXTFUNC LPFN_ASN1VIEWERSAVEASTEXTFUNC;

class __declspec(dllexport) CViewer
{
public:
	CViewer();           
	virtual ~CViewer();
	CStringA GetViewerFileFullPath();
	void StopViewerFromOutside();
	void StartViewerFromOutside();
	void PauseViewerFromOutside();
	BOOL DeleteEntireDir(const CString &strDir);
	BOOL OpenNewFile(const CString &viewerName =_T(""));
	CString GetViewName(){return m_strViewName;}
	void SetViewName(CString strViewName){m_strViewName = strViewName;}
	BOOL CopyFolder(const CString &desc,const CString &source, TCHAR* strFuncLine);
	BOOL CopyAndRenameExportFile(const CString &oldPath, const CString &newPath, TCHAR* strFuncLine);
	BOOL ExportLogFile(const CString &strExportZipFileName, CString &strError);
	BOOL ExportLogFile(int nDeviceID, const CStringA &strExportZipFileName, CStringA &strError);// Add nDeviceID to support multi-CP processors.
	BOOL ExportLogFile(int nDeviceID, const CStringW &strExportZipFileName, CStringW &strError);// Add nDeviceID to support multi-CP processors.
	BOOL ExportLogFile(int nDeviceID, const CString &strFileName, CList <FilesList, FilesList&> *fileList, CString &strError);// Add nDeviceID to support multi-CP processors.
	BOOL ExportLogFile(int nDeviceID, const CString & strLogName, const CString &strFileName, CList <FilesList, FilesList&> *fileList, CString &strError);
	BOOL ExportLogFile(int nDeviceID, const CString & strLogName, const CStringW &strExportZipFileName, CStringW &strError);
	BOOL ExportLogFile(int nDeviceID, const CStringA & strLogName, const CStringA &strExportZipFileName, CStringA &strError);
	void SetShowLastLine(BOOL bShow = TRUE) { m_bIsEnsureVisible = bShow; }

	static void OpenEntireFilter();
	static void CloseEntireFilter();
	static void SetDIAGFilter(int nDeviceID, const CString &strCat1, const CString &strCat2, const CString &strCat3, int TargetType, BYTE bPass);

	// Develop for India customers' request
	void ClearLog();
	void StartLog();
	void StopLog();
	void PauseLog();
	BOOL SendATCmdAndWait( UINT nDevNum, CString strATCmd, CString &strATWait, int timeout=8000 );
	BOOL SendDiagCmdAndWait( UINT nDevNum, UE_Message &command, UE_Message &report, int timeout=8000 );
	BOOL MiniViewer_SaveAsText(CString strPath);
	BOOL ASN1Viewer_SaveAsText(CString strPath);
	BOOL SetDeviceEnabled(int nDeviceID, BOOL bEnabled);
protected:
private:
	CString m_strViewName;
	BOOL	m_bIsEnsureVisible;
	CString m_strLogFullPathName;


	BOOL SplitStrByChar(CString strToSplit, TCHAR tcChar, CStringList &strATWait);
};


