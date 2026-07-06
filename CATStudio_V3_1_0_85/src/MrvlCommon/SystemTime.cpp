// SystemTime.cpp: implementation of the CSystemTime class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SystemTime.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSystemTime::CSystemTime()
{
}

CSystemTime::~CSystemTime()
{
}
/*
void CSystemTime::operator = (CSystemTime &sysTime)
{
	wYear =	sysTime.wYear;
	wMonth = sysTime.wMonth;
	wDayOfWeek = sysTime.wDayOfWeek;
	wDay = sysTime.wDay;
	wHour =	sysTime.wHour;
	wMinute = sysTime.wMinute;
	wSecond = sysTime.wSecond;
	wMilliseconds = sysTime.wMilliseconds;
}*/




void CSystemTime::Serialize(CArchive &ar)
{
	if (ar.IsStoring())
	{
		ar << wYear;
		ar << wMonth;
		ar << wDayOfWeek;
		ar << wDay;
		ar << wHour;
		ar << wMinute;
		ar << wSecond;
		ar << wMilliseconds;
	}
	else // IsLoading
	{
		ar >> wYear;
		ar >> wMonth;
		ar >> wDayOfWeek;
		ar >> wDay;
		ar >> wHour;
		ar >> wMinute;
		ar >> wSecond;
		ar >> wMilliseconds;
	}
}



void CSystemTime::Serialize(void* pv)
{

	WORD *p	= (WORD*)pv;
	*(p)    = wYear;
	*(p+1)  = wMonth;
	*(p+2)  = wDayOfWeek;
	*(p+3)  = wDay;
	*(p+4)  = wHour;
	*(p+5)  = wMinute;
	*(p+6)  = wSecond;
	*(p+7)  = wMilliseconds;

}