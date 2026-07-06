#pragma once
#include "GeneralMacroDefine.h"

class CICATMessage;
class CATCORE_DLLEXPORT ISFilter
{
public:

public:
  ISFilter(void);
  virtual ~ISFilter(void);

  virtual void    LoadFilter()=0;
  virtual void    SaveFilter()=0;
  virtual char*   GetFilter()=0;

  virtual void    SetAllPass(bool)=0;
  virtual BOOL    IsPassFilter(CICATMessage* pMessage)=0;

  bool    m_bPassIfMSGIDNotFound;
  bool    m_bFilterUpdated;
  int     m_nAllPass;

};
