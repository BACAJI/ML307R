/*--------------------------------------------------------------------------------------------------------------------

 (C) Copyright 2006,2007 Marvell Semiconductor Israel Ltd. All Rights Reserved  

-------------------------------------------------------------------------------------------------------------------*/

// DispatcherManager.h: interface for the CDispatcherManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DISPATCHERMANAGER_H__E758576C_59A5_11D5_8230_0006294FD6F7__INCLUDED_)
#define AFX_DISPATCHERMANAGER_H__E758576C_59A5_11D5_8230_0006294FD6F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WM_PROCESS_MESSAGE	(WM_USER+10)
#define WM_SYSTEM_MESSAGE	(WM_USER+11)

#include <afxtempl.h>
#include "SingletonDestroyer.h"

class CMessageSender;

class CDispatcherManager  
{
public:
	static CDispatcherManager * Instance();

	CMessageSender* CreateMsgSender(const CString& strModuleName, const CString& strInstanceName);
	void DeleteMsgSender(CMessageSender* pSender);

private:
	static CDispatcherManager *m_pThis;
	
	CDispatcherManager();
	virtual ~CDispatcherManager();
	static CSingletonDestroyer<CDispatcherManager> m_Destroyer;
	friend class CSingletonDestroyer<CDispatcherManager>;

	CList <CMessageSender*> m_SenderList;
	CMap<int, int&, int, int&> m_SendersMap;

public:
	int InstanceNameToID(int moduleID, CString &instanceName);
};

#endif // !defined(AFX_DISPATCHERMANAGER_H__E758576C_59A5_11D5_8230_0006294FD6F7__INCLUDED_)
