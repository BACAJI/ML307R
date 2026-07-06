#pragma once
#include "CommonDefs.h"
#include "ICATMessage.h"
#include "XmlConfig.h"
#include "GeneralMacroDefine.h"

enum ECommSettingsErr
{
   eNoErr = 0,
   eLoadFailed = 1,
   eStoreFailed =2,
   eInvalidArguments=3,
};

class CATCORE_DLLEXPORT CCommSettings
{
public:
  //=============== Public ===============
	BOOL			m_bEnabled;
  int				m_nDevice;
  ECommType			m_eCommType;
  EProtocolType		m_eProtType;
  CString			m_strDrvName;
  BOOL				m_bAutoDetect;		// Share for USB and UART
  BOOL				m_bDumpRecvData;
  //=============== USB ===============
  CString			m_sUSBRecStr;
  CString			m_sTmpUSBRecStr;
  CString			m_sUSBName;
  CString			m_sSavedUSBNames;
  //=============== UART ===============
  UINT				m_nComNum;
  UINT				m_nBaudRate;
  CString			m_sComName;
  CString			m_sSavedComNames;
  BOOL				m_bReliableSerial;
  BOOL				m_bSplitLineSerial;
  //=============== TCP/UDP ===============
  UINT				m_nIPPort;
  CString			m_sIPAddr;
  UINT				m_nRemoteIPPort;
  CString			m_sRemoteIPAddr;
  //=============== ADB ===============
  CString			m_sADBSerialNum;
  CString			m_sTmpADBSerialNum;
  //CString			m_sADBName;
  //CString			m_sSavedADBNames;

  CCommSettings()
  {
	//=============== Public ===============
	  m_bEnabled		=	FALSE;
	m_nDevice			=	0;
	m_eCommType			=	eUSB;
	m_eProtType			=	eDIAGProtocol;
	m_strDrvName		=	_T("");
	m_bAutoDetect		=	FALSE;
	//=============== USB ===============
	m_sUSBName			=	_T("");
	m_sUSBRecStr		=	_T("");
	m_sTmpUSBRecStr		=	_T("");
	m_sSavedUSBNames	=	_T("");
	//=============== UART ===============
	m_nComNum			=	0;
	m_nBaudRate			=	115200;
	m_sComName			=	_T("");
	m_sSavedComNames	=	_T("");
	//=============== TCP/UDP ===============
	m_nIPPort			=	0;
	m_sIPAddr			=	_T("127.0.0.1");
	m_nRemoteIPPort		=	0;
	m_sRemoteIPAddr		=	_T("127.0.0.1");
  }

  BOOL operator == (const CCommSettings &settings) const
  {
	  return (m_bEnabled == settings.m_bEnabled) && (m_nDevice == settings.m_nDevice) && (m_eCommType == settings.m_eCommType) && (m_eProtType == settings.m_eProtType) && (m_strDrvName == settings.m_strDrvName)
		  && (m_bAutoDetect == settings.m_bAutoDetect) && (m_bDumpRecvData == settings.m_bDumpRecvData) && (m_sUSBRecStr == settings.m_sUSBRecStr) && (m_sTmpUSBRecStr == settings.m_sTmpUSBRecStr) && (m_sUSBName == settings.m_sUSBName)
		  && (m_sSavedUSBNames == settings.m_sSavedUSBNames) && (m_nComNum == settings.m_nComNum) && (m_nBaudRate == settings.m_nBaudRate) && (m_sComName == settings.m_sComName) 
		  && (m_sSavedComNames == settings.m_sSavedComNames) && (m_nIPPort == settings.m_nIPPort) && (m_sIPAddr == settings.m_sIPAddr) 
		  && (m_nRemoteIPPort == settings.m_nRemoteIPPort) && (m_sRemoteIPAddr == settings.m_sRemoteIPAddr);
  }

  BOOL operator != (const CCommSettings &settings) const
  {
	  return !operator == (settings);
  }

  CCommSettings& operator = (const CCommSettings& sourceCommSettings)
  {
	  if (this == &sourceCommSettings)	return (*this);

	  this->m_bEnabled = sourceCommSettings.m_bEnabled;
	  this->m_nDevice = sourceCommSettings.m_nDevice;
	  this->m_eCommType = sourceCommSettings.m_eCommType;
	  this->m_eProtType = sourceCommSettings.m_eProtType;
	  this->m_strDrvName = sourceCommSettings.m_strDrvName;
	  this->m_bAutoDetect = sourceCommSettings.m_bAutoDetect;
	  this->m_bDumpRecvData = sourceCommSettings.m_bDumpRecvData;
	  this->m_sUSBRecStr = sourceCommSettings.m_sUSBRecStr;
	  this->m_sTmpUSBRecStr = sourceCommSettings.m_sTmpUSBRecStr;
	  this->m_sUSBName = sourceCommSettings.m_sUSBName;
	  this->m_sSavedUSBNames = sourceCommSettings.m_sSavedUSBNames;
	  this->m_nComNum = sourceCommSettings.m_nComNum;
	  this->m_nBaudRate = sourceCommSettings.m_nBaudRate;
	  this->m_sComName = sourceCommSettings.m_sComName;
	  this->m_sSavedComNames = sourceCommSettings.m_sSavedComNames;
	  this->m_bReliableSerial = sourceCommSettings.m_bReliableSerial;
	  this->m_bSplitLineSerial = sourceCommSettings.m_bSplitLineSerial;
	  this->m_nIPPort = sourceCommSettings.m_nIPPort;
	  this->m_sIPAddr = sourceCommSettings.m_sIPAddr;
	  this->m_nRemoteIPPort = sourceCommSettings.m_nRemoteIPPort;
	  this->m_sRemoteIPAddr = sourceCommSettings.m_sRemoteIPAddr;
	  this->m_sADBSerialNum = sourceCommSettings.m_sADBSerialNum;
	  this->m_sTmpADBSerialNum = sourceCommSettings.m_sTmpADBSerialNum;

	  return *this;
  }

  /*CCommSettings(const CCommSettings& rhs )
  {
    m_nDevice =rhs.m_nDevice;
    m_eCommType	=rhs.m_eCommType ;
    m_eProtType	=rhs.m_eProtType ;
    m_sUSBRecStr=rhs.m_sUSBRecStr;
    m_nComNum	=rhs.m_nComNum     ;
    m_nBaudRate	=rhs.m_nBaudRate ;
    m_nIPPort = rhs.m_nIPPort;
    m_sIPAddr = rhs.m_sIPAddr;
  }

  CCommSettings& operator=(const CCommSettings& rhs)
  {
    m_nDevice =rhs.m_nDevice;
    m_eCommType	=rhs.m_eCommType ;
    m_eProtType	=rhs.m_eProtType ;
    m_sUSBRecStr=rhs.m_sUSBRecStr;
    m_nComNum	=rhs.m_nComNum     ;
    m_nBaudRate	=rhs.m_nBaudRate ;
    m_nIPPort = rhs.m_nIPPort;
    m_sIPAddr = rhs.m_sIPAddr;

    return *this;
  }*/

  ECommSettingsErr	LoadSettings(int nDevice);
  ECommSettingsErr	SaveSettings();
  ECommSettingsErr SetEnabled( BOOL bEnabled );
  BOOL				IsEnabled();
  static  ECommSettingsErr  SaveSettings(const CCommSettings& settings);
  CString SettingsToLog();
};

