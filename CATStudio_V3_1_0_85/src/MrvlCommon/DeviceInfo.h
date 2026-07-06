#pragma once

#include "DeviceStatus.h"
#include "CommSettings.h"


class CDeviceInfo
{
public:
   DeviceStatus  m_nState;
   CCommSettings m_Settings;
   CDeviceInfo()
   {
      m_nState=eDISABLED;
   }
};
