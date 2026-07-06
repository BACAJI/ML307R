#include "stdafx.h"
#include "config.h"
#include "XmlData.h"

CConfig::CConfig()
{
   m_pXmlNodeData = NULL;
}

CConfig::~CConfig()
{
	if(m_pXmlNodeData)
	{
		delete m_pXmlNodeData;
		m_pXmlNodeData=NULL;
	}
}

CConfig* CConfig::Instance()
{
   static CConfig s_config;
   return &s_config;
}

CXmlNodeData* CConfig::GetRootNode()
{
   return m_pXmlNodeData;
}
