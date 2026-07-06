#pragma once


#define MAX_DEVICE_NUM    5

// 
// enum eTargetType
// {
//   UE_None      = -1,
//   UE_Comm_Side = 0,
//   UE_App_Side
// };

enum ESockProtocol { 
   eTCP = 1, 
   eUDP = 2
};

enum ECommType {
   eComTypeNone = 0, 
   eUSB = 1, 
   eCOM, 
   eSOCKET, 
   eSocketTcpClient, 
   eSocketTcpServer, 
   eSocketUdp
};

typedef enum {
   UE_OK							= 0,
   UE_FILE_EXIST					= 0,
   UE_TIMEOUT_ERR				 /*	= 1 */,
   UE_PARAM_ERR				 /*	= 2 */,
   UE_COMMAND_NOT_FOUND_ERR	 /*	= 3 */,
   UE_REPORT_NOT_FOUND_ERR		 /*	= 4 */,
   UE_OPEN_PC_FILE_ERR			 /* = 5 */,
   UE_OPEN_TARGET_FILE_ERR		 /* = 6 */,
   UE_CLOSE_TARGET_FILE_ERR	 /* = 7 */,
   UE_FILES_DONT_MATCH_ERR		 /* = 8 */,
   UE_WRITE_TO_TARGET_ERR		 /* = 9 */,
   UE_READ_FROM_TARGET_ERR	     /* = 10*/,
   UE_STATUS_FILE_ERR			 /* = 11*/,
   UE_RENAME_FILE_ERR			 /* = 12*/,
   UE_REMOVE_FLASH_FILE_ERR	 /* = 13*/,
   UE_FIND_FILE_ERROR			 /* = 14*/,
   UE_FORMAT_FLASH_ERR			 /* = 15*/,
   UE_CHANGE_MODE_ERR			 /* = 16*/,
   UE_FDI_DRIVER_IN_USE_ERR	 /* = 17*/,
   UE_NOT_ENOUGH_MEMORY_SPACE	 /* = 18*/,
   UE_EXCEED_MAX_FILE_NAME_LEN	 /* = 19*/,
   UE_INVALID_TARGET_FILE_NAME	 /* = 20*/,
   UE_OPEN_DIR_ERR				 /* = 21*/,
   UE_READ_DIR_ERR				 /* = 22*/,
   UE_CLOSE_DIR_ERR			 /* = 23*/,
   UE_FILE_SEEK_ERR			 /* = 24*/,
   UE_FILE_STAT_ERR			 /* = 25*/,
   UE_MAKE_DIR_ERR				 /* = 26*/,
   UE_DELETE_DIR_ERR			 /* = 27*/,
   UE_USER_BREAK				 /* = 28*/,
   UE_COMMAND_AND_CONTROL_INSTANCE_ERR /* = 29*/,
   UE_DEVICE_NOT_CONNECT /* = 30*/,
   UE_TARGETTYPE_MISMATCH_ERR /* = 31*/,
   UE_CREATE_PC_FILE_ERR /* = 32*/,
   UE_TARGETPROTOCOL_MISMATCH_ERR /* = 33*/,
   UE_RENAME_TO_EXIST_ERR		 /* = 34*/,
   UE_DB_VERSION_NOT_MATCH		 /* = 35*/,
   UE_COMMAND_FILE_NOT_START_ERR /* = 36*/,
   UE_WRITE_FILE_DISK_FULL		/* = 37*/,
   UE_FILE_NOT_EXIST			/* =38 */
} UE_errCode_t;


enum DiagSAP
{
  INTERNAL_SERVICE		     =0,
  COMMAND_SERVER			   /*=1*/,        
  RSVP_COMMAND_SERVER		/*=2*/,
  FIXUPS_COMMAND_SERVER	   /*=3*/,
};



#define MAX_PDU_LEN						0xFFFC
#define PDU_HEADER_LEN                 12
#define DIAG_SAP_INDEX			         0
#define APP_SIDE_MASK_FOR_SENDING		((BYTE)0x80)
#define APP_SIDE_MASK_FOR_RECEIVING		((WORD)0x8000)

#define APPLICATION_REPORT			      0
#define RETURN_SERVICE				      1
#define RSVP_SERVICE				         2
#define APPLICATION_REPORT_ALIGNED	   4
#define DIAG_MI_LOGGED_SIGNAL			   5
#define DIAG_MI_COMMAND					   5
#define DIAG_MI_SIGNAL					   6
#define DIAG_MI_SPECIAL_LOGGED_SIGNAL	7
#define DIAG_SAP_IML_LOG	            9
#define DIAG_ERROR_REPORT				  0x7f

#define INVALID_SIGID                 0xffffffff


#define DIAG_HEADER_FOR_RECEIVING_MI_SIGNALS	8	// only Diag-SAP + Time-Stamp
#define DIAG_HEADER_FOR_RECEIVING_MI_SIGANLS	DIAG_HEADER_FOR_RECEIVING_MI_SIGNALS	// backwards compatibility

/************************ EMMI Protocol Specific ************************/
#define SIGNAL_MI			   211
#define LOGGED_SIGNAL_MI	212
#define COMMAND_MI			213

#define EMMI_HEADER_LEN		1

#define SIGNAL_BODY_OFFSET			   (EMMI_HEADER_LEN + MI_SIGNAL_HEADER_LENGTH)
#define LOGGED_SIGNAL_BODY_OFFSET	(EMMI_HEADER_LEN + MI_LOGGED_SIGNAL_HEADER_LENGTH)
#define COMMAND_BODY_OFFSET			(EMMI_HEADER_LEN + MI_COMMAND_HEADER_LENGTH)
/************************************************************************/



/********************* Compiler Options **************************************/

typedef enum {
  eAlignMinimum = 1,
  eAlign4Bytes  = 4,
  eAlign8Bytes  = 8

} EStructureAlignment;


typedef enum {
  eEnumSizeAsNeeded = 0,
  eEnumSize2Bytes, 
  eEnumSize4Bytes
} EEnumSize;


#define MAX_ALIGN_STRUCT	4
#define ALIGN(counter, align) ((counter) += ((UINT)(counter) % (align)) ? ((align)-(((UINT)(counter)) % (align))) : 0)

#define UNKNOWN_ENUM_TYPE	"UnknownEnum"

/*****************************************************************************/

typedef enum {kComm, kApp, kMaxChipSetNum}EChipSet;


enum EInternalService{
  VERSION_ID			    = 0,
  TRANSFER_DATABASE	/*=1*/,
  GET_CLOCK_RATE		/*=2*/,
  SET_FILTER_LEVEL	/*=3*/,
  ICAT_READY_NOTIFY	/*=4*/,
  GET_FILTER_LEVEL	/*=5*/,
  ENTER_BOOTLOADER_MODE /*=6*/,
  EXTERNAL_CONNECTION_CEASED /*7 user can not access this service */,
  EXTERNAL_CONNECTION_QUERY /*8 user can not access this service */,
  SEND_FULL_FRAME_NUM /*=9*/,
  ATOMIC_READY_NOTIFY_AND_DB_VER /*=10*/,
  UE_CP_INFO /*=11*/,
  ACAT_DISCONNECT_NOTIFY/*=12*/,
  ACAT_KEEP_ALIVE/*=13*/,
  GET_AP_LOG=0x40,
  CP_LOG_START=0x41,
  CP_LOG_STOP=0x42,
  MAX_INTERNAL_SERVICE_ID
};

#define INTERNAL_SENDANDWAIT_TIMEOUT  5000


enum EFilterType
{
   eDIAGFilter        = 1,
   eDIAGFilterAppSide = 2,
   eGKIFilter         = 3,
   eDSPFilter         = 4,
   eAllFilter         = 5,
};

// Define for notify to catstudio2.0
typedef void (*PFN_MESSAGE_FUNC)(LPVOID lpObj, int iDevice, int protocol, BYTE* sdu, int sduLen);
typedef void (*PFN_DEVICESTATUS_FUNC)(LPVOID lpObj, int iDevice, int newStatus, int protocol);
typedef long (*PFN_ENABLEDEV)(int);
typedef long (*PFN_DISABLEDEV)(int);
class CCommSettings;
typedef long (*PFN_SETCOMMSETTINGS)(CCommSettings);
typedef long (*PFN_GETCOMMSETTINGS)(int, CCommSettings&);
typedef long (*PFN_UPDATACOMMSETTINGS)(CCommSettings&);
typedef void (*PFN_FACTSETTING_FUNC)(LPVOID lpObj, CCommSettings FactSettings); // Only for DevComm.dll UI - xxliu 2012-07-12

typedef void (*PFN_INIT_LOGGING)(LPVOID);
typedef PFN_INIT_LOGGING LPFN_INIT_LOGGING;


typedef void (*PFN_INIT_CONFIGINSTANCE)(LPVOID);
typedef PFN_INIT_CONFIGINSTANCE LPFN_INIT_CONFIGINSTANCE;

#ifndef DEL_PTR
#define DEL_PTR(ptr) {\
   if (NULL != (ptr))\
{\
   delete (ptr);\
   (ptr)=NULL;\
}\
}
#endif // DEL_PTR

#ifndef DEL_ARRAY_PTR
#define DEL_ARRAY_PTR(ptr) {\
   if (NULL != (ptr))\
{\
   delete [](ptr);\
   (ptr)=NULL;\
}\
}
#endif // DEL_ARRAY_PTR


enum EDatabaseFileType
{
   eTXT = 0,
   eMDB = 1
};

typedef struct tagMdbTableItem
{
	CString strTableName;
	DWORD	dwBegin;
	DWORD	dwEnd;
}
sMdbTableItem;