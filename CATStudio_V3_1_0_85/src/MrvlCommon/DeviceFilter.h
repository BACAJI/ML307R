#pragma once
#include "GeneralMacroDefine.h"

class CATCORE_DLLEXPORT CDeviceFilter
{
public:
   CDeviceFilter(int iDevice, int nInitReceiver);
   virtual ~CDeviceFilter();

   bool UpdateFilter(bool bPass);
   bool IsPassFilter(){return m_nReceiver>0;};
   
private:
   int  m_nReceiver;
   int  m_iDevice;
};