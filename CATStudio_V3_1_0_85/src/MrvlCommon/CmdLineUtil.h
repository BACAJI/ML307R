#pragma once
#include <Afxmt.h>
#include "GeneralMacroDefine.h"


CString CmdLine_GetIniPath( LPCTSTR lpszCmdLineString=NULL );


class CATCORE_DLLEXPORT CCmdLineInfo : public CCommandLineInfo
{
public:
   static   CCmdLineInfo* Instance();
   static   CCmdLineInfo* m_pInstance;
   static   CCriticalSection m_Lock;
   virtual  ~CCmdLineInfo();

   CString  GetCfgFilePath();
   CString  GetCfgFileDirectory();
   CString  GetWorkingDirectory();


   void     ParseParam(LPCTSTR   lpszParam,   BOOL   bFlag,   BOOL   bLast);
private:
   CCmdLineInfo();
   CString  m_strIniPath;
   CString  m_strIniDirectory;
   CString  m_strWorkingDir;

};