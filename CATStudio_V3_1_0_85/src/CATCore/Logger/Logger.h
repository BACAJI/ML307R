#pragma once
#include "MrvlCommon/ICATMessage.h"
#include "MrvlCommon/imc/ImcListener.h"
#include "MrvlCommon/CommonDefs.h"
#include "MrvlCommon/UEInfo.h"
#include <vector>
#include <list>
#include <utility>
using namespace std;




#ifdef _LOGGER_DLL
#define LOGGER_EXPORT __declspec(dllexport)
#else
#define LOGGER_EXPORT
#endif

class CLogFileInf
{
public:
   CString strFilename;
   CString strFilePathName;
   DWORD   dwFilesize;
   int     iFileIndex;
};

class CLogFileInfOnline : public CLogFileInf
{
public:
   pair<UINT64, UINT64> idxRange;
};

class CMessageReceiver;
class CLogFile;
class CLogDescrFile;
class CICATMessageReceiver;
class LOGGER_EXPORT CLogger: public ImcListener
{
public:
   static CLogger* Instance();
   static void DestroyInstance();
   static CLogger* ms_pInstance;
   static CCriticalSection ms_Lock;
   friend class CLoggerUIOnline;

   CLogger();
   ~CLogger();

   enum EDiskFullOperation
   {
      eDeleteOldest=0,
      eStopLogging=1,
   };
   enum ELogNameConvention
   {
      eAcatLogName,
      eCreationTime,
      eCustomized,
   };

   
   void  StartLogging();
   void  StopLogging();
   BOOL  CloseLogFile(bool isPauseRequested = false);
   CString GetFullPath();
   CString GetFileName();
   void  SetMaxFilesizeMB(DWORD dwMaxFilesizeMB);
   void  SetMinDiskFreeSpaceMB(DWORD dwMinSpaceMB);
   void  GetCurrentFilename(CString& strFilename, int& iFileIndex);
   void  SetLogFilePath(const CString& strLogPath);
   CString GetLogFilePath();
   void  SetDiskFullOperation(EDiskFullOperation val);
   void  SetUseAcatLogName(bool bUseAcatLogName);
   UINT  GetNumOfDroppedMsg();
   void  ClearBinLogs();
   void  SetCustomizedLogName(CString strLogName);
   LRESULT OnMessageReceived(CMessage* pMessage);
private:
   static UINT  ThreadProc(LPVOID);
   static UINT  ClearBinLogsThread(LPVOID lpVoid);
   static UINT MergeLogFiles(LPVOID logFilesMergeDataStruct);
   static UINT MergeLogDescriptorFiles(LPVOID logDescriptorFilesMergeDataStruct);
   UINT     ThreadFunc();
   void     HandleMessage(CICATMessage* pMessage);
   void     CloseFileInternal(CLogFile* logFile = NULL, CArchive* logArchive = NULL, CLogDescrFile* logDescriptorFile = NULL, bool addClosedLogAddedToLogFilesList = true);
   BOOL     OpenFileInternal(const CString* fileName = NULL, bool isAlreadyExistingFile = false);
   void     LockFile();
   void     UnlockFile();
   void     DiskFullOperation();
   void     DeleteOldFiles(/*LPCTSTR lpszLogsDir, DWORD dwHoursAgo*/);
   void     ClearFileInfoList();
   void     RecordPausedLogFile();
   void     EraseLogFileFromLists(const CString* filePath);
   
   UINT     ClearBinLogsFunc();
   void     EnumBinLogs(CStringList& lstBinLogs);
   BOOL     RemoveOldestFile();
   void     DeleteOldFilesFunc();
private:
   CMessageReceiver* m_pImcReceiver;
   CICATMessageReceiver* m_pMessageReceiver;
   CCriticalSection  m_FileLock;
   CLogFile*         m_pLogFile;
   CArchive*         m_pArchive;
   CLogDescrFile*    m_pLogDescrFile;
   CString           m_strFilename;
   CString           m_strLogFolder;
   CString           m_pausedLogPath; // The path of the log file that has been closed when the user clicked "Pause"; irrelevant and contains an empty string if either not during pause, or the log file created on pause has already been closed.
   ULONGLONG         m_pausedLogSize; // The size (in bytes) of the log file that has been closed when the user clicked "Pause"; irrelevant and contains zero if either not during pause, or the log file created on pause has already been closed.
   UINT64            m_nMsgCount;
   UINT64            m_iMsgIndex;
   UINT64            m_iMsgIndexFirst;
   bool              m_bUseAcatLogName;
   int               m_iAcatLogNameIndex;
   bool              m_bCustomized;
   int               m_iCustomizedLogIndex;
   CString           m_strCustomizedLogTitle;       
   EDiskFullOperation m_eDiskFullOperation;
   int               m_iFileIndex;
   CCriticalSection  m_FileListLock;
   vector<CLogFileInfOnline> m_LogFileList;
   vector<CLogFileInfOnline> m_PausedLogFile;
   bool             m_bPaused;
   bool             m_bStopped;
   DWORD            m_UEVersion[MAX_DEVICE_NUM];
   DWORD            m_UEVersionAppSide[MAX_DEVICE_NUM];
   int              m_Protocol[MAX_DEVICE_NUM];
   int              m_ConnStatus[MAX_DEVICE_NUM];
   CUeCpInfo        m_UeCpInfo[MAX_DEVICE_NUM];
   CCriticalSection m_LockUeCpInfo;
   list<CString>    m_lstDelete;
   
   

   HANDLE   m_hThread;
   HANDLE   m_hCloseFile;
   HANDLE   m_hExitThread;
   DWORD    m_dwFileSize;
   DWORD    m_dwMaxMergedFileSizeMB; // The maximum size of a current log (in bytes) that's merged with the previously paused log file in case of a Pause-Play buttons clicking sequence.
   DWORD    m_dwMaxFileSizeMB;
   DWORD    m_dwMinDiskSpaceMB;
  

};