#pragma once


#ifdef _CATCORE_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT 
#endif

class DLL_EXPORT TimeUtil
{
public:
   TimeUtil(void);
   ~TimeUtil(void);

   static time_t s_timezoneBiasSec;

   static time_t GetTimezoneBiasSec();
   static void   TimetToSystemTime(time_t t, LPSYSTEMTIME pst);
   static void   TimetToLocalTime(time_t t, SYSTEMTIME& localTime);
   static void   TimetToFileTime(time_t t, LPFILETIME pft);
   static void   SystemTimeToTimet(const SYSTEMTIME& st, time_t *pt);
   static void   SystemTimeToLocalTime(const SYSTEMTIME& stUTC, SYSTEMTIME& stLocal);
   static void   SystemTimeToLocalTime2(const SYSTEMTIME& stUTC, SYSTEMTIME& stLocal);
   static void   SystemTimeToLocalTime(time_t utcTimet, SYSTEMTIME& stLocal);
   static time_t UTCTime_tToLocalTime_t(time_t utcTime_t);

};
