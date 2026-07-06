/*--------------------------------------------------------------------------------------------------------------------

 (C) Copyright 2006,2007 Marvell Semiconductor Israel Ltd. All Rights Reserved  

-------------------------------------------------------------------------------------------------------------------*/

#ifndef		__IPTK_RECORDER_STRUCTURES__
#define		__IPTK_RECORDER_STRUCTURES__

#include "IPtkRecorderDefinitions.h"
#include "USB2_Drivers/Ioctls.h"
#include <afxmt.h>
#include "ApplicationINI.h"

typedef		VCR_PARAM		SAcquisitionCommand;


// SRecordedData:
//---------------------

//	The following structure is used for ponting to the 
//	specific parts of the memory space. these specific pointers 
//	are sent to the operating system in order to receive the 
//  data recorded from the communication interface.
//	the overlapped structure contains the event that notifies us that 
//	the data has arrived from communication. 

struct SRecordedData
{
	DWORD m_dwBufferSize;
	DWORD m_dwNumBytesRecorded;
	BYTE * m_pStartOfBuffer;
	HANDLE m_hReadyForRead;//this field is relevant only to the Trigger Recorder
	HANDLE m_hReadyForSearch;//this field is relevant only to the Trigger Recorder
	
	SRecordedData() : m_pStartOfBuffer(NULL),m_dwBufferSize(0),m_dwNumBytesRecorded(0),m_hReadyForRead(INVALID_HANDLE_VALUE),m_hReadyForSearch(INVALID_HANDLE_VALUE){}

};

// SRecorderMemoryMap:
//---------------------

// The following structure is used for holding the 
// whole memory space of the recorded data. 
// It's memory is not initialized through the constructor 
// (or freed through the destructor), since it may have 
// several allocation methods (new, or VirtualAllocEx).
//

struct SRecorderMemoryMap
{
	BYTE * m_pStartOfMemory;	// points to the start of memory
	DWORD m_dwMemSize;			// Size of allocated memory in bytes	
	SRecordedData * m_psRecordedDataArray;	// contains an array of SRecordedData structured.
											// that point to specific memory locations
	DWORD m_dwCurPossition;		// current position (index) in the array 				
	DWORD m_dwNumOfArrElemets;	// number of elements in the array.

	SRecorderMemoryMap() : m_pStartOfMemory(NULL),m_dwMemSize(0),
	m_psRecordedDataArray(NULL),m_dwCurPossition(0),m_dwNumOfArrElemets(0) {};
};

//SRecorderAPIParam
//-------------------
// this struct is sent from the caller to the Recorder manager:
struct SRecorderAPIParams
{
	CString strMsgTrigger;
	CString strMsgTriggerDefinition;
	DWORD	dwMsgTriggerOpcode;
	CString strMsgTriggerOpcode;
	int		iTriggerPosition;
	CString	strTriggerPosition;
	DWORD   dwStopRecordingTimeout;		// When requesting to stop - the time waited for event before killing the thread
	DWORD	dwMaxNumBytesToRecord;		// target file maximum size in bytes
	UINT	uiBufferSize;				// The size of the buffer used for recieving the data from communication (in bytes)
	BYTE	byteVendorRequestSend;		// used for communicating with acquisition card
	BYTE	byteVendorRequestStop;		// used for communicating with acquisition card
	BYTE	byteVendorRequestVersion;	// used for communicating with acquisition card
	int		iConnectionInterface;
	int		iRecordingMode;
	int		iWinMsgSendingFreq;			// The frequency of updating the screen with the recording progress. affects performance.
	CString strTargetFile;
	CString strTextEditor; 
	CWnd * pMsgHandler;					// will be used to inform the caller of the progress /
										// end of Recording through window messages.
	BOOL	bAutoIncrementFileName;
	BOOL	bAutoStart;
	
	//constructor, initializes the structure with the default values:
	SRecorderAPIParams() : dwMsgTriggerOpcode(DEFAULT_TRIGGER_OPCODE),strMsgTriggerDefinition(DEFAULT_STR_TRIGGER_DEFINITION),strMsgTriggerOpcode(DEFAULT_STR_TRIGGER_OPCODE),strMsgTrigger(DEFAULT_STR_TRIGGER_MSG), strTriggerPosition(DEFAULT_STR_TRIGGER_POSITION),
						   iTriggerPosition(DEFAULT_TRIGGER_POSITION),uiBufferSize(DEFAULT_RECORDING_BUFFER_SIZE), byteVendorRequestSend(USB2_VENDOR_REQ_SEND_DATA),byteVendorRequestStop(USB2_VENDOR_REQ_STOP_DATA),byteVendorRequestVersion(USB2_VENDOR_REQ_GET_VERSION), 
						   dwStopRecordingTimeout(STOP_RECORDING_TIMEOUT),dwMaxNumBytesToRecord(DEFAULT_NUM_BYTES_TO_RECORD),iConnectionInterface (CONNECTION_INTERFACE_USB2_IPTK),iRecordingMode(RECORD_NON_CYCLIC),iWinMsgSendingFreq(RECORDER_WIN_MSG_SENDING_FREQ),
						   strTextEditor(DEFAULT_TEXT_EDITOR),pMsgHandler(NULL), bAutoIncrementFileName(DEFAULT_AUTO_INCREMENT_FILE_NAME), bAutoStart(FALSE) 
	{
		
		CString strtem=AppPath();
		//strTargetFile.Format("%s\\..\\IMLT\\%s.%s",strtem,DEFAULT_BIN_FILE_NAME,DEFAULT_BIN_FILE_EXTENSION);//dawei editted
		strTargetFile.Format(_T("%s\\IMLogs\\%s.%s"),strtem,DEFAULT_BIN_FILE_NAME,DEFAULT_BIN_FILE_EXTENSION);	// change the default log path to ./IMLogs
		//strTargetFile = AppPath()+_T("\\IMLogs\\")+DEFAULT_BIN_FILE_NAME+_T(".")+DEFAULT_BIN_FILE_EXTENSION;
	};
};

//SRecorderAPIParam
//-------------------
// this struct is sent from the caller to the Recorder manager:

struct SPTInterfaceParams 
{
	int iMaxBufferSize;						//the number of bytes which will transfer to the PT in each iteration 
	DCCallBackDataFn pCallBuckDataFunc;		//callback function pointer for transfering the recorded data to the PT
	DCCallBackEventFn pCallBuckEventFunc;	//callback function pointer for indication to the PT of end/error of/in the session 

	//constructor, initializes the structure with the default values:
	SPTInterfaceParams() : iMaxBufferSize (PT_DEFAULT_BUFFER_SIZE), pCallBuckDataFunc(NULL),pCallBuckEventFunc(NULL) {};
	
};

//The SRecorderParams structure is used in the record ugly (old architecture).
// It should be canceled when moving the regular recorder to the new architecture.
struct SRecorderParams	
{
	//all these events are used in the record ugly (old architecture).
	// These events should be removed when moving the regular recorder to the new architecture.

	CEvent stopRecordingRequestEvent;		// signals the engine that the requester asked to stop the Recording 
	CEvent stopRecordingAccomplishedEvent;	// signals the requester that the engine has exited the Recording as resultto a stop request. 
	CEvent stopSavingRequestEvent;			// signals the engine that the requester asked to stop the Recording, or that recording has terminated as result of exceeding max file size. 
	CEvent stopSavingAccomplishedEvent;		// signals the requester that the engine has stoped saving as result to a stop request. 
	//for external api's :
	CEvent initRecSucceessEvent;			// Used only for the api function - this event is set when the communication initialization succeeded, and the actual recording has started.
	CEvent initRecFailedEvent;			// Used only for the api function - this event is set when the communication initialization succeeded, and the actual recording has started.
	SRecorderAPIParams apiParamsStruct;
	
	// default constructor:
	SRecorderParams() : stopRecordingRequestEvent(FALSE,TRUE),stopRecordingAccomplishedEvent(FALSE,TRUE),stopSavingRequestEvent(FALSE,TRUE),
						stopSavingAccomplishedEvent(FALSE,TRUE),
						initRecSucceessEvent(FALSE,TRUE),initRecFailedEvent(FALSE,TRUE){};
};

#endif //__IPTK_RECORDER_STRUCTURES__
