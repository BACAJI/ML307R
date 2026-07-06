#pragma once
#include "stdafx.h"
#include "Threading.h"



HANDLE BeginThread( 
                   AFX_THREADPROC pfnThreadProc, 
                   LPVOID pParam, 
                   int nPriority /* = THREAD_PRIORITY_NORMAL */)
{
   HANDLE hThread;

   CWinThread* pThread = AfxBeginThread(
      pfnThreadProc, 
      pParam,   //param
      nPriority, // priority
      0,      // initialStackSize
      CREATE_SUSPENDED); // Create flags

   if (pThread == NULL)
   {
       TRACE0("AfxBeginThread failed!\n");
       return NULL;
   }

   BOOL bRet = DuplicateHandle(GetCurrentProcess(), 
      pThread->m_hThread, 
      GetCurrentProcess(),
      &hThread, 
      0,
      FALSE,
      DUPLICATE_SAME_ACCESS);
   pThread->ResumeThread();

   return hThread;
}
