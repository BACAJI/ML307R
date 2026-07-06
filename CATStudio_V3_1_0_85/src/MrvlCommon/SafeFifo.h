#pragma once

#include <afxtempl.h>
#include <afxmt.h>

template<class TYPE, class ARG_TYPE = const TYPE&>
class CSafeFifo : protected CList <TYPE, ARG_TYPE>
{
public:
	CSafeFifo() : m_NotEmptyEvent(FALSE, TRUE)
	{
	}

	virtual ~CSafeFifo()
	{
	}

	POSITION Put(ARG_TYPE newElement)
	{
		CSingleLock sLock(&m_CritSec, TRUE);
		POSITION pos = AddTail(newElement);
		m_NotEmptyEvent.SetEvent();
		return pos;
	}

	TYPE Get()
	{
		CSingleLock sLock(&m_CritSec, TRUE);

		ASSERT(GetCount() > 0);

		TYPE elem = RemoveHead();
		if ( GetCount() == 0 )
			m_NotEmptyEvent.ResetEvent();

		return elem;
	}

	virtual void Clean()
	{
		CSingleLock sLock(&m_CritSec, TRUE);
		RemoveAll();
		m_NotEmptyEvent.ResetEvent();
	}

	BOOL IsEmpty()
	{
		CSingleLock sLock(&m_CritSec, TRUE);
		return __super::IsEmpty();
	}

	HANDLE GetNotEmptyEvent() { return m_NotEmptyEvent.m_hObject; }

protected:
	CEvent m_NotEmptyEvent;
	CCriticalSection m_CritSec;
};


template<class TYPE>
class CSafePtrFifo : public CSafeFifo <TYPE*>
{
public: 
	virtual void Clean()
	{
		CSingleLock sLock(&m_CritSec, TRUE);

		while ( !IsEmpty() )
		{
			TYPE* elem = RemoveHead();
			delete elem;
		}

		m_NotEmptyEvent.ResetEvent();
	}
};
