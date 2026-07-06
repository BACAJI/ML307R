/*--------------------------------------------------------------------------------------------------------------------

 (C) Copyright 2006,2007 Marvell Semiconductor Israel Ltd. All Rights Reserved  

-------------------------------------------------------------------------------------------------------------------*/


#if !defined(AFX_CONFIGDEVICE_H__74873A93_E8A3_4F11_BF29_73AD043A7C7A__INCLUDED_)
#define AFX_CONFIGDEVICE_H__74873A93_E8A3_4F11_BF29_73AD043A7C7A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CConfigDevice  
{
public:
	CConfigDevice();
	CConfigDevice(const CConfigDevice& oConfigDevice);
	virtual ~CConfigDevice();

	void operator=(const CConfigDevice& oConfigDevice);

	CString					m_strDevGPIBAddress;          
	CString					m_strBoardInterface;		// the GPIB board on the PC (can be 0 or 1).
	CString					m_strDeviceName;			// a name unique to a device.
	CString					m_strDeviceCfgName;			// a name unique to the device in the specific configuration (if 
	CString                 m_strDeviceProtocol;													// there are 2 instances of the same device in 1 configuration).
	
	BOOL					m_bReset;
	BOOL					m_bSendIdn;
	BOOL					m_bHasSecondaryAddresses;
		
};

#endif // !defined(AFX_CONFIGDEVICE_H__74873A93_E8A3_4F11_BF29_73AD043A7C7A__INCLUDED_)
