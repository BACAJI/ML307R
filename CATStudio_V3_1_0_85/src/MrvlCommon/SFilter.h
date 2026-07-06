#pragma once
#include "SDIAGFilter.h"
#include "SGKIFilter.h"

enum EMSGType
{
   eDIAGCPMSG      = 1,
   eDIAGAPMSG      = 2,
   eGKIMSG         = 3,
   eDSPMSG         = 4,
   eMSG            = 5,
   eMSGTypeMask    = 0xF
};


class CICATMessage;

class CATCORE_DLLEXPORT CSFilter
{
public:
  CSFilter(int nDevice);
  ~CSFilter(void);
  
public:  
  bool   UpdateFilter(EFilterType fileterType, void* buf, int count, int size, bool pass);
  bool   IsPassFilter(CICATMessage* pMessage);
  bool   SetAllPassBlock(EFilterType filterType, bool bPass);


private:
  EFilterType GetFilterType(LPVOID lpCmdData, int nCmdDataLen);
  EFilterType GetFilterType(CICATMessage* pMessage);

public:
  CSDIAGFilter m_DiagFilterAppSide;
  CSDIAGFilter m_DiagFilter;
  CSGKIFilter  m_GKIFilter;
  bool        m_bPassIfFilterError;
  int         m_nDevice;

};
