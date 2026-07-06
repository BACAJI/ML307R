/*--------------------------------------------------------------------------------------------------------------------

 (C) Copyright 2006,2007 Marvell Semiconductor Israel Ltd. All Rights Reserved  

-------------------------------------------------------------------------------------------------------------------*/


#ifndef		__IPTK_RECORDER_DEFINITIONS__
#define		__IPTK_RECORDER_DEFINITIONS__

#include "../IMLTDefinitions.h"

// Cycle record with create new file
#define _CYCLE_CREATENEW 0

// Ini File Definitions:
//-----------------------

#define			LOAD_DEFAULT_PARAMS				0
#define			LOAD_LAST_ENTERED_PARAMS		1
#define			SAVE_TO_DEFAULT_PARAMS			2
#define			SAVE_TO_LAST_ENTERED_PARAMS		3

// Recorder Definitions:
//------------------------

#define			NUM_OF_PENDING_OBJECTS 				16

#define			MIN_RECORDING_BUFFER_SIZE			512
#define			DEFAULT_RECORDING_BUFFER_SIZE		(64*1024)	// 64 KB

#define			GET_VERSION_BUFFER_SIZE				512			//this is the size used for getting 
																// the ac. card's version number 
//Hui#define			SYSTEM_ERROR_BUF_SIZE				256			//size of buffer used for getting the os last error message


#define			DEFAULT_MAX_RECORDING_FILE_SIZE		100	//in mega bytes (100 MB)
#define			MIN_MB_DISK_SPACE_REQUIREMENT		250	//in mega bytes (250 MB)

#define			DEFAULT_NUM_BYTES_TO_RECORD			(1024*1024) //in bytes (1 MB)

#define			NUM_FIFO_CLEANING_ROUNDS			5
#define			EMPTY_FIFO_WAITING_TIME				200			//200 millisec

//connection interfaces: 
//-----------------------

#define			CONNECTION_INTERFACE_USB2_IPTK		2
#define			CONNECTION_INTERFACE_SCSI			3	// for future use  

//timeouts :

#define			RECORDER_LAST_BUFFER_READING_TIMEOUT	750			//750 msec
#define			RECORDER_VERSION_REQUEST_TIMEOUT		500			//500 msec

#define			STOP_RECORDING_TIMEOUT					12000		// 12 seconds
#define			STOP_SEARCHING_TIMEOUT					6000		// 6 seconds
#define			MIN_STOP_RECORDING_TIMEOUT				4000		// 4 seconds
#define			STOP_RECORDING							30000

// Recording Modes:
//-----------------

#define			RECORD_NON_CYCLIC						0
#define			RECORD_CYCLIC							1
#define			RECORD_STRESS_NON_CYCLIC				2
#define			RECORD_STRESS_CYCLIC					3
#define			RECORD_TRIGGER							4
#define			PT_RECORDER								5

// Recorder States:
//------------------

#define			RECORDER_STATE_NOT_RUNNING				0
#define			RECORDER_STATE_RECORDING				1
#define			RECORDER_STATE_SAVING					2

// Stress Recorder:
//-----------------

// the minimum workingset (physical memory reserved for the current process) of
// the process will be the number of bytes to record +  MIN_WORKINGSET_ADDITIONAL_MEMORY.
// in the same way the maximum workingset of the process will be the number of bytes to record 
// +  MAX_WORKINGSET_ADDITIONAL_MEMORY.
		
#define			MIN_WORKINGSET_ADDITIONAL_MEMORY		(10*1024*1024)
#define			MAX_WORKINGSET_ADDITIONAL_MEMORY		(50*1024*1024)

#define			MAX_STRESS_RECORDER_FILE_SIZE			(1024*1024*1024)//1GB

// Gui Definitions:
//-----------------

#define			RECORDER_WIN_MSG_SENDING_FREQ			16
#define			RECORDER_NO_WIN_MSG_SENDING				-1
	
#define			NUM_OF_RECORDER_STATUS_MSGS				8
// Recorder Window Messages:
//---------------------------
 
// these window messages are used to inform the caller of the 
// recording (that needs for this purpose to have a member, or inherit from CWND)
// of the status, and termination of the recording function, that is running on a secondary thread.

#define			IPTK_RECORDER_WND_MSG_OFFSET			(WM_USER + 200)	// an abritary value...must not conjest with other module's win messages

#define			WM_RECORDING_PROGRESS				(IPTK_RECORDER_WND_MSG_OFFSET + 1) 
#define			WM_RECORDING_TERMINATED				(IPTK_RECORDER_WND_MSG_OFFSET + 2)
#define			WM_RECORDING_IS_STILL_RUNNING		(IPTK_RECORDER_WND_MSG_OFFSET + 3)
#define			WM_RECORDING_GEN_MSG				(IPTK_RECORDER_WND_MSG_OFFSET + 4) 

#define			WM_SAVING_PROGRESS					(IPTK_RECORDER_WND_MSG_OFFSET + 10) 
#define			WM_SAVING_TERMINATED				(IPTK_RECORDER_WND_MSG_OFFSET + 11)
#define			WM_SAVING_IS_STILL_RUNNING			(IPTK_RECORDER_WND_MSG_OFFSET + 12) // currently unused
#define			WM_SAVING_GEN_MSG					(IPTK_RECORDER_WND_MSG_OFFSET + 13) 


// Message Parameters:  
//--------------------
// WM_RECORDING_PROGRESS - WPARAM - a UINT - num bytes RECORDed, LPARAM - percentage of the file Recorded (0 to 100)
// WM_RECORDING_TERMINATED - WPARAM - a BOOL - success or failure, LPARAM - a pointer to a CString message
//WM_RECORDING_IS_STILL_RUNNING - WPARAM - a pointer to a CString message


//USB2 definitions :
//-------------------
#define			IPTK_CARD_RESPONSE_BUFFER_SIZE		256

#define			DEFAULT_USB2_READING_BUFFER_SIZE	512				// in BYTES
#define			USB2_VENDOR_REQ_SEND_DATA			0xb3			// signals the iptk acq card to send data.
#define			USB2_VENDOR_REQ_STOP_DATA			0xb2			// signals the iptk acq card to stop sending data.
#define			USB2_VENDOR_REQ_GET_VERSION			0xb7			// signals the iptk acq card to Get the cards version.
#define			USB2_VENDOR_REQ_SEND_XDA_DATA		0xb4			// signals the iptk acq card to send only data coming from the XScale/ARM (and without headers).
			
// HSL Message Headers:  
//---------------------
#define			TCU_MSG_HEADER_BYTE					0x14
#define			SINGLE_HEADER_BYTE					0x13	
#define			LONG_MSG_HEADER_BYTE				0x12
#define			ZERO_PADDING_HEADER_BYTE			0x00

//Recording Trigger Setting:
//--------------------------
#define			DEFAULT_STR_TRIGGER_OPCODE			""
#define			DEFAULT_STR_TRIGGER_DEFINITION		""
#define			DEFAULT_STR_TRIGGER_MSG				"Default Trigger (0x0000)"	
#define			DEFAULT_STR_TRIGGER_POSITION		"0"	
#define			DEFAULT_TRIGGER_OPCODE				0x0000
#define			DEFAULT_TRIGGER_POSITION			0

//Opcode / field presentation:
//-----------------------------
#define			HEXADECIMAL_PRESENTATION			0
#define			DECIMAL_PRESENTATION				1

//Recorded filr name
//----------------------------
#define			DEFAULT_AUTO_INCREMENT_FILE_NAME	TRUE

// for getting the hard disk size:

typedef BOOL (__stdcall * pfuncGetDiskFreeSpaceEx) (LPCTSTR lpDirectoryName,PULARGE_INTEGER lpFreeBytesAvailable,PULARGE_INTEGER lpTotalNumberOfBytes,PULARGE_INTEGER lpTotalNumberOfFreeBytes);

// Macros:
//----------

//Used for getting the system's last error string:

#define			GET_SYSTEM_LAST_ERROR_STRING(pBuff,iBufSize)	::FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,NULL,::GetLastError(),0,(pBuff),((iBufSize)-1),NULL)

#endif	//	__IPTK_RECORDER_DEFINITIONS__
