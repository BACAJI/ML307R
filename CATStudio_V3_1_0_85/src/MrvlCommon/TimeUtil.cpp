#include "StdAfx.h"
#include "TimeUtil.h"

time_t TimeUtil::s_timezoneBiasSec= TimeUtil::GetTimezoneBiasSec();

TimeUtil::TimeUtil(void)
{
}

TimeUtil::~TimeUtil(void)
{
}

time_t TimeUtil::GetTimezoneBiasSec()
{
   SYSTEMTIME st1, st2;
   GetSystemTime(&st1);
   GetLocalTime(&st2);
   time_t t1, t2, tdelta;
   SystemTimeToTimet(st1, &t1);
   SystemTimeToTimet(st2, &t2);
   tdelta = t2-t1;
   return tdelta;
}

void TimeUtil::TimetToSystemTime( time_t t, LPSYSTEMTIME pst )
{
   FILETIME ft;
   TimetToFileTime(t, &ft);
   FileTimeToSystemTime(&ft, pst );
}

void TimeUtil::TimetToLocalTime( time_t t, SYSTEMTIME& localTime )
{
   t += s_timezoneBiasSec;
   TimetToSystemTime(t, &localTime);
}

void TimeUtil::SystemTimeToTimet(const SYSTEMTIME& st, time_t *pt )
{
   FILETIME ft;
   SystemTimeToFileTime( &st, &ft );

   LONGLONG ll;

   ULARGE_INTEGER ui;
   ui.LowPart = ft.dwLowDateTime;
   ui.HighPart = ft.dwHighDateTime;

   ll = (((LONGLONG)ft.dwHighDateTime)<<32) + ft.dwLowDateTime;

   *pt = (DWORD)((LONGLONG)(ui.QuadPart - 116444736000000000) / 10000000);
}


void TimeUtil::SystemTimeToLocalTime( const SYSTEMTIME& stUTC, SYSTEMTIME& stLocal )
{
   memset(&stLocal, 0, sizeof(SYSTEMTIME));
   TIME_ZONE_INFORMATION zinfo;
   GetTimeZoneInformation(&zinfo);
   SystemTimeToTzSpecificLocalTime(&zinfo, &stUTC, &stLocal);
}

void TimeUtil::SystemTimeToLocalTime( time_t utcTimet, SYSTEMTIME& stLocal )
{
   time_t localTimet= utcTimet + s_timezoneBiasSec;
   TimetToSystemTime(localTimet, & stLocal);
}


void TimeUtil::SystemTimeToLocalTime2( const SYSTEMTIME& stUTC, SYSTEMTIME& stLocal )
{
   time_t t3;
   SystemTimeToTimet(stUTC, &t3);
   t3 += s_timezoneBiasSec;
   TimetToSystemTime( t3 , &stLocal);
   stLocal.wMilliseconds = stUTC.wMilliseconds;
}

time_t TimeUtil::UTCTime_tToLocalTime_t( time_t utcTime_t )
{
   return utcTime_t + s_timezoneBiasSec;
}

void TimeUtil::TimetToFileTime( time_t t, LPFILETIME pft )
{
   LONGLONG ll = Int32x32To64(t, 10000000) + 116444736000000000;
   pft->dwLowDateTime = (DWORD) ll;
   pft->dwHighDateTime = (DWORD)(ll >> 32);
}


