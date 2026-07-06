#include "stdafx.h"
#include "ICATMessage.h"
#include "CommonDefs.h"
#include "Logging/Logging.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
	


//////////////////////////////////////////////////////////////////////////
///[CICATMessage implementation][5-11-2011]-------------------------------
#define DIAG_MI_LOGGED_SIGNAL	5
#define PDU_HEADER_LEN			  12

CCriticalSection CICATMessage::m_NumberLock;             // Used for Inc/Dec/ MessageCounter. 
CCriticalSection CICATMessage::m_ReceiversCounterLock;   // Used for Message refer counter.
UINT64 CICATMessage::m_MessageCounter=0;

#ifdef _DEBUG
#define SUPPORT_CAT_MSG_SNAPSHOT
#endif

#ifdef SUPPORT_CAT_MSG_SNAPSHOT
#include "../MiniViewerDll_Generic/khash.h"
#if UINTPTR_MAX == UINT32_MAX
KHASH_MAP_INIT_INT(p2m, UINT64)
#else
KHASH_MAP_INIT_INT64(p2m, UINT64)
#endif
CCriticalSection *s_msgRefLock = new CCriticalSection;
static khash_t(p2m) *s_msgRefMap = NULL;
#define MAX_NAME_LEN 64
#define MAX_NUM_NAME 31
static TCHAR s_callerNames[MAX_NUM_NAME][MAX_NAME_LEN] = {{0}};
static int s_numNames = 0;

static void cat_msg_create(CICATMessage *pThis)
{
	ASSERT(pThis);
	if (pThis)
	{
		CSingleLock lock(s_msgRefLock);
		lock.Lock();
		if (s_msgRefMap == NULL)
		{
			s_msgRefMap = kh_init(p2m);
		}
		ASSERT(s_msgRefMap);
		if (s_msgRefMap)
		{
			khiter_t k;
			int res;
			k = kh_put(p2m, s_msgRefMap, (uintptr_t) pThis, &res);
			ASSERT(res > 0);
			if (k != kh_end(s_msgRefMap))
			{
				kh_value(s_msgRefMap, k) = 0;
			}
		}
	}
}

static CString cat_msg_get_ref_str(UINT64 ullRefs)
{
	CString res;
	UINT64 mask = 3;
	for (int n = 0; n <= s_numNames; ++n)
	{
		UINT64 value = (ullRefs & mask);
		if (value)
		{
			value >>= 2 * n;
			res.AppendFormat(_T(" %s %u"),
							 n ? s_callerNames[n - 1] : _T("(NULL)"), 
							 (unsigned) value);
		}
		mask <<= 2;
	}
	return res;
}

static void cat_msg_destroy(CICATMessage *pThis)
{
	ASSERT(pThis);
	if (pThis)
	{
		CSingleLock lock(s_msgRefLock);
		lock.Lock();
		ASSERT(s_msgRefMap);
		if (s_msgRefMap)
		{
			khiter_t k;
			k = kh_get(p2m, s_msgRefMap, (uintptr_t) pThis);
			ASSERT(k != kh_end(s_msgRefMap));
			if (k != kh_end(s_msgRefMap))
			{
				kh_del(p2m, s_msgRefMap, k);
				if (kh_size(s_msgRefMap) == 0)
				{
					kh_destroy(p2m, s_msgRefMap);
					s_msgRefMap = NULL;
				}
			}
		}
	}
}

static void cat_msg_reset(CICATMessage *pThis)
{
	ASSERT(pThis);
	if (pThis)
	{
		CSingleLock lock(s_msgRefLock);
		lock.Lock();
		ASSERT(s_msgRefMap);
		if (s_msgRefMap)
		{
			khiter_t k;
			k = kh_get(p2m, s_msgRefMap, (uintptr_t) pThis);
			ASSERT(k != kh_end(s_msgRefMap));
			if (k != kh_end(s_msgRefMap))
			{
				kh_value(s_msgRefMap, k) = 0;
			}
		}
	}
}

static void cat_msg_add_ref(CICATMessage *pThis, const CString *callerName)
{
	ASSERT(pThis);
	if (pThis)
	{
		CSingleLock lock(s_msgRefLock);
		lock.Lock();
		ASSERT(s_msgRefMap);
		if (s_msgRefMap)
		{
			khiter_t k;
			k = kh_get(p2m, s_msgRefMap, (uintptr_t) pThis);
			ASSERT(k != kh_end(s_msgRefMap));
			if (k != kh_end(s_msgRefMap))
			{
				UINT64 ullRefs = kh_value(s_msgRefMap, k);
				if (callerName == NULL || callerName->IsEmpty())
				{
					if ((ullRefs & 3) == 3)
					{
						CString refs = cat_msg_get_ref_str(ullRefs);
						LOG_WARN(_T("Unnamed reference saturated for msg %I64u refs %s"), pThis->m_MessageNumber, refs);
						ASSERT(FALSE);
					}
					else
					{
						ullRefs += 1;
					}
				}
				else if (callerName->GetLength() < MAX_NAME_LEN)
				{
					int n;
					for (n = 0; n < s_numNames; ++n)
					{
						if (callerName->Compare(s_callerNames[n]) == 0)
						{
							break;
						}
					}
					if (n == s_numNames)
					{
						ASSERT(n < MAX_NUM_NAME);
						if (n < MAX_NUM_NAME)
						{
							_tcscpy_s(s_callerNames[n], *callerName);
							++s_numNames;
						}
					}
					if (n < s_numNames)
					{
						UINT64 mask = 3ULL << (2 * (n + 1));
						if ((ullRefs & mask) == mask)
						{
							CString refs = cat_msg_get_ref_str(ullRefs);
							LOG_WARN(_T("Reference %s saturated for msg %I64u refs %s"), *callerName, pThis->m_MessageNumber, refs);
							ASSERT(FALSE);
						}
						else
						{
							mask &= (mask >> 1);
							ullRefs += mask;
						}
					}
					else
					{
						LOG_WARN(_T("Reference %s not counted for msg %I64u"), *callerName, pThis->m_MessageNumber);
					}
				}
				else
				{
					CString refs = cat_msg_get_ref_str(ullRefs);
					LOG_WARN(_T("Reference %s not counted for msg %I64u refs %s"), *callerName, pThis->m_MessageNumber, refs);
					ASSERT(FALSE);
				}
				kh_value(s_msgRefMap, k) = ullRefs;
			}
		}
	}
}

static void cat_msg_delete(CICATMessage *pThis, const CString *callerName)
{
	ASSERT(pThis);
	if (pThis)
	{
		CSingleLock lock(s_msgRefLock);
		lock.Lock();
		ASSERT(s_msgRefMap);
		if (s_msgRefMap)
		{
			khiter_t k;
			k = kh_get(p2m, s_msgRefMap, (uintptr_t) pThis);
			ASSERT(k != kh_end(s_msgRefMap));
			if (k != kh_end(s_msgRefMap))
			{
				UINT64 ullRefs = kh_value(s_msgRefMap, k);
				if (callerName == NULL || callerName->IsEmpty())
				{
					if ((ullRefs & 3) == 0)
					{
						CString refs = cat_msg_get_ref_str(ullRefs);
						LOG_WARN(_T("Unnamed reference saturated for msg %I64u refs %s"), pThis->m_MessageNumber, refs);
						ASSERT(FALSE);
					}
					else
					{
						ullRefs -= 1;
					}
				}
				else if (callerName->GetLength() < MAX_NAME_LEN)
				{
					int n;
					for (n = 0; n < s_numNames; ++n)
					{
						if (callerName->Compare(s_callerNames[n]) == 0)
						{
							break;
						}
					}
					if (n == s_numNames)
					{
						ASSERT(n < MAX_NUM_NAME);
						if (n < MAX_NUM_NAME)
						{
							_tcscpy_s(s_callerNames[n], *callerName);
							++s_numNames;
						}
					}
					if (n < s_numNames)
					{
						UINT64 mask = 3ULL << (2 * (n + 1));
						if ((ullRefs & mask) == 0)
						{
							CString refs = cat_msg_get_ref_str(ullRefs);
							LOG_WARN(_T("Reference %s saturated for msg %I64u refs %s"), *callerName, pThis->m_MessageNumber, refs);
							ASSERT(FALSE);
						}
						else
						{
							mask &= (mask >> 1);
							ullRefs -= mask;
						}
					}
					else
					{
						LOG_WARN(_T("Reference %s not counted for msg %I64u"), *callerName, pThis->m_MessageNumber);
					}
				}
				else
				{
					CString refs = cat_msg_get_ref_str(ullRefs);
					LOG_WARN(_T("Reference %s not counted for msg %I64u refs %s"), *callerName, pThis->m_MessageNumber, refs);
					ASSERT(FALSE);
				}
				kh_value(s_msgRefMap, k) = ullRefs;
			}
		}
	}
}

CString __declspec(dllexport) cat_msg_get_snapshot_str()
{
	CString res;
	CSingleLock lock(s_msgRefLock);
	lock.Lock();
	if (s_msgRefMap)
	{
		khiter_t k;
		for (k = kh_begin(s_msgRefMap); k != kh_end(s_msgRefMap); ++k)
		{
			if (!kh_exist(s_msgRefMap, k))
				continue;
			CICATMessage *pMessage = reinterpret_cast<CICATMessage *>(kh_key(s_msgRefMap, k));
			UINT64 ullRefs = kh_val(s_msgRefMap, k);
			CString refs = cat_msg_get_ref_str(ullRefs);
			res.AppendFormat(_T("Msg %I64u refs %s\n"), pMessage->m_MessageNumber, refs);
		}
	}
	return res;
}
#endif

#ifdef DEBUG
#define LOGGING_REQUIRED	(12345 == this->m_MessageNumber)


bool CICATMessage::s_firstLoggingForSession = true;


// Append given trace string, followed by a newline, to file <Log.txt>, which is located in the system root directory (usually "C:\Windows").
// Before doing so for the first time in the current app session, clear this file.
// Return 0 if succeeded, and a negative value if failed.
int CICATMessage::Log(const CString* trace /* NULL */)
{
	if (trace)
	{
		std::ios_base::openmode openMode = (ios::out | ios::app);
		if (CICATMessage::s_firstLoggingForSession)
		{
			openMode = ios::out; // Before starting to log for the current app session, any previous contents should be cleared from the log file.
			CICATMessage::s_firstLoggingForSession = false;
		}

		char* systemRoot = getenv ("systemroot");
		if (NULL == systemRoot)	return -1;
		CString logFolder(systemRoot);
		CString logPath;
		logPath.Format(_T("%s\\Log.txt"), logFolder);
		std::wofstream logFile;
		logFile.open(logPath, openMode);
		logFile << ((LPCTSTR)(*trace)) << std::endl;
	}
    return 0;
}
#endif // Debug

	
CICATMessage::~CICATMessage() 
{ 
   try
   {
      if(m_pData) 
      {
         delete []m_pData; 
         m_pData=NULL;
      }
   }
   catch (...)
   {
      LOG_ERROR(_T("Exception, throw from delete ICATMessage::m_pData"));
   }

	if(m_bIsMsgInit)
	{
		delete m_pDiagMessage;
		m_pDiagMessage = NULL;
		m_bIsMsgInit = false;
	}
	
#ifdef DEBUG
   if (LOGGING_REQUIRED)
   {
	   CString trace;
	   trace.Format(_T("Msg# %d: dtor"), this->m_MessageNumber);
	   CICATMessage::Log(&trace);
   }
#endif
#ifdef SUPPORT_CAT_MSG_SNAPSHOT
   cat_msg_destroy(this);
#endif
}


CICATMessage::CICATMessage():m_tmpMsg(this)
{ 
   m_bConvertable = 0;
   m_nDiagHCounter = 0;
   m_ModuleID = 0;
   m_InstanceID = 0;
   m_DataLen = 0;
   m_pData = NULL;

   m_ReceiversCounter = 0;
   ::GetLocalTime(&m_Time);
   m_Direction = MessageOUT_ALL;
   CSingleLock NumberSingleLock(&m_NumberLock);
   NumberSingleLock.Lock();
   m_MessageNumber = m_MessageCounter++;
   NumberSingleLock.Unlock();
   m_UserRemark = 0;
   m_Error = kNoError;
	 
	m_pDiagMessage = NULL;
	m_bIsMsgInit = false;
	InitDiagMsg();

#ifdef DEBUG
   if (LOGGING_REQUIRED)
   {
	   CString trace;
	   trace.Format(_T("Msg# %d: ctor (ref=%d)"), this->m_MessageNumber, this->m_ReceiversCounter);
	   CICATMessage::Log(&trace);
   }
#endif
#ifdef SUPPORT_CAT_MSG_SNAPSHOT
   cat_msg_create(this);
#endif
}

CICATMessage::CICATMessage(int Prot, int m, int i, BYTE *pd /*=NULL*/, int dl /*=0*/, BOOL bMemAllocation /*true*/):m_tmpMsg(this)
{
  m_bConvertable = Prot;
  m_nDiagHCounter = 0;
  m_ModuleID = m;
  m_InstanceID = i;
  m_DataLen = dl;

  if (pd && dl)
  {
    if (bMemAllocation)
    {
      m_pData = new BYTE[m_DataLen];
      memcpy(m_pData, pd, m_DataLen);
    }
    else
    {
      m_pData = pd;
    }
  }
  else
  {
    m_pData = NULL;
  }

  if(m_ModuleID == 1 && m_bConvertable == eDIAGProtocol)
  {
    if(dl> kRMsgHCount)
    {
      if( m_pData[kRMsgHCount] && *(WORD*)&m_pData[kMsgSap] != DIAG_MI_LOGGED_SIGNAL)
      {
        m_nDiagHCounter = m_pData[kRMsgHCount];
        m_pData[kRMsgHCount] = 0;
      }
    }
  }

  m_ReceiversCounter = 0;
  ::GetLocalTime(&m_Time);
  m_Direction = MessageOUT_ALL;
  CSingleLock NumberSingleLock(&m_NumberLock);
  NumberSingleLock.Lock();
  m_MessageNumber = m_MessageCounter++;
  NumberSingleLock.Unlock();
  m_UserRemark = 0;
  m_Error = kNoError;

  m_pDiagMessage = NULL;
  m_bIsMsgInit = false;
  InitDiagMsg();
  
#ifdef DEBUG
  if (LOGGING_REQUIRED)
  {
	  CString trace;
	  trace.Format(_T("Msg# %d: ctor (ref=%d)"), this->m_MessageNumber, this->m_ReceiversCounter);
	  CICATMessage::Log(&trace);
  }
#endif
#ifdef SUPPORT_CAT_MSG_SNAPSHOT
   cat_msg_create(this);
#endif
}

CICATMessage::CICATMessage(int m, int i, BYTE *pd /*=NULL*/, int dl /*=0*/, BOOL bMemAllocation /*true*/):m_tmpMsg(this)
{
   m_nDiagHCounter = 0;
   m_ModuleID = m;
   m_InstanceID = i;
   m_DataLen = dl;

   if (pd && dl)
   {
      if (bMemAllocation)
      {
         m_pData = new BYTE[m_DataLen];
         memcpy(m_pData, pd, m_DataLen);
      }
      else
      {
         m_pData = pd;
      }
   }
   else
   {
      m_pData = NULL;
   }

   m_ReceiversCounter = 0;
   ::GetLocalTime(&m_Time);
   m_Direction = MessageOUT_ALL;
   CSingleLock NumberSingleLock(&m_NumberLock);
   NumberSingleLock.Lock();
   m_MessageNumber = m_MessageCounter++;
   NumberSingleLock.Unlock();
   m_bConvertable = eStringProtocol;
   m_UserRemark = 0;
   m_Error = kNoError;

   if(m_DataLen > PDU_HEADER_LEN && m_ModuleID == 1 && m_bConvertable == eDIAGProtocol)
   {
      if(dl>kRMsgHCount)
      {
         if( m_pData[kRMsgHCount] && *(WORD*)&m_pData[kMsgSap] != DIAG_MI_LOGGED_SIGNAL)
         {
            m_nDiagHCounter = m_pData[kRMsgHCount];
            m_pData[kRMsgHCount] = 0;
         }
      }
   }

	m_pDiagMessage = NULL;
	m_bIsMsgInit = false;
	InitDiagMsg();
	
#ifdef DEBUG
   if (LOGGING_REQUIRED)
   {
	   CString trace;
	   trace.Format(_T("Msg# %d: ctor (ref=%d)"), this->m_MessageNumber, this->m_ReceiversCounter);
	   CICATMessage::Log(&trace);
   }
#endif
#ifdef SUPPORT_CAT_MSG_SNAPSHOT
   cat_msg_create(this);
#endif
}

CICATMessage::CICATMessage(int m, int i, BYTE *pd , int dl , BYTE *pd2 , int dl2):m_tmpMsg(this)
{
	m_nDiagHCounter = 0;
	m_ModuleID = m;
	m_InstanceID = i;
	m_DataLen = dl + dl2;
	

	m_pData = new BYTE[m_DataLen];
	memcpy(m_pData, pd, dl);
	memcpy(m_pData+dl, pd2, dl2);
	
	m_ReceiversCounter = 0;
	::GetLocalTime(&m_Time);
	m_Direction = MessageOUT_ALL;
	CSingleLock NumberSingleLock(&m_NumberLock);
	NumberSingleLock.Lock();
    m_MessageNumber = m_MessageCounter++;
    NumberSingleLock.Unlock();
	m_bConvertable = eStringProtocol;
	m_UserRemark = 0;
	m_Error = kNoError;
	
if(m_DataLen > PDU_HEADER_LEN && m_ModuleID == 1 && m_bConvertable == eDIAGProtocol)
   {
      if(dl>kRMsgHCount)
      {
         if( m_pData[kRMsgHCount] && *(WORD*)&m_pData[kMsgSap] != DIAG_MI_LOGGED_SIGNAL)
         {
            m_nDiagHCounter = m_pData[kRMsgHCount];
            m_pData[kRMsgHCount] = 0;
         }
      }
   }


	m_pDiagMessage = NULL;
	m_bIsMsgInit = false;
	InitDiagMsg();
#ifdef SUPPORT_CAT_MSG_SNAPSHOT
   cat_msg_create(this);
#endif
}

CICATMessage::CICATMessage(CICATMessage &message):m_tmpMsg(this)
{
   m_nDiagHCounter = message.m_nDiagHCounter;
   m_ModuleID = message.m_ModuleID;
   m_InstanceID = message.m_InstanceID;
   m_DataLen = message.m_DataLen;
   if (m_DataLen)
   {
      m_pData = new BYTE[m_DataLen];
      memcpy(m_pData, message.m_pData, m_DataLen);
   }
   else
      m_pData = NULL;
   m_ReceiversCounter = 0;
   ::GetLocalTime(&m_Time);
   m_Direction = MessageOUT_ALL;
   m_MessageNumber = message.m_MessageNumber;
   m_bConvertable = message.m_bConvertable;
   m_UserRemark = message.m_UserRemark;
   m_Error = message.m_Error;

	m_bIsMsgInit = false;
	InitDiagMsg();
	
#ifdef DEBUG
   if (LOGGING_REQUIRED)
   {
	   CString trace;
	   trace.Format(_T("Msg# %d: ctor (ref=%d)"), this->m_MessageNumber, this->m_ReceiversCounter);
	   CICATMessage::Log(&trace);
   }
#endif
#ifdef SUPPORT_CAT_MSG_SNAPSHOT
   cat_msg_create(this);
#endif
}


// WARNING: this method changes the message contents without locking it, so it shouldn't be used along concurrency!
void CICATMessage::operator = (CICATMessage &message)
{
   m_nDiagHCounter = message.m_nDiagHCounter;
   m_ModuleID = message.m_ModuleID;
   m_InstanceID = message.m_InstanceID;
   m_Time = message.m_Time;
   if (m_pData != NULL)
   {
      delete [] m_pData;
      m_pData=NULL;
   }
   if (message.m_DataLen > 0 && message.m_pData != NULL)
   {
      m_DataLen = message.m_DataLen;
      m_pData = new BYTE[m_DataLen];
      memcpy(m_pData, message.m_pData, m_DataLen);
   }
   else
   {
      m_DataLen = 0;
      m_pData = NULL;
   }
   m_Direction = message.m_Direction;
   m_MessageNumber = message.m_MessageNumber;
   m_bConvertable = message.m_bConvertable;
   m_UserRemark = message.m_UserRemark;
   m_Error = message.m_Error;

	InitDiagMsg();
	CSingleLock ReceiversCounterSingleLock(&m_ReceiversCounterLock);
   ReceiversCounterSingleLock.Lock();
   m_ReceiversCounter = 0;
#ifdef SUPPORT_CAT_MSG_SNAPSHOT
   cat_msg_reset(this);
#endif
}


void CICATMessage::InitDiagMsg()
{
	if(m_bIsMsgInit)
	{
		delete m_pDiagMessage;
		m_pDiagMessage = NULL;
	}	

	m_pDiagMessage = &m_tmpMsg;
	m_bIsMsgInit = false;
}

IDiagMessage* CICATMessage::CreateDiagMsg()
{
	CSingleLock sl(&m_LockDiagmsg,TRUE);

	if (m_bIsMsgInit)
	{
		return m_pDiagMessage;
	}

	if (m_Error != kNoError)
	{
		m_pDiagMessage = new CDiagMessage(this);
		m_bIsMsgInit = true;
		return m_pDiagMessage;
	}

	switch(m_bConvertable)
	{
	case eDIAGProtocol:
		{
			BYTE sap = *(m_pData) & 0x0F;

			if (m_ModuleID == 1) // MODULE_COMMUNICATION
			{
				switch (sap)
				{
				case APPLICATION_REPORT:
				case APPLICATION_REPORT_ALIGNED:
					m_pDiagMessage = new CDiag1MessageDiag(this);
					break;
				case RETURN_SERVICE:
					m_pDiagMessage = new CDiag1MessageIS(this);
					break;
				case DIAG_MI_LOGGED_SIGNAL:
				case DIAG_MI_SIGNAL:
				case DIAG_MI_SPECIAL_LOGGED_SIGNAL:
					m_pDiagMessage = new CDiag1MessageGKI(this);
					break;
				default:
					m_pDiagMessage = new CDiag1Message(this);
				}
			}
			else
			{
				switch (sap)
				{
				case COMMAND_SERVER:
				case FIXUPS_COMMAND_SERVER:
					m_pDiagMessage = new CDiag1MessageDiag(this);
					break;
				case INTERNAL_SERVICE:
					m_pDiagMessage = new CDiag1MessageIS(this);
					break;
				case DIAG_MI_SIGNAL:
					m_pDiagMessage = new CDiag1MessageGKI(this);
					break;
				default:
					m_pDiagMessage = new CDiag1Message(this);
				}
			}
		}
		break;
	case eStringProtocol:
		m_pDiagMessage = new CStringMessage(this);
		break;

	default:
		m_pDiagMessage = new CDiagMessage(this);
	}

	m_bIsMsgInit = true;
	return m_pDiagMessage;
}

LPBYTE CICATMessage::GetDataBuffer()
{ 
	return m_pDiagMessage->GetDataBuffer();	
}

WORD CICATMessage::GetDataBufferLen()
{ 
	return m_pDiagMessage->GetDataBufferLen();	
}

BYTE CICATMessage::GetMsgType()
{ 
	return m_pDiagMessage->GetMsgType();	
}

BYTE CICATMessage::GetHeaderLen_DW()
{ 
	return m_pDiagMessage->GetHeaderLen_DW();	
}

BYTE CICATMessage::GetPriority()
{ 
	BYTE tmpPriority = m_pDiagMessage->GetChannel();

	if (tmpPriority != 2 && tmpPriority != 3)
	{
		tmpPriority = 0;//to indicate that this is a message that should be shown
	}

	return tmpPriority; 	
}

BYTE CICATMessage::GetChannel()
{ 
	return m_pDiagMessage->GetChannel();	
}

BYTE CICATMessage::GetSrcId()
{ 
	return m_pDiagMessage->GetSrcId();	
}

BYTE CICATMessage::GetDstId()
{ 
	return m_pDiagMessage->GetDstId();	
}


unsigned long long CICATMessage::Delete(const CString* callerName /*= NULL*/)
{
	UINT64 messageNumber = this->m_MessageNumber;
#ifdef SUPPORT_CAT_MSG_SNAPSHOT
   cat_msg_delete(this, callerName);
#endif

    if (!m_ReceiversCounterLock.IsKindOf(RUNTIME_CLASS(CCriticalSection)))
        // in case m_ReceiversCounterLock get destructed before this, such as
        // in ClearFIFO() called from SmartShell< CommandChannel > destructor
    {
        if (0 < m_ReceiversCounter && 0 == --m_ReceiversCounter)
        {
            try
            {
                delete this;
                TRACE(_T("Message %I64u deleted without locking\n"), messageNumber);
            }
            catch (...)
            {
                TRACE(_T("Exception thrown on delete message %I64u\n"), messageNumber);
            }
        }
        return messageNumber;
    }

	//m_ReceiversCounterLock.Lock();
  CSingleLock singleLock(&m_ReceiversCounterLock);
  singleLock.Lock();

	if (0 < m_ReceiversCounter)
	{
		m_ReceiversCounter--;

#ifdef DEBUG
		if (LOGGING_REQUIRED)
		{
			CString trace;
			trace.Format(_T("Msg# %I64d: del by %s (ref=%d)"), this->m_MessageNumber, (callerName ? (*callerName) : _T("anonymous")), this->m_ReceiversCounter);
			CICATMessage::Log(&trace);
		}
#endif

		if (0 == m_ReceiversCounter)
		{
			try
			{
				delete this;
			}
			catch (CMemoryException* e)
			{
				(void)e;
				LOG_ERROR(_T("MemoryException thrown by delete message (message index - %I64u)"), messageNumber);
			}
			catch (...)
			{
				LOG_ERROR(_T("Exception throw by delete message (message index: %I64u)"), messageNumber);
			}
		}
	}

	//m_ReceiversCounterLock.Unlock();
  singleLock.Unlock();

	return messageNumber;
}


void CICATMessage::GetNumber()
{
	CSingleLock NumberSingleLock(&m_NumberLock);
	NumberSingleLock.Lock();
   m_MessageNumber = m_MessageCounter++;
}


void CICATMessage::Serialize(CArchive& ar)
{
   if (ar.IsStoring())
   {
      ar << m_ModuleID;
      ar << m_InstanceID;
      m_Time.Serialize(ar);

      ar << m_DataLen;

      if (PDU_HEADER_LEN < m_DataLen )
      {
         int nOffset = m_DataLen - PDU_HEADER_LEN;

         if (m_ModuleID == 1 && m_nDiagHCounter && nOffset >= 0)
         {
            BYTE pHeader[PDU_HEADER_LEN];

            memcpy(pHeader, m_pData, PDU_HEADER_LEN);

            pHeader[kMsgHCount] = m_nDiagHCounter;

            ar.Write(pHeader, PDU_HEADER_LEN);

            if (nOffset)
            {
               ar.Write(&m_pData[PDU_HEADER_LEN], nOffset);
            }
         }
         else
         {
            ar.Write(m_pData, m_DataLen);
         }
      }
      else
      {
         ar.Write(m_pData, m_DataLen);
      }

      int dir = (int)m_Direction;
      ar << dir;

      DWORD low = LODWORD(m_MessageNumber);
      ar << low;
      DWORD hi = HIDWORD(m_MessageNumber);
      ar << hi;

      UINT uiConvertAndError = m_bConvertable | ((UINT)((WORD)m_Error)<<16);

      ar << uiConvertAndError;

      ASSERT( m_UserRemark == '\0' );
      ar << m_UserRemark;
   }
   else
   {
		InitDiagMsg();

      ar >> m_ModuleID;
      ar >> m_InstanceID;
      m_Time.Serialize(ar);

      ar >> m_DataLen;

      if (m_DataLen > 0)
      {
         if (m_pData)
         {
            delete []m_pData;
            m_pData=NULL;
         }

         m_pData = new BYTE[m_DataLen];
         ar.Read(m_pData, m_DataLen);
      }
      int dir;
      ar >> dir;
      m_Direction = (eDirection)dir;

      DWORD hi, low;
      ar >> low;
      ar >> hi;
      m_MessageNumber = MAKEUINT64(low, hi);

      UINT uiConvertAndError;
      ar >> uiConvertAndError;
      m_bConvertable = uiConvertAndError & (0x0000FFFF);
      m_Error = (EMsgError)(uiConvertAndError >> 16);

      ar >> m_UserRemark;

      if (m_ModuleID == 1 && m_DataLen > PDU_HEADER_LEN && m_bConvertable == eDIAGProtocol && m_pData[kRMsgHCount] &&
         *(WORD*)&m_pData[kMsgSap] != DIAG_MI_LOGGED_SIGNAL && m_pData[kMsgHCount])
      {
         m_nDiagHCounter = m_pData[kMsgHCount];
         m_pData[kMsgHCount] = 0;
      }
   }
}

void CICATMessage::AddRef(const CString* callerName /*=NULL*/)
{
	CSingleLock ReceiversCounterSingleLock(&m_ReceiversCounterLock);
	ReceiversCounterSingleLock.Lock();
   ++m_ReceiversCounter;

#ifdef DEBUG
   if (LOGGING_REQUIRED)
   {
	   if ((callerName == NULL) || CString(_T("")) == (*callerName))	
		   throw std::exception::exception("CICATMessage::AddRef requires a callerName parameter!");

	   CString trace;
	   trace.Format(_T("Msg# %I64d: add-ref by %s (ref=%d)"), this->m_MessageNumber, (callerName ? (*callerName) : _T("anonymous")), this->m_ReceiversCounter);
	   CICATMessage::Log(&trace);
   }
#endif

#ifdef SUPPORT_CAT_MSG_SNAPSHOT
   cat_msg_add_ref(this, callerName);
#endif
}

bool CICATMessage::IsFromTarget()
{
	return (m_ModuleID == 1);
}

DWORD CICATMessage::GetFrameNum()
{ 
	SetMessage();
	return m_pDiagMessage->GetFrameNum();	
}

BOOL CICATMessage::IsEmpty()
{
	return (m_pData == NULL || m_DataLen == 0);
}


BOOL CICATMessage::IsDiagProtocol()
{
	SetMessage();

	return (m_bConvertable == eDIAGProtocol);
}

bool	CICATMessage::IsMessageTypeDiag()			
{ 
	SetMessage();

	return m_pDiagMessage->IsMessageTypeDiag();	
}

// bool CICATMessage::IsApp()
// {
// 	if(IsEmpty())
// 		return false;
// 
// 	if (IsFromTarget())
// 		return ((((WORD*)m_pData)[0] & 0x8000) > 0);
// 	else
// 		return ((m_pData[0] & 0x80) > 0);
// }	

bool CICATMessage::IsClientMatch( int targetType )
{
	if(IsEmpty())
		return false;

	SetMessage();

	return ((m_pDiagMessage->GetClientID() == targetType) /*|| (IsApp() && IS_APP_SIDE(targetType))*/);
}

int CICATMessage::GetClientID()
{
	SetMessage();

	return m_pDiagMessage->GetClientID();
}

WORD CICATMessage::GetMsgId()
{ 
	SetMessage();

	return m_pDiagMessage->GetMsgId();	
}

BYTE CICATMessage::GetModuleID(bool bFromData/*= false*/)
{ 	
	SetMessage();

	return m_pDiagMessage->GetModuleID(bFromData);	
}

WORD CICATMessage::GetDataLen()
{ 
	SetMessage();
	return m_pDiagMessage->GetDataLen();	
}

LPBYTE CICATMessage::GetData(UINT nIdx)
{ 
	SetMessage();
	return m_pDiagMessage->GetData(nIdx);	
}

int	CICATMessage::GetDevice()
{ 
	SetMessage();
	return m_pDiagMessage->GetDevice();	
}

DWORD CICATMessage::GetTargetTs()
{ 
	SetMessage();
	return m_pDiagMessage->GetTargetTs();	
}

WORD CICATMessage::GetMsgCtr()
{ 
	SetMessage();
	return m_pDiagMessage->GetMsgCtr();	
}

DWORD CICATMessage::GetFrame2Num()
{ 
	SetMessage();
	return m_pDiagMessage->GetFrame2Num();	
}

WORD CICATMessage::GetHeaderLen()
{ 
	SetMessage();
	return m_pDiagMessage->GetHeaderLen();	
}

BYTE CICATMessage::GetDiagSap()
{ 
	SetMessage();
	return m_pDiagMessage->GetDiagSap();	
}

BYTE CICATMessage::GetService()
{ 
	SetMessage();
	return m_pDiagMessage->GetService();	
}

WORD CICATMessage::GetFullDiagSap()
{ 
	SetMessage();
	return m_pDiagMessage->GetFullDiagSap();	
}

BYTE CICATMessage::GetDiagId()
{ 
	SetMessage();
	return m_pDiagMessage->GetDiagId();	
}

WORD CICATMessage::GetExtraData()
{
	SetMessage();
	return m_pDiagMessage->GetExtraData();
}

bool CICATMessage::IsMessageTypeService()
{ 
	SetMessage();
	return m_pDiagMessage->IsMessageTypeService();	
}

bool CICATMessage::IsMessageTypeSignal()
{ 
	SetMessage();
	return m_pDiagMessage->IsMessageTypeSignal();	
}

bool CICATMessage::IsMessageTypeString()
{ 
	SetMessage();
	return m_pDiagMessage->IsMessageTypeString();	
}

bool CICATMessage::IsValidMessage()
{ 
	SetMessage();
	return m_pDiagMessage->IsValidMessage();	
}

int	CICATMessage::GetDiagMessageType()
{ 
	SetMessage();
	return m_pDiagMessage->GetDiagMessageType();	
}

bool CICATMessage::IsAligned()
{ 
	SetMessage();
	return m_pDiagMessage->IsAligned();	
}

UINT64 CICATMessage::GetMessageNumber()
{ 
	SetMessage();
	return m_MessageNumber;	
}

const CSystemTime&	CICATMessage::GetPCTimeStamp()
{ 
	SetMessage();
	return m_pDiagMessage->GetPCTimeStamp();	
}

WORD CICATMessage::GetDspOpCode()
{ 
	SetMessage();
	return m_pDiagMessage->GetDspOpCode();	
}

WORD CICATMessage::GetEntireDspOpCode()
{ 
	SetMessage();
	return m_pDiagMessage->GetEntireDspOpCode();	
}

bool CICATMessage::GetUserRemark( CString& str)
{ 
	SetMessage();
	return m_pDiagMessage->GetUserRemark(str);	
}

bool CICATMessage::IsPrintMessage()
{ 
	SetMessage();
	return m_pDiagMessage->IsPrintMessage();	
}

int CICATMessage::GetMsgSize(bool bIncludeDataLength /*= true*/)
{
	int tmp = sizeof(CSerialzeData) + sizeof(SYSTEMTIME) /*+ m_UserRemark.GetLength() + 1/*The NULL character at the end of the string*/ ;

	if (bIncludeDataLength)
	{
		tmp += m_DataLen;
	}

	return tmp; 
}

UINT CICATMessage::GetLengthInFile()
{
   return GetMsgSize();//45 + m_DataLen;
}

