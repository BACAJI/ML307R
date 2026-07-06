/*--------------------------------------------------------------------------------------------------------------------

 (C) Copyright 2006,2007 Marvell Semiconductor Israel Ltd. All Rights Reserved  

-------------------------------------------------------------------------------------------------------------------*/



#ifndef		__XDEVSTRUCTURES__
#define		__XDEVSTRUCTURES__

//#include "Definitions.h"
#include <afxtempl.h>
#include <afxmt.h>

#include "GeneralMacroDefine.h"
// This struct is held in the XDEVSession. 

#ifndef		__COMMON_API_STRUCTURES__
#define		__COMMON_API_STRUCTURES__

// COMMON_API_STRUCTURES -	structures used also by device drivers with 
//							special initialization api functions.

typedef struct SecAddressParams
{
	int iSecAddress;
	CString strInitMode;		

}sSecAddressParams;

typedef struct AttenuationParams
{
	CString strPortName;
	CString strBandOrFreqArea;
	double  dAttenuation; 

}sAttenuationParams;

typedef struct ConfigDevParams
{
	CString strConfigDevName;
	CString strDevName;
	int iAddress;
	int iGPIB;
	BOOL bUseXdevAsComInterface;

}sConfigDevParams;

//sSecondarySession - contains all information needed for device 
//					 secondary address initialization.

typedef struct SecondarySession	
{
	int				iSecondaryAddress;		// the gpib secondary address
	unsigned long	secondaryViSession;		// a session to the primary  address.
	CString			strInitMode;			// a string indicating  the initialization mode of the secondary address.
}sSecondarySession;



// sDeviceSessions - This struct is held in the XDEVSession. 
// This is the struct that will eventually 
// be sent back to the to the scripts.

typedef struct DeviceSessions
{
	CString			strPrimaryAddress;	// the gpib primary address	
	unsigned long		primaryViSession;	// a session to the primary  address.
	CArray<sSecondarySession,sSecondarySession&> arrSecondarySessions;	
										// a session array to the secondary 
										// address sessions (sSecondarySession).
}sDeviceSessions;

#endif			//__COMMON_API_STRUCTURES__


typedef struct sAttenuationStructure
{
	CString strPortName;
	CString strBandOrFreqArea;
	double  dAttenuation;
}sAttenuation;


// XDEVSession  -	contains sDeviceConfiguration that is sent back to the Test Engine, 
//					and other details about a specific instrument, that are kept 
//					in the Connection Managers OwnerConnectionMap. 
typedef struct XDEVSession	
{
	sDeviceSessions	sSessions;			//a struct with viSessions to the device's 
										//primary address and secondary addresses.
	CString					ConfigName;
	CString					driverName;
	BOOL					reset;
	BOOL					sendIdn;
	BOOL					hasSecondaryAddresses;
	CString					devInitFunc;
	CString					devTerminateFunc;
	CString					devResetFunc;
	CString					deviceName;				// a name unique to a device.
	CString					deviceGroup;			// The device's primary category.							
	CString					deviceCfgName;			// a name unique to the device in the specific configuration (if 
													// there are 2 instances of the same device in 1 configuration).
	CString					boardInterface;			// the GPIB board on the PC (can be 0 or 1).
	HMODULE					dllHandle;
	CString					idnRequest;
	
}sXDEVSession;


typedef struct sDeviceInitResults
{
	CStringArray successful;
	CStringArray unsuccessful;
	int errorCode;
	CString strMsg;

} sScriptValidationResults;

//InitializationStruct - sent by the Test Engine, filled by XDEV.

struct sInitialization
{
	CString strOwner;				//who's asking for the initialization - can be Test Engine,
									// Test Plan, Send Command, etc.	
	CString strConfigName;			// The name of the configuration to be initialized (a new API requirement)
	
									// then the strConfigName indicates the specific device
	BOOL iOvernightMode;			// determines whether there will be message boxes or not.
	CPtrArray * arrDeviceHandlers;	// an array of sDeviceConfiguration structures.
	sDeviceInitResults sReports;	//a struct, containing two string arrays. One with the devices which were initialized successfully,
									// the other with the ones that were not, with their error messages.	
	CString strResourcePath;		// the path of the database and images.	
	CString strAdditionalParam;		// Can Be any additional parameter needed in the future.In SINGLE_DEVICE_INITIALIZATION mode - 
									// if not empty, strAdditionalParam	indicates a specific primary address.	
	int iThreadNum;
	
	CSingleLock *pCSLock;
	CEvent m_KillEvent;
	CEvent m_CanKillEvent;

	sInitialization() : m_KillEvent(0,1), m_CanKillEvent(1,1),pCSLock(NULL),arrDeviceHandlers(NULL) {};

};					// This struct is sent by any external module, to be filled by the user. 


struct tDeviceParam
{
	CString m_strDevName;
	CString m_strDllName;
	
	CString m_strInitFunc;
	CString m_strCloseFunc;
	CString m_strResetFunc;
	
	CString m_strDevGruop;
	CString m_strIDNString;
	CString m_strProtocol;
	int		m_iGPIB;
	int		m_iAddress;
	BOOL	m_bIsIDNable;
	BOOL	m_bIsResetable;

	tDeviceParam()
	{
		m_strDevName = "";
		m_strDllName = "";
		m_strInitFunc = "";
		m_strCloseFunc = "";
		m_strResetFunc = "";
		m_strDevGruop = "Other";
		m_strIDNString = "None";
		m_strProtocol = "visa";
		m_iGPIB = 0;
		m_iAddress = 1;
		m_bIsIDNable = FALSE;
		m_bIsResetable = FALSE;
	}

};

struct tDeviceParamEx : public tDeviceParam
{
	BOOL m_bHasSecAddress;
	BOOL m_bHasAttenuationSetting;
	
	CArray<sSecAddressParams,sSecAddressParams&> arrSecAddress;
	CArray<sAttenuationParams,sAttenuationParams&> arrAttenuation;	

	tDeviceParamEx()
	{
		m_bHasSecAddress = FALSE;
		m_bHasAttenuationSetting = FALSE;
	}

};



#endif //__XDEVSTRUCTURES__
