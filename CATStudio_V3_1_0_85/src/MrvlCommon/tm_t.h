#pragma once

struct tm_t
{
   UINT32 tm_uSec;
   UINT32 tm_sec;
   UINT32 tm_min;
   UINT32 tm_hour;
   UINT32 tm_mday;
   UINT32 tm_mon;
   UINT32 tm_year;
   UINT32 tm_wday;
   UINT32 tm_yday;
   UINT32 tm_isdst;
   UINT32 tm_zone;
};