#pragma once
#include "DIAGFilter.h"
#include "GKIFilter.h"
#include "afxmt.h"

class CICATMessage;
class CFilter
{
  enum EMSGType
  {
    eDIAGCPMSG      = 1,
    eDIAGAPMSG      = 2,
    eGKIMSG         = 3,
    eDSPMSG         = 4,
    eMSGTypeMask    = 0xF
  };

  enum EFilterType
  {
    eUnknowFilter   = 0,
    eDIAGFilterCP = 1,
    eDIAGFilterAP = 2,
    eGKIFilter  = 3,
    eDSPFilter  = 4,
  };

private:
  static CFilter*   Instance();
  static void       SafeClose();
  static CFilter*   m_pInstance;
  static CCriticalSection m_Lock;


public:
  CFilter(void);
  ~CFilter(void);
  
  
public:
  void        UpdateFilter(LPVOID lpCmdData, int nCmdDataLen);
  BOOL        IsPassFilter(CICATMessage* pMessage);
  BOOL        IsPassFilterSeries(CICATMessage* pMessage);

private:
  EFilterType GetFilterType(LPVOID lpCmdData, int nCmdDataLen);
  EFilterType GetFilterType(CICATMessage* pMessage);
  BOOL        inline Lock();
  void        inline UnLock();

  CDIAGFilter m_DiagFilterAppSide;
  CDIAGFilter m_DiagFilter;
  CGKIFilter  m_GKIFilter;
  BOOL        m_bPassIfFilterError;

};

BOOL  CFilter::Lock()
{
  m_Lock.Lock();

  if( m_pInstance==NULL )
  {
    m_Lock.Unlock();
    return false;
  }
  else
    return true;
}

void CFilter::UnLock()
{
  m_Lock.Unlock();
}


#define theFilter   (CFilter::Instance())