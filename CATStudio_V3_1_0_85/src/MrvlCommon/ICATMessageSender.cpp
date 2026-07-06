#include "stdafx.h"
#include "ICATMessage.h"
#include "ICATMessageSender.h"
#include "Dispatcher.h"

//////////////////////////////////////////////////////////////////////////

CICATMessageSender::CICATMessageSender()
{
   m_pDispatcher = CDispatcher::Instance();
}

CICATMessageSender::~CICATMessageSender()
{

}

void CICATMessageSender::SendICATMessage( CICATMessage* pMessage )
{
   m_pDispatcher->HandleMessage(pMessage);
}
