#pragma once
#include "ISFilter.h"

class CATCORE_DLLEXPORT CSDIAGFilter : public ISFilter
{
public:
  CSDIAGFilter(bool bAppSide=false);
  virtual ~CSDIAGFilter(void);
  
  void        LoadFilter(){};
  void        SaveFilter(){};
  char*       GetFilter(){return m_pFilter;};

  void        SetAllPass(bool bPass);
  long        UpdateFilter( LPVOID lpMessageIdBuffer, int nMsgIdCount, int nMsgIdSize, bool bLetItPass );
  BOOL        IsPassFilter(CICATMessage* pMessage);

private:
  char*       m_pFilter;
  UINT        m_nFilterSize;
  bool        m_bAppSide;

};
