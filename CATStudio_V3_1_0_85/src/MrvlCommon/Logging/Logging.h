//========================================================
// NOTICE: DON NOT modify before making sense of it.
// AUTHOR: Hongliang Zhu
//========================================================
#pragma once
#include <list>
#include <queue>
#include <string>
#include <afxmt.h>
#include <iostream>
#include "HtmlAppender.h"
#include "TxtFileAppender.h"
#include "GeneralMacroDefine.h"



using namespace std;


#ifdef _UNICODE
typedef wstring tstring;
#else
typedef string  tstring;
#endif

#define  INLINE __forceinline

//#define  TIME_STAMP_FORMAT_DATE_TIME

#ifdef _DEBUG
#pragma push_macro("new")
#define new DEBUG_NEW
#endif

//========================================================
// Level
typedef int  LogLevel;
#define LEVEL_OFF    INT_MAX
#define LEVEL_FATAL  50000 
#define LEVEL_ERROR  40000 
#define LEVEL_WARN   30000
#define LEVEL_NOTICE 25000
#define LEVEL_INFO   20000
#define LEVEL_TEST   15000
#define LEVEL_DEBUG  10000 
#define LEVEL_TRACE  5000
#define LEVEL_ALL    0 

const tstring  ksLevelOff   =_T("OFF");
const tstring  ksLevelFatal =_T("FATAL");
const tstring  ksLevelError =_T("ERROR");
const tstring  ksLevelWarn  =_T("WARN");
const tstring  ksLevelNotice =_T("NOTICE");
const tstring  ksLevelInfo  =_T("INFO");
const tstring  ksLevelTest  =_T("TEST");
const tstring  ksLevelDebug =_T("DEBUG");
const tstring  ksLevelTrace =_T("TRACE");
const tstring  ksLevelAll   =_T("ALL");
const tstring  ksLevelUndef =_T("UNDEF");
INLINE  const  tstring& LevelString(LogLevel level) {
  switch( level )
  {
  case LEVEL_OFF:
    return ksLevelOff;

  case LEVEL_FATAL:
    return ksLevelFatal;

  case LEVEL_ERROR:
    return ksLevelError;

  case LEVEL_WARN:
    return ksLevelWarn;

  case LEVEL_NOTICE:
     return ksLevelNotice;

  case LEVEL_INFO:
    return ksLevelInfo;

  case LEVEL_TEST:
     return ksLevelTest;

  case LEVEL_DEBUG:
    return ksLevelDebug;

  case LEVEL_TRACE:
    return ksLevelTrace;

  case LEVEL_ALL:
    return ksLevelAll;

  default:
    return ksLevelUndef;
  }
}


//========================================================
// LogMessage
struct LogMessage
{
  typedef TCHAR ElemType;

  virtual INLINE ~LogMessage(){
      delete[] m_sLogString;
  }

  INLINE LogMessage(size_t nTStrBufLength, LogLevel level)
    : m_nLevel(level) {
    m_nTStrBufLength =  nTStrBufLength;
    m_sLogString = new ElemType[m_nTStrBufLength];
    m_nMessageNumber = InterlockedIncrement(&m_nMessageCounter);
#ifndef LOG_WITHOUT_THREAD_ID
    m_nThreadID = GetCurrentThreadId();
#endif
  }
  INLINE LogMessage(LogLevel level, SYSTEMTIME* timeStamp, TCHAR* msg, int msgLen)
    : m_nLevel(level) {
      m_nTStrLen  = msgLen;
      m_nTStrBufLength =  msgLen+sizeof(TCHAR);
      m_sLogString = new ElemType[m_nTStrBufLength];
      m_sLogString[m_nTStrBufLength-1] = '\0';
      m_nMessageNumber = InterlockedIncrement(&m_nMessageCounter);
      m_timeStamp = * timeStamp;
      memcpy(m_sLogString, msg, m_nTStrBufLength*sizeof(TCHAR));
      m_nLevel = level;
#ifndef LOG_WITHOUT_THREAD_ID
      m_nThreadID = GetCurrentThreadId();
#endif
  }

  INLINE ElemType* Payload(){
    return  m_sLogString;
  }

  INLINE void SetTimeStamp(SYSTEMTIME* lpSystemTime=NULL){
    if( lpSystemTime==NULL )
      GetLocalTime(&m_timeStamp);
    else
      m_timeStamp = *lpSystemTime;
  }

  // return payload capacity in characters
  INLINE int Capacity() {
    return m_nTStrBufLength;
  }

  INLINE void SetLevel(LogLevel level){
    m_nLevel = level;
  }

  INLINE TCHAR* String(){
    return m_sLogString;
  }
  
  INLINE void  ZeroString(){
    m_sLogString=NULL;
  }

  INLINE size_t StringLength(){
    return m_nTStrLen;
  }

  INLINE const tstring& LevelString(){
    return  ::LevelString(m_nLevel);
  }

  INLINE LogLevel GetLevel(){
    return  m_nLevel;
  }

  INLINE void SetStringLength(int nLengthInCharacters){
    m_nTStrLen = nLengthInCharacters;
  }


  INLINE SYSTEMTIME& TimeStamp(){
    return m_timeStamp;
  }

  // buf:  buffer for formatted string
  // bufLen: buffer length in characters
  INLINE int FormatTimeStamp(TCHAR* buf, int bufLen){
        SYSTEMTIME& time=m_timeStamp;

#ifdef TIME_STAMP_FORMAT_DATE_TIME
        int nTCharWritten = _stprintf_s(buf, bufLen, 
           _T("%u/%02u/%02u %02u:%02u:%02u.%03u"), 
           time.wYear, time.wMonth, time.wDay, time.wHour, 
           time.wMinute, time.wSecond, time.wMilliseconds);
#else
        int nTCharWritten = _stprintf_s(buf, bufLen, 
           _T("%02u:%02u:%02u.%03u"), 
           time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);
#endif


        if( nTCharWritten==-1 ) { 
          nTCharWritten = bufLen-1;
          buf[bufLen-1] = '\0';
        }
        return nTCharWritten;
  }

  INLINE void TimeStampToString(tstring& str ){
     TCHAR buf[32];
     int nLen = FormatTimeStamp(buf, 32);
     str.assign(buf,nLen);
  }

  INLINE tstring TimeStampString(){
    TCHAR buf[32];
    int nLen = FormatTimeStamp(buf, 32);
    tstring str;
    str.assign(buf,nLen);
    return str;
  }

  INLINE long GetMessageNumber() {
    return m_nMessageNumber;
  }

  INLINE tstring MessageNumberString() {
    TCHAR buf[16];
    _itot_s(m_nMessageNumber, buf, 16, 10);
    tstring str((const TCHAR*)buf);
    return str;
  }

#ifndef LOG_WITHOUT_THREAD_ID
  INLINE unsigned long GetThreadID() {
    return m_nThreadID;
  }

  INLINE tstring ThreadIDString() {
    TCHAR buf[16];
    _ultot_s(m_nThreadID, buf, 16, 10);
    tstring str((const TCHAR*)buf);
    return str;
  }
#endif

private:
  TCHAR*      m_sLogString;
  LogLevel    m_nLevel;
  SYSTEMTIME  m_timeStamp;
  size_t      m_nTStrBufLength; // In character
  size_t      m_nTStrLen; // In character
  long        m_nMessageNumber;
#ifndef LOG_WITHOUT_THREAD_ID
  unsigned long m_nThreadID;
#endif
  static long m_nMessageCounter;
};


//===============================================================
// Layout
class LogLayout
{

};



//========================================================
// LogMessage queue
// Wrapper around std::queue specialized for LogMessage which adds a Swap
// helper method.
class LogMessageQueue : public std::queue<LogMessage> {
public:
  void Swap(LogMessageQueue* queue){
    c.swap(queue->c); // Calls std::deque::swap.
  }
};


//===============================================================
// Logging class declaration.
// Logging class has an alias : CLog.
// The core of Logging class is two queue and one Run thread: 
// The forst queue is incoming queue,and another is work queue. 
// Incoming queue buffering received log message. 
// Run thread get log message from work queue, and append to 
// destination appender. When work queue is empty, Run thread
// Swap incoming queue and work queue.
// By this way, work queue is lock free. It avoid race condition.
// 
// Usage:
// For example: LOG_FATAL(_T("Connect to server failed. Error code=%u"), GetLastError());
// Use following function to logging a message.
// LOG_TRACE(...) 输入一条TRACE级别的log 信息
// LOG_DEBUG(...)
// LOG_INFO(...)  
// LOG_WARN(...)  
// LOG_ERROR(...) 
// LOG_FATAL(...) 
// LOG_TRACE_IF(condition, ...) 如果condition为true，则输出一条log 信息
// LOG_DEBUG_IF(condition, ...)
// LOG_INFO_IF(condition, ...)
// LOG_WARN_IF(condition, ...)
// LOG_ERROR_IF(condition, ...)
// LOG_FATAL_IF(condition, ...)

// Remarks:
// 在Release模式下，为了减少一些不必要的log信息，Level会设置为WARN级别，
// 在这个级别下，DEBUG 和TRACE级别的消息将会被丢掉。
// 因此向大的循环里面加入Log消息时，请慎重考虑，避免给应用程序增加太多的开销。

// Level 的参考定义：
// FATAL : 会导致程序无法正常运行或错误的结果。(e.g. Connect to server failed.)
// ERROR : 某个执行产生的结果不是期望，但不会影响程序正常运行。
//         (e.g. GetCpVersion failed, UE not response)
// WARN  : (Broadcast message to clients failed, clients may exited.)
// INFO  : 重要的信息  (e.g. Connect server success.)
// DEBUG : 调试程序错误 (e.g. )
// TRACE : 跟踪程序流程 (e.g. )


class CATCORE_DLLEXPORT Logging
{
private:
  Logging();
public:
  ~Logging();
  static Logging* CreateInstance();
  static void     DestroyInstance();
  static void     CopyInstance(Logging* pInstance);
  static Logging* Instance();
  static Logging* m_pInstance;

  bool      InitLogging(LogLevel level, Appender* appender);
  void      FinalizeLogging();
  void      Log(LogLevel level, const TCHAR* from, const TCHAR* format, ...);
  void      SetLevel(LogLevel level) {m_nLogLevel = level;}
  LogLevel  GetLevel(){return m_nLogLevel;};
  size_t    AcceptedCount(){return m_nAccepted;};
  size_t    ReceivedCount(){return m_nReceived;};
  size_t    AppendedCount(){return m_nAppended;};

  
  //  Return a pointer to appender which's refcount is 1.
  static Appender* CreateHtmlAppender(LPCTSTR lpszFilename, 
                                      OldFileDeletionFlag flag=DELETE_OLD_FILE);
  //  Return a pointer to appender which's refcount is 1.
  static Appender* CreateTxtAppender(LPCTSTR lpszFilename, 
                                      OldFileDeletionFlag flag=DELETE_OLD_FILE);
  static UINT ThreadProc(LPVOID lpVoid);

  UINT  ThreadFunc();

private:
  INLINE void Append(LogMessage& message);
  INLINE bool IsAccept(LogLevel level) {return level>=m_nLogLevel;};
  void        Log1(LogLevel level, const TCHAR* from, const TCHAR* format, va_list args );
  Appender*  m_pAppender;
  LogLevel   m_nLogLevel;
  size_t     m_nReceived;
  size_t     m_nAccepted;
  size_t     m_nAppended;
  const size_t m_knMaxStrLen; //in charaters
  tstring    m_strFileName;
  

  volatile bool    m_bTermThread;
  CEvent           m_incomingEvent;
  CEvent           m_quitThreadEvent;
  HANDLE           m_hThread;
  queue<LogMessage>*  m_workQue;
  queue<LogMessage>*  m_incomeQue;
  CCriticalSection m_queLock;
};


typedef Logging     CLog;

#define theLog Logging::Instance

#define LOGGING(level, format, ...) \
  Logging::Instance()->Log(level, NULL, format, ##__VA_ARGS__)

#define LOGGING_FROM(level, from, format, ...) \
   Logging::Instance()->Log(level, from, format, ##__VA_ARGS__)


#define LOGEX   LOGGING_FROM
#define LOG     LOGEX

#define WSTRX(x) L ## #x
#define WSTR(x) WSTRX(x)
#define STRX(x) #x
#define STR(x) STRX(x)

#ifdef _UNICODE
#define TSTRX WSTRX
#define TSTR WSTR
#define STR2TSTR

#define __STR2WSTR(x)    L##x
#define _STR2WSTR(x)     __STR2WSTR(x)


#else
#define TSTRX STRX
#define TSTR STR
#endif



//========================================================
// From information
#ifdef _UNICODE
#define __FUNC_LINE__  \
   _STR2WSTR(__FUNCTION__) L" (L" WSTR(__LINE__) L") :"
#else
#define __FUNC_LINE__  \
   STR(__FUNCTION__) " (Line " STR(__LINE__) ") : >"
#endif
#define __FILE_LINE__  \
   __FILEW__ L" (Line " WSTR(__LINE__) L") : >"

#ifdef _LOGGING_USE_FILE_LINE_
#define __FROM_INFO__ __FILE_LINE__
#else 
#define __FROM_INFO__ __FUNC_LINE__
#endif


//========================================================
// LOGEX can write FROM info to file.
#if 0
#define LOGEX_TRACE(format, ...) \
  LOGGING_FROM(LEVEL_TRACE, __FROM_INFO__, format, ##__VA_ARGS__)
#define LOGEX_DEBUG(format, ...) \
  LOGGING_FROM(LEVEL_DEBUG, __FROM_INFO__, format, ##__VA_ARGS__)
#else
#define LOGEX_TRACE(format, ...) \
  (LEVEL_TRACE >= Logging::Instance()->GetLevel() ? LOGGING_FROM(LEVEL_TRACE, __FROM_INFO__, format, ##__VA_ARGS__) : (void) 0)
#define LOGEX_DEBUG(format, ...) \
  (LEVEL_DEBUG >= Logging::Instance()->GetLevel() ? LOGGING_FROM(LEVEL_DEBUG, __FROM_INFO__, format, ##__VA_ARGS__) : (void) 0)
#endif
#define LOGEX_TEST(format, ...) \
  LOGGING_FROM(LEVEL_TEST, __FROM_INFO__, format, ##__VA_ARGS__)
#define LOGEX_INFO(format, ...) \
   LOGGING_FROM(LEVEL_INFO, __FROM_INFO__, format, ##__VA_ARGS__)
#define LOGEX_NOTICE(format, ...) \
   LOGGING_FROM(LEVEL_NOTICE, __FROM_INFO__, format, ##__VA_ARGS__)
#define LOGEX_WARN(format, ...) \
  LOGGING_FROM(LEVEL_WARN, __FROM_INFO__, format, ##__VA_ARGS__)
#define LOGEX_ERROR(format, ...) \
  LOGGING_FROM(LEVEL_ERROR, __FROM_INFO__, format, ##__VA_ARGS__)
#define LOGEX_FATAL(format, ...) \
  LOGGING_FROM(LEVEL_FATAL, __FROM_INFO__, format, ##__VA_ARGS__)

#define LOG_TRACE       LOGEX_TRACE
#define LOG_DEBUG       LOGEX_DEBUG
#define LOG_TEST        LOGEX_TEST
#define LOG_INFO        LOGEX_INFO
#define LOG_NOTICE      LOGEX_NOTICE
#define LOG_WARN        LOGEX_WARN
#define LOG_ERROR       LOGEX_ERROR
#define LOG_FATAL       LOGEX_FATAL


//========================================================
// Conditional LOGEX
//========================================================
// Conditional Logging
#define LOGEX_IF(condition, level, format, ...) \
  do {  \
  if( condition ) \
  LOGGING_FROM(level, __FROM_INFO__, format, ##__VA_ARGS__); \
  } while(0)

#define LOGEX_TRACE_IF(condition, format, ...) \
  LOGEX_IF(condition, LEVEL_TRACE, format, ##__VA_ARGS__)
#define LOGEX_DEBUG_IF(condition, format, ...) \
  LOGEX_IF(condition, LEVEL_DEBUG, format, ##__VA_ARGS__)
#define LOGEX_TEST_IF(condition, format, ...) \
  LOGEX_IF(condition, LEVEL_TEST, format, ##__VA_ARGS__)
#define LOGEX_INFO_IF(condition, format, ...) \
   LOGEX_IF(condition, LEVEL_INFO, format, ##__VA_ARGS__)
#define LOGEX_NOTICE_IF(condition, format, ...) \
   LOGEX_IF(condition, LEVEL_NOTICE, format, ##__VA_ARGS__)
#define LOGEX_WARN_IF(condition, format, ...) \
  LOGEX_IF(condition, LEVEL_WARN, format, ##__VA_ARGS__)
#define LOGEX_ERROR_IF(condition, format, ...) \
  LOGEX_IF(condition, LEVEL_ERROR, format, ##__VA_ARGS__)
#define LOGEX_FATAL_IF(condition, format, ...) \
  LOGEX_IF(condition, LEVEL_FATAL, format, ##__VA_ARGS__)

#define LOG_TRACE_IF       LOGEX_TRACE_IF
#define LOG_DEBUG_IF       LOGEX_DEBUG_IF
#define LOG_TEST_IF        LOGEX_TEST_IF 
#define LOG_INFO_IF        LOGEX_INFO_IF
#define LOG_NOTICE_IF      LOGEX_NOTICE_IF
#define LOG_WARN_IF        LOGEX_WARN_IF 
#define LOG_ERROR_IF       LOGEX_ERROR_IF
#define LOG_FATAL_IF       LOGEX_FATAL_IF

#define LOG_INFO_WARN(condition, format, ...) \
   (condition)? LOG_INFO(format, ##__VA_ARGS__):LOG_WARN(format, ##__VA_ARGS__)

#define LOG_INFO_ERROR(condition, format, ...) \
   (condition)? LOG_INFO(format, ##__VA_ARGS__):LOG_ERROR(format, ##__VA_ARGS__)

#define LOG_NOTICE_WARN(condition, format, ...) \
   (condition)? LOG_NOTICE(format, ##__VA_ARGS__):LOG_WARN(format, ##__VA_ARGS__)

#define LOG_NOTICE_ERROR(condition, format, ...) \
   (condition)? LOG_NOTICE(format, ##__VA_ARGS__):LOG_ERROR(format, ##__VA_ARGS__)


#define LOG_FUNCADDRESS(module, func, address) \
   LOG_NOTICE(_T("ModuleFuncAddress: %s %s 0x%08x"), module, func, address);


//========================================================
// DCHECK 
#define DCHECK_IS_ON()  true

#define  CHECK_OP_RESULT_STRING_FILE(val1, val2, op) \
  (val1 op val2)? ( __FILEW__ L"(" WSTR(__LINE__) L") : Condition"  L" " L"(" L#val1 L" " L#op L" " L#val2 L") is true.") : ( L">" __FILEW__ L"(" WSTR(__LINE__) L") : Condition"  L" " L"(" L#val1 L" " L#op L" " L#val2 L") is false.")

#define  CHECK_OP_RESULT_STRING_FUNC(val1, val2, op) \
  (val1 op val2)? ( __FUNCTIONW__ L" (line " WSTR(__LINE__) L") : Condition (" L#val1 L" " L#op L" " L#val2 L") is true.") : ( L">" __FUNCTIONW__ L" (line " WSTR(__LINE__) L") : Condition (" L#val1 L" " L#op L" " L#val2 L") is false.") 

#define DCHECK_OP(val1, val2, op) \
  if( DCHECK_IS_ON() ) {  \
    if(val1 op val2) \
      LOG(LEVEL_INFO, CHECK_OP_RESULT_STRING_FUNC(val1, val2, op), NULL); \
    else \
      LOG(LEVEL_FATAL, CHECK_OP_RESULT_STRING_FUNC(val1, val2, op), NULL); \
  }

#define DCHECK_EQ(val1, val2) DCHECK_OP( val1, val2, ==)
#define DCHECK_NE(val1, val2) DCHECK_OP( val1, val2, !=)
#define DCHECK_LE(val1, val2) DCHECK_OP( val1, val2, <=)
#define DCHECK_LT(val1, val2) DCHECK_OP( val1, val2, < )
#define DCHECK_GE(val1, val2) DCHECK_OP( val1, val2, >=)
#define DCHECK_GT(val1, val2) DCHECK_OP( val1, val2, > )



//Logging thread

class CLogThreadInfo
{
public:
   CLogThreadInfo(LPCTSTR lpszFunc)
   {
      m_strFunc = lpszFunc;
      m_nThreadID = GetCurrentThreadId();
      LOGGING_FROM(LEVEL_INFO, m_strFunc, _T(": EnterThread(TID#%d)"), m_nThreadID);
   }

   ~CLogThreadInfo()
   {
      LOGGING_FROM(LEVEL_INFO, m_strFunc, _T(": ExitThread(TID#%d)"), m_nThreadID);
   }

   CString m_strFunc;
   UINT    m_nThreadID;
};

#ifdef _DEBUG
#pragma pop_macro("new")
#endif
#define LOG_THREAD  CLogThreadInfo LogThreadInfo(__FUNCTIONW__)