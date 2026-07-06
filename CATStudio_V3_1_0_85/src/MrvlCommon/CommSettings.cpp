#pragma once
#include "stdafx.h"
#include "CommSettings.h"
//#include "ApplicationINI.h"


ECommSettingsErr CCommSettings::LoadSettings( int nDevice )
{

	///[Device Number][6-10-2011]--------------------------------------------------
	if( nDevice<0 || nDevice>7 )
	{
		return eInvalidArguments;
	}

	CString sSection;
	sSection.Format(_T("DevComm\\Device_%d_Settings"), nDevice);


	m_nDevice = nDevice;

	UINT	nEnabled		= AppIni()->GetProfileInt(sSection, _T("Enabled"), 0 );
	CString sProto			= AppIni()->GetProfileString(sSection, _T("ProtocolType"), _T("Diag") );
	CString sComm			= AppIni()->GetProfileString(sSection, _T("CommunicationType"), _T("USB") );
	CString sDrvName		= AppIni()->GetProfileString(sSection, _T("DriverName"), _T("MDiagUSB") );
	UINT	nAutoDetect		= AppIni()->GetProfileInt(sSection, _T("AutoDetect"), 0 );
	UINT	nDumpRecvData	= AppIni()->GetProfileInt(sSection, _T("DumpRecvData"), 0 );
	CString sUSBName		= AppIni()->GetProfileString(sSection, _T("USBName"), _T("") );
	CString sUsbRec			= AppIni()->GetProfileString(sSection, _T("USBRecognitionString"), _T("") );
	CString sSavedUSBNames	= AppIni()->GetProfileString(sSection, _T("SavedUSBNames"), _T("") );
	CString sCOMName		= AppIni()->GetProfileString(sSection, _T("COMName"), _T("") );
	UINT    nCOMNum			= AppIni()->GetProfileInt(sSection, _T("COMNumber"), 0 );  
	UINT    nBaud			= AppIni()->GetProfileInt(sSection, _T("BaudRate"), 0 );
	CString sSavedCOMNames	= AppIni()->GetProfileString(sSection, _T("SavedCOMNames"), _T("") );
	UINT	nReliableSerial	= AppIni()->GetProfileInt(sSection, _T("ReliableSerial"), 0 );
	UINT	nSplitLineSerial= AppIni()->GetProfileInt(sSection, _T("SplitLineSerial"), 0 );
	CString sIPAddr			= AppIni()->GetProfileString(sSection, _T("IPAddress"), _T("") );
	UINT    nPort			= AppIni()->GetProfileInt(sSection, _T("PortNumber"), 0);
	CString sRemoteIPAddr	= AppIni()->GetProfileString(sSection, _T("RemoteIPAddress"), _T("") );
	UINT    nRemotePort		= AppIni()->GetProfileInt(sSection, _T("RemotePortNumber"), 0);
	CString sADBSerialNum	= AppIni()->GetProfileString(sSection, _T("ADBSerialNum"), _T("") );


	sProto.TrimLeft(); sProto.TrimRight(); //sProto.MakeUpper();
	sComm.TrimLeft(); sComm.TrimRight(); //sComm.MakeUpper();



	///[Comm Type Proto Type][6-10-2011]--------------------------------------------------
	if( sComm==_T("Serial") )
	{
		m_eCommType = eCOM;
	}
	else if( sComm==_T("USB") )
	{
		m_eCommType = eUSB;
	}
	else if( sComm==_T("TCPServer") )
	{
		m_eCommType = eSocketTcpServer;
	}
	else if( sComm==_T("TCPClient") )
	{
		m_eCommType = eSocketTcpClient;
	}
	else if( sComm==_T("UDP") )
	{
		m_eCommType = eSocketUdp;
	}

	if( sProto==_T("RawData") )
		m_eProtType = eStringProtocol;
	else if( sProto==_T("Diag") )
		m_eProtType = eDIAGProtocol;
	else if( sProto==_T("MEED") )
		m_eProtType = eMEEDProtocol;
	else if( sProto==_T("AdbData") )
		m_eProtType = eADBProtocol;
	//else if( sProto==_T("NMEA") )
	//	m_eProtType = eNMEAProtocol;

	m_strDrvName = sDrvName;
	m_bEnabled = nEnabled == 0 ? FALSE : TRUE;
	m_bAutoDetect = nAutoDetect == 0 ? FALSE : TRUE;
	m_bDumpRecvData = nDumpRecvData == 0 ? FALSE : TRUE;

	///[USB][6-10-2011]--------------------------------------------------
	m_sUSBName = sUSBName;
	m_sUSBRecStr = sUsbRec;
	m_sSavedUSBNames = sSavedUSBNames;

	///[COM][6-10-2011]--------------------------------------------------
	m_sComName = sCOMName;
	m_nComNum = nCOMNum;
	m_nBaudRate = nBaud;
	m_sSavedComNames = sSavedCOMNames;
	m_bReliableSerial  = nReliableSerial==0 ? FALSE : TRUE;
	m_bSplitLineSerial = nSplitLineSerial==0 ? FALSE : TRUE;


	///[TCP UDP][6-10-2011]--------------------------------------------------
	m_sIPAddr = sIPAddr;
	m_nIPPort = nPort;
	m_sRemoteIPAddr = sRemoteIPAddr;
	m_nRemoteIPPort = nRemotePort;

	//[ADB][11-07-2014]--------------------------------------------------
	m_sADBSerialNum = sADBSerialNum;

	return eNoErr;
}

ECommSettingsErr CCommSettings::SaveSettings()
{

	return SaveSettings(*this);

}

ECommSettingsErr CCommSettings::SaveSettings( const CCommSettings& settings )
{

	if( settings.m_nDevice<0 || settings.m_nDevice>7 )
	{
		return eInvalidArguments;
	}

	//=============== Public ===============
	CString sSection;
	sSection.Format(_T("DevComm\\Device_%d_Settings"), settings.m_nDevice);

	CString sProtType = _T("Diag");
	if( settings.m_eProtType== eStringProtocol )
	{
		sProtType = _T("RawData");
	}
	else if ( settings.m_eProtType==eMEEDProtocol )
	{
		sProtType = _T("MEED");
	}
	else if( settings.m_eProtType== eADBProtocol )
	{
		sProtType = _T("AdbData");
	}
	//else if( settings.m_eProtType==eNMEAProtocol )
	//{
	//	sProtType = _T("NMEA");
	//}

	CString sCommType;//		= settings.m_eCommType==eCOM? _T("Serial") :( settings.m_eCommType==eSocketTcpServer? _T("TCP Server"):_T("USB") );
	switch (settings.m_eCommType)
	{
		case eCOM:
			sCommType = _T("Serial");
			break;
		case eUSB:
			sCommType = _T("USB");
			break;
		case eSocketTcpServer:
			sCommType = _T("TCPServer");
			break;
		case eSocketTcpClient:
			sCommType = _T("TCPClient");
			break;
		case eSocketUdp:
			sCommType = _T("UDP");
			break;
		default:
			break;
	}

	CString sDrvName		= settings.m_strDrvName;
	UINT	nAutoDetect		= settings.m_bAutoDetect ? 1 : 0;
	UINT	nDumpRecvData	= settings.m_bDumpRecvData ? 1 : 0;
	//=============== USB ===============
	CString sUSBName		= settings.m_sUSBName;
	CString sUSBRec			= nAutoDetect == 1 ? _T("") : settings.m_sUSBRecStr;
	CString sSavedUSBNames	= settings.m_sSavedUSBNames;
	//=============== UART ===============
	CString sCOMName		= settings.m_sComName;
	UINT    nCOMNum			= nAutoDetect == 1 ? 0 : settings.m_nComNum;
	UINT    nBaud			= settings.m_nBaudRate;
	CString sSavedComNames	= settings.m_sSavedComNames;
	UINT	nReliableSerial	= settings.m_bReliableSerial ? 1 : 0;
	UINT	nSplitLineSerial= settings.m_bSplitLineSerial ? 1 : 0;
	//=============== TCP/UDP ===============
	UINT    nPort			= settings.m_nIPPort;
	CString sIPAddr			= settings.m_sIPAddr;
	UINT    nRemotePort		= settings.m_nRemoteIPPort;
	CString sRemoteIPAddr	= settings.m_sRemoteIPAddr;
	//=============== ADB ===============
	CString sADBSerialNum		= settings.m_sADBSerialNum;

	// Remove the Com number before save to ini
	int nPos = 0;	
	nPos = settings.m_sComName.ReverseFind('(');
	if ( -1 != nPos )
	{
		sCOMName = settings.m_sComName.Left(nPos).Trim();
	}


	////=============== Public ===============
	//AppIni()->WriteProfileString(sSection, _T("Protocol Type"), sProtType);
	//AppIni()->WriteProfileString(sSection, _T("Communication Type"), sCommType );
	//AppIni()->WriteProfileInt(sSection, _T("Auto Detect"), nAutoDetect );
	////=============== USB ===============
	//AppIni()->WriteProfileString(sSection, _T("USB Name"), sUSBName );
	//AppIni()->WriteProfileString(sSection, _T("USB Recognition String"), sUSBRec );
	//AppIni()->WriteProfileString(sSection, _T("Saved USB Names"), sSavedUSBNames );
	////=============== UART ===============
	//AppIni()->WriteProfileString(sSection, _T("COM Name"), sCOMName );
	//AppIni()->WriteProfileInt(sSection, _T("COM Number"), nCOMNum );
	//AppIni()->WriteProfileInt(sSection, _T("Baud Rate"), nBaud );
	//AppIni()->WriteProfileString(sSection, _T("Saved COM Names"), sSavedComNames );
	////=============== TCP/UDP ===============
	//AppIni()->WriteProfileString(sSection, _T("IP Address"), sIPAddr );
	//AppIni()->WriteProfileInt(sSection, _T("Port Number"), nPort );

	//AppIni()->FlushData();

	//=============== Public ===============
	AppIni()->WriteProfileString(sSection, _T("DriverName"), sDrvName);
	AppIni()->WriteProfileString(sSection, _T("ProtocolType"), sProtType);
	AppIni()->WriteProfileString(sSection, _T("CommunicationType"), sCommType );
	AppIni()->WriteProfileInt(sSection, _T("AutoDetect"), nAutoDetect );
	AppIni()->WriteProfileInt(sSection, _T("DumpRecvData"), nDumpRecvData );
	//=============== USB ===============
	AppIni()->WriteProfileString(sSection, _T("USBName"), sUSBName );
	AppIni()->WriteProfileString(sSection, _T("USBRecognitionString"), sUSBRec );
	AppIni()->WriteProfileString(sSection, _T("SavedUSBNames"), sSavedUSBNames );
	//=============== UART ===============
	AppIni()->WriteProfileString(sSection, _T("COMName"), sCOMName );
	AppIni()->WriteProfileInt(sSection, _T("COMNumber"), nCOMNum );
	AppIni()->WriteProfileInt(sSection, _T("BaudRate"), nBaud );
	AppIni()->WriteProfileString(sSection, _T("SavedCOMNames"), sSavedComNames );
	AppIni()->WriteProfileInt(sSection, _T("ReliableSerial"), nReliableSerial );
	AppIni()->WriteProfileInt(sSection, _T("SplitLineSerial"), nSplitLineSerial );
	//=============== TCP/UDP ===============
	AppIni()->WriteProfileString(sSection, _T("IPAddress"), sIPAddr );
	AppIni()->WriteProfileInt(sSection, _T("PortNumber"), nPort );
	AppIni()->WriteProfileString(sSection, _T("RemoteIPAddress"), sRemoteIPAddr );
	AppIni()->WriteProfileInt(sSection, _T("RemotePortNumber"), nRemotePort );
	//=============== ADB ===============
	AppIni()->WriteProfileString(sSection, _T("ADBSerialNum"), sADBSerialNum );

	AppIni()->FlushData();

	return eNoErr;

}

ECommSettingsErr CCommSettings::SetEnabled( BOOL bEnabled )
{
	CString sSection;
	sSection.Format(_T("DevComm\\Device_%d_Settings"), m_nDevice);

	m_bEnabled = bEnabled;
	UINT unEnabled = bEnabled ? 1 : 0;
	BOOL bRet = AppIni()->WriteProfileInt(sSection, _T("Enabled"), unEnabled );
	AppIni()->FlushData();
	return eNoErr;
}

BOOL CCommSettings::IsEnabled()
{
	return m_bEnabled;
}

CString CCommSettings::SettingsToLog()
{
	CString strLog = _T("");
	CString strCommType		= m_eCommType==eCOM? _T("Serial") :( m_eCommType==eSocketTcpServer? _T("TCP Server"):_T("USB") );
	CString	strAutoDetect		= m_bAutoDetect ? _T("ON") : _T("OFF");
	//=============== USB ===============
	CString strUSBName		= m_sUSBName;
	CString strUSBRec			= m_bAutoDetect ? _T("") : m_sUSBRecStr;
	CString strSavedUSBNames	= m_sSavedUSBNames;
	//=============== UART ===============
	CString strCOMName		= m_sComName;
	UINT    nCOMNum			= m_bAutoDetect ? 0 : m_nComNum;
	CString sSavedComNames	= m_sSavedComNames;
	//=============== TCP/UDP ===============
	UINT    nPort			= m_nIPPort;
	CString strIPAddr			= m_sIPAddr;

	strLog.Format(_T("Dev %d - Communication settings: AutoDetect: %s, CommType: %s, USBName: %s, USBRecStr: %s, COMName: %s, COMNum: %d, IPAddr: %s, IPPort: %d"), 
		m_nDevice, strAutoDetect, strCommType, strUSBName, strUSBRec, strCOMName, nCOMNum, strIPAddr, nPort);
	return strLog;
}
