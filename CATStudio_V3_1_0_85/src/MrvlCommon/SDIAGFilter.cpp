#include "StdAfx.h"
#include "CommonDefs.h"
#include "SDIAGFilter.h"
#include "ICATMessage.h"
#include "Logging/Logging.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CSDIAGFilter::CSDIAGFilter(bool bAppSide)
{
  m_bAppSide = bAppSide;
  m_nFilterSize = 64*1024;

  m_pFilter = new char[m_nFilterSize];

  for(UINT i=0; i<m_nFilterSize; ++i)
  {
     m_pFilter[i] = 0;
  }
  
}

CSDIAGFilter::~CSDIAGFilter(void)
{
	if(m_pFilter)
	{
		delete []m_pFilter;
		m_pFilter = NULL;
	}
	m_nFilterSize = 0;
}

long CSDIAGFilter::UpdateFilter( LPVOID lpMessageIdBuffer, int nMsgIdCount, int nMsgIdSize, bool bLetItPass  )
{
   LOG_INFO(_T(""));
 
   ASSERT(nMsgIdSize==2);
   char delta = bLetItPass? 1:-1;
   USHORT* pBuffer = (USHORT*) lpMessageIdBuffer;

   for(int i=0; i<nMsgIdCount; ++i)
   {
      USHORT uMsgId = pBuffer[i];
      if( uMsgId>=m_nFilterSize )
      {
         LOG_ERROR(_T("Message id exceeds filter size(%d)"), (int)uMsgId);
         continue;
      }
 
      m_pFilter[uMsgId]  = max(0, m_pFilter[uMsgId] + delta);
   }

   return 0;


   /*int nZeroRecver=0;
   int nOneRecver=0;
   int nTwoRecver=0;
   int nThreeRecver=0;
   for(unsigned int i=0; i<m_nFilterSize; ++i)
   {
      if( m_pFilter[i]==0 )
         ++nZeroRecver;
      if( m_pFilter[i]==1 )
         ++nOneRecver;
      if( m_pFilter[i]==2 )
         ++nTwoRecver;
   }

   LOG_NOTICE(_T("ZeroRcvr=%d, OneRcvr=%d, TwoRcvr=%d"), nZeroRecver, nOneRecver, nTwoRecver);
   
   return 0;
   */
}

BOOL CSDIAGFilter::IsPassFilter( CICATMessage* pMessage )
{
   if ( pMessage->m_bConvertable != eDIAGProtocol )
      return TRUE;

   if ( pMessage->m_pData == NULL || pMessage->m_DataLen < PDU_HEADER_LEN )
      return TRUE;

   WORD diagSap = *((WORD *)&pMessage->m_pData[0]);
   if ( !m_bAppSide )
   {
      if ( diagSap != APPLICATION_REPORT && diagSap != APPLICATION_REPORT_ALIGNED )
         return TRUE;
   }
   else
   {
      if ( diagSap != (APPLICATION_REPORT|APP_SIDE_MASK_FOR_RECEIVING) && diagSap != (APPLICATION_REPORT_ALIGNED|APP_SIDE_MASK_FOR_RECEIVING) )
         return TRUE;
   }

   USHORT moduleID = *((USHORT *)(&pMessage->m_pData[DIAG_SAP_INDEX + 4]));
   USHORT uMsgId = *((USHORT *)(&pMessage->m_pData[DIAG_SAP_INDEX + 6]));


   if ( uMsgId >= m_nFilterSize )
   {
      LOG_WARN(_T("MessageId(%d) exceeds FilterSize(%d)"), uMsgId, m_nFilterSize);
      return TRUE;
   }

   if( m_pFilter[uMsgId] > 0 )
   {
      return TRUE;
   }
   else
   {
      return FALSE;
   }
  
}

void CSDIAGFilter::SetAllPass(bool bPass)
{
   LOG_NOTICE(_T("DIAG%s %s"), m_bAppSide? _T("AppSide"):_T(""), bPass? _T("Pass"):_T("Block"));
   char delta = bPass? 1:-1;
   for(unsigned int i=0; i<m_nFilterSize; ++i)
   {
      m_pFilter[i] = max(0, m_pFilter[i] + delta);
   }

}
