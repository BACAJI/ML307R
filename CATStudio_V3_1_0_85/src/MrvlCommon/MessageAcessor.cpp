#include "stdafx.h"
#include "MessageAcessor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCriticalSection CMessageAcessor::m_Lock;
CMessageAcessor* CMessageAcessor::m_pInstance=NULL;
SmartShellMapVer<CMessageAcessor> CMessageAcessor::m_SmartShell;


CMessageAcessor* CMessageAcessor::Instance(DWORD dwTid, int nTcpPortNumber/*=IPPC_PORT*/)
{
   if( m_SmartShell.IsAlive(dwTid) )
      return m_SmartShell[dwTid];
   
   CMessageAcessor* pInstance=NULL;

   m_Lock.Lock();
   if( !m_SmartShell.IsAlive(dwTid) )
   {
      pInstance = new CMessageAcessor(nTcpPortNumber);
      m_SmartShell.Set(dwTid, pInstance);
   }
   m_Lock.Unlock();

   return pInstance;
}

void CMessageAcessor::SafeFree(DWORD dwTId)
{
   m_Lock.Lock();
   if( m_SmartShell.IsAlive(dwTId) )
      m_SmartShell.DestroyAt(dwTId);
   m_Lock.Unlock();
}

CMessageAcessor::CMessageAcessor( int nTcpPortNumber )
{
   ms_CounterLock.Lock();
   m_lAssessorId = ms_lAccessorCount++;
   ms_CounterLock.Unlock();

   m_hMemMap  = NULL;
   m_pMemView = NULL;
   m_bOpen = FALSE ;
   m_hNewMsgEvent = NULL;
   m_piSmNextIndex = NULL;
   m_pxMsgQue = NULL;
   m_nQueSize = 0;
   m_iQueNextReadPos  = -1;
   m_pDataBuf = NULL;
   m_nDataBufLen = 0;
   m_iLastIndex   = -1;
   m_hNewMsgEvent = NULL; 
   m_pSyncBlock = NULL;



   CStringW wsName;
   CString  tsName;
   wsName.Format(SHMEM_NAME_PREFIX L"%d", nTcpPortNumber );
   tsName = CString(wsName);
   m_bOpen = Open(tsName);

}

CMessageAcessor::~CMessageAcessor(void)
{
  Close();
}

BOOL CMessageAcessor::Open(LPCTSTR lpszShmemName)
{

  BOOL bRet=FALSE;
  m_hMemMap = OpenFileMapping(/*FILE_MAP_READ*/FILE_MAP_ALL_ACCESS, FALSE, lpszShmemName );
  if( m_hMemMap == NULL )
  {
     bRet =FALSE;
    return FALSE;
  }
    

 
  m_pMemView  = MapViewOfFile(m_hMemMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);
  if( m_pMemView == NULL ) 
  {
    CloseHandle(m_hMemMap);
    bRet =FALSE;
    return FALSE;
  }

  
  m_shm.Init(m_pMemView, false);

   
  m_pxMsgQue  = static_cast<CxMessage*>( m_shm.GetQueue() );
  m_pDataBuf = static_cast<LPBYTE>( m_shm.GetDataBuffer() );
  m_nQueSize = m_shm.GetQueSize();
  m_nDataBufLen  = m_shm.GetDataBufSize();
  m_iQueNextReadPos = m_shm.GetQueNextWritePos();
  m_iLastIndex =  max( m_shm.GetNextInt64Index()-1, -1);
  m_piSmNextIndex = m_shm.GetNextInt64IndexPointer();

#ifdef _UNICODE
  wstring wstr(lpszShmemName);
#else
  CString asName(lpszShmemName);
  WCHAR* wszName = new WCHAR[asName.GetLength()+1];
  MultiByteToWideChar(CP_ACP, 0, asName.GetBuffer(0), -1, wszName, asName.GetLength()+1);
  wstring wstr(wszName);
  delete []wszName;
#endif



  m_pSyncBlock = new SyncBlockClient();
  m_pSyncBlock->Init(m_shm.GetSyncBlock(), m_shm.GetSyncBlockSize(), wstr );


  if( !Login() )
  {
     ASSERT(FALSE);
     return FALSE;
  }

  return TRUE;
}


void CMessageAcessor::Close()
{
      try
      {
		if( IsOpen() )
		{
			Logout();
			UnmapViewOfFile( m_pMemView );
			CloseHandle( m_hMemMap );
			CloseHandle( m_hNewMsgEvent );
			m_hMemMap  = NULL;
			m_pMemView = NULL;
			m_hNewMsgEvent = NULL;
		}
      }
      catch (...)
      {
         ;
      }

}

EMessageAcessorError
CMessageAcessor::GetNextMessage(CICATMessage& message, bool bMemAlloc, DWORD Timeout)
{ 
   if( !IsOpen() )
   {
      if(bMemAlloc) 
         message.m_pData=NULL;
      return eShmError;
   }


   EMessageAcessorError rc;
   DWORD dwWait;

   rc = GetNextMessage1(message, bMemAlloc);
   if( rc == eNoNewMsg )
   {
      ResetEvent(m_hNewMsgEvent);
      dwWait = WaitForSingleObject(m_hNewMsgEvent, Timeout);
      if( dwWait==WAIT_OBJECT_0 )
      {
         rc = GetNextMessage1(message, bMemAlloc);
      }
   }

   return rc;
}



EMessageAcessorError CMessageAcessor::GetNextMessage1(CICATMessage& message, bool bMemAlloc)
{  
   if( *m_piSmNextIndex<=0 )
   {
      return eNoNewMsg;
   }

   int   iQueReadPos  = m_iQueNextReadPos;
   INT64 iIndex11 = m_pxMsgQue[iQueReadPos].iMyIndex;
   if( iIndex11<=m_iLastIndex )
   {
      return eNoNewMsg;
   }


   // 备份
   LPBYTE  pTemp    = message.m_pData;
   int     nBufLen  = message.m_DataLen;

   // 复制消息主体部分
   memcpy(&message, &m_pxMsgQue[iQueReadPos].IcatMsg, sizeof(CICATMessage) );

   // 得到消息数据在缓冲区中的位置
   int   iDataPos = (int) message.m_pData;

   // 复制消息数据部分
   if( message.m_DataLen > 0 )
   {
      int nCopyLen;
      if( bMemAlloc )
      {
         message.m_pData = new BYTE[message.m_DataLen];
         nCopyLen = message.m_DataLen;
      }
      else
      {
         message.m_pData = pTemp;
         nCopyLen  = min(nBufLen, message.m_DataLen );
      }

      // 8字节对齐
      if( iDataPos+(int)sizeof(INT64) > m_nDataBufLen )
      {
         iDataPos=0;
      }
      
      // Index指针
      LPBYTE pIndex2  = m_pDataBuf + iDataPos; 
      
      // 消息数据指针
      LPBYTE pBuf     = pIndex2 + sizeof(INT64);

      // buffer尾部剩余长度
      int nRestBufLen = m_nDataBufLen - sizeof(INT64) - iDataPos;
      if( nRestBufLen>=nCopyLen )
      {
         memcpy(message.m_pData, pBuf, nCopyLen);
      }
      else
      {
         memcpy( message.m_pData, pBuf, nRestBufLen );
         memcpy( message.m_pData+nRestBufLen, m_pDataBuf+0, nCopyLen-nRestBufLen );
      }
      
      INT64  iIndex2  = *(INT64*)pIndex2; /// 数据缓冲区中保存的Index
      INT64  iIndex12 = m_pxMsgQue[iQueReadPos].iMyIndex; ///第二次读取消息队列中保存的Index

      if( iIndex12 != iIndex11 || iIndex11 != iIndex2 )
      {
         return eMsgError;
      }

   }
   else
   {
      message.m_pData=NULL;
   }

   m_iQueNextReadPos = (iQueReadPos+1)%m_nQueSize;
   m_iLastIndex  = iIndex11;
  
   return eNoError;
}

BOOL CMessageAcessor::Login()
{
   AcsrLoginLogout login;
   AcsrLoginLogout_Result Result;
   login.is_login = true;
   login.process_id  = GetCurrentProcessId();
   login.accessor_id = m_lAssessorId;

   uint32 timeout;
   timeout = INFINITE;

   if(m_pSyncBlock) 
   {
      long error = m_pSyncBlock->SendAndWait(login, Result, timeout);
      if( error==0 )
      {     
         m_hNewMsgEvent = OpenEventW(EVENT_ALL_ACCESS, FALSE, Result.str.c_str());
         return TRUE;
      }
   }

   return FALSE;
}

BOOL CMessageAcessor::Logout()
{
   if(IsOpen())
   {
      AcsrLoginLogout logout;
      AcsrLoginLogout_Result Result;
      logout.is_login = false;
      logout.process_id  = GetCurrentProcessId();
      logout.accessor_id = m_lAssessorId;

      if(m_pSyncBlock) 
      {
         long error = m_pSyncBlock->SendAndWait(logout, Result, 50);
         if( error==0 )
            return TRUE;
      }
   }
   return FALSE;
}

void CMessageAcessor::UpdateReadPosition()
{
   if( IsOpen() )
   {
      m_iQueNextReadPos = m_shm.GetQueNextWritePos();
      m_iLastIndex =  max( m_shm.GetNextInt64Index()-1, -1);
      m_piSmNextIndex = m_shm.GetNextInt64IndexPointer();
   }
   else
   {
   }
}







CCriticalSection CMessageAcessor::ms_CounterLock;

long CMessageAcessor::ms_lAccessorCount=0;

