/*----------------------------------------------------------------------------*\
|* (C)Copyright 2008-2010 Marvell Technology Shanghai Ltd., Hefei Branch.     *|
|* All Rights Reserved.                                                       *|
\*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * DiagCommDef.h: 
 *   Header file of DiagCommDef.
 *----------------------------------------------------------------------------*/


#ifndef _DIAGCOMMDEF_H_
#define _DIAGCOMMDEF_H_
// 
//#include "StdAfx.h" 
// #if !MICL_BUILD
//  typedef enum {
//  	VERSION_ID			 = 0,
//  	TRANSFER_DATABASE	/*=1*/,
//  	GET_CLOCK_RATE		/*=2*/,
//  	SET_FILTER_LEVEL	/*=3*/,
//  	ICAT_READY_NOTIFY	/*=4*/,
//  	GET_FILTER_LEVEL	/*=5*/,
//  	ENTER_BOOTLOADER_MODE /*=6*/,
//  	EXTERNAL_CONNECTION_CEASED /*7 user can not access this service */,
//  	EXTERNAL_CONNECTION_QUERY /*8 user can not access this service */,
//  	SEND_FULL_FRAME_NUM /*=9*/
//  
//  } InternalService;
// #endif

// typedef enum {
// 	eAlignMinimum = 1,
// 	eAlign4Bytes = 4
// } EStructureAlignment;
// 
// 
// typedef enum {
// 	eEnumSizeAsNeeded = 0,
// 	eEnumSize2Bytes, 
// 	eEnumSize4Bytes
// } EEnumSize;
// 
// 
// typedef struct{
// 	S16 length;
// 	S16 EUsbPID;
// 	U16 DiagSAP;
// 	U16 DiagCounter;
// }PDUHeader;
// 
// #define APP_SIDE_MASK_FOR_SENDING		((BYTE)0x80)
// #define APP_SIDE_MASK_FOR_RECEIVING		((WORD)0x8000)
// 
// #define APPLICATION_REPORT			0
// #define RETURN_SERVICE				1
// #define RSVP_SERVICE				2
// //#define APPLICATION_REPORT_FIXUP	3
// #define APPLICATION_REPORT_ALIGNED	4
// #define DIAG_MI_LOGGED_SIGNAL			5
// #define DIAG_MI_COMMAND					5
// #define DIAG_MI_SIGNAL					6
// #define DIAG_MI_SPECIAL_LOGGED_SIGNAL	7
// #define DIAG_SAP_IML_LOG	9
// #define DIAG_ERROR_REPORT				0x7f
// 
// #define MODULE_ID_LENGTH		sizeof(U16)
// #define MESSAGE_ID_LENGTH	sizeof(U16)
// #define UE_TIMESTAMP_LENGTH	sizeof(U32)	//unused
// #define SOURCE_ID_LENGTH	sizeof(U32) //unused
// #define GKI_SIGNAL_LENGTH	sizeof(U16)
// #define GKI_FRAME_NUMBER_LENGTH sizeof(U32)
// #define GKI_FRAME_TICKS_LENGTH sizeof(U32)
// 
// #define MAX_ALIGN_STRUCT	4
// #define ALIGN(counter, align) ((counter) += ((UINT)(counter) % (align)) ? ((align)-(((UINT)(counter)) % (align))) : 0)

#define MvlDiagEncDecExports

#ifdef	MvlDiagEncDecExports
#define MVLDLLAPI	__declspec(dllexport)  
#define EXPIMP_TEMPLATE
#else
#define MVLDLLAPI	
#endif

#define UNKNOWN_ENUM_TYPE	"UnknownEnum"

struct EnumValsRecord 
{
	long	m_FileId; // Module-ID.
	long	m_EnumVal; // Message-ID.
	BYTE	m_EnumType; // 0 for Report, 1 for Command.
	CString	m_ReportLine;
	CString m_Cat1;
	CString m_Cat2;
	CString m_Cat3;
	CString m_DefaultData;
	BOOL	m_bIsExtCommand;
	CString	m_DefaultExtOpcode;
	BOOL	m_bIsExtReport;
	bool	m_bIsAlign4;
	bool    m_bIsPLP;


	EnumValsRecord() 
	{ 
		m_FileId = 0;
		m_EnumVal = 0;
		m_EnumType = 0;
		m_ReportLine = _T("");
		m_Cat1 = _T("");
		m_Cat2 = _T("");
		m_Cat3 = _T("");
		m_DefaultData = _T("");
		m_bIsExtCommand = FALSE;
		m_DefaultExtOpcode = _T("");
		m_bIsExtReport	= FALSE;
		m_bIsAlign4 = false;
		m_bIsPLP	= false;
	}

	EnumValsRecord(const EnumValsRecord &rec) 
	{
		m_FileId = rec.m_FileId;
		m_EnumVal = rec.m_EnumVal;
		m_EnumType = rec.m_EnumType;
		m_ReportLine = rec.m_ReportLine;
		m_Cat1 = rec.m_Cat1;
		m_Cat2 = rec.m_Cat2;
		m_Cat3 = rec.m_Cat3;
		m_DefaultData = rec.m_DefaultData;
		m_bIsExtCommand = rec.m_bIsExtCommand;
		m_DefaultExtOpcode = m_DefaultExtOpcode;
		m_bIsExtReport	= FALSE;
		m_bIsAlign4	= (m_ReportLine.Find(_T("diagPrintf_4")) > -1);
		m_bIsPLP	= rec.m_bIsPLP;
	}

	EnumValsRecord& operator= (const EnumValsRecord &rec)
	{
		m_FileId = rec.m_FileId;
		m_EnumVal = rec.m_EnumVal;
		m_EnumType = rec.m_EnumType;
		m_ReportLine = rec.m_ReportLine;
		m_Cat1 = rec.m_Cat1;
		m_Cat2 = rec.m_Cat2;
		m_Cat3 = rec.m_Cat3;
		m_DefaultData = rec.m_DefaultData;
		m_bIsExtCommand = rec.m_bIsExtCommand;
		m_DefaultExtOpcode = m_DefaultExtOpcode;
		m_bIsExtReport	= FALSE;
		m_bIsAlign4	= (m_ReportLine.Find(_T("diagPrintf_4")) > -1);
		m_bIsPLP	= rec.m_bIsPLP;
		return *this;
	}
};


struct EnumValPair{
	CString strValName;
	long	lValValue;

	EnumValPair(const CString &valName = _T(""), long lVal = 0) 
	{ 
		strValName = valName; 
		lValValue = lVal;
	}

	EnumValPair(const EnumValPair &val) 
	{
		strValName = val.strValName;
		lValValue = val.lValValue;
	}

	EnumValPair& operator= (const EnumValPair &val)
	{
		strValName = val.strValName;
		lValValue = val.lValValue;
		return *this;
	}
};

#endif

