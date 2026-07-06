#pragma once

typedef enum 
{
	RUN_TEST_ENGINE,							
	ZIP_FILE_CREATED,						
	SEND_SCRIPT_FILE,						
	GET_SCRIPT_FILE,						
	SEND_TRACE_LOG,						
	RUN_TRACE,						
	GET_BATCH_ENDED_INFO,
	LOAD_BATCH,								
	STOP_TEST_ENGINE,						
	TE_BATCH_ENDED,						
	OPEN_VIEWER,						
	ADD_BATCH_PARAMETER,
	START_AUTOMATION_MODE,
	STOP_AUTOMATION_MODE,				
	L1_TE_WND_READY,
	ATS_WND_READY = L1_TE_WND_READY,
	START_RECORDING_IML,
	GET_BATCH_FAILURE_REASON,
	TE_BATCH_FAILURE_REASON	,
	SET_TARGET_DB,
	SET_TARGET_DB_FAILED,
	STOP_RECORDING_IML,
	CLOSE_VIEWER,
	SET_ON_SCRIPT_FAILURE,
	SET_DONT_FREE_DLLS,
	RUN_SELECTED_TEST_ENGINE,
	GET_BATCH_STATE,
	TE_BATCH_STATE,
	DEVICE_CONNECTION_STATUS,
	SET_DONT_CATCH_EXCEPTIONS,
	SET_BATCH_ITERATIONS,
	GET_BATCH_ITERATIONS,
	TE_BATCH_ITERATIONS,
	IMPORT_IML_DB,
	GET_CURRENT_SCRIPT_INDEX,
	TE_CURRENT_SCRIPT_INDEX,
	STOP_AND_WAIT_RECORDING_IML,
	SET_IML_RECORDER_SETTINGS,
	GET_CURRENT_SCRIPT_NAME,
	TE_CURRENT_SCRIPT_NAME,
	GET_SCRIPT_NAME_AT,
	TE_SCRIPT_NAME_AT,
	SET_RECORD_BY_TRACER,
	//DigRF Messages
	////////////////////////////////////////
	CONNECT_DIGRF_UTIL,
	SET_DIGRF_UTIL_CONFIGURATION_FILE,
	SET_DIGRF_UTIL_MPHYREG_FILE,
	START_DIGRF_UTIL,
	STOP_DIGRF_UTIL,
	STOP_DIGRF_UTIL_AND_WAIT,
	TE_DIGRF_UTIL_RX_TRIGGER_FOUND,
	TE_DIGRF_UTIL_RX_SAVE_DATA_FINISHED,
	TE_DIGRF_UTIL_RX_SAVE_DATA_FAILED,
	TE_DIGRF_UTIL_RX_FAILED_OPENING_FILE,
	TE_DIGRF_UTIL_TX_TRIGGER_FOUND,
	TE_DIGRF_UTIL_TX_SAVE_DATA_FINISHED,
	TE_DIGRF_UTIL_TX_SAVE_DATA_FAILED,
	TE_DIGRF_UTIL_TX_FAILED_OPENING_FILE,
	TE_DIGRF_UTIL_RUN_FINISHED,
	TE_DIGRF_UTIL_RUN_STOPPED,
	////////////////////////////////////////
	GET_ACAT_VERSION_STR,
	TE_ACAT_VERSION_STR,
	GET_ACAT_VERSION_NUM,
	TE_ACAT_VERSION_NUM,
	SET_TRACER_OUTPUT_DIRECTION,
	ABORT_RECORDING_IML,
	TE_RECORDING_IML_STOPED,
	GET_DUMP_FOLDER_PATH,
	TE_DUMP_FOLDER_PATH,
	GET_CURRENT_SCRIPT_ITERATION,
	TE_CURRENT_SCRIPT_ITERATION,
	SEND_L1_TE_WND_READY,
	//Add for India costumer's request
	CLEAR_LOG,
	TE_CLEAR_LOG_OK,
	SEND_ATCMD,
	TE_SEND_ATCMD_OK,
	TE_SEND_ATCMD_FAIL,
	QUERY_LTEERRC_CONNECTSTATE,
	TE_QUERY_LTEERRC_CONNECTSTATE_OK,
	TE_QUERY_LTEERRC_CONNECTSTATE_FAIL,
	MINIVIEW_SAVEASTEXT,
	TE_MINIVIEW_SAVEASTEXT_OK,
	TE_MINIVIEW_SAVEASTEXT_FAIL,
	ASN1VIEW_SAVEASTEXT,
	TE_ASN1VIEW_SAVEASTEXT_OK,
	TE_ASN1VIEW_SAVEASTEXT_FAIL,
	START_LOG,
	TE_START_LOG_OK,
	STOP_LOG,
	TE_STOP_LOG_OK,
	PAUSE_LOG,
	TE_PAUSE_LOG_OK,
	EXPORT_LOG,
	TE_EXPORT_LOG_OK,
	TE_EXPORT_LOG_FAIL,
	// Add for Mars to control Sulog
	//MARS -> Sulog
	MS_START_RECORD,
	MS_STOP_RECORD,
	MS_ABORT_RECORD,
	MS_RECORDED_FILE_SIZE,
	//Sulog -> MARS
	SM_WRONG_FLAGS,
	SM_RECORD_ENDED,
	SM_RECORDED_FILE_SIZE, // send the size of recorded bin file in bytes (decimal)
	SM_BIN_FILE_READY,
	// newly added
	ENABLE_DEVICE,
	TE_ENABLE_DEVICE_OK,
	TE_ENABLE_DEVICE_FAIL,
	DISABLE_DEVICE,
	TE_DISABLE_DEVICE_OK,
	TE_DISABLE_DEVICE_FAIL,
	PUSH_FILE,
	TE_PUSH_FILE_OK,
	TE_PUSH_FILE_FAIL,
	PULL_FILE,
	TE_PULL_FILE_OK,
	TE_PULL_FILE_FAIL,
	DEL_FILE,
	TE_DEL_FILE_OK,
	TE_DEL_FILE_FAIL,
	LIST_FILE,
	TE_LIST_FILE_OK,
	TE_LIST_FILE_FAIL,
	MONITOR_CAT123,
	TE_MONITOR_CAT123,
	TE_MONITOR_STARTED,
	STOP_MONITOR,
	TE_MONITOR_STOPPED,

}eATSMessagesID;

// #define RUN_TEST_ENGINE							1	//structure contains: batch file name.
// #define ZIP_FILE_CREATED						15
// #define SEND_SCRIPT_FILE						16
// #define GET_SCRIPT_FILE							17
// #define SEND_TRACE_LOG							18
// #define RUN_TRACE								19
// #define GET_BATCH_ENDED_INFO					20
// #define LOAD_BATCH								21
// #define STOP_TEST_ENGINE						22	
// #define TE_BATCH_ENDED							23
// #define OPEN_VIEWER								24
// #define ADD_BATCH_PARAMETER						25
// #define START_AUTOMATION_MODE					26
// #define STOP_AUTOMATION_MODE					27
// #define L1_TE_WND_READY							28
// #define ATS_WND_READY							L1_TE_WND_READY
// #define START_RECORDING_IML						29
// #define GET_BATCH_FAILURE_REASON				30
// #define TE_BATCH_FAILURE_REASON					31
// #define SET_TARGET_DB							32
// #define SET_TARGET_DB_FAILED					33
// #define STOP_RECORDING_IML						34
// #define CLOSE_VIEWER							35
// #define SET_ON_SCRIPT_FAILURE					36
// #define SET_DONT_FREE_DLLS						37
// #define RUN_SELECTED_TEST_ENGINE				39
// #define GET_BATCH_STATE							40
// #define TE_BATCH_STATE							41
// #define DEVICE_CONNECTION_STATUS				42 
// #define SET_DONT_CATCH_EXCEPTIONS				43 
// #define SET_BATCH_ITERATIONS					44
// #define GET_BATCH_ITERATIONS					45
// #define TE_BATCH_ITERATIONS						46
// #define IMPORT_IML_DB							47
// #define GET_CURRENT_SCRIPT_INDEX				48
// #define TE_CURRENT_SCRIPT_INDEX					49
// #define STOP_AND_WAIT_RECORDING_IML				50
// #define SET_IML_RECORDER_SETTINGS				51
// #define GET_CURRENT_SCRIPT_NAME					52
// #define TE_CURRENT_SCRIPT_NAME					53
// #define GET_SCRIPT_NAME_AT						54
// #define TE_SCRIPT_NAME_AT						55
// #define SET_RECORD_BY_TRACER					56
// //DigRF Messages
// //////////////////////////////////////////////////
// #define CONNECT_DIGRF_UTIL						57
// #define SET_DIGRF_UTIL_CONFIGURATION_FILE		58
// #define SET_DIGRF_UTIL_MPHYREG_FILE				59
// #define START_DIGRF_UTIL						60
// #define STOP_DIGRF_UTIL							61
// #define STOP_DIGRF_UTIL_AND_WAIT				62
// #define TE_DIGRF_UTIL_RX_TRIGGER_FOUND			63
// #define TE_DIGRF_UTIL_RX_SAVE_DATA_FINISHED		64
// #define TE_DIGRF_UTIL_RX_SAVE_DATA_FAILED		65
// #define TE_DIGRF_UTIL_RX_FAILED_OPENING_FILE	66
// #define TE_DIGRF_UTIL_TX_TRIGGER_FOUND			67
// #define TE_DIGRF_UTIL_TX_SAVE_DATA_FINISHED		68
// #define TE_DIGRF_UTIL_TX_SAVE_DATA_FAILED		69
// #define TE_DIGRF_UTIL_TX_FAILED_OPENING_FILE	70
// #define TE_DIGRF_UTIL_RUN_FINISHED				71
// #define TE_DIGRF_UTIL_RUN_STOPPED				72
// //////////////////////////////////////////////////
// #define GET_ACAT_VERSION_STR					73
// #define TE_ACAT_VERSION_STR						74
// #define GET_ACAT_VERSION_NUM					75
// #define TE_ACAT_VERSION_NUM						76
// #define SET_TRACER_OUTPUT_DIRECTION				77 //DDR_Streaming = 0,BlackStone = 1,DDR_SD = 2,DDR = 3
// #define ABORT_RECORDING_IML						78
// #define TE_RECORDING_IML_STOPED					79
// #define GET_DUMP_FOLDER_PATH					80
// #define TE_DUMP_FOLDER_PATH						81
// #define GET_CURRENT_SCRIPT_ITERATION			82
// #define TE_CURRENT_SCRIPT_ITERATION				83
// #define SEND_L1_TE_WND_READY					84



typedef struct sTEBatchParams_tag
{
	WCHAR strParamName[256];
	WCHAR strParamValue[256];
}sTEBatchParams;


typedef struct sIMLParams_tag
{
	WCHAR strTargetFile[256];
	DWORD dwFileSizeInMB;
	int iRecordingMode /*= RECORD_STRESS_CYCLIC*/;
	WCHAR strErrMsg [500]/*= CString("")*/;
	DWORD dwTriggerOpcode /*= 0x0000*/;
	int iTriggerPosition /*= 0 */;

	sIMLParams_tag()
	{
		iRecordingMode = 3;//RECORD_STRESS_CYCLIC;
		strErrMsg[0] = '\0';
		dwTriggerOpcode = 0x0000;
		iTriggerPosition = 0;
	};

}sIMLParams;

typedef struct sTargetDB_tag
{
	WCHAR strTargetCommandsDB[MAX_PATH];
	WCHAR strTargetNVMDB[MAX_PATH];
	WCHAR strTargetAPPCommandsDB[MAX_PATH];
	WCHAR strTargetAPPNVMDB[MAX_PATH];
	WCHAR strTargetDSPDB[MAX_PATH];
	WCHAR strTargetMSACommandsDB[MAX_PATH];
	WCHAR strTargetMSANVMDB[MAX_PATH];
	WCHAR strTargetRFBinCommandsDB[MAX_PATH];
	WCHAR strTargetRFBinNVMDB[MAX_PATH];

	WCHAR strTargetCOMTXTDB[MAX_PATH];
	WCHAR strTargetAPPTXTDB[MAX_PATH];
	WCHAR strTargetMSATXTDB[MAX_PATH];
	WCHAR strTargetRFBinTXTDB[MAX_PATH];

	int nDevice;
	sTargetDB_tag()
	{
		strTargetCommandsDB[0] = '\0';
		strTargetNVMDB[0] = '\0';
		strTargetAPPCommandsDB[0] = '\0';
		strTargetAPPNVMDB[0] = '\0';
		strTargetDSPDB[0] = '\0';
		strTargetMSACommandsDB[0] = '\0';
		strTargetMSANVMDB[0] = '\0';
		strTargetRFBinCommandsDB[0] = '\0';
		strTargetRFBinNVMDB[0] = '\0';

		strTargetCOMTXTDB[0] = '\0';
		strTargetAPPTXTDB[0] = '\0';
		strTargetMSATXTDB[0] = '\0'; 
		strTargetRFBinTXTDB[0] = '\0';

		nDevice = 0;
	};

}sTargetDB;

#define DEFAULT_PARAM 0xFF
#define DEFAULT_STR ""

/************************************************************************/
/* The values must be different from:
/*
/* int/BOOL/DWORD != 0xFF
/* String != "" (empty string)	
/* 
/* Any parameter that will be different from the default will be set
/************************************************************************/

struct ATS_IMLRecorderParams
{
	WCHAR strMsgTrigger[MAX_PATH];
	WCHAR strMsgTriggerDefinition[MAX_PATH];

	//Must be set together 
	//////////////////////////////////////////////////////////////////////////
	DWORD	dwMsgTriggerOpcode;
	WCHAR strMsgTriggerOpcode[MAX_PATH];
	//////////////////////////////////////////////////////////////////////////

	//Must be set together 
	//////////////////////////////////////////////////////////////////////////
	int		iTriggerPosition;			
	WCHAR	strTriggerPosition[MAX_PATH];
	//////////////////////////////////////////////////////////////////////////

	DWORD   dwStopRecordingTimeout;		// (> 4000) When requesting to stop - the time waited for event before killing the thread
	DWORD	dwMaxNumBytesToRecord;		// (< 4096) target file maximum size in bytes 
	UINT	uiBufferSize;				// The size of the buffer used for receiving the data from communication (in bytes)
	//  0   - "512 Bytes"
	//	1   - "1	 KB"
	//	2   - "2   KB"
	//	16  - "16  KB"
	//	32  - "32  KB"
	//	64  - "64  KB"
	//	128 - "128 KB"

	BYTE	byteVendorRequestSend;		// used for communicating with acquisition card
	BYTE	byteVendorRequestStop;		// used for communicating with acquisition card
	BYTE	byteVendorRequestVersion;	// used for communicating with acquisition card
	int		iConnectionInterface;
	int		iRecordingMode;				//  Valid Params:
	//	RECORD_NON_CYCLIC						0
	//	RECORD_CYCLIC							1
	//	RECORD_STRESS_NON_CYCLIC				2
	//	RECORD_STRESS_CYCLIC					3
	//	RECORD_TRIGGER							4
	//	PT_RECORDER								5

	int		iWinMsgSendingFreq;			// The frequency of updating the screen with the recording progress. affects performance.
	//	-1 - "Only at end of recording"
	//	 2 - "Every Second Buffer (for low bit rate)"
	//	16 - "Every 16 Buffers (recommended)"
	//	80 - "Every 80 Buffers (for high bit rate)"
	WCHAR strTargetFile[MAX_PATH];
	WCHAR strTextEditor[MAX_PATH]; 

	BOOL	bAutoIncrementFileName;		//BOOL 1 - TRUE 0 - FALSE

	//constructor, initializes the structure with the default values:
	ATS_IMLRecorderParams() : 
	dwMsgTriggerOpcode(DEFAULT_PARAM),	
	iTriggerPosition(DEFAULT_PARAM),
	uiBufferSize(DEFAULT_PARAM), 
	byteVendorRequestSend(DEFAULT_PARAM),
	byteVendorRequestStop(DEFAULT_PARAM),
	byteVendorRequestVersion(DEFAULT_PARAM), 
	dwStopRecordingTimeout(DEFAULT_PARAM),
	dwMaxNumBytesToRecord(DEFAULT_PARAM),
	iConnectionInterface (DEFAULT_PARAM),
	iRecordingMode(DEFAULT_PARAM),
	iWinMsgSendingFreq(DEFAULT_PARAM),
	bAutoIncrementFileName(DEFAULT_PARAM)
	{
		strMsgTriggerDefinition[0] = '\0';
		strMsgTriggerOpcode[0] = '\0';
		strMsgTrigger[0] = '\0'; 
		strTriggerPosition[0] = '\0';
		strTargetFile[0] = '\0';
		strTextEditor[0] = '\0';
	};
};