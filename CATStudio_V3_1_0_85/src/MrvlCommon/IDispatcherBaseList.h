/*--------------------------------------------------------------------------------------------------------------------

 (C) Copyright 2006,2007 Marvell Semiconductor Israel Ltd. All Rights Reserved  

-------------------------------------------------------------------------------------------------------------------*/



// IDispatcherBaseList.h: interface for the IDispatcherBaseList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IDISPATCHERBASELIST_H__9B877200_FFEB_4B14_9508_DBDDC87CB0FA__INCLUDED_)
#define AFX_IDISPATCHERBASELIST_H__9B877200_FFEB_4B14_9508_DBDDC87CB0FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>
#include "singletondestroyer.h"

class IDispatcherBase;

class IDispatcherBaseList : public CList<IDispatcherBase *, IDispatcherBase *> 
{
public:
	static IDispatcherBaseList *Instance();

private:
	static IDispatcherBaseList *m_pThis;
	IDispatcherBaseList();
	virtual ~IDispatcherBaseList();

	static CSingletonDestroyer<IDispatcherBaseList> m_Destroyer;
	friend class CSingletonDestroyer<IDispatcherBaseList>;

};

#endif // !defined(AFX_IDISPATCHERBASELIST_H__9B877200_FFEB_4B14_9508_DBDDC87CB0FA__INCLUDED_)
