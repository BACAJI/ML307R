#pragma once

#ifdef _CATCORE_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

class CXmlNodeData;
class DLL_EXPORT CConfig
{
public:
   CConfig();
   ~CConfig();

   static CConfig* Instance();

   CXmlNodeData*  GetRootNode();

   CXmlNodeData*  m_pXmlNodeData;
   
};

