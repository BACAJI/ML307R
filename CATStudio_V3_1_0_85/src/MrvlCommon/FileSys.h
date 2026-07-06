#pragma once
#include "imagehlp.h"
#pragma comment(lib, "imagehlp.lib")

#ifdef _CATCORE_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

class DLL_EXPORT FileSys
{
public:
   struct MultiCopyResult
   {
      int nCopied;
      int nFailed;
   };

   enum FileTime
   {
      FileTime_Created,
      FileTime_Accessed,
      FileTime_Modified,
   };


   static BOOL CopyFile(CString srcFile, CString dstDir);
   static BOOL MoveFile(CString srcFile, CString dstDir);
   static void CopyFiles(CString srcDir, CString dstDir, CString filterInc=_T("*"), CString filterExc=_T(""), BOOL bRecursive=TRUE, CStringList* pListCopied=NULL, CStringList* pListFailed=NULL);
   static void MoveFiles( CString srcDir, CString dstDir, CString filterInc=_T("*"), CString filterExc=_T(""), BOOL bRecursive=TRUE, CStringList* pListMoved=NULL, CStringList* pListFailed=NULL );
   static BOOL FileExist(CString filename);
   static DWORD GetFileSize(CString filename);
   static BOOL DirExist(CString dir);
   static BOOL IsRoot(CString dir);
   static BOOL IsAbsDir(CString dir);
   static BOOL RmDir(CString dir, BOOL bDirEmpty=FALSE);
   static BOOL RmDir(CString dir, CString filterExc, BOOL bDirEmpty=FALSE);
   static BOOL MkDir(CString dir);
   static BOOL RmFile(CString filename);
   static BOOL EnumFile(CString dir, CStringList& fileList, BOOL bRecursive, CString filter=_T("*"));
   static BOOL EnumFolder( CString dir, CStringList& folderPathList, BOOL bRecursive);
   static CString GetNameInPath(CString path);
   static CString GetTitleInPath(CString path);
   static CString GetExtension(const CString& path);
   static CString GetUpperDir(CString& path);
   static CString GetUpperDir(const CString& path);
   static void    ReplaceExtension(CString& path, CString strNewExtension);
   static CString GetCurrentDir();
   static void    SetCurrentDir(const CString& path);
   static CString GetModuleDir();
   static CString GetFilterStrPairs(CString strFilter);
   static BOOL    SortByTime(CStringList& fileList, FileTime byTime=FileTime_Created);
   static ULONGLONG GetFolderSize(LPCTSTR lpszPath, BOOL bRecurse=TRUE);
   static BOOL GetFileCreationTime(CString DirName, SYSTEMTIME &stime);
   static BOOL GetFileAccessTime(CString DirName, SYSTEMTIME &stime);
   static BOOL GetFileModifiedTime(CString DirName, SYSTEMTIME &stime);
   static BOOL GetFileSystemTime(CString DirName, SYSTEMTIME &stime, FileSys::FileTime eTimeType);
   static LONGLONG GetTimeSpanMilliSeconds(const SYSTEMTIME& st1, const SYSTEMTIME& st2);
   static LONGLONG GetTimeSpanSeconds(const SYSTEMTIME& st1, const SYSTEMTIME& st2);
   static LONGLONG GetTimeSpanMinutes(const SYSTEMTIME& st1, const SYSTEMTIME& st2);
   static LONGLONG GetTimeSpanHours(const SYSTEMTIME& st1, const SYSTEMTIME& st2);
   static int      GetTimeSpanDays(const SYSTEMTIME& st1, const SYSTEMTIME& st2);
   static int      GetTimeSpanWeeks(const SYSTEMTIME& st1, const SYSTEMTIME& st2);
   static int      GetTimeSpanYears(const SYSTEMTIME& st1, const SYSTEMTIME& st2);
   static BOOL FindEarliestAccessedFile(LPCTSTR lpszDirName, FILETIME& ftLastAccess, CString& strFilePath );
   static BOOL DeleteOldestFile(LPCTSTR lpszDirName);
   static void RemoveOldestFolder(LPCTSTR lpszDirName, UINT nSecondsBeforeNow=0);
   static void RemoveOldFolder(LPCTSTR strDirName, FileTime eTimeType, UINT nSecondsBeforeNow=0, LPCTSTR filterExc=_T(""));
   static void RemoveOldFolderByCreationTime(LPCTSTR strDirName, UINT nSecondsBeforeNow=0, LPCTSTR filterExc=_T(""));
   static void RemoveOldFolderByAccessedTime(LPCTSTR strDirName, UINT nSecondsBeforeNow=0, LPCTSTR filterExc=_T(""));
   static void RemoveOldFolderByModifiedTime(LPCTSTR strDirName, UINT nSecondsBeforeNow=0, LPCTSTR filterExc=_T(""));
   static void RemoveOldFile(LPCTSTR lpszDir, FileTime eTimeType, UINT nSecondsBeforeNow=0, LPCTSTR filterInc=_T("*"), LPCTSTR filterExc=_T(""));
   static void RemoveOldFileByCreationTime(LPCTSTR lpszDir, UINT nSecondsBeforeNow=0, LPCTSTR filterInc=_T("*"), LPCTSTR filterExc=_T(""));
   static void RemoveOldFileByAccessedTime(LPCTSTR lpszDir, UINT nSecondsBeforeNow=0, LPCTSTR filterInc=_T("*"), LPCTSTR filterExc=_T(""));
   static void RemoveOldFileByModifiedTime(LPCTSTR lpszDir, UINT nSecondsBeforeNow=0, LPCTSTR filterInc=_T("*"), LPCTSTR filterExc=_T(""));



private:
   static BOOL    _GetFileSize64(LPCTSTR lpszPath, PLARGE_INTEGER lpFileSize);
   static BOOL    _GetFolderSize(LPCTSTR lpszStartFolder, BOOL bRecurse, BOOL bQuickSize, PLARGE_INTEGER lpFolderSize, LPDWORD lpFolderCount =NULL, LPDWORD lpFileCount=NULL);

   static MultiCopyResult _CopyFilesEx(  CString srcDir,
                              CString dstDir,
                              CString filterInclude,
                              CString filterExclude,
                              BOOL bRecursive=TRUE,
                              BOOL bDeleteSrc=FALSE,
                              BOOL bCopyHidden=FALSE,
                              BOOL bTransaction=TRUE,
                              CStringList* pListCopied=NULL, 
                              CStringList* pListFailed=NULL);

};

#define _FLT(_x) FileSys::GetFilterStrPairs(_x)

void MsgBox(int i);
void MsgBox(UINT ui);

