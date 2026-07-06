// EventForMultiLock.h: interface for the CEventForMultiLock class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVENTFORMULTILOCK_H__A93FF1B1_3914_4097_8EA7_6CF850C833BC__INCLUDED_)
#define AFX_EVENTFORMULTILOCK_H__A93FF1B1_3914_4097_8EA7_6CF850C833BC__INCLUDED_
/*--------------------------------------------------------------------------------------------------------------------

 (C) Copyright 2006,2007 Marvell Semiconductor Israel Ltd. All Rights Reserved  

-------------------------------------------------------------------------------------------------------------------*/



#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CEventForMultiLock : public CEvent
{
public:
	
	CEventForMultiLock() : CEvent(1){}
	
	BOOL Lock(DWORD dwTimeout = INFINITE)
	{	
		return (::WaitForSingleObject(m_hObject,dwTimeout) != WAIT_TIMEOUT) ;
	}
	
	BOOL Unlock()
	{
		OutputDebugString(_T(""));
		return SetEvent();
	}
	
}; 

#endif // !defined(AFX_EventForMultiLock_H__A93FF1B1_3914_4097_8EA7_6CF850C833BC__INCLUDED_)
