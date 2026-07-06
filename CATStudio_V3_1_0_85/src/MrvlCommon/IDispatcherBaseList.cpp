// IDispatcherBaseList.cpp: implementation of the IDispatcherBaseList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IDispatcherBaseList.h"

#include "IDispatcherBase.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IDispatcherBaseList * IDispatcherBaseList::m_pThis;
CSingletonDestroyer<IDispatcherBaseList> IDispatcherBaseList::m_Destroyer;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IDispatcherBaseList::IDispatcherBaseList()
{
	RemoveAll();	
}

IDispatcherBaseList::~IDispatcherBaseList()
{
	while ( !IsEmpty() )
	{
		IDispatcherBase *pBase = RemoveHead();
		if(pBase)
		{
			delete pBase;
		}
	}
}


IDispatcherBaseList * IDispatcherBaseList::Instance()
{
	if (m_pThis == NULL)
	{
		m_pThis = new IDispatcherBaseList;
		m_Destroyer.Set(m_pThis);
	}

	return m_pThis;
}
