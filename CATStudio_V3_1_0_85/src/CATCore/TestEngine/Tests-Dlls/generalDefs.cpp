/*--------------------------------------------------------------------------------------*
| (C) Copyright 2006,2007 Marvell Semiconductor Israel Ltd. All Rights Reserved		|
*--------------------------------------------------------------------------------------*/

//////////////////////////////////////////////////////////////////////
/////generalDefs.cpp  - includes the necessary includes for the tests/
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "generalDefs.h"

//////////////////////
/////Globals here/////
//////////////////////
/*DWORD g_tlsIndex = 0;*/
CConfigFile				IniFile;

// LPVOID GetParams()
// {
// 	
// 	return TlsGetValue(g_tlsIndex);
// 	/*return CThreadLocalDataInterface::Instance()->GetValue();*/
// }

void InitializeParams(TestInterface *ti)
{
	
	CThreadLocalDataInterface::SetData(ti);
	/*TlsSetValue(g_tlsIndex,(LPVOID)ti);*/
	// find the ini file.
	CString path = CString(CTestEngine::FindDirectory());
	path += "\\Tests-Dlls\\tests.ini";

	IniFile.Read(path);
};


void UpdateIniFile()
{
	// find the ini file.
	CString path = CString(CTestEngine::FindDirectory());
	path += "\\Tests-Dlls\\tests.ini";

	IniFile.Write(path);
}



/**************************************************************************
This function calculates (and returns) the interval between to SYSTEMTIME
structures. The result will be in milli-firsts. The internal must not be more
than 24 hours or else the function will return an incorrect calculation.
/**************************************************************************/
UINT GetIntervalTime(SYSTEMTIME &first, SYSTEMTIME &second)
{
	UINT interval = 0;
	BOOL carry = FALSE;

	if (second.wMilliseconds >= first.wMilliseconds)
		interval += second.wMilliseconds - first.wMilliseconds;
	else
	{
		interval += 1000 + second.wMilliseconds - first.wMilliseconds;
		carry = TRUE;
	}

	if (carry)
	{
		if (second.wSecond > 0)
		{
			second.wSecond--;
			carry = FALSE;
		}
		else
			second.wSecond = 59;
	}

	if (second.wSecond >= first.wSecond)
		interval += (second.wSecond - first.wSecond) *1000;
	else
	{
		interval += (60 + second.wSecond - first.wSecond) *1000;
		carry = TRUE;
	}

	if (carry)
	{
		if (second.wMinute > 0)
		{
			second.wMinute--;
			carry = FALSE;
		}
		else
			second.wMinute = 59;
	}

	if (second.wMinute >= first.wMinute)
		interval += (second.wMinute - first.wMinute) *60000;
	else
	{
		interval += (60 + second.wMinute - first.wMinute) *60000;
		carry = TRUE;
	}

	if (carry)
	{
		if (second.wHour > 0)
		{
			second.wHour--;
			carry = FALSE;
		}
		else
			second.wHour = 23;
	}

	if (second.wHour >= first.wHour)
		interval += (second.wHour - first.wHour) *1440000;
	else
	{
		interval += (24 + second.wHour - first.wHour) *1440000;
		carry = TRUE;
	}

	return interval;
}


extern "C" __declspec(dllexport) bool IsDebugDLL()
{
#ifdef _DEBUG
	return true;
#else 
	return false;
#endif
}