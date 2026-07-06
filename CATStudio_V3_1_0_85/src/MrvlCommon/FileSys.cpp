#include "StdAfx.h"
#include "FileSys.h"
#include "direct.h"
#include "logging/logging.h"

BOOL FileSys::CopyFile( CString srcFile, CString dstDir )
{
   if( !FileExist(srcFile) || !DirExist(dstDir) && !MkDir(dstDir) )
   {
      ASSERT(FALSE);
      return FALSE;
   }

   CString filename = GetNameInPath(srcFile);

   BOOL bRes = ::CopyFile(srcFile, dstDir+_T("\\")+filename, NULL); 

   return bRes;
}

BOOL FileSys::MoveFile( CString srcFile, CString dstDir )
{
   if( !FileExist(srcFile) || !DirExist(dstDir) && !MkDir(dstDir) )
   {
      ASSERT(FALSE);
      return FALSE;
   }

   CString filename = GetNameInPath(srcFile);

   BOOL bRes = ::MoveFileEx(srcFile, dstDir+_T("\\")+filename, MOVEFILE_COPY_ALLOWED|MOVEFILE_WRITE_THROUGH|MOVEFILE_REPLACE_EXISTING);

   return bRes;
}

void FileSys::CopyFiles( CString srcDir, CString dstDir, CString filterInc/*=_T("*")*/, CString filterExc/*=_T("")*/, BOOL bRecursive/*=TRUE*/, CStringList* pListCopied/*=NULL*/, CStringList* pListFailed/*=NULL*/ )
{
   MultiCopyResult res;

   res = _CopyFilesEx(srcDir, dstDir, filterInc, filterExc, bRecursive, FALSE, TRUE, FALSE, pListCopied, pListFailed);

   return;
}

void FileSys::MoveFiles( CString srcDir, CString dstDir, CString filterInc/*=_T("*")*/, CString filterExc/*=_T("")*/, BOOL bRecursive/*=TRUE*/, CStringList* pListMoved/*=NULL*/, CStringList* pListFailed/*=NULL*/ )
{
   MultiCopyResult res;

   res = _CopyFilesEx(srcDir, dstDir, filterInc, filterExc, bRecursive, TRUE, TRUE, FALSE, pListMoved, pListFailed);
}

BOOL FileSys::FileExist( CString filename )
{
   CFileStatus fStatus;
   BOOL bRet = CFile::GetStatus(filename, fStatus) && !(fStatus.m_attribute & CFile::directory);
   return bRet;
}

BOOL FileSys::DirExist( CString dir )
{
   CFileStatus fStatus;
   BOOL bRet = CFile::GetStatus(dir, fStatus) && (fStatus.m_attribute & CFile::directory);
   return bRet;
}


BOOL FileSys::IsRoot( CString dir )
{
   dir.TrimLeft();
   dir.TrimRight();
   dir.TrimRight('\\');dir.TrimRight('/');
   dir.TrimRight();

   if(dir.GetLength()!=2 )
      return FALSE;

   TCHAR tchDrive = dir.GetAt(0);
   TCHAR tchColon = dir.GetAt(1);

   if(tchColon!=':')
      return FALSE;
   if(!(tchDrive>='a' && tchDrive<='z' || tchDrive>='A' && tchDrive<='Z'))
      return FALSE;
   
   return TRUE;
}


BOOL FileSys::RmDir( CString dir, BOOL bDirEmpty/*=FALSE*/ )
{
   if(!DirExist(dir))
   {
      return TRUE;
   }
   if( bDirEmpty )
   {
      BOOL bDeleted = ::RemoveDirectory(_T("\\\\?\\") + dir);
      DWORD err = GetLastError();
      TRACE2("Error: Remove %s failed, errno ", dir, err);
      return bDeleted;
   }

   CFileFind finder;
   CString strFile;

   BOOL bWorking = finder.FindFile(dir + _T("\\*"));
   while ( bWorking )
   {
      bWorking = finder.FindNextFile();

      // skip . and .. files; otherwise, we'd
      // recur infinitely!		
      if (finder.IsDots())
         continue;


      if (!finder.IsDirectory())//It is file
      {
         strFile = finder.GetFilePath();

         try
         {
            CFile::Remove(strFile);
         }
         catch (CFileException* e)
         {
            CFileStatus fStatus;
#if 0
            CFile::GetStatus(strFile, fStatus);
            if ( fStatus.m_attribute & CFile::readOnly )
            {
               fStatus.m_attribute &= (~CFile::readOnly);
               CFile::SetStatus(strFile, fStatus);
            }
#endif
            try
            {
            if (CFile::GetStatus(strFile, fStatus) && (fStatus.m_attribute & CFile::readOnly))
            {
               fStatus.m_attribute &= (~CFile::readOnly);
               CFile::SetStatus(strFile, fStatus);
            }
            CFile::Remove(strFile);
            }
            catch(...)
            {
               AfxMessageBox(_T("There is a problem removing ") + strFile);
               continue;
            }
         }
         catch(...)
         {
            AfxMessageBox(_T("There is a problem removing ") + strFile);
            continue;
         }
      }
      else//It is Directory
      {
         RmDir(finder.GetFilePath());
         ::RemoveDirectory(_T("\\\\?\\") + dir);
      }
   }

   finder.Close();

   ::RemoveDirectory(dir);

   return(TRUE);
}

BOOL FileSys::RmDir( CString dir, CString filterExc, BOOL bDirEmpty/*=FALSE*/ )
{
   if(!DirExist(dir))
   {
      return TRUE;
   }

   if( bDirEmpty )
   {
      BOOL bDeleted = ::RemoveDirectory(_T("\\\\?\\") + dir);
      DWORD err = GetLastError();
      TRACE2("Error: Remove %s failed, errno ", dir, err);
      return bDeleted;
   }

   

   // list excludes
   CStringArray excludes;
   int iTokenExc=0;
   CString tokenExc = filterExc.Tokenize(_T("|"), iTokenExc);
   while( tokenExc!=_T("") )
   {
      excludes.Add(tokenExc);
      tokenExc = filterExc.Tokenize(_T("|"), iTokenExc);
   }


   CFileFind finder;
   CString strFile;

   BOOL bWorking = finder.FindFile(dir + _T("\\*"));
   while ( bWorking )
   {
      bWorking = finder.FindNextFile();

      // skip . and .. files; otherwise, we'd
      // recur infinitely!		
      if (finder.IsDots())
         continue;


      if (!finder.IsDirectory())//It is file
      {
         strFile = finder.GetFilePath();
  
         CString extension = GetExtension(strFile);
         BOOL bExc=FALSE;
         for(int i=0; i<excludes.GetCount(); ++i)
         {
            if(excludes.GetAt(i)==_T("*") || extension.CompareNoCase(excludes.GetAt(i))==0 )
            {
               bExc=TRUE;
               break;
            }
         }

         if(!bExc)
         {
            try
            {
               CFile::Remove(strFile);
            }
            catch (CFileException* e)
            {
               CFileStatus fStatus;
#if 0
               CFile::GetStatus(strFile, fStatus);
               if ( fStatus.m_attribute & CFile::readOnly )
               {
                  fStatus.m_attribute &= (~CFile::readOnly);
                  CFile::SetStatus(strFile, fStatus);
               }
#endif
               try
               {
               if (CFile::GetStatus(strFile, fStatus) && (fStatus.m_attribute & CFile::readOnly))
               {
                  fStatus.m_attribute &= (~CFile::readOnly);
                  CFile::SetStatus(strFile, fStatus);
               }
               CFile::Remove(strFile);
               }
               catch(...)
               {
                  AfxMessageBox(_T("There is a problem removing ") + strFile);
                  continue;
               }
            }
            catch(...)
            {
               AfxMessageBox(_T("There is a problem removing ") + strFile);
               continue;
            }
         }
      }
      else//It is Directory
      {
         RmDir(finder.GetFilePath());
         ::RemoveDirectory(_T("\\\\?\\") + dir);
      }
   }

   finder.Close();

   ::RemoveDirectory(dir);

   return(TRUE);
}

BOOL FileSys::MkDir( CString strDir )
{
    strDir.TrimLeft();
    strDir.TrimRight();
    if(strDir.IsEmpty())
       return FALSE;

    if(DirExist(strDir))
       return TRUE;

    if(IsRoot(strDir))
       return FALSE;

    if(!DirExist(GetUpperDir(strDir)))
       if(!MkDir(GetUpperDir(strDir)))
          return FALSE;
   
    return CreateDirectory(strDir, NULL);
}


CString FileSys::GetNameInPath( CString path )
{
   path.TrimLeft(_T("./ \\"));
   path.TrimRight(_T("./ \\"));
   int iIndex = path.Find(':');
   if(iIndex>=0)
      path = path.Mid(iIndex+1);

   iIndex = max(path.ReverseFind('\\'), path.ReverseFind('/') );

   CString strFileName = path.Mid(iIndex+1);

   return strFileName;
}

CString FileSys::GetTitleInPath( CString path )
{
   CString filename = GetNameInPath(path);
   int iDot = filename.ReverseFind('.');
   return filename.Left(iDot);
}

CString FileSys::GetExtension(const CString& path )
{
   int iIndex = max(path.ReverseFind('\\'), path.ReverseFind('/') );
   int iDot = path.ReverseFind('.');
   if(iDot!=-1 && iDot>iIndex)
      return path.Mid(iDot+1);
   else
      return _T("");
}


CString FileSys::GetUpperDir( CString& path )
{
   path.TrimLeft(' ');
   path.TrimRight('\\');
   path.TrimRight('/');

   return GetUpperDir((const CString&)path);
}

CString FileSys::GetUpperDir( const CString& path )
{
	CString strUpperDir;

	int iIndex = max(path.ReverseFind('\\'), path.ReverseFind('/') );
	if( iIndex >= 0 )
	{
		strUpperDir = path.Left(iIndex);
	}

	if(strUpperDir==_T("."))
		strUpperDir = GetCurrentDir();
	else if( strUpperDir==_T("..") )
	{
		strUpperDir = GetCurrentDir();
		return GetUpperDir(strUpperDir);
	}

	return strUpperDir;
}

void FileSys::ReplaceExtension(CString& path, CString strNewExtension )
{
   CString strDir = FileSys::GetUpperDir(path);
   CString strTitle = FileSys::GetTitleInPath(path);
   path = strDir + _T("\\") + strTitle + _T(".") + strNewExtension;
}

CString FileSys::GetCurrentDir()
{
   TCHAR path[1024];
   GetCurrentDirectory(1024, path);
   return path;
}

FileSys::MultiCopyResult FileSys::_CopyFilesEx(CString srcDir,
                           CString dstDir,
                           CString strFilterInclude,
                           CString strFilterExclude,
                           BOOL bRecursive/*=TRUE*/,
                           BOOL bDeleteSrc/*=FALSE*/,
                           BOOL bCopyHidden/*=FALSE*/,
                           BOOL bTransaction/*=TRUE*/,
                           CStringList* pListCopied/*=NULL*/,
                           CStringList* pListFailed/*=NULL*/ )
{
   srcDir.TrimRight(_T("/ \\"));
   srcDir.TrimRight(_T("/ \\"));
   dstDir.TrimLeft(_T("/ \\"));
   dstDir.TrimRight(_T("/ \\"));

   BOOL bDstDirExist = DirExist(dstDir);
   if( !bDstDirExist )
   { MkDir(dstDir); }


   // list excludes
   CStringArray excludes;
   int iTokenExc=0;
   CString tokenExc = strFilterExclude.Tokenize(_T("|"), iTokenExc);
   while( tokenExc!=_T("") )
   {
      excludes.Add(tokenExc);
      tokenExc = strFilterExclude.Tokenize(_T("|"), iTokenExc);
   }

   // list includes
   int iTokenInc=0;
   CStringArray includes;
   CString tokenInc = strFilterInclude.Tokenize(_T("|"), iTokenInc);
   while( tokenInc!=_T("") )
   {
      includes.Add(tokenInc);
      tokenInc = strFilterInclude.Tokenize(_T("|"), iTokenInc);
   }



   int nCopied=0, nFailed=0;
   
   // find file
   CFileFind finder;
   CString strFinder = srcDir + _T("\\*.*");
   BOOL bWorking = finder.FindFile(strFinder);
   while(bWorking)   
   {
      bWorking = finder.FindNextFile();

      // is directory
      if( bRecursive && finder.IsDirectory() && !finder.IsDots() )
      {
         MultiCopyResult subRes;
         CString filename = finder.GetFileName();
         CString dstFile = dstDir + _T("\\") + filename;
         subRes = _CopyFilesEx(finder.GetFilePath(), dstFile, strFilterInclude, strFilterExclude, bRecursive, bDeleteSrc, bCopyHidden, bTransaction, pListCopied, pListFailed);
         nCopied += subRes.nCopied;
         nFailed += subRes.nFailed;
      }
      else if(!finder.IsDots())
      {
         // is file
         CString filename = finder.GetFileName();
         CString extension = GetExtension(filename);
         BOOL bInc=FALSE;
         for(int i=0; i<includes.GetCount(); ++i)
         {
            if(includes.GetAt(i)==_T("*") || extension.CompareNoCase(includes.GetAt(i))==0 )
            {
               bInc = TRUE;
               break;
            }
         }

         BOOL bExc=FALSE;
         for(int i=0; i<excludes.GetCount(); ++i)
         {
            if(excludes.GetAt(i)==_T("*") || extension.CompareNoCase(excludes.GetAt(i))==0 )
            {
               bExc=TRUE;
               break;
            }
         }

         if( bInc && !bExc )
         {
            CString dstFile = dstDir + _T("\\") + filename;

            BOOL ok;
            if( bDeleteSrc )
            {
               ok = ::MoveFileEx(finder.GetFilePath(), dstFile, MOVEFILE_COPY_ALLOWED|MOVEFILE_WRITE_THROUGH|MOVEFILE_REPLACE_EXISTING);
            }
            else
            {
               ok = ::CopyFile(finder.GetFilePath(), dstFile, FALSE);
            }

            if( ok )
            {
               ++nCopied;
               if( pListCopied )
                  pListCopied->AddTail( dstFile );
            }
            else
            {
               ++nFailed;
               if( pListFailed )
                  pListFailed->AddTail( finder.GetFilePath() );
            }
         }
      }
   }


   finder.Close();

   if(bDeleteSrc && strFilterInclude==_T("*") && strFilterExclude==_T(""))
   {
      RmDir(srcDir, TRUE);
   }

   if( !bDstDirExist && nCopied==0)
   {
      RmDir(dstDir, TRUE);
   }

   MultiCopyResult res;
   res.nCopied = nCopied;
   res.nFailed = nFailed;

   return res;
}

CString FileSys::GetModuleDir()
{
   TCHAR szModuleDir[1024];
   DWORD nResult = ::GetModuleFileName(NULL, szModuleDir, MAX_PATH);
   if (0 == nResult)
   {
      return _T("");
   }

   CString strModuleDir(szModuleDir);
   UINT nIndex = strModuleDir.ReverseFind('\\');
   return strModuleDir.Left(nIndex);
}

CString FileSys::GetFilterStrPairs(CString strFilter)
{
    ASSERT(strFilter.Find(_T('*')) >= 0);
    if (strFilter.ReverseFind(_T('|')) >= 0)
    {
        ASSERT(strFilter.Right(2) == _T("||"));
        return strFilter;
    }
    LPCTSTR s = strFilter.GetString();
	LPCTCH p = _tcschr(s, _T('*'));
	ASSERT(p);
	LPCTCH q = p + 1;
	while (p > s)
	{
		--p;
		if (*p == _T(' ') || *p == _T('('))
		{
			++p;
			break;
		}
	}
	while (*q && *q != _T(' ') && *q != _T(')'))
	{
		++q;
	}
	CString strGlob = CString(p, q - p);
	strFilter.AppendFormat(_T("|%s||"), strGlob);
	LOG_DEBUG(_T("Got %s"), strFilter);
	return strFilter;
}

BOOL FileSys::SortByTime( CStringList& fileList, FileTime byTime/*=FileTime_Created*/ )
{
   CMap<__time64_t, __time64_t, CString, CString> mapFile;

   POSITION pos = fileList.GetHeadPosition();
   while(pos)
   {
      CFileStatus fStatus;
      CString strPath = fileList.GetNext(pos);
      if ( CFile::GetStatus(strPath, fStatus) )
      {
         
         __time64_t key;
         switch (byTime)
         {
         case FileTime_Accessed:
            key = fStatus.m_atime.GetTime();
            break;

         case FileTime_Modified:
            key = fStatus.m_mtime.GetTime();
            break;

         case FileTime_Created:
         default:
            key = fStatus.m_ctime.GetTime();
            break;
         }
         
         mapFile[key] = strPath;
      }
      else
      {
         return FALSE;
      }
   }

   fileList.RemoveAll();

   pos = mapFile.GetStartPosition();
   while(pos)
   {
      __time64_t key;
      CString val;
      mapFile.GetNextAssoc(pos, key, val);
      fileList.AddTail(val);
   }

   return TRUE;
}

ULONGLONG FileSys::GetFolderSize( LPCTSTR lpszPath, BOOL bRecurse/*=TRUE*/ )
{
   LARGE_INTEGER folderSize;
   _GetFolderSize(lpszPath, bRecurse, TRUE, &folderSize, NULL, NULL);
   return folderSize.QuadPart;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetFolderSize()
//
// Purpose:     Get folder size
//
// Parameters:  lpszStartFolder - fully qualified starting folder path
//              bRecurse        - TRUE = recurse into subdirectories
//              bQuickSize      - TRUE = if lpszStartFolder is a drive, use 
//                                SHGetDiskFreeSpace() to get size for entire
//                                disk, instead of recursing (folder count
//                                and file count will be 0).
//              lpFolderSize    - pointer to 64-bit folder size
//              lpFolderCount   - pointer to 32-bit folder count (optional,
//                                may be NULL)
//              lpFileCount     - pointer to 64-bit file count (optional,
//                                may be NULL)
//
// Returns:     BOOL - Returns nonzero if successful or zero otherwise.
//
// 
BOOL FileSys::_GetFolderSize(LPCTSTR lpszStartFolder, 
                  BOOL bRecurse, 
                  BOOL bQuickSize,
                  PLARGE_INTEGER lpFolderSize,
                  LPDWORD lpFolderCount /*= NULL*/,
                  LPDWORD lpFileCount /*= NULL*/)
{
   BOOL rc = FALSE;

   _ASSERTE(lpszStartFolder);
   _ASSERTE(lpFolderSize);

   if (lpszStartFolder && lpFolderSize)
   {
      lpFolderSize->QuadPart = 0;
      if (lpFolderCount)
         *lpFolderCount = 0;
      if (lpFileCount)
         *lpFileCount = 0;

      if (bQuickSize && (_tcslen(lpszStartFolder) < 4))
      {
         // get used space for entire volume

         ULARGE_INTEGER ulFreeCaller;
         ulFreeCaller.QuadPart = 0;
         ULARGE_INTEGER ulTotal;
         ulTotal.QuadPart = 0;
         ULARGE_INTEGER ulFree;
         ulFree.QuadPart = 0;

         rc = SHGetDiskFreeSpace(lpszStartFolder, &ulFreeCaller, &ulTotal, &ulFree);
         lpFolderSize->QuadPart = ulTotal.QuadPart - ulFree.QuadPart;
         return rc;
      }

      HANDLE hFF = 0;
      WIN32_FIND_DATA wfd = { 0 };
      TCHAR szPath[2000];
      LARGE_INTEGER li_total;
      li_total.QuadPart = 0;
      DWORD dwTotalFolderCount = 0;
      DWORD dwTotalFileCount = 0;

      _tcsncpy_s(szPath, 2000, lpszStartFolder, sizeof(szPath)/sizeof(TCHAR)-1);
      _tcscat_s(szPath, 2000, _T("\\*"));

      hFF = FindFirstFile(szPath, &wfd);

      if (hFF != INVALID_HANDLE_VALUE)
      {
         rc = TRUE;

         do
         {
            _tcsncpy_s(szPath, 2000, lpszStartFolder, sizeof(szPath)/sizeof(TCHAR)-1);
            _tcscat_s(szPath, 2000, _T("\\"));
            _tcscat_s(szPath, 2000, wfd.cFileName);

            if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
               if (_tcscmp(wfd.cFileName, _T(".")) &&
                  _tcscmp(wfd.cFileName, _T("..")) &&
                  bRecurse)
               {
                  // recurse into the subdirectory

                  LARGE_INTEGER li;
                  li.QuadPart = 0;
                  DWORD dwFolderCount = 0;
                  DWORD dwFileCount = 0;
                  rc = _GetFolderSize(szPath, bRecurse, bQuickSize, &li, 
                     &dwFolderCount, &dwFileCount);
                  li_total.QuadPart += li.QuadPart;
                  dwTotalFolderCount += dwFolderCount + 1;
                  dwTotalFileCount += dwFileCount;
               }
            }
            else
            {
               LARGE_INTEGER li;
               li.QuadPart = 0;
               rc = _GetFileSize64(szPath, &li);
               li_total.QuadPart += li.QuadPart;
               dwTotalFileCount += 1;
            }

         } while (FindNextFile(hFF, &wfd));
      }

      *lpFolderSize = li_total;
      if (lpFolderCount)
         *lpFolderCount = dwTotalFolderCount;
      if (lpFileCount)
         *lpFileCount = dwTotalFileCount;
   }

   return rc;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetFileSize64()
//
// Purpose:     Get 64-bit file size
//
// Parameters:  lpszPath   - fully qualified path to file
//              lpFileSize - 64-bit file size
//
// Returns:     BOOL - Returns nonzero if successful or zero otherwise.
//
BOOL FileSys::_GetFileSize64(LPCTSTR lpszPath, PLARGE_INTEGER lpFileSize)
{
   BOOL rc = FALSE;

   _ASSERTE(lpszPath);
   _ASSERTE(lpFileSize);

   if (lpszPath && lpFileSize)
   {
      lpFileSize->QuadPart = 0;
      HANDLE hFile = NULL;

      hFile = CreateFile(lpszPath, READ_CONTROL, 0, NULL,
         OPEN_EXISTING, 0, NULL);

      if (hFile != INVALID_HANDLE_VALUE)
      {
         rc = GetFileSizeEx(hFile, lpFileSize);
         CloseHandle(hFile);
      }
   }

   return rc;
}

BOOL FileSys::IsAbsDir( CString dir )
{
   int dirLen = dir.GetLength();
   
   if(dirLen==2 && dir[1]==':')
      return TRUE;

   if(dirLen>2 && dir[1]==':' && (dir[2]=='\\' || dir[2]=='/') )
      return TRUE;

   return FALSE;
}

BOOL FileSys::GetFileCreationTime(CString DirName, SYSTEMTIME &stime)
{
   return GetFileSystemTime(DirName, stime, FileTime_Created);
}

BOOL FileSys::GetFileAccessTime(CString DirName, SYSTEMTIME &stime)
{
   return GetFileSystemTime(DirName, stime, FileTime_Accessed);
}

BOOL FileSys::GetFileModifiedTime(CString DirName, SYSTEMTIME &stime)
{
   return GetFileSystemTime(DirName, stime, FileTime_Modified);
}

BOOL FileSys::GetFileSystemTime(CString DirName, SYSTEMTIME &stime, FileSys::FileTime eTimeType)
{
   BOOL retval = FALSE;
   HANDLE hDir = CreateFile (DirName, GENERIC_READ,
      FILE_SHARE_READ|FILE_SHARE_DELETE,
      NULL, OPEN_EXISTING,
      FILE_FLAG_BACKUP_SEMANTICS, NULL);

   if(!hDir)
   {
	   LOG_ERROR(_T("ErrCode: %d"),GetLastError());
	   return FALSE;
   }

   FILETIME CreationTime;
   FILETIME LastAccessTime;
   FILETIME LastWriteTime;
   if (GetFileTime(hDir, &CreationTime, &LastAccessTime, &LastWriteTime))
   {
      FILETIME* pFileTime = NULL;
      switch(eTimeType)
      {
      case FileTime_Created:
         pFileTime = &CreationTime;
         break;

      case FileTime_Modified:
         pFileTime = &LastWriteTime;
         break;

      case FileTime_Accessed:
         pFileTime = &LastWriteTime;
         break;

      default:
		  LOG_ERROR(_T("Not found error."));
         return FALSE;
      }

      FILETIME ftime;
      FileTimeToLocalFileTime(pFileTime, &ftime); // 转换成本地时间
      FileTimeToSystemTime(&ftime, &stime); // 转换成系统时间格式

      retval = TRUE;
   }
   CloseHandle(hDir);
   return retval;
}

BOOL FileSys::FindEarliestAccessedFile(LPCTSTR lpszDirName, FILETIME& ftLastAccess, CString& strFilePath )
{
   FILETIME minift;
   minift.dwHighDateTime = MAXDWORD;
   minift.dwLowDateTime  = MAXDWORD;
   CString   strTheFilePath;
   CFileFind tempFind; 
   CString sTempFileFind = lpszDirName + CString(_T("\\*.*"));
   BOOL IsFinded = tempFind.FindFile(sTempFileFind); 
   BOOL bRet = FALSE;

   while (IsFinded)
   { 
      IsFinded = tempFind.FindNextFile(); 

      if (!tempFind.IsDots()) 
      { 
         CString sFoundFileName = tempFind.GetFileName();
         if (tempFind.IsDirectory()) 
         { 
            CString sTempDir = lpszDirName + CString(_T("\\")) + sFoundFileName;
            FILETIME ftTemp;
            CString sTempFilePath;

            FindEarliestAccessedFile(sTempDir, ftTemp, sTempFilePath);
            if( sTempFilePath.GetLength()>0 )
            {
               // 比较 FILETIME
               if( ftTemp.dwHighDateTime<minift.dwHighDateTime 
                  ||( ftTemp.dwHighDateTime==minift.dwHighDateTime 
                  && ftTemp.dwLowDateTime<minift.dwLowDateTime ) )
               {
                  minift.dwHighDateTime = ftTemp.dwHighDateTime;
                  minift.dwLowDateTime  = ftTemp.dwLowDateTime;
                  strTheFilePath = sTempFilePath;
                  bRet = TRUE;
               }
            }
         } 
         else 
         { 
            CString sTempFilePath = tempFind.GetFilePath();//lpszDirName + CString(_T("\\")) + sFoundFileName;
            FILETIME ftTemp;
            if( tempFind.GetLastAccessTime(&ftTemp) )
            {
               // 比较 FILETIME
               if( ftTemp.dwHighDateTime<minift.dwHighDateTime 
                  ||( ftTemp.dwHighDateTime==minift.dwHighDateTime 
                  && ftTemp.dwLowDateTime<minift.dwLowDateTime ) )
               {
                  minift.dwHighDateTime = ftTemp.dwHighDateTime;
                  minift.dwLowDateTime  = ftTemp.dwLowDateTime;
                  strTheFilePath = sTempFilePath;
                  bRet = TRUE;
               }
            }
         } 
      } 
   } 
   tempFind.Close(); 

   ftLastAccess = minift;
   strFilePath = strTheFilePath;

   return bRet;
}



BOOL FileSys::DeleteOldestFile(LPCTSTR lpszDirName) 
{ 
   FILETIME ftLastAccess;
   CString  strFilePath;
   if( FindEarliestAccessedFile(lpszDirName, ftLastAccess, strFilePath)
      && strFilePath.GetLength()>0 )
   {
      return DeleteFile(strFilePath.GetString());
   }

   return FALSE;
}

BOOL FileSys::EnumFile( CString dir, CStringList& fileList, BOOL bRecursive, CString filter/*=_T("*")*/ )
{
   dir.TrimRight(_T("/ \\"));
   dir.TrimRight(_T("/ \\"));
   dir.TrimLeft(_T("/ \\"));
   dir.TrimRight(_T("/ \\"));

   if(!FileSys::DirExist(dir))
      return FALSE;


   // list includes
   int iTokenInc=0;
   CStringArray includes;
   CString tokenInc = filter.Tokenize(_T("|"), iTokenInc);
   while( tokenInc!=_T("") )
   {
      includes.Add(tokenInc);
      tokenInc = filter.Tokenize(_T("|"), iTokenInc);
   }


   // find file
   CFileFind finder;
   CString strFinder = dir + _T("\\*.*");
   BOOL bWorking = finder.FindFile(strFinder);
   while(bWorking)   
   {
      bWorking = finder.FindNextFile();

      // is directory
      if( bRecursive && finder.IsDirectory() && !finder.IsDots() )
      {
         CString filename = finder.GetFileName();
         CString path = dir + _T("\\") + filename;
         EnumFile(path, fileList, bRecursive, filter);
      }
      else if(!finder.IsDots())
      {
         CString filename = finder.GetFileName();
         CString extension = GetExtension(filename);
         BOOL bInc=FALSE;
         for(int i=0; i<includes.GetCount(); ++i)
         {
            if(includes.GetAt(i)==_T("*") || extension.CompareNoCase(includes.GetAt(i))==0 )
            {
               filename = dir + _T("\\") + filename;
               fileList.AddTail(filename);
               break;
            }
         }
      }
   }


   finder.Close();
   return TRUE;
}

BOOL FileSys::EnumFolder( CString dir, CStringList& folderPathList, BOOL bRecursive)
{
   dir.TrimRight(_T("/ \\"));
   dir.TrimRight(_T("/ \\"));
   dir.TrimLeft(_T("/ \\"));
   dir.TrimRight(_T("/ \\"));

   if(!FileSys::DirExist(dir))
      return FALSE;


   // find file
   CFileFind finder;
   CString strFinder = dir + _T("\\*.*");
   BOOL bWorking = finder.FindFile(strFinder);
   while(bWorking)   
   {
      bWorking = finder.FindNextFile();

      // is directory
      if( bRecursive && finder.IsDirectory() && !finder.IsDots() )
      {
         CString filename = finder.GetFileName();
         CString path = dir + _T("\\") + filename;
         EnumFolder(path, folderPathList, bRecursive);
      }

      if( finder.IsDirectory() && !finder.IsDots() )
      {
         CString filename = finder.GetFileName();
         CString path = dir + _T("\\") + filename;
         folderPathList.AddTail(path);

         if( bRecursive )
         {
            EnumFolder(path, folderPathList, bRecursive);
         }
      }
         
   }


   finder.Close();
   return TRUE;
}

BOOL FileSys::RmFile( CString filename )
{
   return DeleteFile(filename.GetString());
}

LONGLONG FileSys::GetTimeSpanMilliSeconds( const SYSTEMTIME& st1, const SYSTEMTIME& st2 )
{
   FILETIME ft1, ft2;
   if( SystemTimeToFileTime(&st1, &ft1) && SystemTimeToFileTime(&st2, &ft2))
   {
      LONGLONG llHundredNano = (*(LONGLONG*)&ft2) - (*(LONGLONG*)&ft1);
      return llHundredNano/10/1000;
   }
   return 0;
}

LONGLONG FileSys::GetTimeSpanSeconds( const SYSTEMTIME& st1, const SYSTEMTIME& st2 )
{
   return GetTimeSpanMilliSeconds(st1, st2)/1000;
}

LONGLONG FileSys::GetTimeSpanMinutes( const SYSTEMTIME& st1, const SYSTEMTIME& st2 )
{
   return GetTimeSpanSeconds(st1, st2)/60;
}

LONGLONG FileSys::GetTimeSpanHours( const SYSTEMTIME& st1, const SYSTEMTIME& st2 )
{
   return GetTimeSpanMinutes(st1,st2)/60;
}

int FileSys::GetTimeSpanDays( const SYSTEMTIME& st1, const SYSTEMTIME& st2 )
{
   return (int)(GetTimeSpanHours(st1,st2)/24);
}

int FileSys::GetTimeSpanWeeks( const SYSTEMTIME& st1, const SYSTEMTIME& st2 )
{
   return GetTimeSpanDays(st1,st2)/7;
}

int FileSys::GetTimeSpanYears( const SYSTEMTIME& st1, const SYSTEMTIME& st2 )
{
   return GetTimeSpanDays(st1,st2)/365;
}

void FileSys::RemoveOldFolder( LPCTSTR lpszDirName, FileTime eTimeType, UINT nSecondsBeforeNow/*=0*/, LPCTSTR filterExc/*=_T("")*/ )
{
   CStringList folderPathList;
   if( EnumFolder(lpszDirName, folderPathList, FALSE) )
   {
      SYSTEMTIME stNow;
      GetLocalTime(&stNow);
      POSITION pos = folderPathList.GetHeadPosition();
      for(; pos!=NULL; )
      {
         CString& strFolderPath = folderPathList.GetNext(pos);
         SYSTEMTIME stime;
         if(GetFileSystemTime(strFolderPath, stime, eTimeType) && GetTimeSpanSeconds(stime, stNow)>nSecondsBeforeNow)
         {
            RmDir(strFolderPath, filterExc, FALSE);
         }

         //CString str;
         //str.Format(_T("%s: %d-%d-%d"), strFolderPath, stime.wMonth, stime.wDay, stime.wHour);
         //AfxMessageBox(str);
      }
   }
}

void FileSys::RemoveOldFolderByCreationTime( LPCTSTR strDirName, UINT nSecondsBeforeNow/*=0*/, LPCTSTR filterExc/*=_T("")*/ )
{
   RemoveOldFolder(strDirName, FileTime_Created, nSecondsBeforeNow, filterExc);
}

void FileSys::RemoveOldFolderByAccessedTime( LPCTSTR strDirName, UINT nSecondsBeforeNow/*=0*/, LPCTSTR filterExc/*=_T("")*/ )
{
   RemoveOldFolder(strDirName, FileTime_Accessed, nSecondsBeforeNow, filterExc);
}

void FileSys::RemoveOldFolderByModifiedTime( LPCTSTR strDirName, UINT nSecondsBeforeNow/*=0*/, LPCTSTR filterExc/*=_T("")*/ )
{
   RemoveOldFolder(strDirName, FileTime_Modified, nSecondsBeforeNow, filterExc);
}

void FileSys::RemoveOldFile( LPCTSTR lpszDir, FileTime eTimeType, UINT nSecondsBeforeNow/*=0*/, LPCTSTR filterInc/*=_T("*")*/, LPCTSTR filterExc/*=_T("")*/ )
{
   CStringList filePathList;
   if( EnumFile(lpszDir, filePathList, FALSE, filterInc) )
   {
      SYSTEMTIME stNow;
      GetLocalTime(&stNow);
      POSITION pos = filePathList.GetHeadPosition();
      for(; pos!=NULL; )
      {
         CString& strFilePath = filePathList.GetNext(pos);
         SYSTEMTIME stime;
         if(GetFileSystemTime(strFilePath, stime, eTimeType) && GetTimeSpanSeconds(stime, stNow)>nSecondsBeforeNow)
         {
            RmFile(strFilePath);
         }
      }
   }
}

void FileSys::RemoveOldFileByCreationTime( LPCTSTR lpszDir, UINT nSecondsBeforeNow/*=0*/, LPCTSTR filterInc/*=_T("*")*/, LPCTSTR filterExc/*=_T("")*/ )
{
   RemoveOldFile(lpszDir, FileTime_Created, nSecondsBeforeNow, filterInc, filterExc);
}

void FileSys::RemoveOldFileByAccessedTime( LPCTSTR lpszDir, UINT nSecondsBeforeNow/*=0*/, LPCTSTR filterInc/*=_T("*")*/, LPCTSTR filterExc/*=_T("")*/ )
{
   RemoveOldFile(lpszDir, FileTime_Accessed, nSecondsBeforeNow, filterInc, filterExc);
}

void FileSys::RemoveOldFileByModifiedTime( LPCTSTR lpszDir, UINT nSecondsBeforeNow/*=0*/, LPCTSTR filterInc/*=_T("*")*/, LPCTSTR filterExc/*=_T("")*/ )
{
   RemoveOldFile(lpszDir, FileTime_Modified, nSecondsBeforeNow, filterInc, filterExc);
}

void FileSys::SetCurrentDir( const CString& path )
{
	SetCurrentDirectory(path);
}

DWORD FileSys::GetFileSize( CString filename )
{
   LARGE_INTEGER liFilesize;
   liFilesize.QuadPart = 0;
   _GetFileSize64(filename, &liFilesize);
   return (DWORD)liFilesize.QuadPart;
}

void MsgBox( int i )
{
   CString str;
   str.Format(_T("%d"),i);
   AfxMessageBox(str);
}

void MsgBox( UINT ui )
{
   CString str;
   str.Format(_T("%u"),ui);
   AfxMessageBox(str);
}
