/*--------------------------------------------------------------------------------------------------------------------

 (C) Copyright 2006,2007 Marvell Semiconductor Israel Ltd. All Rights Reserved  

-------------------------------------------------------------------------------------------------------------------*/


// IDispatcherBase.h: interface for the IDispatcherBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IDISPATCHERBASE_H__5C7AE647_74A8_424D_BDFA_876CCA2E8A6C__INCLUDED_)
#define AFX_IDISPATCHERBASE_H__5C7AE647_74A8_424D_BDFA_876CCA2E8A6C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "ICATMessage.h"

//IFLVC9_Inc_Export_H_Begin************************************
//#include "..\IFLExport.h" 
//IFLVC9_Inc_Export_H_End**************************************

typedef void (LP_ICAT_MESSAGE_FUNC)(LPVOID, CICATMessage *);

#define TO_ALL	 -1

class CAllFilters;

class  __declspec(dllexport) IDispatcherBase  
{
private:
public: /////////////////////////////////////////////////////////////////////////
	IDispatcherBase();

#ifdef RF_CAL_MAIN
	~IDispatcherBase();
#else
	virtual ~IDispatcherBase();
#endif
	
	friend class IDispatcherBaseList;

/*****   Message Sender Functions *****/
public:
	int		m_ModuleID;
	int		m_InstanceID;
	int     m_nError;
	CString m_ModuleName;
	CString m_InstanceName;

	virtual void SetInstanceName(const CString &strName) { m_InstanceName = strName; }

	virtual void OpenSpecificLogger() { AfxMessageBox(_T("Option not available in current version !")); }
	virtual void OpenSpecificViewer() { AfxMessageBox(_T("Option not available in current version !")); }

	virtual void SendICATMessage(BYTE *pData, int length, CICATMessage::eDirection dir = CICATMessage::MessageOUT_ALL) { }
	virtual void SendICATMessage(const CString &strMessage, CICATMessage::eDirection dir = CICATMessage::MessageOUT_ALL) { }
	virtual void SendICATMessage(const char *strFmt, ...) { }
	virtual void SendICATMessage(CICATMessage *pMessage) { }
	
	virtual void SendMessage(BYTE *pData, int length, CICATMessage::eDirection dir = CICATMessage::MessageOUT_ALL){}
	virtual void SendMessage(const CString &strMessage, CICATMessage::eDirection dir = CICATMessage::MessageOUT_ALL){}
	virtual void SendMessage(const char *strFmt, ...){}

	CString GetModuleName() { return m_ModuleName; }


/*****   Message Receiver Functions *****/
protected:
	LPVOID	m_pHandlingClass;
	LP_ICAT_MESSAGE_FUNC *m_pICATMessageFunc;

public:
	virtual CAllFilters * GetFilters() { return NULL; }
	virtual void OpenFilterWindow(const CString &strTitle = _T("")) { AfxMessageBox(_T("Option not available in current version !")); }
	virtual BOOL WaitForEmptyFIFO(DWORD timeout = INFINITE) { return false; }
	virtual void RegisterByDB(const CString &moduleName, BOOL unregAllElse = false) { }
	virtual void ShowRegistryWindow() { AfxMessageBox(_T("Option not available in current version !")); }
	virtual BOOL IsRegistered(int moduleID, int instanceID) { return FALSE; }
	virtual BOOL Register(int dispModuleID = TO_ALL, int dispInstanceID = TO_ALL) { return false; }
	virtual BOOL Unregister(int dispModuleID = TO_ALL, int dispInstanceID = TO_ALL) { return false; }
	virtual void ResumeReceiver() { }
	virtual void StopReceiver() { }
	virtual void OpenReceiver() { }
	virtual void CloseReceiver() { }
	virtual BOOL IsReceiving() { return false; }
	virtual BOOL IsReceiverOpen() { return false; }
	virtual void Terminate(int exitCode) { }
	virtual DWORD GetNumMessagesInFIFO() { return (DWORD)(-1); }
	virtual BOOL  SetPriority(int nPriority){return FALSE;};

/*****   Static Functions *****/
public:
	static void DeleteMessageSender(IDispatcherBase* &pBase);
	static void DeleteMessageReceiver(IDispatcherBase* &pBase);
	static IDispatcherBase * CreateMessageSender(const CString &strModuleName, const CString &strInstanceName = _T(""));
	static IDispatcherBase * CreateMessageReceiver(LPVOID pClass, BOOL bStartReceiving, LP_ICAT_MESSAGE_FUNC *pICATMessageFunc = NULL, void *pReserved = NULL);

};


//Richard add this function for RFCal Project	2012-02-07
extern "C" __declspec (dllexport) IDispatcherBase* RFCCreateMessageSender(const CString &strModuleName, const CString &strInstanceName = _T(""));
//Richard add this function for RFCal Project	2012-02-07


#endif // !defined(AFX_IDISPATCHERBASE_H__5C7AE647_74A8_424D_BDFA_876CCA2E8A6C__INCLUDED_)
