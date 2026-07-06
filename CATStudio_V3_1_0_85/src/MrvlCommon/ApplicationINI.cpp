// ApplicationINI.cpp: implementation of the CApplicationINI class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ApplicationINI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//CString CApplicationINI::m_strIniName;
CApplicationINI * CApplicationINI::m_pThis;
CSingletonDestroyer<CApplicationINI> CApplicationINI::m_Destroyer;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CApplicationINI::CApplicationINI(LPCTSTR lpszIniName)
{
   if( lpszIniName )
   {
      m_sAppIniPath = lpszIniName;
      Read(lpszIniName);
   }
}


CApplicationINI::~CApplicationINI()
{
	FlushData();
	if(this==CApplicationINI::m_pThis)
	{
		CApplicationINI::m_pThis=NULL;
		CApplicationINI::m_Destroyer.Set(NULL);
	}
}


CApplicationINI * CApplicationINI::Instance(LPCTSTR lpszPath)
{
	if (m_pThis == NULL)
	{
		m_pThis = new CApplicationINI(lpszPath);
		m_Destroyer.Set(m_pThis);
	}

	return m_pThis;
}

UINT CApplicationINI::GetProfileInt(LPCTSTR lpszSection, LPCTSTR lpszEntry, int nDefault)
{
	UINT uiVal;
	if ( GetValue(lpszSection, lpszEntry, uiVal) )
		return uiVal;
	return nDefault;
}

BOOL CApplicationINI::WriteProfileInt(LPCTSTR lpszSection, LPCTSTR lpszEntry, int nValue)
{
	return (BOOL)SetValue(lpszSection, lpszEntry, nValue);
}

CString CApplicationINI::GetProfileString(LPCTSTR lpszSection, LPCTSTR lpszEntry, LPCTSTR lpszDefault /*=NULL*/)
{
	CString strVal;
	if ( GetValue(lpszSection, lpszEntry, strVal) )
		return strVal;
		
	return CString(lpszDefault);
}

BOOL CApplicationINI::WriteProfileString(LPCTSTR lpszSection, LPCTSTR lpszEntry, LPCTSTR lpszValue)
{
	return (BOOL)SetValue(lpszSection, lpszEntry, lpszValue);
}


BOOL CApplicationINI::FlushData()
{
   return (BOOL) Write(m_sAppIniPath);
}


CString  CApplicationINI::GetAppDBPath()
{
   if( m_sAppDBPath.IsEmpty() )
   {
       m_sAppDBPath = GetAppPath() + _T("\\DB");
   }

   return m_sAppDBPath;
}

CString  CApplicationINI::GetAppPath()
{
  if ( m_sAppPath.IsEmpty())
  {
     TCHAR szTemp[1024];
     ::GetModuleFileName(GetModuleHandle(_T("CATStudio.exe")), szTemp, 1024);
     m_sAppPath = (const TCHAR*)szTemp;
     int iIndex = m_sAppPath.ReverseFind('\\');
     m_sAppPath = m_sAppPath.Left(iIndex);
  }

  return m_sAppPath;
}