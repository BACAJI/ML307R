#pragma once
#include "tm_t.h"

static const TCHAR* UERatTypeString[]={_T("N/A"), _T("LWG"), _T("LTG"), _T("WG"), _T("TG")};
static const TCHAR* SIMTypeString[]={_T("N/A"), _T("SSSS"), _T("DSDS"), _T("DSDL")};
static const TCHAR* BoardVersionString[]={_T("N/A"), _T("MIFI"), _T("Dongle"), _T("LT02 R0.3")};



struct SUeCpInfo
{
   long  i32Version;
   char  i8UeRatType; // 0=N/A, 1=LWG, 2=LTG, 3=WG, 4=TG
   char  i8SimType; // 0= N/A, 1=SSSS, 2=DSDS, 3=DSDL
   char  i8Reserved1;
   char  i8Reserved2;
   long  Reserved3;
   long  Reserved4;
   char  szCpVersion[64];
   char  szMsaVersion[64];
   char  szBoardVersion[64]; // "" = N/A, "MIFI", "Dongle", "LT02 R0.3"
   char  szPlatformStream[32]; // ¡°¡±= N/A, ¡°HE_LWG_Dev¡±, ¡°HE_LWG_MOGG¡±, ¡°HE_LTG_DSDS_OT¡±
   char  szProtocolStream[32]; // ¡°¡±= N/A, ¡°LTE_W_PS¡±, ¡°LTE_PS_DS_CSFB¡±, ¡°LTE_W_PS_MOGG¡±
   char  szMsaStream[32]; // ¡°¡±= N/A, ¡°NeZha_5MD¡±, ¡°NeZha_5MD_MOGG¡±, ¡°Nezha_LTG¡±
   tm_t  tmSystemTime;
   DWORD dwTargetTs;
};

class CUeCpInfo
{
public:
   CUeCpInfo(){};
   CUeCpInfo(const SUeCpInfo& UeCpInfo)
   {
      m_i32Version = UeCpInfo.i32Version;
      m_strUeRatType =  (UeCpInfo.i8UeRatType>=0 && UeCpInfo.i8UeRatType<=4)? UERatTypeString[UeCpInfo.i8UeRatType]:_T("N/A");
      m_strSimType =  (UeCpInfo.i8SimType>=0 && UeCpInfo.i8SimType<=3)? SIMTypeString[UeCpInfo.i8SimType]:_T("N/A");
      m_strCpVersion = CString((LPCSTR)UeCpInfo.szCpVersion);
      m_strMsaVersion = CString((LPCSTR)UeCpInfo.szMsaVersion);
      m_strBoardVersion = (UeCpInfo.szBoardVersion[0]==0)? _T("N/A"):CString((LPCSTR)UeCpInfo.szBoardVersion);
      m_strPlatformStream = (UeCpInfo.szPlatformStream[0]==0)? _T("N/A"):CString((LPCSTR)(UeCpInfo.szPlatformStream));
      m_strProtocolStream = (UeCpInfo.szProtocolStream[0]==0)? _T("N/A"):CString((LPCSTR)(UeCpInfo.szProtocolStream));
      m_strMsaStream     = (UeCpInfo.szMsaStream[0]==0)? _T("N/A"):CString((LPCSTR)(UeCpInfo.szMsaStream));
      m_tmSystemTime = UeCpInfo.tmSystemTime;
      m_dwTargetTs = UeCpInfo.dwTargetTs;
   }

   long     m_i32Version;
   CString  m_strUeRatType;
   CString  m_strSimType;
   CString  m_strCpVersion;
   CString  m_strMsaVersion;
   CString  m_strBoardVersion;
   CString  m_strPlatformStream;
   CString  m_strProtocolStream;
   CString  m_strMsaStream;
   tm_t     m_tmSystemTime;
   DWORD    m_dwTargetTs;
};