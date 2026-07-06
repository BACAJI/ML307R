#pragma once

#ifdef _CATCORE_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

class CICATMessage;
class CDispatcher;
class DLL_EXPORT CICATMessageSender
{
public:
   CICATMessageSender();
   ~CICATMessageSender();

   void SendICATMessage(CICATMessage* pMessage);

private:
   CDispatcher* m_pDispatcher;
};
