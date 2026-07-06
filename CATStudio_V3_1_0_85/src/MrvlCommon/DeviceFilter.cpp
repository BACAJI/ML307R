#include "stdafx.h"
#include "DeviceFilter.h"



CDeviceFilter::CDeviceFilter( int iDevice, int nInitReceiver )
{
   m_iDevice = iDevice;
   m_nReceiver = nInitReceiver;
}

CDeviceFilter::~CDeviceFilter()
{

}

bool CDeviceFilter::UpdateFilter( bool bPass )
{
   m_nReceiver = min( 0, m_nReceiver+(bPass?1:-1) );
   return true;
}

