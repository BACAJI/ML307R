/*--------------------------------------------------------------------------------------------------------------------

 (C) Copyright 2006,2007 Marvell Semiconductor Israel Ltd. All Rights Reserved  

-------------------------------------------------------------------------------------------------------------------*/


#if !defined(AFX_XDEVREPORTER_H__3B5C683A_BD99_4CDA_861D_587C02F9CD30__INCLUDED_)
#define AFX_XDEVREPORTER_H__3B5C683A_BD99_4CDA_861D_587C02F9CD30__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define		DEFAULT_MSG_BOX_MODE		MB_OK

class CStringArray;
class CAdoDbConnector;
struct sDeviceInitResults;

class CXDEVReporter
{

	public:
		void GetInitResultMessage(sDeviceInitResults *initReports);
		void SetOvernightMode(BOOL iOvernightMode);
		BOOL GetOvernightMode();
		void SetMsgBoxType(UINT msgBoxType);
		CXDEVReporter();
		CXDEVReporter(BOOL bOvernightMode);
		virtual ~CXDEVReporter();

		int SendMsg(int errCode);
        int SendMsg(CAdoDbConnector *dbCon, int errCode,CString *strErrMessage);
		int SendMsg(int errCode,CString *strAddin);
		int SendMsg(int errCode,int AddinNum);
		int SendMsg(const CString *msg);
		int SendMsg(const CString *msg,bool sendToMsgBox,bool sendToICAT);
		void GetErrorMessage(const CString *strAddin, int errCode, CString *strErrMessage);

        void GetErrorMessage(CAdoDbConnector *dbCon, int errCode, CString *strErrMessage);
		bool ReportInitializationResults(sDeviceInitResults *initReports);
		void SetSendToICAT(bool usersChoise);
		void SetSendToMsgBox(bool usersChoise);

	protected:
		BOOL m_OvernightMode;
		bool m_SendToMsgBox;
		bool m_SendToICAT;
		UINT m_MsgBoxType;
		void StrArrayToMsgString(const CStringArray *stringArray,
								 CString *msgString);

};

#endif // !defined(AFX_XDEVREPORTER_H__3B5C683A_BD99_4CDA_861D_587C02F9CD30__INCLUDED_)
