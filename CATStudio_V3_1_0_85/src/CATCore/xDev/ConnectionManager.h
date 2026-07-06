/*--------------------------------------------------------------------------------------------------------------------

 (C) Copyright 2006,2007 Marvell Semiconductor Israel Ltd. All Rights Reserved  

-------------------------------------------------------------------------------------------------------------------*/



#include <afxmt.h>
#include <afxtempl.h>
#include "ConnectionSwitcher.h"
#include "XDEVReporter.h"
#include "../Converter/db/AdoDbConnector.h"
#include "singletondestroyer.h"

//IFLVC9_Inc_Export_H_Begin************************************
//#include "..\IFLExport.h" 
//IFLVC9_Inc_Export_H_End**************************************


#define		VALIDATE_RESOURCE_PATH		1
#define		VALIDATE_DB_PATH			2
#define		VALIDATE_IMAGES_PATH		3

#define		WM_CREATE_STATUS_WND	WM_USER+1
#define		WM_DESTROY_STATUS_WND	WM_USER+2
#define		WM_SHOW_STATUS_WND		WM_USER+3
#define		WM_HIDE_STATUS_WND		WM_USER+4
#define		WM_SET_STATUS_WND_TEXT	WM_USER+5

#define TheConnectionManager	CConnectionManager::GetUniqueStaticInstance()	//this function returns a pointer to a single
																				//instance of the connecion manager.

#if !defined(AFX_CONNECTIONMANAGER_H__605885E1_94B3_415A_A781_75D65479A19C__INCLUDED_)
#define AFX_CONNECTIONMANAGER_H__605885E1_94B3_415A_A781_75D65479A19C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//class CSetConnectionDlg;
class CStringArray;
class CPtrArray;
class CMapStringToPtr;
class CInitializationStatusDlg;
class CConfigDevice;
class CDBLayer;



class  /*IFLAPI*/ CConnectionManager /*: public CWnd*/
{
	public:
		int FreeDeviceDrivers(CPtrArray *pSessionPtrArray);
		void InitStructToViSessionArray(const sInitialization *pInit,CDWordArray &arrViSessions);
		int FreeViInterface(sInitialization *pInit);
		BOOL WasKilledInInitialization();
		void SetWasKilledInInitialization(BOOL bWasKilled);
		int TerminateConnectionsByOwner(CString strOwnerName,  CString *pstrInitMsg  ,CString * pstrDeviceName);
		void StartDeviceInitialization(sInitialization *sInit);
		BOOL  InitializationInteruptHandler(sInitialization *sInit);
		
		//unsigned long GetDeviceHandle(const CString &strOwnerName,const CString &strDeviceName,HMODULE &hDllHandle,
		//							  int iSecondaryAddress /* = NO_SECONDARY_ADDRESSES*/,CString *pstrErrorMsg /*= NULL*/,CString *pstrPrimaryAddress/* = NULL*/);

		friend class CSingletonDestroyer<CConnectionManager>;
		//CSetConnectionDlg *m_pSetConDlg;							//the pointer is used for a modeless window
		static CConnectionManager * GetUniqueStaticInstance();		//returns a pointer to a static object of the
																	//class ConnectionManager. creates one if it doesn't exist.
		void TerminateAllConnections();
		int TerminateConnectionsByOwner(sInitialization *sInit);
		inline void TerminateSingleConnection(CString *pStrDeviceName,CConnectionSwitcher *pConnectionSwitcher,CPtrArray *pSessionPtrArray);

		
				
	protected:
		BOOL m_WasKilledInInitialization;

		//inline void InitStructToSingleDeviceMode(sInitialization *pInit,const CString &strOwnerName,const CString &strDeviceName,CString *pstrPrimaryAddress /*= NULL*/);
		inline sXDEVSession * GetXDEVSessionFromMap(const CString &strOwner,const CString &strDeviceName,const CString &strPrimaryAddress);
		inline sXDEVSession * GetXDEVSessionFromArray(CPtrArray *parrDevStructs, const CString &strDeviceName, const CString &strPrimaryAddress /*= ""*/);
        inline bool GetDbConfigFieldVals(sXDEVSession *pXdevSession,CAdoDbConnector *pDbConnector);
        inline bool GetDeviceDefaultFieldVals(sXDEVSession *pXdevSession,CAdoDbConnector *pDbConnector);
        inline int GetCommonFieldVals(sXDEVSession *pXdevSession,CAdoDbConnector *pDbConnector);
		inline int ApproveInitializationEntry(sInitialization *sInit,int &iIsConfigInitByOther);
		inline void RunPostInitialization(sInitialization *sInit,int iIsConfigInitByOther );
		inline void LoadFromIniFile();
		inline void FreeAllocatedMemory();
		inline void FreeOwnerCSLockMap();
		inline void FreeOwnerConnectionMap();
		inline void FreeSessionPtrArray(CPtrArray *&sessionPtrArray);

		inline int InitInitiallizationStruct(sInitialization *sInit);
		int GetThreadNum(sInitialization *sInit);
		inline void OpenInitStatusDlg(int iThreadNum,CString *strMsg);

		int TestAndSetInitializationEntryList(sInitialization *sInit,int *iInitEntryApproved);
		int RemoveFromInitializationEntryList(sInitialization *sInit);

		inline int CSUnlock(CSingleLock *pSingleLock);
		inline int CSLock(CSingleLock *pSingleLock,int iLockMode);

		BOOL ConfigAlreadyInitHandler(sInitialization *sInit);
		inline int DbToSecAddrStruct(sXDEVSession *xdevSession);
        inline int RecToSecAddrStruct(sDeviceSessions *pDeviceSessionStruct,CAdoDbConnector *pDbConnector);

		int IsConfigInitialized(sInitialization *sInit);

		CConnectionManager();
		virtual ~CConnectionManager();
		static CSingletonDestroyer<CConnectionManager> m_Destroyer;
		static CConnectionManager *m_pThis;

		int DbToXDEVSessionArray(sInitialization *sInit);
        inline int RecToXDEVSession(sXDEVSession *xdevSession,CAdoDbConnector *dbConnector);
        int ValidateInitData(sXDEVSession *xdevSession,CAdoDbConnector *dbConnector);
		inline void FormatAddresses(sXDEVSession *xdevSession);
		inline int ValidateDeviceAddress(sXDEVSession *xdevSession);
		inline void FormatFunctionSymbol(sXDEVSession *xdevSession);

		int CheckForSharedDevices(sInitialization *sInit,int &iDeviceInitialized);
		int UpdateConnectionOwnerMap(sInitialization *sInit);

		inline int GetXDEVSession(const CString &strOwner, const CString &strDevice,sXDEVSession *& pXDEVSession);

		//CTokenizer m_Tokenizer;
		CString m_dbPath;
		CString m_imagesPath;
		CMapStringToPtr *m_pOwnerConnectionMap,*m_pOwnerCSLockMap;
		CDBLayer *m_pDbLayer;


		CMutex m_DeviceInitCriticalSection;
		// the following 2 arrays contain the addresses of the devices that are currently being initialized,
		// and their corresponding owners.

		CStringArray m_arrInitEntryList[2];	// m_arrInitEntryList[0] - the owner of the specific device that is in initialization.
											// m_arrInitEntryList[1] - the address of the specific device that is in initialization.
		int m_NumCurrentRunningInitThreads; // number of threadsthat are currently running.
		int m_MaxNumInitThreads;			// maximum number of threads, allowed to run.
		int m_MaxNumRetries;				// maximum number of times, trying to enter the critical section.
		DWORD m_SleepingTime;				// sleeping time between attempts to initialize devices.
		CInitializationStatusDlg * m_arrInitStatusDlg;
		LRESULT DefWindowProc( UINT message, WPARAM wParam, LPARAM lParam );
		/*DECLARE_MESSAGE_MAP()*/

};

#endif // !defined(AFX_CONNECTIONMANAGER_H__605885E1_94B3_415A_A781_75D65479A19C__INCLUDED_)
