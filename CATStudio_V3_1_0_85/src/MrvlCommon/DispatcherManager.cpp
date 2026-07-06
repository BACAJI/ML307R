// DispatcherManager.cpp: implementation of the CDispatcherManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DispatcherManager.h"
#include "XmlConfig.h"
#include "MessageSender.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


CDispatcherManager * CDispatcherManager::m_pThis;
CSingletonDestroyer<CDispatcherManager> CDispatcherManager::m_Destroyer;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDispatcherManager::CDispatcherManager()
{
	m_SendersMap.InitHashTable(11);
}


CDispatcherManager::~CDispatcherManager()
{
	while ( !m_SenderList.IsEmpty() )
		delete m_SenderList.RemoveHead();
}


CDispatcherManager * CDispatcherManager::Instance()
{
	if (m_pThis == NULL)
	{
		m_pThis = new CDispatcherManager();
		m_Destroyer.Set(m_pThis);
	}

	return m_pThis;
}

CMessageSender* CDispatcherManager::CreateMsgSender(const CString& strModuleName, const CString& strInstanceName)
{
	int moduleID = AppXml()->GetProfileInt(_T("SendingModules"),strModuleName,0);
	if (moduleID < 0)
		return NULL;

	int instanceID;
	if ( !m_SendersMap.Lookup(moduleID, instanceID) )
		instanceID = 0;
//	else
		instanceID++;
	m_SendersMap.SetAt(moduleID, instanceID);

	CMessageSender *pSender = new CMessageSender;
	pSender->m_ModuleID = moduleID;
	pSender->m_InstanceID = instanceID;
	pSender->m_ModuleName = strModuleName;
	pSender->m_InstanceName.Format(_T("%s %d"), strModuleName, instanceID);
	m_SenderList.AddTail(pSender);

	return pSender;
}

void CDispatcherManager::DeleteMsgSender(CMessageSender* pSender)
{
	POSITION pos = m_SenderList.Find(pSender);
	if (pos != NULL)
	{
		m_SenderList.RemoveAt(pos);
	}

	delete pSender;
}

int CDispatcherManager::InstanceNameToID(int moduleID, CString &instanceName)
{
	for (POSITION pos = m_SenderList.GetHeadPosition(); pos != NULL; )
	{
		CMessageSender* pSender = m_SenderList.GetNext(pos);
		if (pSender->m_ModuleID == moduleID && pSender->m_InstanceName == instanceName)
			return pSender->m_InstanceID;
	}
	
	return -1;	// not found.
}
