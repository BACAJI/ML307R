/*--------------------------------------------------------------------------------------------------------------------

 (C) Copyright 2006,2007 Marvell Semiconductor Israel Ltd. All Rights Reserved  

-------------------------------------------------------------------------------------------------------------------*/


#ifndef		__XDEV_DEFINITIONS__
#define		__XDEV_DEFINITIONS__


#include "XDEVStructures.h"

//Default Device's parameters:
//-------------------------------
#define		DEFAULT_PROTOCOL			_T("visa")
#define		DEFAULT_GPIB_INTERFACE			0	
#define		DEFAULT_PRIMARY_ADDRESS			1
#define		DEFAULT_DEV_GROUP			_T("Other")	
#define		DEFAULT_BAND_OR_FREQ		_T("None")	
#define		DEFAULT_GPIB_INTERFACE			0
#define		DEFAULT_IDN_STRING			_T("None")

//Default Device's parameters:
//-------------------------------
#define		DEFAULT_CONFIG_GROUP		_T("Other")
#define		NO_CONFIGURATION_STRING		_T("No Configuration")

//Database:
//---------
#define		XDEV_DB_FILE_NAME					_T("XDEV.mdb")
#define		INSERT_TO_DB					0
#define		UPDATE_DB						1
#define		MAX_DB_SHORT_STRING_LENGTH		100
#define		DB_DEFAULT_PATH					_T("exec\\Db")
#define		DB_DEFAULT_FOLDER				_T("\\DB\\")

//GUI:
//-----
#define		REGISTER_DEV_MODE				0
#define		EDIT_DEV_MODE					1
#define		DELETE_DEV_MODE					2
#define		REGISTER_CONFIG_MODE			3
#define		EDIT_CONFIG_MODE				4
#define		DELETE_CONFIG_MODE				5
#define		EXPORT_DEV_MODE					6
#define		EXPORT_CONFIG_MODE				7
#define		IMPORT_DEV_MODE					8
#define		IMPORT_CONFIG_MODE				9


#define		NUM_OF_GPIB_INTERFACE			2
#define		NUM_OF_DEV_ON_GPIB_INTERFACE	30
#define		TOTAL_NUM_OF_DEVICES			30


#define		COL_PORT						0
#define		COL_BAND_OR_FREQ_AREA			1
#define		COL_ATTENUATION					2 

#define		COL_SEC_ADDRESS					0
#define		COL_INIT_MODE					1

#define		SEC_ADDRESS_DLG					0
#define		ATTENUATION_DLG					1


// ERROR CODES:
//--------------

#define		NO_ERRORS								0

#define		INVALID_DATA							-1
#define		LOAD_DLL_ERROR							-2
#define		GET_PROC_ADD_ERROR						-3
#define		INVALID_ARGUMENTS						-4
#define		THREAD_LOCK_ERROR						-5
#define		INITIALIZATION_ENTRY_DENIED				-6
#define		TO_MANY_THREADS_ERROR					-7
#define		THREAD_KILLED_IN_INITIALIZATION_ERROR	-8

#define		INIT_ERROR								-10
#define		IDN_ERROR								-11
#define		RESET_ERROR								-12
#define		CONFIG_CAGHT_BY_OTHER_OWNER				-13
#define		SHARED_DEVICES_VIOLATION				-14
#define		TERMINATION_ERROR						-15
#define		NO_ITEMS_FOUND_DB_ERROR					-16
#define		XDEV_DB_ERROR								-17


#ifndef		BUFFER_STUFFING_ERROR
#define		BUFFER_STUFFING_ERROR					-51
#endif	//	BUFFER_STUFFING_ERROR

#define		SEND_COMMAND_ERROR						-52
#define		MULTIPLE_COMMANDS_ERROR					-53

#ifndef		VISA_CONNECTOR_ERROR
#define		VISA_CONNECTOR_ERROR					-60
#endif


#define		USER_ABORTION							-100




// MULTITHREADED DEFINITIONS:
//--------------------

#define		MAX_NUM_INIT_THREADS					3
#define		MAX_NUM_INIT_RETRIES					7
#define		MAX_CSLOCK_WAITING_TIME					6000
#define		SLEEPING_TIME_BETWEEN_INIT_ATTEMPTS		2000


// VISA CONNECTOR MODULE DEFINITIONS :
//-------------------------------------

#define			VISA_CONNECTOR_MODULE_NAME			"VisaConnector.dll"

#define			VISA_CONNECTOR_READ_FUNC_NAME		"_Read@12"
#define			VISA_CONNECTOR_WRITE_FUNC_NAME		"_Write@12"
#define			VISA_CONNECTOR_QUERY_FUNC_NAME		"_Query@16"

// OTHER
//-------
#define		DYN_OBJ_INIT_SIZE						10

#define		MIN_GPIB_PRIMARY_ADDRESS				1
#define		MAX_GPIB_PRIMARY_ADDRESS				32

#define		CONFIG_NOT_INITIALIZED					0
#define		CONFIG_INITIALIZED_BY_ME				1

#define		NO_SECONDARY_ADDRESSES					-12480

#define		INVALID_SESSION1						0
#define		INVALID_SESSION2						0xcdcdcdcd

#define		ICAT_MENU_CFG_DLG_MODE					1
#define		NEW_SCRIPT_CFG_DLG_MODE					2
#define		SELECT_SCRIPT_CFG_DLG_MODE				3


/*
#define	PROJECT_DEFAULT_FOLDER_NAME			"XDEV"




// MY DB :
#define	DB_DEFAULT_FILE_NAME			"XDEV_Integrated_DB.mdb"
#define	DB_DEFAULT_PATH					"exec\\Db"
#define DB_DEFAULT_FOLDER				"\\DB\\"


// OTHER DEFINITIONS:
//--------------------

#define		SINGLE_DEVICE_INITIALIZATION			-8976





#define		SEC_ADDRESS_DELIMITER					","
#define		NO_INITIAL_CONFIG_ID					-1

#define		IMAGES_DEFAULT_FOLDER_NAME				"Images"
#define		IMAGES_DEFAULT_REL_PATH					"..\\XDEV\\Images"
#define		MAX_CONFIGURATION_DEVICES				16


#define		USER_DEFINED_SET_CFG_DLG_MODE_STRING	"User Defined Configuration (Default)"
#define		OLD_BMP_SET_CFG_DLG_MODE_STRING			"Bitmap Configuration"

#define		ICAT_MENU_CFG_DLG_MODE					1
#define		NEW_SCRIPT_CFG_DLG_MODE					2
#define		SELECT_SCRIPT_CFG_DLG_MODE				3


#define		NO_CONFIGURATION_KEY					0
#define		NO_CONFIGURATION_STRING					"No Configuration"
#define		CONFIGURATION_NAME_FIELD				"Configuration_Name"
#define		CONFIGURATION_ID_FIELD					"Configuration_ID"

*/
	
#endif	 //__XDEV_DEFINITIONS__
