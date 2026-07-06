#pragma once
#include "ICATMessage.h"
#include <string>
#include <xstring>


#define SHM_QUEUE_ALIGNMENT    sizeof(INT64)
#define SHM_HEADER_MAXSIZE     128 
#define SHM_AVERAGE_PDU_SIZE   128
#define SHM_SYNC_BLOCK_SIZE    1024
#define SHM_XMSG_QUEUE_SIZE    4096
#define SHM_XMSG_DATABUF_SIZE  SHM_XMSG_QUEUE_SIZE * SHM_AVERAGE_PDU_SIZE * 2
#ifdef _UNICODE
typedef  std::wstring tstring;
#else
typedef  std::string  tstring; 
#endif

typedef struct SHAREMEMORY_INFORMATION
{
   DWORD    dwSmSize;     
   DWORD    dwXMsgSize;
   DWORD    dwSyncBlockOff;
   DWORD    dwSyncBlockSize;
   DWORD    dwQueOff;
   DWORD    dwQueSize;
   DWORD    dwBufOff;
   DWORD    dwBufSize;
   long     volatile  iQueNextWritePos;
   INT64    volatile  iNextIndex;
   long     volatile  bLocked;
   long     volatile  lPId;
   long     volatile  lAccessorId;
   long     volatile  QueLocked;

}* LPSHAREMEMORY_INFORMATION;

typedef SHAREMEMORY_INFORMATION  SHMINFO;


class CxMessage
{
public:
   INT64        iMyIndex;
   CICATMessage IcatMsg;
};


struct SHM
{
   SHM(){ 
      memset(this, 0, sizeof(SHM) ); 
   }
   ~SHM(){};


   void Init(void* pView, bool bNeedReset)
   {
      m_pHeader = (SHMINFO*) pView;
      if( bNeedReset )
         ResetHeader();

      SHMINFO* pHeader = (SHMINFO*) m_pHeader;
      m_pSyncBlock = ((char*)pView) + pHeader->dwSyncBlockOff;
      m_pQueue = ((char*)pView) + pHeader->dwQueOff;
      m_pDataBuffer = ((char*)pView) + pHeader->dwBufOff;
   }

   void ResetHeader(){    
      memset( m_pHeader, 0, SHM_HEADER_MAXSIZE );
      int xsize = sizeof( CxMessage );
      xsize = xsize + SHM_QUEUE_ALIGNMENT - (xsize%SHM_QUEUE_ALIGNMENT)%SHM_QUEUE_ALIGNMENT;
      DWORD    dwOff=0;


      SHMINFO* pHeader = (SHMINFO*) m_pHeader;
      pHeader->dwXMsgSize = xsize;
      pHeader->dwSyncBlockSize = SHM_SYNC_BLOCK_SIZE; 
      pHeader->dwQueSize  = SHM_XMSG_QUEUE_SIZE;
      pHeader->dwBufSize  = SHM_XMSG_DATABUF_SIZE;

      dwOff = SHM_HEADER_MAXSIZE; // currently 128
      pHeader->dwSyncBlockOff = dwOff; dwOff += pHeader->dwSyncBlockSize;
      pHeader->dwQueOff  = dwOff;      dwOff += pHeader->dwXMsgSize * pHeader->dwQueSize;
      pHeader->dwBufOff  = dwOff;      dwOff += pHeader->dwBufSize;
      pHeader->dwSmSize  = dwOff;
      pHeader->iQueNextWritePos = 0;
      pHeader->iNextIndex= 0;
      pHeader->bLocked=0;
      pHeader->lPId=0;
      pHeader->lAccessorId=0;
      pHeader->QueLocked = 0;

   }

   __forceinline void* GetHeader(){
      return m_pHeader;
   }
   __forceinline void* GetSyncBlock(){
      return m_pSyncBlock;
   }
   __forceinline void* GetQueue(){
      return m_pQueue;
   }
   __forceinline void* GetDataBuffer(){
      return m_pDataBuffer;
   }

   __forceinline DWORD GetHeaderSize() {
      return sizeof( SHMINFO );
   }
   __forceinline DWORD GetQueSize(){
      return m_pHeader->dwQueSize;
   }
   __forceinline DWORD GetSyncBlockSize() {
      return m_pHeader->dwSyncBlockSize;
   }
   __forceinline DWORD GetDataBufSize() {
      return m_pHeader->dwBufSize;
   }

   __forceinline  INT64 GetNextInt64Index() const {
      return  m_pHeader->iNextIndex;
   }
   __forceinline volatile INT64* GetNextInt64IndexPointer() const {
      return & ( (SHMINFO*) m_pHeader )->iNextIndex;
   }

   __forceinline int GetQueNextWritePos() const {
      return  ( (SHMINFO*) m_pHeader )->iQueNextWritePos;
   }

   __forceinline INT64 SetNextUInt64Index(INT64 iNextIndex) const {
      return  ( (SHMINFO*) m_pHeader )->iNextIndex = iNextIndex;
   }

   __forceinline int SetQueNextWritePos(int iNextWritePos) const {
      return  ( (SHMINFO*) m_pHeader )->iQueNextWritePos = iNextWritePos;
   }


   static DWORD Capacity() {
      int elemSize = sizeof( CxMessage );
      elemSize = elemSize + SHM_QUEUE_ALIGNMENT - (elemSize%SHM_QUEUE_ALIGNMENT)%SHM_QUEUE_ALIGNMENT;
      DWORD dwCapcity = 
         SHM_HEADER_MAXSIZE
         + SHM_SYNC_BLOCK_SIZE
         + SHM_XMSG_QUEUE_SIZE * elemSize
         + SHM_XMSG_DATABUF_SIZE;

      return dwCapcity;
   }


private:
   SHMINFO* m_pHeader;
   void* m_pQueue;
   void* m_pDataBuffer;
   void* m_pSyncBlock;

};


static CString GetCurrentProcessNameAndID()
{
	//Richard added for named share-memory	2011-08-10	Begin
  UINT  nFactor=sizeof(TCHAR);
  int pid = GetCurrentProcessId();
  CString strPID;
  strPID.Format(_T("%d"), pid);
  TCHAR   szFileFullPath[MAX_PATH]; 
  ::GetModuleFileName(NULL,   szFileFullPath,   MAX_PATH);
  CString szProcessName(szFileFullPath); 
  int nPos = szProcessName.ReverseFind('\\'); 
  szProcessName = szProcessName.Right(szProcessName.GetLength() - nPos - 1);
  szProcessName += strPID;
  //Richard added for named share-memory	2011-08-10	End
  //////////////////////////////////////////////////////////////////////////
  TCHAR  szSharePointName[256];
  memset(szSharePointName, 0, sizeof(TCHAR) * 256);
  memcpy(szSharePointName, szProcessName, nFactor+nFactor*_tcslen(szProcessName));
  return CString(szSharePointName);
};


#define OnlineDataPoolName       _T("CATStudioOnlineDataPool")
#define OnlineNewMsgEventName    _T("CATStudioOnlineDataPoolNewMsgEvent")
//#define OnlineCommTcpPort        2011
#define OfflineDataPoolName      _T("CATStudioOfflineDataPool")
#define OfflineNewMsgEventName   _T("CATStudioOfflineDataPoolNewMsgEvent")
#define OfflineCommTcpPort       2012

#define PIdAccessIdNamingFormat  _T("_%d_%d")
#define RegisterAccessorLockName _T("_RegAccessorLockName")
#define NewAccessorSemaName      _T("_NewAccessorSemaName")
#define MAX_CLIENT_NUM           64