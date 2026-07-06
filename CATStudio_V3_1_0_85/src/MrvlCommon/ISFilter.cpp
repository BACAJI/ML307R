#include "StdAfx.h"
#include "ISFilter.h"

ISFilter::ISFilter(void)
{
  m_bFilterUpdated = false;
  m_bPassIfMSGIDNotFound  = true;
  m_nAllPass = 0;
}

ISFilter::~ISFilter(void)
{
}

