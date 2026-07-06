#pragma once

#include "iptkrecorderstructures.h"
using namespace std;

#pragma region Base_functions

#ifdef __cplusplus 
#define IMLLOGGER_API extern "C" __declspec (dllexport)
#else
#define IMLLOGGER_API __declspec (dllexport)
#endif


IMLLOGGER_API BOOL IMLLogger_StartRecord(const CString & strTargetFile,DWORD dwFileSizeInMB,int iRecordingMode = RECORD_STRESS_NON_CYCLIC,CString &strErrMsg = CString(""), DWORD dwTriggerOpcode = 0x0000,int iTriggerPosition = 0);
IMLLOGGER_API BOOL IMLLogger_StopRecord();
IMLLOGGER_API BOOL IMLLogger_StopRecordAndWait();
IMLLOGGER_API BOOL IMLLogger_AbortRecord();
IMLLOGGER_API BOOL IMLLogger_RecorderSettings(SRecorderAPIParams& RecorderAPIParams,CString &strErrMsg);
//IMLLOGGER_API BOOL IMLLogger_GetLogPath(CString &strLogPath);
