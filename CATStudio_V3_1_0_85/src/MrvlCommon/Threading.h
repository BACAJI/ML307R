#pragma once
#include <afxmt.h>
#include "RWLock.h"

struct CCriticalSectionLock
{
   CCriticalSectionLock(CCriticalSection& csLock)
      : m_csLock(csLock){
         m_csLock.Lock();
         m_bLocked = true;
   }
   ~CCriticalSectionLock(){
      if(m_bLocked){
         m_csLock.Unlock();
         m_bLocked = false;
      }
   }

   void Unlock(){
      if(m_bLocked){
         m_csLock.Unlock();
         m_bLocked=false;
      }
   }

   bool  m_bLocked;
   CCriticalSection& m_csLock;
};

typedef CCriticalSectionLock AutoCSLock;

struct AutoSetEvent
{
   AutoSetEvent(HANDLE handle)
      : m_handle(handle){
   }
   ~AutoSetEvent(){
      SetEvent(m_handle);
   }

   HANDLE m_handle;
};

struct AutoEventLock
{
   AutoEventLock(HANDLE handle){
      m_handle = handle;
      m_bLocked = true;
      ResetEvent(m_handle);
   }
   ~AutoEventLock(){
      if(m_bLocked){
         SetEvent(m_handle);
         m_bLocked = false;
      }
   }
   void Unlock(){
      if(m_bLocked){
         SetEvent(m_handle);
         m_bLocked=false;
      }
   }

   bool m_bLocked;
   HANDLE m_handle;
};

struct AutoHandleCloser
{
   AutoHandleCloser(HANDLE handle) 
      : m_handle(handle){
   }

   ~AutoHandleCloser() {
      CloseHandle(m_handle);
   }

   HANDLE m_handle;
};

#ifdef _CATCORE_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT 
#endif

HANDLE DLL_EXPORT BeginThread( AFX_THREADPROC pfnThreadProc, 
                   LPVOID pParam, 
                   int nPriority = THREAD_PRIORITY_NORMAL );