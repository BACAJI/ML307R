#include "StdAfx.h"
#include "CommonDefs.h"
#include "SGKIFilter.h"
#include "ICATMessage.h"
#include "Logging/Logging.h"

CSGKIFilter::CSGKIFilter(void)
{
   m_nAllPass = 0;
}

CSGKIFilter::~CSGKIFilter(void)
{
  m_mapFilter.clear();
}

void CSGKIFilter::SetAllPass(bool bPass)
{
   LOG_NOTICE(_T("GKI Pass/Block=%s"), bPass?_T("Pass"):_T("Block"));
   if( bPass )
      m_nAllPass++;
   else
      m_nAllPass--;
   
   m_nAllPass = max(0, m_nAllPass);
}


long CSGKIFilter::UpdateFilter( LPVOID lpMessageIdBuffer, int nMsgIdCount, int nMsgIdSize, bool bLetItPass )
{
   ASSERT(nMsgIdSize==4);
   DWORD* pdwBuffer = (DWORD*) lpMessageIdBuffer;
   DWORD  dwMsgId;
   int8   delta = bLetItPass? 1:-1;
   for(int i=0; i<nMsgIdCount; ++i)
   {
       dwMsgId = pdwBuffer[i];

       map<uint32, int8>::iterator it = m_mapFilter.find(dwMsgId);

       // 如果key不存在则添加
       if( it==m_mapFilter.end() )
       {
          m_mapFilter[dwMsgId] = max(0, delta);
       }
       else
       {
          m_mapFilter[dwMsgId] = max(0, m_mapFilter[dwMsgId] + delta);
       }
   }

   return 0;
}


BOOL CSGKIFilter::IsPassFilter( CICATMessage* pMessage )
{

  DWORD nSigID;

 if ( pMessage->m_bConvertable == eDIAGProtocol )
  {   
    int iLength=pMessage->m_DataLen-DIAG_HEADER_FOR_RECEIVING_MI_SIGANLS;
    if ( pMessage->m_pData == NULL || pMessage->m_DataLen < DIAG_HEADER_FOR_RECEIVING_MI_SIGANLS )
      return TRUE;

    WORD diagSap = *((WORD *)&pMessage->m_pData[0]);
    if ( diagSap == DIAG_MI_SIGNAL || diagSap == DIAG_MI_LOGGED_SIGNAL || diagSap == DIAG_MI_SPECIAL_LOGGED_SIGNAL )
      nSigID = FindGKISignalID_DIAG(diagSap, &pMessage->m_pData[DIAG_HEADER_FOR_RECEIVING_MI_SIGANLS],iLength);
    else
      return TRUE;

    iter_t it = m_mapFilter.find(nSigID); 
    if( it != m_mapFilter.end() && it->second>0 )
       return TRUE;
    if( m_nAllPass>0 )
       return TRUE;
    return FALSE;

  }
  else if ( pMessage->m_bConvertable == eEMMIProtocol )
  {
    int iLength=pMessage->m_DataLen-EMMI_HEADER_LEN;
    if ( pMessage->m_pData == NULL || pMessage->m_DataLen < EMMI_HEADER_LEN )
      return TRUE;

    BYTE signalType = pMessage->m_pData[0];
    if ( signalType == SIGNAL_MI || signalType == LOGGED_SIGNAL_MI )
      nSigID = FindGKISignalID_EMMI(signalType, &pMessage->m_pData[EMMI_HEADER_LEN],iLength);
    else
      return TRUE;
  

    iter_t it = m_mapFilter.find(nSigID); 
    if( it != m_mapFilter.end() && it->second>0 )
       return TRUE;

    if( m_nAllPass>0 )
       return TRUE;
    
    return FALSE;
  }

  return TRUE;
}

DWORD CSGKIFilter::FindGKISignalID_DIAG( WORD diagSap, BYTE *pBuffer,int iLength )
{
  switch ( diagSap )
  {
  case DIAG_MI_SIGNAL:
    return FindGKISignalID(pBuffer,iLength);
  case DIAG_MI_LOGGED_SIGNAL:
    return FindGKILoggedSignalID(pBuffer,iLength);
  case DIAG_MI_SPECIAL_LOGGED_SIGNAL:
    return FindGKISpecialLoggedSignalID(pBuffer,iLength);
  default:
    break;
  }

  return (DWORD)(INVALID_SIGID);  
}



DWORD CSGKIFilter::FindGKISignalID(BYTE *pBuffer, int iLength, BOOL bSide)
{ 
  int taskIDSize = eTaskIdSize;
  int counter = 2*taskIDSize;
  int structAlign = (eAlignPolicy == eAlignMinimum) ?  sizeof(short) : eAlign4Bytes;
  ALIGN(counter, structAlign);
  counter += sizeof(short); //Length
  int nSignalIDSize = eSignalIdSize; 

  ALIGN(counter, nSignalIDSize);
  if(counter>=iLength||counter<0)
    return INVALID_SIGID;
  else
  {
    DWORD dwSigID = ( nSignalIDSize == 2 ) ? (DWORD)(*((WORD *)&pBuffer[counter])) : *((DWORD *)&pBuffer[counter]);
    return dwSigID;
  }
}



DWORD CSGKIFilter::FindGKILoggedSignalID(BYTE *pBuffer, int iLength,BOOL bSide)
{	
   int taskIDSize = eTaskIdSize;
   int nSignalIDSize = eSignalIdSize;
   int counter = 2*taskIDSize;
   ALIGN(counter, MAX_ALIGN_STRUCT);
   counter += 2*sizeof(long) + sizeof(short); // Time-Ticks, Tick-Counter and Length
   ALIGN(counter, nSignalIDSize);

   /*
   CConverterManager *pCM = theCM;
   int taskIDSize = pCM->GetGKITaskIDSize(bSide);
   int counter = 2*taskIDSize;
   ALIGN(counter, MAX_ALIGN_STRUCT);

   counter += 2*sizeof(long) + sizeof(short); // Time-Ticks, Tick-Counter and Length

   int nSignalIDSize = pCM->GetGKISignalIDSize(bSide);
   ALIGN(counter, nSignalIDSize);
   */
  

  if(counter>=iLength||counter<0)
    return INVALID_SIGID;
  else
  {
    DWORD dwSigID = ( nSignalIDSize == 2 ) ? (DWORD)(*((WORD *)&pBuffer[counter])) : *((DWORD *)&pBuffer[counter]);
    return dwSigID;
  }
}



DWORD CSGKIFilter::FindGKISpecialLoggedSignalID(BYTE *pBuffer,int iLength, BOOL bSide)
{
   /*
  return INVALID_SIGID;

  CConverterManager *pCM = theCM;

  int counter = 2*sizeof(long); // frameNumber, frameTicks

  DWORD dwSkipSize = *((DWORD *)(&pBuffer[counter]));
  counter += sizeof(DWORD);
  counter += dwSkipSize;

  EEnumSize enumSize = pCM->GetEnumerationSize(bSide);

  ALIGN(counter, enumSize == eEnumSize4Bytes ? 4 : 2);	

  int taskIDSize = pCM->GetGKITaskIDSize(bSide);
  ALIGN(counter, taskIDSize);

  counter += 2*taskIDSize;	// Source & Target task-IDs

  int structAlign = (pCM->GetStructureAlignment(bSide) == eAlignMinimum) ?  sizeof(short) : eAlign4Bytes; 
  ALIGN(counter, structAlign);

  counter += sizeof(USHORT);	// Length

  int nSignalIDSize = pCM->GetGKISignalIDSize(bSide);
  ALIGN(counter, nSignalIDSize);

  if(counter>=iLength||counter<0)
    return INVALID_SIGID;
  else
  {
    DWORD dwSigID = ( nSignalIDSize == 2 ) ? (DWORD)(*((WORD *)&pBuffer[counter])) : *((DWORD *)&pBuffer[counter]);
    return dwSigID;
  }
  */



  int counter = 2*sizeof(long); // frameNumber, frameTicks

  DWORD dwSkipSize = *((DWORD *)(&pBuffer[counter]));
  counter += sizeof(DWORD);
  counter += dwSkipSize;

  EEnumSize enumSize = (EEnumSize) eEnumSize;

  ALIGN(counter, enumSize == eEnumSize4Bytes ? 4 : 2);	

  int taskIDSize = eTaskIdSize;
  ALIGN(counter, taskIDSize);

  counter += 2*taskIDSize;	// Source & Target task-IDs

  int structAlign = (eAlignPolicy == eAlignMinimum) ?  sizeof(short) : eAlign4Bytes; 
  ALIGN(counter, structAlign);

  counter += sizeof(USHORT);	// Length

  int nSignalIDSize = eSignalIdSize;
  ALIGN(counter, nSignalIDSize);

  if(counter>=iLength||counter<0)
     return INVALID_SIGID;
  else
  {
     DWORD dwSigID = ( nSignalIDSize == 2 ) ? (DWORD)(*((WORD *)&pBuffer[counter])) : *((DWORD *)&pBuffer[counter]);
     return dwSigID;
  }

}

DWORD CSGKIFilter::FindGKISignalID_EMMI(BYTE signalType,BYTE *pBuffer,int iLength )
{

  if ( signalType == SIGNAL_MI )
    return FindGKISignalID(pBuffer,iLength);

  return FindGKILoggedSignalID(pBuffer,iLength);
}


