// MessageSender.cpp: implementation of the CMessageSender class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MessageSender.h"
#include "DispatcherManager.h"
#include "Dispatcher.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMessageSender::CMessageSender()
{
	m_ModuleID = -2;
	m_InstanceID = -2;
	m_nError = 0;
	m_pDispatcher = CDispatcher::Instance();
}


CMessageSender::~CMessageSender()
{
}


CMessageSender* CMessageSender::CreateMessageSender(const CString &strModuleName, const CString &strInstanceName/*=_T("")*/)
{
	return CDispatcherManager::Instance()->CreateMsgSender(strModuleName, strInstanceName);
}

void CMessageSender::DeleteMessageSender(CMessageSender*& pSender)
{
	CDispatcherManager::Instance()->DeleteMsgSender(pSender);
	pSender = NULL;
}

void CMessageSender::SendMessage(const TCHAR *strFmt, ...)
{
	va_list params;
	va_start(params, strFmt);
	
	CString strMessage;
	strMessage.FormatV(strFmt, params);
	SendICATMessage(strMessage);
}

void CMessageSender::SendMessage(const CString &strMessage, CICATMessage::eDirection dir)
{
	SendICATMessage(strMessage, dir);
}

void CMessageSender::SendMessage(BYTE *pData, int length, CICATMessage::eDirection dir /*=CICATMessage::MessageOUT_ALL*/)
{
	SendICATMessage(pData, length, dir);
}

void CMessageSender::SendICATMessage(CICATMessage *pMessage)
{
	//pMessage->GetNumber();
	
	m_pDispatcher->HandleMessage(pMessage);
}


void CMessageSender::SendICATMessage(const CString &strMessage, CICATMessage::eDirection dir /*=CICATMessage::MessageOUT_ALL*/)
{
	CStringA strTemp(strMessage);
	int len = strTemp.GetLength();
	if ( len == 0 )
		return;

	CICATMessage *pMessage = new CICATMessage(m_ModuleID, m_InstanceID, (BYTE *)strTemp.GetBuffer(len), len);
	pMessage->m_bConvertable = eStringProtocol;
	pMessage->m_Direction = dir;
	pMessage->m_Error = (EMsgError)m_nError;
	SendICATMessage(pMessage);
	m_nError = 0;
}


void CMessageSender::SendICATMessage(BYTE *pData, int length, CICATMessage::eDirection dir /*=CICATMessage::MessageOUT_ALL*/){
	CICATMessage *pMessage = new CICATMessage(m_ModuleID, m_InstanceID, pData, length); 
	pMessage->m_Direction = dir;
	SendICATMessage(pMessage);
}


void CMessageSender::SendICATMessage(const TCHAR *strFmt, ...)
{
	va_list params;
	va_start(params, strFmt);
	
	CString strMessage;
	strMessage.FormatV(strFmt, params);
	SendICATMessage(strMessage);
}

void CMessageSender::SetInstanceName(const CString &strName)
{
	m_InstanceName = strName;
}