#ifndef GENERAL_FUNCTIONS_H
#define GENERAL_FUNCTIONS_H

/*--------------------------------------------------------------------------------------------------------------------

 (C) Copyright 2006,2007 Marvell Semiconductor Israel Ltd. All Rights Reserved  

-------------------------------------------------------------------------------------------------------------------*/


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define TRACE_LOGGER_ENABLED
#define WM_ICAT_MESSAGE		WM_USER+245
#include "GeneralMacroDefine.h"

//IFLVC9_Inc_Export_H_Begin************************************
//#include "..\IFLExport.h" 
//IFLVC9_Inc_Export_H_End**************************************

extern "C" int CATCORE_DLLEXPORT hexatoi(char* str);

#ifdef TRACE_LOGGER_ENABLED
#define DBGLOG_4U32(u32Id, u32Data0,u32Data1,u32Data2,u32Data3) ZdlLog4U32(u32Id, u32Data0,u32Data1,u32Data2,u32Data3)
#define DBGLOG_TEXT(kszLog) ZdlLogText(kszLog)
#define DBGLOG_BUF(u32Id, kpu8Log, u32Len) ZdlLogBuf(u32Id, kpu8Log, u32Len)
#else
#define DBGLOG_4U32(u32Id, u32Data0,u32Data1,u32Data2,u32Data3) 
#define DBGLOG_TEXT(kszLog) 
#define DBGLOG_BUF(u32Id, kpu8Log, u32Len) 
#endif


//ACAT_DEBUG_COMM
#define COMM_TRACE_LOGGER_ENABLED
#ifdef COMM_TRACE_LOGGER_ENABLED
#define COMM_TRACE_LOG(szLog) AppendTraceLog(szLog)
#define COMM_DBGLOG_4U32(u32Id, u32Data0,u32Data1,u32Data2,u32Data3) ZdlLog4U32(u32Id, u32Data0,u32Data1,u32Data2,u32Data3)
#define COMM_DBGLOG_TEXT(kszLog) ZdlLogText(kszLog)
#define COMM_DBGLOG_BUF(u32Id, kpu8Log, u32Len) ZdlLogBuf(u32Id, kpu8Log, u32Len)
#else
#define COMM_TRACE_LOG(szLog) 
#define COMM_DBGLOG_4U32(u32Id, u32Data0,u32Data1,u32Data2,u32Data3) 
#define COMM_DBGLOG_TEXT(kszLog) 
#define COMM_DBGLOG_BUF(u32Id, kpu8Log, u32Len) 
#endif

//ACAT_DEBUG_MC
#define MC_TRACE_LOGGER_ENABLED
#ifdef MC_TRACE_LOGGER_ENABLED
#define MC_TRACE_LOG(szLog) AppendTraceLog(szLog)
#define MC_DBGLOG_4U32(u32Id, u32Data0,u32Data1,u32Data2,u32Data3) ZdlLog4U32(u32Id, u32Data0,u32Data1,u32Data2,u32Data3)
#define MC_DBGLOG_TEXT(kszLog) ZdlLogText(kszLog)
#define MC_DBGLOG_BUF(u32Id, kpu8Log, u32Len) ZdlLogBuf(u32Id, kpu8Log, u32Len)
#else
#define MC_TRACE_LOG(szLog) 
#define MC_DBGLOG_4U32(u32Id, u32Data0,u32Data1,u32Data2,u32Data3) 
#define MC_DBGLOG_TEXT(kszLog) 
#define MC_DBGLOG_BUF(u32Id, kpu8Log, u32Len) 
#endif


//ACAT_DEBUG_TE
#define TE_TRACE_LOGGER_ENABLED
#ifdef TE_TRACE_LOGGER_ENABLED
#define TE_TRACE_LOG(szLog) AppendTraceLog(szLog)
#define TE_DBGLOG_4U32(u32Id, u32Data0,u32Data1,u32Data2,u32Data3) ZdlLog4U32(u32Id, u32Data0,u32Data1,u32Data2,u32Data3)
#define TE_DBGLOG_TEXT(kszLog) ZdlLogText(kszLog)
#define TE_DBGLOG_BUF(u32Id, kpu8Log, u32Len) ZdlLogBuf(u32Id, kpu8Log, u32Len)
#else
#define TE_TRACE_LOG(szLog) 
#define TE_DBGLOG_4U32(u32Id, u32Data0,u32Data1,u32Data2,u32Data3) 
#define TE_DBGLOG_TEXT(kszLog) 
#define TE_DBGLOG_BUF(u32Id, kpu8Log, u32Len) 
#endif

//ACAT_DEBUG_FE
#define FE_TRACE_LOGGER_ENABLED
#ifdef FE_TRACE_LOGGER_ENABLED
#define FE_TRACE_LOG(szLog) AppendTraceLog(szLog)
#define FE_DBGLOG_4U32(u32Id, u32Data0,u32Data1,u32Data2,u32Data3) ZdlLog4U32(u32Id, u32Data0,u32Data1,u32Data2,u32Data3)
#define FE_DBGLOG_TEXT(kszLog) ZdlLogText(kszLog)
#define FE_DBGLOG_BUF(u32Id, kpu8Log, u32Len) ZdlLogBuf(u32Id, kpu8Log, u32Len)
#else
#define FE_TRACE_LOG(szLog) 
#define FE_DBGLOG_4U32(u32Id, u32Data0,u32Data1,u32Data2,u32Data3) 
#define FE_DBGLOG_TEXT(kszLog) 
#define FE_DBGLOG_BUF(u32Id, kpu8Log, u32Len) 
#endif

#endif
