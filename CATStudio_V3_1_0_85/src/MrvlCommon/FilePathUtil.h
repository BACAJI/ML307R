#pragma once
#include "GeneralMacroDefine.h"
#include "imagehlp.h"
#pragma comment(lib, "imagehlp.lib")

BOOL CATCORE_DLLEXPORT CopyFileToDir( CString strSrcFile, CString strDestDir );
BOOL CATCORE_DLLEXPORT MoveFileToDir( CString strSrcFile, CString strDestDir );
void CATCORE_DLLEXPORT CopyFiles(CString strSrcDir, CString strDstDir, CString strFilter, BOOL bRecursive, CStringList* pListCopied, CStringList* pListFailed);
void CATCORE_DLLEXPORT MoveFiles(CString strSrcDir, CString strDstDir, CString strFilter, BOOL bRecursive, CStringList* pListMoved, CStringList* pListFailed);
void CATCORE_DLLEXPORT CopyMoveFiles(CString strSrcDir, CString strDstDir, CString strFilter, BOOL bRecursive, BOOL bMove, int& numSuccess, int& numFailed, CStringList* pListSuccess, CStringList* pListFailed);
BOOL CATCORE_DLLEXPORT CopyFolder( CString strSrcFolder, CString strTarDir);
BOOL CATCORE_DLLEXPORT MoveFolder( CString strSrcFolder, CString strTarDir);
BOOL CATCORE_DLLEXPORT CopyMoveFolder( CString strSrcFolder, CString strTarDir, BOOL bMove);
BOOL CATCORE_DLLEXPORT IsFileExists( CString strFilename );
BOOL CATCORE_DLLEXPORT IsDirExists( CString strDir );
BOOL CATCORE_DLLEXPORT MakeSureDirExists( CString strDir );
BOOL CATCORE_DLLEXPORT MKDIR( LPCTSTR lpszDir );
BOOL CATCORE_DLLEXPORT DeleteEntireDir(const CString &strDir);
BOOL CATCORE_DLLEXPORT GetUpperDirectory( CString strDir, CString& strUpperDir );
int  CATCORE_DLLEXPORT GetFileCount( CString strDir, CString strFilter, BOOL bRecursive );
BOOL CATCORE_DLLEXPORT SortFileByCreateTime(CStringList& fileList);
CString CATCORE_DLLEXPORT GetNameInPath( CString strFilePath);