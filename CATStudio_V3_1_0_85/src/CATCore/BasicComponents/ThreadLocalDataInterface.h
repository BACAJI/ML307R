/*--------------------------------------------------------------------------------------------------------------------

 (C) Copyright 2006,2007 Marvell Semiconductor Israel Ltd. All Rights Reserved  

-------------------------------------------------------------------------------------------------------------------*/



// ThreadLocalDataInterface.h: interface for the CThreadLocalDataInterface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_THREADLOCALDATAINTERFACE_H__19503C28_3699_4766_99CF_3C3DD4574A62__INCLUDED_)
#define AFX_THREADLOCALDATAINTERFACE_H__19503C28_3699_4766_99CF_3C3DD4574A62__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class  CThreadLocalDataInterface  
{
private:
	CThreadLocalDataInterface();
	//virtual ~CThreadLocalDataInterface();
	static __declspec(thread) LPVOID m_pData;
	
	
public:
	virtual ~CThreadLocalDataInterface();
	static __declspec(dllexport) LPVOID GetData();
	static __declspec(dllexport) void SetData(LPVOID);
};

#endif // !defined(AFX_THREADLOCALDATAINTERFACE_H__19503C28_3699_4766_99CF_3C3DD4574A62__INCLUDED_)
