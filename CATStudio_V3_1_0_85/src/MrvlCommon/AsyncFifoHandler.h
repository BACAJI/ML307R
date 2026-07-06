#pragma once
#include "SafeFifo.h"

template<class CONT,class TYPE, class ARG_TYPE = const TYPE&>
class CAsyncFifoHandler
{
	typedef void(CONT::*FIFO_HANDLER_FUNC)(void);
	typedef void(CONT::*CLEAN_FIFO_FUNC)(void);

protected:
	CSafeFifo<TYPE>	m_MsgFifo;
	CWinThread*		m_pThread;
	HANDLE			m_hThread;
	CEvent			m_KillEvent;
	bool			m_bStarted;
	
	FIFO_HANDLER_FUNC m_pFifoHandlerFunc;
	CLEAN_FIFO_FUNC   m_pCleanFifoFunc;
	CONT			 *m_pContainer;

	static UINT ThreadFunc(LPVOID pParam);
	void ThreadFuncHelper();
	void Clean();
public:
	CAsyncFifoHandler(CONT *pContainer,FIFO_HANDLER_FUNC pFifoHandlerFunc,CLEAN_FIFO_FUNC  pCleanFifoFunc = NULL);

	virtual ~CAsyncFifoHandler(void);
	void Start();
	void Terminate();
	void AddToFifoTail(ARG_TYPE newElement);
	TYPE GetFifoHead();
	BOOL IsFifoEmpty() {return m_MsgFifo.IsEmpty();};
};

template<class CONT,class TYPE, class ARG_TYPE>
CAsyncFifoHandler<CONT,TYPE, ARG_TYPE>::CAsyncFifoHandler(CONT *pContainer,FIFO_HANDLER_FUNC pFifoHandlerFunc,CLEAN_FIFO_FUNC  pCleanFifoFunc = NULL)
	: m_KillEvent(FALSE, TRUE)
	, m_pThread(NULL)
	, m_bStarted(false)
{
	m_pFifoHandlerFunc = pFifoHandlerFunc;
	m_pCleanFifoFunc   = pCleanFifoFunc;
	m_pContainer       = pContainer;
}

template<class CONT,class TYPE, class ARG_TYPE>
CAsyncFifoHandler<CONT,TYPE, ARG_TYPE>::~CAsyncFifoHandler(void)
{
	Terminate();
}

template<class CONT,class TYPE, class ARG_TYPE>
void CAsyncFifoHandler<CONT,TYPE, ARG_TYPE>::Start()
{
	if ( !m_bStarted )
	{		
		m_pThread = AfxBeginThread(ThreadFunc, this);
		m_hThread = m_pThread->m_hThread;
		m_bStarted = true;
	}
}

template<class CONT,class TYPE, class ARG_TYPE>
void CAsyncFifoHandler<CONT,TYPE, ARG_TYPE>::Terminate()
{
	m_KillEvent.SetEvent();
	if ( m_pThread )
	{
		if ( WaitForSingleObject(m_hThread, 2000) != WAIT_OBJECT_0 )
			TerminateThread(m_hThread, 1);

		m_hThread = NULL;
		m_pThread = NULL;
	}

	if (m_pCleanFifoFunc)
	{
		(m_pContainer->*m_pCleanFifoFunc)();
	} 
	else
	{
		Clean();
	}

	m_bStarted = false;
}

template<class CONT,class TYPE, class ARG_TYPE>
UINT CAsyncFifoHandler<CONT,TYPE, ARG_TYPE>::ThreadFunc( LPVOID pParam )
{
	CAsyncFifoHandler<CONT,TYPE, ARG_TYPE>* pThis = (CAsyncFifoHandler<CONT,TYPE, ARG_TYPE>*)pParam;
	pThis->ThreadFuncHelper();
	return 1;
}


template<class CONT,class TYPE, class ARG_TYPE>
void CAsyncFifoHandler<CONT,TYPE, ARG_TYPE>::ThreadFuncHelper()
{
	HANDLE hWaits[2] = { m_KillEvent.m_hObject, m_MsgFifo.GetNotEmptyEvent() };
	while (true)
	{
		DWORD dwRes = WaitForMultipleObjects(2, hWaits, FALSE, INFINITE);
		if ( dwRes == WAIT_OBJECT_0 )
			break;

		ASSERT(dwRes == (WAIT_OBJECT_0 + 1));

		(m_pContainer->*m_pFifoHandlerFunc)();
	}
}

template<class CONT,class TYPE, class ARG_TYPE>
void CAsyncFifoHandler<CONT,TYPE, ARG_TYPE>::Clean()
{
	m_MsgFifo.Clean();
}


template<class CONT,class TYPE, class ARG_TYPE>
void CAsyncFifoHandler<CONT,TYPE, ARG_TYPE>::AddToFifoTail( ARG_TYPE newElement )
{
	m_MsgFifo.Put(newElement);
}

template<class CONT,class TYPE, class ARG_TYPE>
TYPE CAsyncFifoHandler<CONT,TYPE, ARG_TYPE>::GetFifoHead()
{
	return m_MsgFifo.Get();
}



