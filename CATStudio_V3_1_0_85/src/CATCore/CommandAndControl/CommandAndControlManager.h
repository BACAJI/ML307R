#pragma once
#include "CommandChannel.h"
class CCommandChannel;
class CCommandAndControlManager
{
public:
	CCommandAndControlManager(int nDevice);
	~CCommandAndControlManager(void);
	static CCommandAndControlManager * Instance(int nDevice);
	//**********************************************************************************************************
	//Michal Bukai - add the ability to create several instance of the C&C object in order to 
	//enable Multi-Threaded Programing in the TestEngeain (each thread will get its on C&C object
	//so the user could handle the communication interface without worry of interference of 2 or more
	//thread using the same communication interface (C&C object).
//	static CMap<HANDLE, HANDLE, CCommandAndControl*, CCommandAndControl*>	m_mapCommandAndControlInstance;
	static CCommandChannel* GetCommandAndControlInstance (HANDLE hInstance);
	static void DeleteCommandAndControlInstance(HANDLE hInstance);
	static CMap<HANDLE, HANDLE, CCommandChannel*, CCommandChannel*>	m_mapCommandAndControlInstance;
//	static void DeleteCommandAndControlInstance(HANDLE hInstance);
private:
	int m_nDevice;
	static SmartShell<CCommandAndControlManager> m_SmartShell;
	static CCriticalSection		m_InstanceCreationLock;
	CCommandChannel *m_pCommandAndControl;
	static CCommandAndControlManager *m_pThis;
	class CSignalsFilterManager* m_pSignalsFilterManager;
	friend class SmartShell<CCommandAndControlManager>;

public:
	CSignalsFilterManager * GetSignalsFilterManager();
};
