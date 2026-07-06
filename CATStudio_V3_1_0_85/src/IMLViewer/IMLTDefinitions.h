/*--------------------------------------------------------------------------------------------------------------------

 (C) Copyright 2006,2007 Marvell Semiconductor Israel Ltd. All Rights Reserved  

-------------------------------------------------------------------------------------------------------------------*/

#ifndef     __IMLT_DEFINITIONS__
#define     __IMLT_DEFINITIONS__

#include    "ApplicationINI.h"
#define         MODULE_NAME                     _T("IMLViewer.dll")
// Version 
//-----------
// These strings are written in bin file header:

#define         DEFAULT_IPTK_BIN_HEADER             _T("Source : IPTK Ac")
#define         SOFTWARE_VERSION_STRING             _T("IMLT SW VER 1.95")  //  4 last bytes are specific to IMLT SW version
#define         ACQUISITION_CARD_VERSION_STRING     _T("Ac Card VER ")      //  Add 4 BYTES for IML acquisition card version
#define         UNKNOWN_ACQUISITION_CARD_VERSION    _T("????")              //   this is added to ACQUISITION_CARD_VERSION_STRING if the version is unavaliable.    
#define         BIN_HEADER_SIZE                     48          
#define         PRE_19_BIN_HEADER_SIZE              16                  //   for versions older that ICAT 19        

#define         IML_FOOTER_SIZE                     8                   //for acq card verions 5.3  

// Ini File Definitions:
//-----------------------
#define         INI_FILE_NAME                   _T("IMLogger.ini")
#define         IMLT_DB_FILE_NAME               _T("IMLT.mdb")

#define         LOAD_DEFAULT_PARAMS             0
#define         LOAD_LAST_ENTERED_PARAMS        1
#define         SAVE_TO_DEFAULT_PARAMS          2
#define         SAVE_TO_LAST_ENTERED_PARAMS     3


// Dialog Definitions:
//------------------------

//#define           DEFAULT_TEXT_EDITOR             "C:\\Program Files\\Microsoft Visual Studio\\Common\\MSDev98\\Bin\\msdev.exe" dawei editted
#define         DEFAULT_TEXT_EDITOR             AppPath()   //dawei editted
#define         DEFAULT_BIN_FILE_EXTENSION      _T("bin")
#define         DEFAULT_BIN_FILE_NAME           _T("IML_Binary_Data")

#define         NUM_OF_IMLT_DLG_TABS            2

// The Color of the Status:
//--------------------------

#define         RED_STATUS          RGB(200,0,0)
#define         GREEN_STATUS        RGB(0,80,0)
#define         BLUE_STATUS         RGB(0,0,192)    

// Other Common Definitions:
//----------------------------

#define         UNSELECTED_TAB_INDEX                -1
#define         RECORDER_DLG_TAB_INDEX              0
#define         CONVERTER_DLG_TAB_INDEX             1

// Interface for the Performance Tool for start/stop recording data (XScale/Arm) from the IML acquisition card
//-------------------------------------------------------------------------------------------------------------

#define         ON_LINE_CONNECTION          0
#define         OFF_LINE_CONNECTION         1

#define         END_OF_SESSION_EVENT        0
#define         ERROR_EVENT                 1

#define         PT_DEFAULT_BUFFER_SIZE          1   //  the amount of data which will be transfered to the Performance Tool in each calling to the callbuck function

typedef void (*DCCallBackDataFn)(BYTE *pData, UINT iDataSize);
typedef void (*DCCallBackEventFn)(UINT uiEventId, CString &strErrMsg);

#define         DEFAULT_PT_FILE_EXTENSION       _T("bin")
#define         DEFAULT_PT_FILE_NAME            _T("PT_Binary_Data")


//IML Acquisition card testing process:
#define         WM_UPDATE_TESTING_PROGRESS          WM_USER + 100
#define         WM_UPDATE_TESTING_STATUS            WM_USER + 101
#define         WM_END_TESTING                      WM_USER + 102

//#define           TEXT_EDITOR_1   GetEXEPath("msdev.exe")  //"C:\\Program Files\\Microsoft Visual Studio\\Common\\MSDev98\\Bin\\msdev.exe"//dawei editted
#define         TEXT_EDITOR_1   AppPath()  //"C:\\Program Files\\Microsoft Visual Studio\\Common\\MSDev98\\Bin\\msdev.exe"//dawei editted
#define         TEXT_EDITOR_2   _T("C:\\Windows\\System32\\notepad.exe")
#define         REPORT_FILE     AppPath()+_T("\\IMLSystemTestingProcessReportFile.txt")//dawei editted

#define         SINGLE_HEADER_BYTE                  0x13    
#define         LONG_MSG_HEADER_BYTE                0x12
#define         LONG_MSG_BODY_BYTE                  0x11
#define         LONG_MSG_TAIL_BYTE                  0x10
#define         ZERO_PADDING_HEADER_BYTE            0x00
#define         TIMESTAMP_RESTART_BYTE              0x17

#define         IML_SCENARIO_STAGE_0                0   //Long message
#define         IML_SCENARIO_STAGE_1                1   //Body
#define         IML_SCENARIO_STAGE_2                2   //Body
#define         IML_SCENARIO_STAGE_3                3   //Body
#define         IML_SCENARIO_STAGE_4                4   //Tail
#define         IML_SCENARIO_STAGE_5                5   //Single


#define         MSG_UNCOMPLETED                     0
#define         MSG_INVALID                         -1
#define         MSG_VALID                           1

#define     CYCLIC_INCREMENT_STATUS_INDEX(iStatusMsgArrayIndex)  ( (iStatusMsgArrayIndex) = ( (iStatusMsgArrayIndex) < 7) ? (iStatusMsgArrayIndex) + 1 : 0) 


// Common Macros:
//----------------

//  CALCULATE_DWORD_PERCENTAGE - calculates the percentage (returns an integer between 1 to 100), and accepts 2 DWORDS.
//  the 2 parameters dwNumerator,dwDenomintor are both divided in 2 before calculation, in order to avoid 
//  negative interpetations of them during casting to float (in case the MS bit is 1):
    
#define         CALCULATE_DWORD_PERCENTAGE(dwNumerator,dwDenomintor)    (long)( ( (float)((dwNumerator)/2) / (float)((dwDenomintor)/2) ) * 100 )    

#endif //__IMLT_DEFINITIONS__
