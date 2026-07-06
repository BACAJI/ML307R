#include "StdAfx.h"
#include "PerfCounter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

PerfCounter::PerfCounter(int cn)
{
   m_StartCounter = new LARGE_INTEGER[cn];
   m_EndCounter = new LARGE_INTEGER[cn];
   m_cn = cn;
   QueryPerformanceFrequency(&m_PerfFreq);
}

PerfCounter::~PerfCounter(void)
{
	if(m_StartCounter)
		delete []m_StartCounter;
	m_StartCounter=NULL;
	if(m_EndCounter)
		delete []m_EndCounter;
	m_EndCounter=NULL;
}

void PerfCounter::Start( int i/*=0*/ )
{
   if(i>=m_cn)
   {
      ASSERT(FALSE);
      return;
   }

   QueryPerformanceCounter(&m_StartCounter[i]);
}

void PerfCounter::Stop( int i/*=0*/ )
{
   if(i>=m_cn)
   {
      ASSERT(FALSE);
      return;
   }
   QueryPerformanceCounter(&m_EndCounter[i]);
}

UINT PerfCounter::GetSecond( int i/*=0*/ )
{
   return GetMicro(i)/1000/1000;
}

UINT PerfCounter::GetMilli( int i/*=0*/ )
{
   return GetMicro(i)/1000;
}

UINT PerfCounter::GetMicro( int i/*=0*/ )
{
   if(i>=m_cn)
   {
      ASSERT(FALSE);
      return 0;
   }
   LARGE_INTEGER li;
   li.QuadPart = m_EndCounter[i].QuadPart-m_StartCounter[i].QuadPart;
   li.QuadPart = li.QuadPart/(m_PerfFreq.QuadPart/1000/1000);
   return (UINT)li.QuadPart;
}

CString PerfCounter::GetSecondString( int i/*=0*/ )
{
   CString str;
   str.Format(_T("%d"), GetSecond(i));
   return str;
}

CString PerfCounter::GetMilliString( int i/*=0*/ )
{
   CString str;
   str.Format(_T("%d"), GetMilli(i));
   return str;
}

CString PerfCounter::GetMicroString( int i/*=0*/ )
{
   CString str;
   str.Format(_T("%d"), GetMicro(i));
   return str;
}

CString PerfCounter::GetMilliMicroString( int i/*=0*/ )
{
   CString str;
   UINT nMicro = GetMicro(i);
   str.Format(_T("%d.%d"), nMicro/1000, nMicro%1000);
   return str;
}

double PerfCounter::Compare( int i, int j )
{
   UINT nMicro1 = GetMicro(i);
   UINT nMicro2 = GetMicro(j);
   if(nMicro2==0) return 0;
   return nMicro1/(double)nMicro2;
}
