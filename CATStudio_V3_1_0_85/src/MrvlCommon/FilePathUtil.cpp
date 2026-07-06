#include "stdafx.h"
#include "FilePathUtil.h"



/** @brief Copy a file or a folder to a directory
 * 
 * 
 * @param  strSrcFile Could be a directory.
 * @param  strDestDir 
 * @return 
 * @see 
 * @note 
 */
BOOL CopyFileToDir( CString strSrcFile, CString strDestDir )
{
   if( !IsFileExists(strSrcFile) )
   {
      return FALSE;
   }

   if( !IsDirExists(strDestDir) && !MakeSureDirExists(strDestDir) )
   {
      return FALSE;
   }

   CString strFilename = GetNameInPath(strSrcFile);

   BOOL bRes = ::CopyFile(strSrcFile, strDestDir+_T("\\")+strFilename, NULL); 

   return bRes;
}

BOOL MoveFileToDir( CString strSrcFile, CString strDestDir )
{
   if( !IsFileExists(strSrcFile) )
   {
      return FALSE;
   }

   if( !IsDirExists(strDestDir) && !MakeSureDirExists(strDestDir) )
   {
      return FALSE;
   }

   CString strFilename = GetNameInPath(strSrcFile);
   
   BOOL bRes = ::MoveFileEx(strSrcFile, strDestDir+_T("\\")+strFilename, MOVEFILE_COPY_ALLOWED|MOVEFILE_WRITE_THROUGH|MOVEFILE_REPLACE_EXISTING);
   
   return bRes;
}

void CopyFiles(CString strSrcDir, CString strDstDir, CString strFilter, BOOL bRecursive, CStringList* pListCopied, CStringList* pListFailed)
{
   int numSuccess=0, numFailed=0;
   CopyMoveFiles(strSrcDir, strDstDir, strFilter, bRecursive, FALSE, numSuccess, numFailed, pListCopied, pListFailed);
}

void MoveFiles(CString strSrcDir, CString strDstDir, CString strFilter, BOOL bRecursive, CStringList* pListMoved, CStringList* pListFailed)
{
   int numSuccess=0, numFailed=0;
   CopyMoveFiles(strSrcDir, strDstDir, strFilter, bRecursive, TRUE, numSuccess, numFailed, pListMoved, pListFailed);
   if( numFailed==0 )
   {
      if( strFilter==_T("*") || strFilter==_T("*.*") )
      {
         DeleteEntireDir(strSrcDir);
      }
   }
}


void CopyMoveFiles(CString strSrcDir, CString strDstDir, CString strFilter, BOOL bRecursive, BOOL bMove, int& numSuccess, int& numFailed, CStringList* pListSuccess, CStringList* pListFailed)
{
   strSrcDir.TrimRight(_T("/ \\"));
   strDstDir.TrimRight(_T("/ \\"));
   strFilter.TrimLeft(_T("/ \\"));
   strFilter.TrimRight(_T("/ \\"));

   int  nCopied = 0;
   int  nFailed = 0;
   CFileFind finder;
   CString strFinder;
   if( strFilter.GetLength()==0 )
      strFinder = strSrcDir;
   else
      strFinder = strSrcDir+_T("\\") + strFilter ;

   BOOL bWorking = finder.FindFile(strFinder);
   while(bWorking)   
   {
      bWorking = finder.FindNextFile();
      CString strDstFilePath = strDstDir + _T("\\") + finder.GetFileName();

      if(!finder.IsDirectory())
      {
         BOOL ok;
         if( bMove )
         {
            ok = ::MoveFileEx(finder.GetFilePath(), strDstFilePath, MOVEFILE_COPY_ALLOWED|MOVEFILE_WRITE_THROUGH|MOVEFILE_REPLACE_EXISTING);
         }
         else
         {
            ok = ::CopyFile(finder.GetFilePath(), strDstFilePath, FALSE);
         }

         if( ok )
         {
            ++numSuccess;
            if( pListSuccess )
               pListSuccess->AddTail( strDstFilePath /*finder.GetFilePath()*/ );
         }
         else
         {
            ++numFailed;
            if( pListFailed )
               pListFailed->AddTail( finder.GetFilePath() );
         }
      }
      else if( bRecursive )
      {
         if(finder.GetFileName().Compare(_T(".")) == 0 ||
            finder.GetFileName().Compare(_T("..")) == 0 )
         {
            continue;
         }

         CreateDirectory(strDstFilePath, NULL);
         CopyMoveFiles(finder.GetFilePath(), strDstFilePath, strFilter, bRecursive, bMove, numSuccess, numFailed, pListSuccess, pListFailed);
      } 
      else
      {
         continue;
      }
   }

   return;
}

BOOL CopyFolder( CString strSrcFolder, CString strTarDir)
{
   return CopyMoveFolder(strSrcFolder, strTarDir, FALSE);
}

BOOL MoveFolder( CString strSrcFolder, CString strTarDir)
{
   if( CopyMoveFolder(strSrcFolder, strTarDir, TRUE) )
   {
      DeleteEntireDir(strSrcFolder);
      return TRUE;
   }

   return FALSE;
}

// copy folder, if src folder not exist return false
// if dest folder not exist, create it
BOOL CopyMoveFolder( CString strSrcFolder, CString strTarDir, BOOL bMove)
{ 
   if( !IsDirExists(strSrcFolder) )
   {
      return FALSE;
   }

   if( !MakeSureDirExists( strTarDir ) )
   {
      return FALSE;
   }


   CFileFind finder; 
   BOOL bWorking = finder.FindFile(strSrcFolder+_T("\\*.*") );
   while(bWorking)   
   {
      bWorking = finder.FindNextFile();
      CString strTarFile = strTarDir + _T("\\") + finder.GetFileName();
      if(!finder.IsDirectory())
      {
         BOOL ok;
         if( bMove )
         {
            ok = ::MoveFileEx(finder.GetFilePath(), strTarFile, MOVEFILE_COPY_ALLOWED|MOVEFILE_WRITE_THROUGH|MOVEFILE_REPLACE_EXISTING);
         }
         else
         {
            ok = CopyFile(finder.GetFilePath(), strTarFile, FALSE);
         }
         
         if(!ok)
            return FALSE;
      }
      else
      {
         if(finder.GetFileName().Compare(_T(".")) == 0 ||
            finder.GetFileName().Compare(_T("..")) == 0 )
         {
            continue;
         }

         strTarFile = strTarDir + _T("\\") + finder.GetFileName();   
         CreateDirectory(strTarFile, NULL);

         if( !CopyMoveFolder(finder.GetFilePath(), strTarFile, bMove) )
         {
            return FALSE;
         }
      } 
   }

   return TRUE;
}


// 
// BOOL CopyFiles( CString strSrcFolder, CString strTarFolder, CString sFilter, CStringArray& strFileList, CString& strError )
// {
//    CFileFind finder;
//    BOOL bMoveFailed=FALSE;
//    BOOL bWorking = finder.FindFile(strSrcFolder + _T("\\") + sFilter);
//    BOOL bNext=FALSE; 
//    while(bWorking )
//    {
//       bNext = finder.FindNextFile();
//       CString strNewLog = strTarFolder + _T("\\") + finder.GetFileName();
//       if ( ! ::MoveFileEx(finder.GetFilePath(), strNewLog, MOVEFILE_COPY_ALLOWED|MOVEFILE_WRITE_THROUGH|MOVEFILE_REPLACE_EXISTING) )
//       {
//          bMoveFailed = TRUE;
//       }
//       else
//       {
//          strFileList.Add(strNewLog);
//       }
// 
//       if( !bNext )
//          break;
//    }
// 
//    finder.Close();
// 
//    if( !bWorking )
//    {
//       strError = _T("Cannot locate log file folder in unzipped files");
//       return FALSE;
//    }
//    else if( bMoveFailed )
//    {
//       strError = _T("Error moving log file to destination directory.\nA file with the same name may be currently open in ACAT or CATStudio.");
//       return FALSE;
//    }
//    else
//    {
//       return TRUE;
//    }
// }





BOOL IsFileExists( CString strFilename )
{
   CFileStatus fStatus;
   if( !CFile::GetStatus(strFilename, fStatus) || (fStatus.m_attribute & CFile::directory ) )
   {
      return FALSE;
   }

   return TRUE;
}

BOOL IsDirExists( CString strDir )
{
   CFileStatus fStatus;
   if( ! CFile::GetStatus(strDir, fStatus) || !(fStatus.m_attribute & CFile::directory ) )
   {
      return FALSE;
   }

   return TRUE;
}


BOOL MakeSureDirExists( CString strDir )
{
   if( IsDirExists(strDir) )
   {
      return TRUE;
   }
   else 
   {
      CString strUpperDir;
      if( !GetUpperDirectory(strDir, strUpperDir) )
         return FALSE;

      if( !MakeSureDirExists(strUpperDir) )
      {
         return FALSE;
      }

      return CreateDirectory(strDir, NULL);
   }

}

BOOL MKDIR( LPCTSTR lpszDir )
{
   return CreateDirectory(lpszDir, NULL);
}


BOOL DeleteEntireDir(const CString &strDir)
{
   CFileFind finder;
   CString strFile;

   BOOL bWorking = finder.FindFile(strDir + _T("\\*"));
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
         catch (CFileException pEx)
         {
            CFileStatus fStatus;
            CFile::GetStatus(strFile, fStatus);
            if ( fStatus.m_attribute & CFile::readOnly )
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
      else//It is Directory
      {
         DeleteEntireDir(finder.GetFilePath());
         ::RemoveDirectory(_T("\\\\?\\") + strDir);
      }
   }

   finder.Close();

   ::RemoveDirectory(strDir);
   DWORD dwErr = GetLastError();

   return(TRUE);
}

BOOL GetUpperDirectory( CString strDir, CString& strUpperDir )
{
   strDir.TrimLeft(' ');
   strDir.TrimRight('\\');
   strDir.TrimRight('/');
   int iIndex = max(strDir.ReverseFind('\\'), strDir.ReverseFind('/') );
   if( iIndex >= 0 )
   {
      strUpperDir = strDir.Left(iIndex);
      return TRUE;
   }
   
   return FALSE;
}

int GetFileCount( CString strDir, CString strFilter, BOOL bRecursive )
{
   CFileFind finder;
   int  nCount=0;
   BOOL bWorking = finder.FindFile(strDir + _T("\\") + strFilter);
   BOOL bNext=FALSE; 
   while(bWorking )
   {
      bNext = finder.FindNextFile();
      
      if( finder.IsDots() )
      {
         //do nothing
      }
      else if(finder.IsDirectory() && bRecursive )
      {
         nCount += GetFileCount( strDir+_T("\\")+finder.GetFileName(), strFilter, bRecursive);
      }
      else
      {
         ++nCount;
      }

      if( !bNext )
         break;
   }

   finder.Close();

   return nCount;
}

BOOL SortFileByCreateTime( CStringList& fileList )
{

   CMap<__time64_t, __time64_t, CString, CString> mapFile;

   POSITION pos = fileList.GetHeadPosition();
   while(pos)
   {
      CFileStatus fStatus;
      CString strPath = fileList.GetNext(pos);
      if ( CFile::GetStatus(strPath, fStatus) )
      {
         __time64_t key = fStatus.m_ctime.GetTime();
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

CString GetNameInPath( CString strFilePath)
{
   strFilePath.TrimLeft(_T("/ \\"));
   strFilePath.TrimRight(_T("/ \\"));
   int iIndex = strFilePath.Find(':');
   if(iIndex>=0)
      strFilePath = strFilePath.Mid(iIndex+1);

   iIndex = max(strFilePath.ReverseFind('\\'), strFilePath.ReverseFind('/') );

   CString strFileName = strFilePath.Mid(iIndex+1);

   return strFileName;
}
