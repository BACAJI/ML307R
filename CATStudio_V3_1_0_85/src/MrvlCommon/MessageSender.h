/*--------------------------------------------------------------------------------------------------------------------

 (C) Copyright 2006,2007 Marvell Semiconductor Israel Ltd. All Rights Reserved  

-------------------------------------------------------------------------------------------------------------------*/

// MessageSender.h: interface for the CMessageSender class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MESSAGESENDER_H__ACD7E800_70BA_4BB9_B07B_743D6DFA0246__INCLUDED_)
#define AFX_MESSAGESENDER_H__ACD7E800_70BA_4BB9_B07B_743D6DFA0246__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "Dispatcher.h"
//#include "../BasicComponents/SystemMessages.h"
#include "ICATMessage.h"
#include <afxmt.h>

#ifdef SendICATMessage
#undef SendICATMessage
#endif

class CDispatcher;
class DLL_EXPORT CMessageSender
{	
public:
	static CMessageSender* CreateMessageSender(const CString &strModuleName, const CString &strInstanceName = _T(""));
	static void DeleteMessageSender(CMessageSender*& pSender);
	
	void SetInstanceName(const CString &strName);
	
	void SendICATMessage(BYTE *pData, int length, CICATMessage::eDirection dir = CICATMessage::MessageOUT_ALL);
	void SendICATMessage(const CString &strMessage, CICATMessage::eDirection dir = CICATMessage::MessageOUT_ALL);
	void SendICATMessage(const TCHAR *strFmt, ...);
	void SendICATMessage(CICATMessage *pMessage);

	void SendMessage(BYTE *pData, int length, CICATMessage::eDirection dir = CICATMessage::MessageOUT_ALL);
	void SendMessage(const CString &strMessage, CICATMessage::eDirection dir = CICATMessage::MessageOUT_ALL);
	void SendMessage(const TCHAR *strFmt, ...);

	CString GetModuleName() { return m_ModuleName; }

	int		m_ModuleID;
	int		m_InstanceID;
	int		m_nError;
	CString m_ModuleName;
	CString m_InstanceName;

private:
	CMessageSender();
	virtual ~CMessageSender();
	CDispatcher* m_pDispatcher;
	friend class CDispatcherManager;
};

#endif // !defined(AFX_MESSAGESENDER_H__ACD7E800_70BA_4BB9_B07B_743D6DFA0246__INCLUDED_)
