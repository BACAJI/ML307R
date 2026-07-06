#pragma once
#include <list>

using namespace std;

#ifdef _CATCORE_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT 
#endif

class DLL_EXPORT IDBProcessEvent
{
public:
	virtual void OnImportCpTextBegin(int nFileSize)		= 0;
	virtual void OnImportCpTextEnd(int nPosition)		= 0;
	virtual void OnImportCpTextProgress(int nPosition)	= 0;
};

class DLL_EXPORT CDatabaseProcessor
{
public:

	CDatabaseProcessor();
	~CDatabaseProcessor();

	void SetEventHandler(IDBProcessEvent* pHandler);

	// Database releated
	bool UpdateNVMDB(int nDevice, const CString &strDBPath, CString &strError, bool bAppSide = false);
	bool UpdateCommandsDB(int nDevice, const CString &strDBPath, CString &strError, bool bAppSideDB = false);
	bool UpdateDspDB(int nDevice, const CString& strDspPath, CString& strError);
	bool ImportCpDbFromText(int nDevice, const CString& strDbTextPath, CString &strError, bool blocking);
	bool ImportApDBFromText(int nDevice, const CString &strDBPath, CString &strError, bool blocking);
	bool BuildApDBFromText(const CString &strTextDBPath, const CString &strOutputDir, CString &strError);
	bool BuildCpDBFromText(const CString &strTextDBPath, const CString &strOutputDir, CString &strError);
	bool CopyApTemplateDB(const CString &strTemplateDir, const CString &strOutputDir, CString &strError);
	bool CopyCpTemplateDB(const CString &strTemplateDir, const CString &strOutputDir, CString &strError);
	bool UpdateCpTextDB(int nDevice, CString& strSrvCpTextDb);
	bool UpdateApTextDB(int nDevice, CString& strSrvApTextDb);
	void StopImportThread();
	inline void SetTemporaryDatabaseProcessor() { m_temporaryDatabaseProcessor = true; };
	inline bool IsTemporaryDatabaseProcessor() { return m_temporaryDatabaseProcessor; };

protected:
	bool BuildCpDbFromText();
	bool BuildApDBFromText(int nDevice, const CString &strTextDBPath, CString &strError);
	
	//Support progress bar.
	void StartParsingThread();
	static UINT  ParsingThreadFunc(LPVOID lpVoid);
	void NotifyParseBegin(int nFileSize);
	void NotifyParseEnd(int nCurPosition);
	void NotifyParseProgress(int nCurPosition);

	void ClearApOldTableRecords(const CString& strSrcDB);
	void ClearCpOldTableRecords(const CString& strDbPath);
protected:
	bool m_temporaryDatabaseProcessor; // A flag that says whether this instance of CDatabaseProcessor is a temporary one, and should be deleted at the end of its usage.
	int m_nDeviceID;
	CString m_strTextDBPath;
	CEvent m_EventKillThread;
	CWinThread* m_pLoadingThread;
	IDBProcessEvent* m_pEventHandler;
};