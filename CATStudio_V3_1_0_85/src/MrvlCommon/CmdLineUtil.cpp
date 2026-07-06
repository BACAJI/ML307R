#include "StdAfx.h"
#include "CmdLineUtil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CCriticalSection CCmdLineInfo::m_Lock;
CCmdLineInfo* CCmdLineInfo::m_pInstance=NULL;

CCmdLineInfo::CCmdLineInfo()
{

}

CCmdLineInfo::~CCmdLineInfo()
{

}


CString CmdLine_GetIniPath( LPCTSTR lpszCmdLineString)
{
   if( lpszCmdLineString==NULL )
   {
      lpszCmdLineString = GetCommandLine();//LPTSTR
   }

   CStringW CmdLineStrW(lpszCmdLineString);
   int      nArgs  = 0;
   LPWSTR*  lpArgs = CommandLineToArgvW(CmdLineStrW, &nArgs);

   for(int i=0; i<nArgs; ++i)
   {
      CString str( lpArgs[i] );
      if( (str==_T("--c") || str==_T("-c")) && i+1<nArgs)
      {
         CStringW strIniPathW = CStringW( lpArgs[i+1] );
         CString  strIniPath (strIniPathW);
         return strIniPath;
      }
   }

   return NULL;
}

void CCmdLineInfo::ParseParam( LPCTSTR lpszParam, BOOL bFlag, BOOL bLast )
{
   if( bFlag )
   {
      if( lpszParam[0]=='c' || lpszParam[0]=='C' )
      {
         ++lpszParam;
         ++lpszParam;
//          CString str = lpszParam;
//          str.AppendFormat(_T("___bFLag%s__bLast%s"), bFlag?_T("TRUE"):_T("FALSE"), bLast?_T("TRUE"):_T("FALSE") );
//          AfxMessageBox(str);
         m_strIniPath = lpszParam;
         int idx = max( m_strIniPath.ReverseFind('\\'), m_strIniPath.ReverseFind('/')) ;
         if( idx>0 ) 
            m_strIniDirectory = m_strIniPath.Left(idx);
      }
      else
      {
//          CString str = lpszParam;
//          str.AppendFormat(_T("++++bFLag%s+++bLast%s"), bFlag?_T("TRUE"):_T("FALSE"), bLast?_T("TRUE"):_T("FALSE") );
//          AfxMessageBox(str);
         CCommandLineInfo::ParseParam(lpszParam,bFlag,bLast);
      }

   }
   else
   {
      CCommandLineInfo::ParseParam(lpszParam,bFlag,bLast);
//       CString str = lpszParam;
//       str.AppendFormat(_T("===bFLag%s===bLast%s"), bFlag?_T("TRUE"):_T("FALSE"), bLast?_T("TRUE"):_T("FALSE") );
//       AfxMessageBox(str);
//       m_strIniPath = lpszParam;
   }
}



CCmdLineInfo* CCmdLineInfo::Instance()
{
   if( m_pInstance )
      return m_pInstance;

   m_Lock.Lock();
   if( !m_pInstance )
   {
      m_pInstance = new CCmdLineInfo();
   }

   m_Lock.Unlock();

   return m_pInstance;
}  

CString CCmdLineInfo::GetCfgFilePath()
{
   return m_strIniPath;
}

CString CCmdLineInfo::GetWorkingDirectory()
{
   return m_strWorkingDir;
}

CString CCmdLineInfo::GetCfgFileDirectory()
{
   return m_strIniDirectory;
}
