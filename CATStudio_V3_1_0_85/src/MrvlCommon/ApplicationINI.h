#ifndef _APPLICATION_INI_
#define _APPLICATION_INI_
#pragma once

#include "ConfigFile.h"
#include "singletondestroyer.h"

#ifdef _CATCORE_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT 
#endif
class DLL_EXPORT CApplicationINI : public CConfigFile  
{
public:
	static CApplicationINI * Instance(LPCTSTR lpszIniName=NULL);

private:
   static CApplicationINI *m_pThis;
   CApplicationINI(LPCTSTR lpszIniName=NULL);
   virtual ~CApplicationINI();
   static CSingletonDestroyer<CApplicationINI> m_Destroyer;
   friend class CSingletonDestroyer<CApplicationINI>;

   CString m_sAppIniPath;
   CString m_sAppPath;
   CString m_sAppDBPath;

public:
   UINT      GetProfileInt(LPCTSTR lpszSection, LPCTSTR lpszEntry, int nDefault);
   BOOL      WriteProfileInt(LPCTSTR lpszSection, LPCTSTR lpszEntry, int nValue);
   CString   GetProfileString(LPCTSTR lpszSection, LPCTSTR lpszEntry, LPCTSTR lpszDefault = NULL);
   BOOL      WriteProfileString(LPCTSTR lpszSection, LPCTSTR lpszEntry, LPCTSTR lpszValue);
   BOOL      FlushData();
   CString   GetAppDBPath();
   CString   GetAppPath();

};

#define AppIni			CApplicationINI::Instance
#define AppPath		CApplicationINI::Instance()->GetAppPath
#define AppDBPath	   CApplicationINI::Instance()->GetAppDBPath
#endif
