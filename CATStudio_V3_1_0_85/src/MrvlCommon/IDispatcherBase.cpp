// IDispatcherBase.cpp: implementation of the IDispatcherBase class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "typeinfo.h"

#include "IDispatcherBase.h"

#include "IDispatcherBaseList.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/// *********************************************************************
/// external function declaration
#ifdef _IFLLITE

extern "C" __declspec(dllexport) void NewMessageSender(IDispatcherBase ** ppBase, LPCSTR moduleName);

extern "C" __declspec(dllexport) void NewMessageReceiver(IDispatcherBase ** ppBase, BOOL bStartReceiving);
 
extern "C" __declspec(dllexport) void RemoveMessageSender(IDispatcherBase *pBase);

#endif //_IFLLITE
/// *********************************************************************



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IDispatcherBase::IDispatcherBase()
{
	m_ModuleID = -2;
	m_InstanceID = -2;
	m_InstanceName = _T("");
	m_nError = 0;

	m_pHandlingClass = NULL;
	m_pICATMessageFunc = NULL;
}


IDispatcherBase::~IDispatcherBase()
{

}


IDispatcherBase * IDispatcherBase::CreateMessageSender(const CString &strModuleName, const CString &strInstanceName /*=_T("")*/)
{
	ASSERT ( !strModuleName.IsEmpty() );
	
	IDispatcherBase *pBase = NULL;

/*	HINSTANCE hDll = AfxLoadLibrary("Dispatcher.dll");
	if (hDll)
	{
		typedef void(LPNEWSENDERPROC)(IDispatcherBase **, LPCSTR);
		LPNEWSENDERPROC *pFunc = (LPNEWSENDERPROC *)::GetProcAddress(hDll, "NewMessageSender");
		if (pFunc)
			pFunc(&pBase, (LPCSTR)strModuleName);
	}*/

	if (pBase == NULL)
		pBase = new IDispatcherBase();

	pBase->m_ModuleName = strModuleName;
	if ( !strInstanceName.IsEmpty() )
		pBase->SetInstanceName(strInstanceName);
	else if (pBase->m_InstanceName.IsEmpty())
		pBase->SetInstanceName(pBase->m_ModuleName);

	IDispatcherBaseList::Instance()->AddTail(pBase);
	return pBase;
}

/// *********************************************************************
/// NOT IFLLite
#ifndef _IFLLITE


#pragma region  NOT IFLLite



IDispatcherBase * IDispatcherBase::CreateMessageReceiver(LPVOID pClass, BOOL bStartReceiving, LP_ICAT_MESSAGE_FUNC *pICATMessageFunc /*=NULL*/, void *pReserved /*=NULL*/)
{
	IDispatcherBase *pBase = NULL;

/*	HINSTANCE hDll = AfxLoadLibrary("Dispatcher.dll");
	if (hDll)
	{
		typedef void(LPNEWRECEIVERPROC)(IDispatcherBase **, BOOL);
		LPNEWRECEIVERPROC *pFunc = (LPNEWRECEIVERPROC *)::GetProcAddress(hDll, "NewMessageReceiver");
		if (pFunc)
			pFunc(&pBase, bStartReceiving);
	}*/

	if (pBase == NULL)
		pBase = new IDispatcherBase();

	pBase->m_pHandlingClass = pClass;
	pBase->m_pICATMessageFunc = pICATMessageFunc;

//	IDispatcherBaseList::Instance()->AddTail(pBase);	// For now - do not add receivers to list.
	return pBase;
}


void IDispatcherBase::DeleteMessageSender(IDispatcherBase* &pBase)
{
	POSITION pos = IDispatcherBaseList::Instance()->Find(pBase);
	if (pos)
	{
	
/*		HINSTANCE hDll = AfxLoadLibrary("Dispatcher.dll");
		if (hDll)
		{
			typedef void(LPDELETESENDERPROC)(IDispatcherBase *);
			LPDELETESENDERPROC *pFunc = (LPDELETESENDERPROC *)::GetProcAddress(hDll, "RemoveMessageSender");
			if (pFunc)
				pFunc(pBase);
		}*/

		IDispatcherBaseList::Instance()->RemoveAt(pos);
		delete pBase;
	}

	pBase = NULL; 
}
#pragma endregion 


/// *********************************************************************
/// IFLLite
#else

IDispatcherBase * IDispatcherBase::CreateMessageSender(const CString &strModuleName, const CString &strInstanceName /*=_T("")*/)
{
	ASSERT ( !strModuleName.IsEmpty() );

	IDispatcherBase *pBase = NULL;

// 	HINSTANCE hDll = AfxLoadLibrary("Dispatcher.dll");
// 	if (hDll)
// 	{
// 		typedef void(LPNEWSENDERPROC)(IDispatcherBase **, LPCSTR);
// 		LPNEWSENDERPROC *pFunc = (LPNEWSENDERPROC *)::GetProcAddress(hDll, "NewMessageSender");
// 		if (pFunc)
// 			pFunc(&pBase, (LPCSTR)strModuleName);
// 	}

	NewMessageSender(&pBase, (LPCSTR)strModuleName);

	if (pBase == NULL)
		pBase = new IDispatcherBase();

	pBase->m_ModuleName = strModuleName;

	if ( !strInstanceName.IsEmpty() )
		pBase->SetInstanceName(strInstanceName);
	else if (pBase->m_InstanceName.IsEmpty())
		pBase->SetInstanceName(pBase->m_ModuleName);

	IDispatcherBaseList::Instance()->AddTail(pBase);
	return pBase;
}


IDispatcherBase * IDispatcherBase::CreateMessageReceiver(LPVOID pClass, BOOL bStartReceiving, LP_ICAT_MESSAGE_FUNC *pICATMessageFunc /*=NULL*/, void *pReserved /*=NULL*/)
{
	IDispatcherBase *pBase = NULL;

// 	HINSTANCE hDll = AfxLoadLibrary("Dispatcher.dll");
// 	if (hDll)
// 	{
// 		typedef void(LPNEWRECEIVERPROC)(IDispatcherBase **, BOOL);
// 		LPNEWRECEIVERPROC *pFunc = (LPNEWRECEIVERPROC *)::GetProcAddress(hDll, "NewMessageReceiver");
// 		if (pFunc)
// 			pFunc
// 	}
	NewMessageReceiver(&pBase, bStartReceiving);

	if (pBase == NULL)
		pBase = new IDispatcherBase();

	pBase->m_pHandlingClass = pClass;
	pBase->m_pICATMessageFunc = pICATMessageFunc;

	//	IDispatcherBaseList::Instance()->AddTail(pBase);	// For now - do not add receivers to list.
	return pBase;
}


void IDispatcherBase::DeleteMessageSender(IDispatcherBase* &pBase)
{
	POSITION pos = IDispatcherBaseList::Instance()->Find(pBase);
	if (pos)
	{

// 		HINSTANCE hDll = AfxLoadLibrary("Dispatcher.dll");
// 		if (hDll)
// 		{
// 			typedef void(LPDELETESENDERPROC)(IDispatcherBase *);
// 			LPDELETESENDERPROC *pFunc = (LPDELETESENDERPROC *)::GetProcAddress(hDll, "RemoveMessageSender");
// 			if (pFunc)
// 				pFunc(pBase);
// 		}
		RemoveMessageSender(pBase);

		IDispatcherBaseList::Instance()->RemoveAt(pos);
		delete pBase;
	}

	pBase = NULL; 
}


#endif //_IFLLITE
/// *********************************************************************




/// *********************************************************************
/// Shared by IFLLite and IFL/ACAT
void IDispatcherBase::DeleteMessageReceiver(IDispatcherBase* &pBase)
{
	// For now the receivers are not stored in a list - so just delete object.
	delete pBase;
	pBase = NULL;
}


//Richard add this function for RFCal Project	2012-02-07
extern "C" __declspec (dllexport) IDispatcherBase* RFCCreateMessageSender(const CString &strModuleName, const CString &strInstanceName)
{
	CString strModName = (CString)strModuleName;
	CString strInstName = (CString)strInstanceName;
	return IDispatcherBase::CreateMessageSender(strModName, strInstName);
}
//Richard add this function for RFCal Project	2012-02-07