#include "stdafx.h"
#include "MessageBank.h"
#include "MrvlCommon/ICATMessage.h"
#include "MrvlCommon/CommonDefs.h"
#include "ipc/ipc_syncblock_server.h"
#include "ipc/ipc_server_sock.h"
#include "MrvlCommon/GeneralUtils.h"
#include "MrvlCommon/Threading.h"
#include "MrvlCommon/Dispatcher.h"
#include "Logging/Logging.h"
#include "ApplicationINI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CMessageBank* CMessageBank::m_pInstance=NULL;
CCriticalSection CMessageBank::m_Lock;

/// ///////////////////////////////////////////////////////////////////////
/// Constructor / Destructor
/// ///////////////////////////////////////////////////////////////////////
//CFile file;

CMessageBank::CMessageBank(int nTcpPort)
{
   m_hFileMap  = NULL;
   m_pFileView = NULL;
   m_Que = NULL;
   m_pBuf = NULL;
   m_QueSize = 0;
   m_BufLen = 0;
   m_iBufNextPos = 0;
   m_iNextIndex  = 0;
   m_bBankOK = FALSE;
   CStringW wsName = SHMEM_NAME_PREFIX;
   wsName.AppendFormat(L"%d", nTcpPort);
   m_sShmemName = CString(wsName);

   BOOL bNoErr = MapMem();

   memset(m_FilterBank, 0, sizeof(m_FilterBank));
   for(int i=0; i<MAX_DEVICE_NUM; ++i)
      m_DeviceFilter[i] = new CDeviceFilter(i, 1);

   CreateReceiver();
   StartReceiver();
   
   CCallHandler::Instance()->RegisterListener(this);

   m_bFilterEnabled = (BOOL) (AppIni()->GetProfileInt(_T("Filter Settings"), _T("Enabled"), 1));

}


CMessageBank::~CMessageBank()
{
	try
	{
		CCallHandler::Instance()->UnregisterListener(this);
		StopReceiver();
		DeleteReceiver();
		UnMapMem();
		for(int i=0; i<MAX_DEVICE_NUM; ++i)
		{
			if(m_DeviceFilter[i])
			{
				delete m_DeviceFilter[i];
				m_DeviceFilter[i]=NULL;
			}
		}

		if(m_pSyncBlock)
		{
			delete m_pSyncBlock;
			m_pSyncBlock=NULL;
		}
	}
	catch(...)
	{
		LOG_WARN(_T("Exception thrown from ~CMessageBank"));
	}
}


CMessageBank* CMessageBank::CreateInstance( int nTcpPort )
{
   if( m_pInstance )
      return m_pInstance;

   m_Lock.Lock();
   if( m_pInstance==NULL )
   {
      m_pInstance = new CMessageBank( nTcpPort );
   }

   m_Lock.Unlock();
   return m_pInstance;
}

CMessageBank* CMessageBank::Instance()
{
   return m_pInstance;
}

void CMessageBank::Destroy()
{
   delete m_pInstance;
   m_pInstance = NULL;
}


//////////////////////////////////////////////////////////////////////////
/// 
void CMessageBank::CreateReceiver()
{
   //m_pMessageReceiver = new CICATMessageReceiver(this, HandleICATMessage);
   //this->m_pMessageReceiver->SetFifoName(_T("CBankMessage"));
}

void CMessageBank::DeleteReceiver()
{
   delete m_pMessageReceiver;
}

void CMessageBank::StartReceiver()
{
   m_pMessageReceiver->Register();
}

void CMessageBank::StopReceiver()
{
   m_pMessageReceiver->Unregister();
}

void CMessageBank::HandleICATMessage( LPVOID lpVoid, CICATMessage* pMessage )
{
   CMessageBank* pClass = (CMessageBank*)lpVoid;
   pClass->HandleMessage(pMessage);
}


BOOL CMessageBank::MapMem()
{

  m_hFileMap = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, SHM::Capacity(), m_sShmemName);
  
  // ================================
  // 
  if( m_hFileMap==NULL ){
     m_BankErr = eShmCreationFailed;
     return FALSE;
  }

  // ================================
  // already exist, held on by one or more running clients.
  // CreateFileMapping return pointer to exist object.
  bool bNeedReset=true;
  if( GetLastError() == ERROR_ALREADY_EXISTS ){
    bNeedReset = false;
  }


  m_pFileView = MapViewOfFile(m_hFileMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);
  if( m_pFileView==NULL ){
     m_BankErr = eShmCreationFailed;
     CloseHandle(m_hFileMap);
     return FALSE;
  }

  m_shm.Init(m_pFileView, bNeedReset);
   
  m_pSyncBlock = new SyncBlockServer();


  CStringW wsName(m_sShmemName);
  m_pSyncBlock->Init( m_shm.GetSyncBlock(), m_shm.GetSyncBlockSize(), wsName.GetBuffer(0), this);
  
  m_Que  = static_cast<CxMessage*>( m_shm.GetQueue() );
  m_pBuf = static_cast<LPBYTE>( m_shm.GetDataBuffer() );
  
  m_QueSize = m_shm.GetQueSize();
  m_BufLen  = m_shm.GetDataBufSize();
  m_iQueNextWritePos = m_shm.GetQueNextWritePos();
  m_iNextIndex = m_shm.GetNextInt64Index();
  m_bBankOK = TRUE;
  m_BankErr = eNoErr;

  return TRUE;
}

void CMessageBank::UnMapMem()
{
   if( m_pFileView )
      UnmapViewOfFile( m_pFileView );
   CloseHandle(m_hFileMap);

   m_pFileView = NULL;
   m_hFileMap = NULL;
   m_pSmInfo  = NULL;
}


BOOL CMessageBank::BankMessage(const CICATMessage* pMessage)
{
   if( !pMessage )
   {
      return TRUE;
   }

   ///[先整个地复制CICATMessage, 然后再修改数据指针、][5-31-2011]------------
   int   iQueWritePos = m_iQueNextWritePos;//m_pSmInfo->iQueNextWritePos;

   m_Que[iQueWritePos].iMyIndex  = -1;
   memcpy( &m_Que[iQueWritePos].IcatMsg, pMessage, sizeof(CICATMessage) );


   ///[确保Buf的剩余连续部分可以容得下一个INT64---------------------------
   int nRestBufLen = m_BufLen - m_iBufNextPos;
   if( nRestBufLen<sizeof(INT64) )
   {
      m_iBufNextPos=0;
      nRestBufLen = m_BufLen;
   }


   ///[只能是相对地址(当前消息数据区相对于整个数据buf头部的偏移量)][5-17-2011]--
   if( pMessage->m_DataLen>0 )
   {
      memcpy(m_pBuf+m_iBufNextPos, &m_iNextIndex, sizeof(INT64) ); 
      m_Que[iQueWritePos].IcatMsg.m_pData  = (BYTE*) m_iBufNextPos;    
      m_iBufNextPos += sizeof(INT64);
      nRestBufLen -= sizeof(INT64);

      if( nRestBufLen<pMessage->m_DataLen )
      {
         memcpy(m_pBuf + m_iBufNextPos, pMessage->m_pData, nRestBufLen );
         memcpy(m_pBuf, pMessage->m_pData+nRestBufLen, pMessage->m_DataLen-nRestBufLen );
         m_iBufNextPos = pMessage->m_DataLen-nRestBufLen;
      }
      else
      {
         memcpy(m_pBuf + m_iBufNextPos, pMessage->m_pData, pMessage->m_DataLen );
         m_iBufNextPos += pMessage->m_DataLen;
      }

   }
   
   if( m_iBufNextPos==m_BufLen )
   {
      m_iBufNextPos = 0;
   }
   
   m_Que[iQueWritePos].iMyIndex = m_iNextIndex;

   m_iQueNextWritePos = (iQueWritePos+1)%m_QueSize;
   m_iNextIndex++;

   SHMINFO* pHeader = (SHMINFO*)m_shm.GetHeader();
   pHeader->iQueNextWritePos = m_iQueNextWritePos;
   pHeader->iNextIndex = m_iNextIndex; 



   CCriticalSectionLock lock(m_mapEventLock);
   map<uint64, HANDLE>::iterator it = m_mapEvent.begin();
   for(; it!=m_mapEvent.end(); ++it) 
   {
      SetEvent(it->second);
   }

   return TRUE;
}

BOOL CMessageBank::HandleMessage( CICATMessage* pMessage )
{
   int iDevice = pMessage->m_InstanceID;
   if( iDevice<0 || iDevice>=MAX_DEVICE_NUM )
   {
      LOGEX_WARN(_T("Invalid CICATMessage::m_InstanceID(%d)"), iDevice);
      return BankMessage(pMessage);
   }

   // Device Filter
   if( !m_DeviceFilter[iDevice]->IsPassFilter() )
   {
      return TRUE;
   }

   // MessageId Filter
   
   CSFilter* pFilter = GetAndLockFilter(pMessage->m_InstanceID);
   BOOL bPassFilter = pFilter->IsPassFilter(pMessage);
   UnlockFilter(pMessage->m_InstanceID);
   BOOL bRet=TRUE;
   if( bPassFilter )
   {
      bRet = BankMessage(pMessage);
      m_PassedMessageMaxIndex = pMessage->m_MessageNumber;
      //LOG_DEBUG(_T("Write a message to shared memory"));
   }

   

   return bRet;
}


CSFilter* CMessageBank::GetAndLockFilter( int iDevice )
{
   if( iDevice<0 || iDevice>=MAX_DEVICE_NUM )
      return NULL;

   m_FilterLock.Lock();

   if( m_FilterBank[iDevice]==NULL )
   {
      m_FilterBank[iDevice] = new CSFilter(iDevice);
   }
  
   return m_FilterBank[iDevice];
}


void CMessageBank::UnlockFilter( int iDevice )
{
   m_FilterLock.Unlock();
}


BOOL CMessageBank::OnMessageReceived( const Message& kMessage )
{
   Message* pMessage = const_cast<Message*>(&kMessage);
   
   UINT  messageId = (UINT) kMessage.GetMessageId();
   int   iDevice;
   CString strFilter;
   switch ( messageId )
   {
   case SID_UPDATEFILTER:  
      {
         tagUpdateFilter ufCommand;
         tagUpdateFilter_Result   result;
         void* iter=NULL;
         pMessage->ReadInt(&iter, &ufCommand.iDevice);
         pMessage->ReadInt(&iter, &ufCommand.filterType);
         pMessage->ReadBool(&iter, &ufCommand.bLetItPass);
         pMessage->ReadInt(&iter, &ufCommand.nMessageIdCount);
         pMessage->ReadInt(&iter, &ufCommand.nMessageIdSize);

         LOG_INFO(_T("[Device%d] FilterType=%d, bPass=%d, MsgIdCount=%d, IdSize=%d"), 
            ufCommand.iDevice, ufCommand.filterType, (int)ufCommand.bLetItPass, ufCommand.nMessageIdCount, ufCommand.nMessageIdSize);
         Sleep(30);

         ufCommand.pIcatMessageId = iter;
         iDevice = ufCommand.iDevice;
         if( ufCommand.iDevice<0 || ufCommand.iDevice>=MAX_DEVICE_NUM )
         {
            LOG_ERROR(_T("Invalid parameter deviceId=%d"), ufCommand.iDevice);
            result.lErrCode = -1;
         }
         else
         {
            CSFilter* pFilter = GetAndLockFilter(ufCommand.iDevice);
            pFilter->UpdateFilter((EFilterType)ufCommand.filterType, ufCommand.pIcatMessageId, ufCommand.nMessageIdCount, ufCommand.nMessageIdSize, ufCommand.bLetItPass);
            UnlockFilter(ufCommand.iDevice);
            switch(ufCommand.filterType)
            {
            case eDIAGFilter: strFilter=_T("DIAGFilter"); break;
            case eDIAGFilterAppSide: strFilter=_T("DIAGFilterAppSide"); break;
            case eGKIFilter: strFilter=_T("GKIFilter"); break;
            case eDSPFilter: strFilter=_T("DSPFilter"); break;
            default: strFilter=_T("Unknown Filter");
            }

            LOGEX_INFO(_T("[Device%d] Update %s OK. MsgIdCount=%d, Pass/Block=%s"), 
               iDevice, strFilter.GetBuffer(0), ufCommand.nMessageIdCount, ufCommand.bLetItPass? _T("Pass"):_T("Block"));
            strFilter.ReleaseBuffer();
            result.lErrCode = NO_ERROR;
         }
         
         CReplyMessage  replyMessage(*pMessage);
         replyMessage.WriteData((const char*)&result, sizeof(result));
         long rc = CCallHandler::Instance()->Send(replyMessage);
         return TRUE;
      }
      break;

   case SID_FILTER_ALL_PASSBLOCK:
      {
         void* iter=NULL;
         tagFilterAllPassBlock command;
         tagFilterAllPassBlock_Result result;
         
         pMessage->ReadInt(&iter, &command.iDevice);
         pMessage->ReadInt(&iter, &command.filterType);
         pMessage->ReadBool(&iter, &command.bPass);
         iDevice = command.iDevice;
         if( command.iDevice<0 || command.iDevice>=MAX_DEVICE_NUM )
         {
            LOG_ERROR(_T("Invalid parameter deviceId=%d"), command.iDevice);
            result.errCode = -1;
         }
         else
         {
            CSFilter* pFilter = GetAndLockFilter(command.iDevice);
            pFilter->SetAllPassBlock((EFilterType)command.filterType, command.bPass);
            UnlockFilter(command.iDevice);
            strFilter = _T("All Filter");
            LOGEX_INFO(_T("[Device%d] Update %s OK. Pass/Block=%s"), 
               iDevice, strFilter.GetBuffer(0), command.bPass? _T("Pass"):_T("Block"));
            strFilter.ReleaseBuffer();
            result.errCode = 0;
         }
         
         CReplyMessage  replyMessage(*pMessage);
         replyMessage.WriteData((const char*)&result, sizeof(result));
         long rc = CCallHandler::Instance()->Send(replyMessage);
         return TRUE;
      }
      break;

   case SID_UPDATE_DEVICE_FILTER:
      {
         void* iter=NULL;
         tagUpdateDeviceFitler command;
         tagUpdateDeviceFitler_Result result;

         pMessage->ReadInt(&iter, &command.iDevice);
         pMessage->ReadBool(&iter, &command.bPass);
         
         if( command.iDevice<0 || command.iDevice>=MAX_DEVICE_NUM )
         {
            LOG_ERROR(_T("Invalid parameter deviceId=%d"), command.iDevice);
            result.errCode = -1;
         }
         else
         {
            m_DeviceFilter[command.iDevice]->UpdateFilter(command.bPass);
            LOG_INFO(_T("[Device%d] Update DeviceFilter OK, bPass=%d"), command.iDevice, (int)command.bPass);
            result.errCode=NO_ERROR;
         }
         
         CReplyMessage  replyMessage(*pMessage);
         replyMessage.WriteData((const char*)&result, sizeof(result));
         long rc = CCallHandler::Instance()->Send(replyMessage);
         return TRUE;
      }
 
   default:
      break;
   }

   
   return FALSE;
}

wstring CMessageBank::AcsrLogin( uint32 processId, uint32 accessorId )
{
   uint64 hi = static_cast<uint64>(processId);
   uint64 low = static_cast<uint64>(accessorId);
   uint64 key = (hi<<32)|low;
   
   CCriticalSectionLock lock(m_mapEventLock);
   
   map<uint64, HANDLE>::iterator it 
      = m_mapEvent.find(key);
   if( it != m_mapEvent.end() )
   {
      HANDLE hEvent = it->second;
      m_mapEvent.erase(it);
      CloseHandle(hEvent);
   }


   CString sName;
   sName.Format(_T("__ProcessId=%u__AccessorId=%u"), processId, accessorId);
   sName = m_sShmemName + sName;

   HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, sName);
   m_mapEvent.insert(pair<uint64, HANDLE>(key, hEvent));
   
   return CStringW(sName).GetBuffer(0);
}

void CMessageBank::AcsrLogout( uint32 processId, uint32 accessorId )
{
   uint64 hi = static_cast<uint64>(processId);
   uint64 low = static_cast<uint64>(accessorId);
   uint64 key = (hi<<32)|low;

   CCriticalSectionLock lock(m_mapEventLock);

   map<uint64, HANDLE>::iterator it = m_mapEvent.find(key);
   if( it != m_mapEvent.end() )
   {
      HANDLE hEvent = it->second;
      m_mapEvent.erase(it);
      CloseHandle(hEvent);
   }

   /*CStringA str;
   str.Format("AcsrLogout ProcessId=%u, AccessorId=%u\n", processId, accessorId);
   file.Write(str.GetBuffer(0), str.GetLength());*/
}

void CMessageBank::PlayEnded()
{
    CIpcMessage message(IPC_ROUTING_BROADCAST, 0, 0, MID_PLAY_ENDED);
    message.WriteUInt64(m_PassedMessageMaxIndex);
    CCallHandler::Instance()->Send(message);
}
