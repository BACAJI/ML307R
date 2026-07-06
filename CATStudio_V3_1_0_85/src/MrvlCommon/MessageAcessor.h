
#pragma once
#include "ICATMessage.h"
#include "IPCDefines.h"
#include "MrvlCommon/ipc/ipc_client_sock.h"
#include "MrvlCommon/ipc/ipc_syncblock_client.h"
#include <map>


#define WM_NEWMESSAGE_ACCESSED  (WM_USER + 201)



template<class OBJECT>
class SmartShellMapVer
{
public:
   SmartShellMapVer();
   ~SmartShellMapVer();
   BOOL IsAlive(DWORD dwTid);
   void DestroyAt(DWORD dwTid);
   void Set(DWORD dwTid, OBJECT* pObject);
   OBJECT* operator [] (DWORD dwTid);
   

private:
   std::map<DWORD, OBJECT*> m_ObjectMap;
};

template <class OBJECT>
inline BOOL SmartShellMapVer<OBJECT>::IsAlive(DWORD dwTid)
{   
   std::map<DWORD, OBJECT*>::iterator it;
   it = m_ObjectMap.find(dwTid);
   if( it!=m_ObjectMap.end() && it->second!=NULL)
   {
      return TRUE;
   }
   else
   {
      return FALSE;
   }

}


template <class OBJECT>
inline OBJECT* SmartShellMapVer<OBJECT>::operator [] (DWORD dwTid)
{
   std::map<DWORD, OBJECT*>::iterator it;
   it = m_ObjectMap.find(dwTid);
   
   if( it!=m_ObjectMap.end())
   {
      return (it->second);
   }
   else
   {
      return NULL;
   }
   
}


template <class OBJECT>
inline SmartShellMapVer<OBJECT>::SmartShellMapVer()
{
}	    

template <class OBJECT>
inline void SmartShellMapVer<OBJECT>::Set(DWORD dwTid, OBJECT* pObject)
{
   DestroyAt(dwTid);
   m_ObjectMap.insert(std::pair<DWORD, OBJECT*>(dwTid, pObject));
}

template <class OBJECT>
inline void SmartShellMapVer<OBJECT>::DestroyAt(DWORD dwTid)
{
   std::map<DWORD, OBJECT*>::iterator it;
   it = m_ObjectMap.find(dwTid);

   if( it!=m_ObjectMap.end() )
   {
      delete it->second;
      m_ObjectMap.erase(it);
   }
}


template <class OBJECT>
inline SmartShellMapVer<OBJECT>::~SmartShellMapVer()
{
   std::map<DWORD, OBJECT*>::iterator it= m_ObjectMap.begin();
   for(; it!=m_ObjectMap.end(); )
   {
          std::map<DWORD, OBJECT*>::iterator iter=it++;
	   if(iter->second)
	   {
	       delete iter->second;
		iter->second=NULL;
	   }
   }
   m_ObjectMap.clear();
}


//==========================================================================
// Message Accessor
//==========================================================================
enum EMessageAcessorError{
   eNoError  = 0,
   eNoNewMsg = 1,
   eMsgError = 2,
   eShmError = 3,
   eTimeout  = 4
};

class CMessageAcessor
{
public:

  CMessageAcessor*  Instance(DWORD dwTid, LPCTSTR lpszShmemName);
  CMessageAcessor(LPCTSTR lpszShmemName);

  static  CMessageAcessor*  Instance(DWORD dwTid=0, int nTcpPortNumber=IPPC_PORT);
  static  void              SafeFree(DWORD dwTid=0);
  static  CCriticalSection  m_Lock;
  static  CMessageAcessor*  m_pInstance;
  CMessageAcessor(int nTcpPortNumber);
  
  static  SmartShellMapVer<CMessageAcessor> m_SmartShell;
  friend  class SmartShellMapVer<CMessageAcessor>;

  
  EMessageAcessorError      GetNextMessage(CICATMessage& message, bool bMemAlloc=true, DWORD Timeout=INFINITE);
  void                      SetModeOnline(){;};
  void                      SetModeOffline(){;};
  BOOL                      IsOpen(){ return m_bOpen ;};
  void                      UpdateReadPosition();

private:
  BOOL                      Open(LPCTSTR lpShMName);
  void                      Close();
  EMessageAcessorError      GetNextMessage1(CICATMessage& message, bool bMemAlloc);
  BOOL                      Login();
  BOOL                      Logout();



  HANDLE           m_hMemMap;
  LPVOID           m_pMemView;
  BOOL             m_bOpen;
  HANDLE           m_hNewMsgEvent;

  volatile INT64*  m_piSmNextIndex;
  CxMessage*       m_pxMsgQue;
  int              m_nQueSize;
  int              m_iQueNextReadPos;
  LPBYTE           m_pDataBuf;
  int              m_nDataBufLen;
  INT64            m_iLastIndex;
  long             m_lAssessorId;
  static  CCriticalSection ms_CounterLock;
  static    long   ms_lAccessorCount;

 
  SHM          m_shm;
  SyncBlockClient* m_pSyncBlock;
  

public:
   ~CMessageAcessor(void); 
};

