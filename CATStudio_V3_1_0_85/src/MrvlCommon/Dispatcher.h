#pragma once
#include <vector>
#include <queue>
#include "ICATMessageReceiver.h"
//#include "MrvlCommon/imc.h"


using namespace std;

class CICATMessage;
typedef queue<CICATMessage*> CICATMessageQueue;
typedef void (*PFN_ICATMESSAGE_HANDLER)(LPVOID, CICATMessage*);

#ifdef _CATCORE_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif


class DLL_EXPORT CDispatcher /*: public ImcListener*/
{
public:
   static CDispatcher* Instance();
   static CDispatcher* GetInstance();
   static CDispatcher* m_pInstance;
   static CCriticalSection m_csLock;
   static void DestroyInstance();
   ~CDispatcher();
private:
   CDispatcher();

public:
   void HandleMessage(CICATMessage* pMessage);
   void RegisterReceiver(CMessageReceiverBase* pReceiver);
   void UnregisterReceiver(CMessageReceiverBase* pReceiver);
   

protected: // Overrides
   //virtual LRESULT OnMessageReceived(CMessage* pMessage);


protected:
   void  DispatchMessage();
   void  DispatchMessage(CICATMessage*);
   UINT  ThreadFunc();
   static UINT ThreadProc(LPVOID);
   std::vector<CMessageReceiverBase*>  m_ReceiverList;
   CCriticalSection  m_RegistryLock;

   CCriticalSection    m_QueueLock;
   CICATMessageQueue*  m_pIncomingQueue;
   CICATMessageQueue*  m_pWorkQueue;
   HANDLE              m_hThread;
   HANDLE              m_hExitEvent;
   HANDLE              m_hQueueEvent;
   UINT64              m_nMessageNumber;
   BOOL                m_bDispatchMessage;
   //CImcReceiver        m_ImcReceiver;
   

private:
   void StartThread();
   void StopThread(DWORD dwTimeout=2000);
   void ClearIncomingQueue();
   void ClearWorkQueue();
   void SwapQueue();
   void StopDispatcher();
   void ResumeDispather();
   CICATMessageQueue* WorkQueue() { return m_pWorkQueue; }
   CICATMessageQueue* IncomingQueue() { return m_pIncomingQueue; }
   CICATMessage*  GetMessage();
};
