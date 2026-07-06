#include "StdAfx.h"
#include "ICATMessage.h"
#include "CommonDefs.h"
#include "SFilter.h"
#include "SGKIFilter.h"
#include "ipc/ipc_message.h"
#include "Logging/Logging.h"


CSFilter::CSFilter(int nDevice)
: m_nDevice(nDevice), m_DiagFilter(false), m_DiagFilterAppSide(true)
{
  m_bPassIfFilterError = true;
}

CSFilter::~CSFilter(void)
{
}

bool CSFilter::IsPassFilter( CICATMessage* pMessage )
{
  BOOL bPass=TRUE;
  bPass = bPass && m_DiagFilter.IsPassFilter(pMessage);

  bPass = bPass && m_DiagFilterAppSide.IsPassFilter(pMessage);

  bPass = bPass && m_GKIFilter.IsPassFilter(pMessage);

  return (bPass==TRUE);
}



bool CSFilter::UpdateFilter( EFilterType fileterType, void* buf, int count, int size, bool pass )
{
   LOG_INFO(_T(""));
   long rc=0;
   switch(fileterType)
   {
   case eDIAGFilter:
      rc=m_DiagFilter.UpdateFilter(buf, count, size, pass);
      return rc==0? true:false;

   case eDIAGFilterAppSide:
      rc=m_DiagFilterAppSide.UpdateFilter(buf, count, size, pass);
      return rc==0? true:false;

   case eGKIFilter:
      rc=m_GKIFilter.UpdateFilter(buf, count, size, pass);
      return rc==0? true:false;

   default:
      return true;
   }
}

bool CSFilter::SetAllPassBlock( EFilterType filterType, bool bPass )
{
   switch(filterType)
   {
   case eDIAGFilter:
      m_DiagFilter.SetAllPass(bPass);
      break;
   case eDIAGFilterAppSide:
      m_DiagFilterAppSide.SetAllPass(bPass);
      break;
   case eGKIFilter:
      m_GKIFilter.SetAllPass(bPass);
      break;
   case eAllFilter:
      m_DiagFilter.SetAllPass(bPass);
      m_DiagFilterAppSide.SetAllPass(bPass);
      m_GKIFilter.SetAllPass(bPass);
      break;
   default:
      break;
   }

   return true;
}
