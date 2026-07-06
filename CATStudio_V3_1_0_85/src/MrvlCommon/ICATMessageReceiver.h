#pragma once
#include <list>

using namespace std;

class CICATMessage;

#ifdef _CATCORE_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

class DLL_EXPORT CMessageReceiverBase
{
public:
   CMessageReceiverBase();
   virtual ~CMessageReceiverBase();
   void Register(bool bStartReceiving=true);
   void Unregister();
   void StartReceiver();
   void StopReceiver();
   void SetReceiverName(const CString& strModule);
   CString GetReceiverName();
   UINT GetDroppedCount();


   virtual void AddToFIFO(CICATMessage* pMessage){};


protected:
   CString             m_strReceiverName;
   CCriticalSection    m_ReceiverNameLock;
   bool                m_bReceiveMessage;
   bool                m_bRegistered;
   UINT                m_uDropMsgCnt;

};

class DLL_EXPORT CICATMessageReceiver : public CMessageReceiverBase
{
public:
   CICATMessageReceiver();
   virtual ~CICATMessageReceiver();

public: //Overrides
   virtual void AddToFIFO(CICATMessage* pMessage);

public: //Operations
   CICATMessage* RemoveHead();
   //UINT64 RemoveMsg(UINT64 messageNum);
   void RemoveAll();
   void SetFIFOSize(size_t sz); //This function is optional. Default size allocated in ctor can hold 200*1024 messages(about 32MByte memory).
   inline void SetFifoOwnerName(CString fifoOwnerName) { this->m_fifoOwnerName = fifoOwnerName; }; // A name to uniquely identify this object in debug traces.
   void FitSize();

   HANDLE  m_hFIFOEvent;

private:
   size_t              m_nMaxsize;
   list<CICATMessage*> m_FIFO;
   CCriticalSection    m_FIFOSync;
   int		m_nAvailableMemoryMB;
   UINT64		m_nPreMessageNumber;
   CString			   m_fifoOwnerName;
};


class DLL_EXPORT CICATMessageReceiverPTK : public CICATMessageReceiver
{
public:
   CICATMessageReceiverPTK();
   virtual ~CICATMessageReceiverPTK();

public: // Overrides
   virtual void AddToFIFO(CICATMessage* pMessage);
   void StartReceiverPtk(){m_bPtkReceiveMessage = true;}
   void StopReceiverPtk(){m_bPtkReceiveMessage = false;}

   typedef void (*PFN_HandleMessage)(void*,CICATMessage*);
   
   PFN_HandleMessage m_pfnHandleMessage;
   void* m_pfnObj;

   bool                m_bPtkReceiveMessage;

};

typedef void (LP_ICAT_MESSAGE_FUNC)(LPVOID, CICATMessage*);

class DLL_EXPORT CICATMessageReceiverEx : public CICATMessageReceiver
{
public:
	static CICATMessageReceiverEx* CreateMsgReceiver(LPVOID pClass, BOOL bStartReceiving, LP_ICAT_MESSAGE_FUNC *pICATMessageFunc = NULL);
	static void DeleteMsgReceiver(CICATMessageReceiverEx*& pReceiver);

private:
	CICATMessageReceiverEx(LPVOID pClass, BOOL bStartReceiving, LP_ICAT_MESSAGE_FUNC *pICATMessageFunc);           
	virtual ~CICATMessageReceiverEx();

	LPVOID m_pHandlingClass;
	LP_ICAT_MESSAGE_FUNC* m_pICATMessageFunc;

	CEvent	m_KillEvent;

	CWinThread* m_pThread;
	static UINT ThreadProc(LPVOID pParam);
	void ReceiveMessage();
	bool DeleteMessage(CICATMessage *pMessage);
};