#pragma once

#define ALL							L""
#define Max_UE_Device				10
#define DEFAULT_TIMEOUT				8000	// msec.
#define DIAG_SAP_INDEX				0
#define PDU_HEADER_LEN				12



#define APP_SIDE_MASK_FOR_SENDING		((BYTE)0x80)
#define APP_SIDE_MASK_FOR_RECEIVING		((WORD)0x8000)
#define UNKNOWN_ENUM_TYPE				"UnknownEnum"
//#define MAX_AT_SEND_COMMANDS_LENGTH		200
#define MAX_AT_SEND_COMMANDS_LENGTH		2000   //Modify by ZQQ to support MEP Command

#define NO_SUFFIX						0
#define SUFFIX_RETURN					1
#define SUFFIX_CTRLZ					2
#define SUFFIX_CRLN						3

#define AT_COMMANDS_RAW_DATA			0
#define AT_COMMANDS_OVER_DIAG			1
#define AT_COMMANDS_OVER_GKI			2

#define ALL_MESSAGES			ALL
#define APPLICATION_REPORT			0
#define APPLICATION_REPORT_ALIGNED	4

#define TO_ALL	 -1

#define ALL_OPCODES				((WORD)(-1))
#define AT_COMMANDS_OVER_STRING			3		//Richard added 2011-08-12

#define	INVALID_DATA				   -1
#define TEMP_DIR_PATH	AppPath()+_T("\\Temp\\")  //hlguo editted


enum eDirection {
	MessageIN = 0,
	MessageOUT = 1,
	MessageOUT_Device1 = 2,
	MessageOUT_Device2 = 4,
	MessageOUT_Device3 = 8,
	MessageOUT_Device4 = 16,
	MessageOUT_Device5 = 32,
	MessageOUT_ALL = 2046,

	MessageIN_Device1 = MessageOUT_Device1,
	MessageIN_Device2 = MessageOUT_Device2,
	MessageIN_Device3 = MessageOUT_Device3,
	MessageIN_Device4 = MessageOUT_Device4,
	MessageIN_Device5 = MessageOUT_Device5,
	MessageIN_ALL = MessageOUT_ALL
};

enum EStructIndices
{
#if MICL_BUILD
	kNoneSI	 = -1,
#else
	kNone	 = -1,
#endif
	kComNvm	 =  0,
	kComGki	 =  1,
	kAppNvm	 =	2,
	kAppGki	 =  3,
	kAsn1	 =  4,
	kStrAll	 =  5
};

#pragma region FlashExplorerData

#define DFM_VOL							_T("dfm/")
#define MFM_VOL							_T("mfm/")
#define	NO_VOL							_T("")
#define HOME_DIRECTORY_WIN				_T("/Windows/Marvell/NVM/")
#define HOME_DIRECTORY_LINUX			_T("/data/Linux/Marvell/NVM/")
#define HOME_DIRECTORY_RTOS				_T("/RTOS/Marvell/NVM/")
#define CMD_FSEEK						_T("FDI__Transport__Fseek")
#define CMD_IN_MSG_BODY_LIMIT			_T("Diag__Utils__InMsgBodyLimit")
#define CMD_OUT_MSG_BODY_LIMIT			_T("Diag__Utils__OutMsgBodyLimit")
#define CMD_FDV_AVIALABLE_SPACE			_T("FDI__Transport__GetFdiFdvAvailableSpace")
#define CMD_MAX_FILE_NAME_LENGTH		_T("FDI__Transport__GetMaxFileNameLen")
#define CMD_FLASH_SIZE				    _T("FDI__Transport__GetFdiFdvSize")

#define ERR_NONE						0
#define ERR_EOF							0x22
#define MAX_FILE_NAME_LENGTH			256
#define MAX_FILES_NAME_BUFFER			1024

#define FDI_VER_5	5
#define FDI_VER_6	6
#define FDI_VER_7	7
#define FDI_VER_71	71
#define FDI_VER_8	8

#define LEVEL_1	    1

#define MAX_AT_COMMANDS_LENGTH	2000 //  //Modify by ZQQ to support MEP Command

#pragma endregion FlashExplorerData