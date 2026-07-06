/*--------------------------------------------------------------------------------------------------------------------

 (C) Copyright 2006,2007 Marvell Semiconductor Israel Ltd. All Rights Reserved  

-------------------------------------------------------------------------------------------------------------------*/

// CommunicationManager.h: interface for the CCommunicationManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMMUNICATIONMANAGER_H__F589A92E_425D_4174_85B6_F1D0BF41EB72__INCLUDED_)
#define AFX_COMMUNICATIONMANAGER_H__F589A92E_425D_4174_85B6_F1D0BF41EB72__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "singletondestroyer.h"
#include <afxtempl.h>


#define WM_INIT_SERIAL	(WM_USER + 10)
#define WM_INIT_SOCKET	(WM_USER + 11)
#define WM_INIT_USB		(WM_USER + 12)
#define WM_CLOSE_DEVICE (WM_USER + 13)
#define WM_INIT_DEVICE  (WM_USER + 14)
#define WM_INIT_COMUSB		(WM_USER + 15)//Peter add for rim USB supporting

//class IBase;
//class CCommRegistry;
class __declspec(dllexport) CCommunicationManager 
{
//	DECLARE_DYNCREATE(CCommunicationManager)

public:

	enum EProtocolType {
		eProtocolDiag = 0,
		eProtocolEmmi,
		eProtocolRawData,
		eProtocolStrings
	};

	enum ECommNumber {
		eCOM1 = 1,
		eCOM2,
		eCOM3,
		eCOM4,
		eCOM5,
		eCOM6,
		eCOM7,
		eCOM8,
		eCOM9,
		eCOM10,
		eCOM11,
		eCOM12,
		eCOM13,
		eCOM14,
		eCOM15,
		eCOM16,
		eCOM17,
		eCOM18,
		eCOM19,
		eCOM20,
		eCOM21,
		eCOM22,
		eCOM23,
		eCOM24,
		eCOM25,
		eCOM26,
		eCOM27,
		eCOM28,
		eCOM29,
		eCOM30,
		eCOM31,
		eCOM32,
		eCOM33,
		eCOM34,
		eCOM35,
		eCOM36,
		eCOM37,
		eCOM38,
		eCOM39,
		eCOM40,
		eCOM41,
		eCOM42,
		eCOM43,
		eCOM44,
		eCOM45,
		eCOM46,
		eCOM47,
		eCOM48,
		eCOM49,
		eCOM50,
		eCOM51,
		eCOM52,
		eCOM53,
		eCOM54,
		eCOM55,
		eCOM56,
		eCOM57,
		eCOM58,
		eCOM59,
		eCOM60,
		eCOM61,
		eCOM62,
		eCOM63,
		eCOM64,
		eCOM65,
		eCOM66,
		eCOM67,
		eCOM68,
		eCOM69,
		eCOM70,
		eCOM71,
		eCOM72,
		eCOM73,
		eCOM74,
		eCOM75,
		eCOM76,
		eCOM77,
		eCOM78,
		eCOM79,
		eCOM80,
		eCOM81,
		eCOM82,
		eCOM83,
		eCOM84,
		eCOM85,
		eCOM86,
		eCOM87,
		eCOM88,
		eCOM89,
		eCOM90,
		eCOM91,
		eCOM92,
		eCOM93,
		eCOM94,
		eCOM95,
		eCOM96,
		eCOM97,
		eCOM98,
		eCOM99,
		eCOM100,
		eCOM101,
		eCOM102,
		eCOM103,
		eCOM104,
		eCOM105,
		eCOM106,
		eCOM107,
		eCOM108,
		eCOM109,
		eCOM110,
		eCOM111,
		eCOM112,
		eCOM113,
		eCOM114,
		eCOM115,
		eCOM116,
		eCOM117,
		eCOM118,
		eCOM119,
		eCOM120,
		eCOM121,
		eCOM122,
		eCOM123,
		eCOM124,
		eCOM125,
		eCOM126,
		eCOM127,
		eCOM128
	};

	enum eFlowControl {
		eNone = 0,
		eXOnXOff,
		eHardware
	};

	enum eSocketType {
		eSocketServer = 0,
		eSocketClient
	};

	enum eSocketProt
	{
		eTCP = 1,
		eUDP = 2
	};
public:
	BOOL Init();
	static CCommunicationManager * Instance();
private:
	CCommunicationManager();
	virtual ~CCommunicationManager();
	
	static CSingletonDestroyer<CCommunicationManager> m_Destroyer;
	static CCommunicationManager *m_pThis;
	friend class CSingletonDestroyer<CCommunicationManager>;

	//BOOL CreateNotifyWindow(LPCTSTR lpWinName);
	//void RestartThread(int nDevice);

public:
	//static UINT TermCommFunc(LPVOID pParam);
	void CloseDevice(int nDevice);
	//void RestartThreads();
	//void Terminate();

	BOOL InitSerial(int nDevice, EProtocolType protocolType, ECommNumber nComNum,
						int nBaudRate = 115200, int nStopBits = ONESTOPBIT, int nParityBits = NOPARITY, 
						int nDataBits = 8, eFlowControl nFlowControl = eNone);
	BOOL InitSocket(int nDevice, EProtocolType protocolType, eSocketType sockType = eSocketServer, 
		            CString IpAddress = _T(""),DWORD PortNumber = 0xfffe);
	BOOL InitSocketEx(int nDevice, EProtocolType protocolType, eSocketType sockType = eSocketServer, 
		            eSocketProt sockProt = eTCP, CString IpAddress = _T(""),DWORD PortNumber = 0xfffe);

	BOOL InitSocketEx2(int nDevice, void* pSocketStruct);		//Richard added for add RawDiag setting 2010-12-13

	BOOL InitUsb(int nDevice, EProtocolType protocolType, CString strRAT = _T("WB"));	
	//BOOL InitUsbEx(int nDevice, UsbDeviceInfo* pUsbDeviceInfo);  //Richard added InitUsbEx() 0311

	BOOL InitComUsb(int nDevice, EProtocolType protocolType);
	BOOL InitDevice(int nDevice);

	//IBase *m_pIBase;

	BOOL IsAlive(int nDevice);
	BOOL IsDIAG(int nDevice);
	BOOL IsEMMI(int nDevice);
	BOOL IsRawData(int nDevice);
	int  IsSerial(int nDevice);
	//int HttpSendDataToServer(const CString& strData, CString& strError);

	//void RegisterToCommMessage(UINT messageID, LPCTSTR lpstrModuleName, LPCTSTR lpstrFuncName, LPVOID pParam);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCommunicationManager)
	//}}AFX_VIRTUAL

protected:
	// Generated message map functions
	//{{AFX_MSG(CCommunicationManager)
	//}}AFX_MSG
	//LRESULT OnCommMessage(WPARAM wParam, LPARAM lParam);
	//LRESULT OnPacketDump(WPARAM wParam, LPARAM lParam);
	//LRESULT OnSystemMessage(WPARAM wParam, LPARAM lParam);
	
	LRESULT InitSerialFunc(WPARAM wParam, LPARAM lParam);
	LRESULT InitSocketFunc(WPARAM wParam, LPARAM lParam);
	LRESULT InitUSBFunc(WPARAM wParam, LPARAM lParam);
	LRESULT InitUSBFuncEx(WPARAM wParam, LPARAM lParam);  //Richard added InitUSBFuncEx() 0311
	LRESULT InitComUSBFunc(WPARAM wParam, LPARAM lParam);
	LRESULT InitDeviceFunc(WPARAM wParam, LPARAM lParam);
	//LRESULT OnCloseDevice(WPARAM wParam, LPARAM lParam);
	//LRESULT UpdateComm(WPARAM wParam, LPARAM lParam);


	//DECLARE_MESSAGE_MAP()

private:

	//static CList <CCommRegistry *, CCommRegistry *> m_MessageRegistryList;
	//void LoadRegistryDB();
	//void DispatchCommMessage(UINT messageID, WPARAM wParam, LPARAM lParam);
	
public:
// 	BOOL GetUsbRecogString(int nDevice, CString& str);			//2011-03-14 Richard added
// 	void EnumUsbRecogString();
	//void RegisterWindowHandleToUsbCommWnd(HWND hwnd);
};

#define COM1 CCommunicationManager::eCOM1
#define COM2 CCommunicationManager::eCOM2
#define COM3 CCommunicationManager::eCOM3
#define COM4 CCommunicationManager::eCOM4
#define COM5 CCommunicationManager::eCOM5
#define COM6 CCommunicationManager::eCOM6
#define COM7 CCommunicationManager::eCOM7
#define COM8 CCommunicationManager::eCOM8
#define COM9 CCommunicationManager::eCOM9
#define COM10 CCommunicationManager::eCOM10
#define COM11 CCommunicationManager::eCOM11
#define COM12 CCommunicationManager::eCOM12
#define COM13 CCommunicationManager::eCOM13
#define COM14 CCommunicationManager::eCOM14
#define COM15 CCommunicationManager::eCOM15
#define COM16 CCommunicationManager::eCOM16
#define COM17 CCommunicationManager::eCOM17
#define COM18 CCommunicationManager::eCOM18
#define COM19 CCommunicationManager::eCOM19
#define COM20 CCommunicationManager::eCOM20
#define COM21 CCommunicationManager::eCOM21
#define COM22 CCommunicationManager::eCOM22
#define COM23 CCommunicationManager::eCOM23
#define COM24 CCommunicationManager::eCOM24
#define COM25 CCommunicationManager::eCOM25
#define COM26 CCommunicationManager::eCOM26
#define COM27 CCommunicationManager::eCOM27
#define COM28 CCommunicationManager::eCOM28
#define COM29 CCommunicationManager::eCOM29
#define COM30 CCommunicationManager::eCOM30
#define COM31 CCommunicationManager::eCOM31
#define COM32 CCommunicationManager::eCOM32
#define COM33  CCommunicationManager::eCOM33 
#define COM34  CCommunicationManager::eCOM34 
#define COM35  CCommunicationManager::eCOM35 
#define COM36  CCommunicationManager::eCOM36 
#define COM37  CCommunicationManager::eCOM37 
#define COM38  CCommunicationManager::eCOM38 
#define COM39  CCommunicationManager::eCOM39 
#define COM40  CCommunicationManager::eCOM40 
#define COM41  CCommunicationManager::eCOM41 
#define COM42  CCommunicationManager::eCOM42 
#define COM43  CCommunicationManager::eCOM43 
#define COM44  CCommunicationManager::eCOM44 
#define COM45  CCommunicationManager::eCOM45 
#define COM46  CCommunicationManager::eCOM46 
#define COM47  CCommunicationManager::eCOM47 
#define COM48  CCommunicationManager::eCOM48 
#define COM49  CCommunicationManager::eCOM49 
#define COM50  CCommunicationManager::eCOM50 
#define COM51  CCommunicationManager::eCOM51 
#define COM52  CCommunicationManager::eCOM52 
#define COM53  CCommunicationManager::eCOM53 
#define COM54  CCommunicationManager::eCOM54 
#define COM55  CCommunicationManager::eCOM55 
#define COM56  CCommunicationManager::eCOM56 
#define COM57  CCommunicationManager::eCOM57 
#define COM58  CCommunicationManager::eCOM58 
#define COM59  CCommunicationManager::eCOM59 
#define COM60  CCommunicationManager::eCOM60 
#define COM61  CCommunicationManager::eCOM61 
#define COM62  CCommunicationManager::eCOM62 
#define COM63  CCommunicationManager::eCOM63 
#define COM64  CCommunicationManager::eCOM64 
#define COM65  CCommunicationManager::eCOM65 
#define COM66  CCommunicationManager::eCOM66 
#define COM67  CCommunicationManager::eCOM67 
#define COM68  CCommunicationManager::eCOM68 
#define COM69  CCommunicationManager::eCOM69 
#define COM70  CCommunicationManager::eCOM70 
#define COM71  CCommunicationManager::eCOM71 
#define COM72  CCommunicationManager::eCOM72 
#define COM73  CCommunicationManager::eCOM73 
#define COM74  CCommunicationManager::eCOM74 
#define COM75  CCommunicationManager::eCOM75 
#define COM76  CCommunicationManager::eCOM76 
#define COM77  CCommunicationManager::eCOM77 
#define COM78  CCommunicationManager::eCOM78 
#define COM79  CCommunicationManager::eCOM79 
#define COM80  CCommunicationManager::eCOM80 
#define COM81  CCommunicationManager::eCOM81 
#define COM82  CCommunicationManager::eCOM82 
#define COM83  CCommunicationManager::eCOM83 
#define COM84  CCommunicationManager::eCOM84 
#define COM85  CCommunicationManager::eCOM85 
#define COM86  CCommunicationManager::eCOM86 
#define COM87  CCommunicationManager::eCOM87 
#define COM88  CCommunicationManager::eCOM88 
#define COM89  CCommunicationManager::eCOM89 
#define COM90  CCommunicationManager::eCOM90 
#define COM91  CCommunicationManager::eCOM91 
#define COM92  CCommunicationManager::eCOM92 
#define COM93  CCommunicationManager::eCOM93 
#define COM94  CCommunicationManager::eCOM94 
#define COM95  CCommunicationManager::eCOM95 
#define COM96  CCommunicationManager::eCOM96 
#define COM97  CCommunicationManager::eCOM97 
#define COM98  CCommunicationManager::eCOM98 
#define COM99  CCommunicationManager::eCOM99 
#define COM100 CCommunicationManager::eCOM100
#define COM101 CCommunicationManager::eCOM101
#define COM102 CCommunicationManager::eCOM102
#define COM103 CCommunicationManager::eCOM103
#define COM104 CCommunicationManager::eCOM104
#define COM105 CCommunicationManager::eCOM105
#define COM106 CCommunicationManager::eCOM106
#define COM107 CCommunicationManager::eCOM107
#define COM108 CCommunicationManager::eCOM108
#define COM109 CCommunicationManager::eCOM109
#define COM110 CCommunicationManager::eCOM110
#define COM111 CCommunicationManager::eCOM111
#define COM112 CCommunicationManager::eCOM112
#define COM113 CCommunicationManager::eCOM113
#define COM114 CCommunicationManager::eCOM114
#define COM115 CCommunicationManager::eCOM115
#define COM116 CCommunicationManager::eCOM116
#define COM117 CCommunicationManager::eCOM117
#define COM118 CCommunicationManager::eCOM118
#define COM119 CCommunicationManager::eCOM119
#define COM120 CCommunicationManager::eCOM120
#define COM121 CCommunicationManager::eCOM121
#define COM122 CCommunicationManager::eCOM122
#define COM123 CCommunicationManager::eCOM123
#define COM124 CCommunicationManager::eCOM124
#define COM125 CCommunicationManager::eCOM125
#define COM126 CCommunicationManager::eCOM126
#define COM127 CCommunicationManager::eCOM127
#define COM128 CCommunicationManager::eCOM128

#define ProtocolDiag CCommunicationManager::eProtocolDiag
#define ProtocolEmmi CCommunicationManager::eProtocolEmmi
#define ProtocolRawData CCommunicationManager::eProtocolRawData
#define ProtocolStrings CCommunicationManager::eProtocolStrings

#define FlowControlNone CCommunicationManager::eFlowControl::eNone
#define FlowControlXOnXOff CCommunicationManager::eFlowControl::eXOnXOff
#define FlowControlHardware CCommunicationManager::eFlowControl::eHardware

#define SocketServer CCommunicationManager::eSocketServer
#define SocketClient CCommunicationManager::eSocketClient

#define TCP			 CCommunicationManager::eTCP
#define UDP			 CCommunicationManager::eUDP


#endif // !defined(AFX_COMMUNICATIONMANAGER_H__F589A92E_425D_4174_85B6_F1D0BF41EB72__INCLUDED_)
