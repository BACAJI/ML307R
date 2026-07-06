/*----------------------------------------------------------------------------*\
|* (C)Copyright 2008-2010 Marvell Technology Shanghai Ltd., Hefei Branch.     *|
|* All Rights Reserved.                                                       *|
\*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * ReturnCode.h: 
 *   Header file of ReturnCode.
 *----------------------------------------------------------------------------*/

#ifndef __ReturnCode_H_INCLUDED__
#define __ReturnCode_H_INCLUDED__

#include "Types.h"
// Common return code
// Bit31~30: indicate types: error, warning, information, status
// Bit29~16: indicate projects, sub-system or components
// Bit15~0: contain modules, error code.
typedef S32 ReturnCode;

#define RC_IS_ERROR(rc) ((rc>>30)==0x3)
#define RC_IS_WARN(rc) ((rc>>30)==0x2)
#define RC_IS_INFO(rc) ((rc>>30)==0x1)
#define RC_IS_STATUS(rc) ((rc>>30)==0x0)

// generic return codes
#define RC_OK				0
#define RC_ERR				0xFFFFFFFF
#define RC_ERR_UNKNOWN		0xC0000000
#define RC_WARN_UNKNOWN		0x80000000
#define RC_INFO_UNKNOWN		0x40000000

#define RC_ERR_SYS_ERR		0xE8000000	// return(RC_ERR_SYS_ERR+GetLastError());

#define RC_ERR_PARAM		0xC0000100
#define RC_ERR_FILE			0xC0000200
#define RC_ERR_MEM			0xC0000300
#define RC_ERR_NODEV		0xC0000400
#define RC_ERR_PROTCOL		0xC0000500

#define RC_ERR_PARAM_WRONG (RC_ERR_PARAM+1)
#define RC_ERR_PARAM_NULL_POINTER (RC_ERR_PARAM+2)
#define RC_ERR_PARAM_EXCEED_LIMIT (RC_ERR_PARAM+3)

// For application of ExtractDbVerId
#define RC_MODULE_EXTDBVER 0x0F00F100
#define RC_ERR_EXTDBVER (RC_ERR_UNKNOWN+RC_MODULE_EXTDBVER)
#define RC_ERR_EXTDBVER_DBFILE_OPEN_ERROR (RC_ERR_EXTDBVER+0x01)	// open database file error

// For DiagEncDec
#define RC_MODULE_DIAGENCDEC 0x0F00F200
#define RC_ERR_DIAGENCDEC (RC_ERR_UNKNOWN+RC_MODULE_DIAGENCDEC)
#define RC_ERR_DIAGENCDEC_PDU_EMPTY_ERROR (RC_ERR_DIAGENCDEC+0x01)
#define RC_ERR_DIAGENCDEC_DBFILE_OPEN_ERROR (RC_ERR_DIAGENCDEC+0x02)
#define RC_ERR_DIAGENCDEC_DATA_ERROR		(RC_ERR_DIAGENCDEC+0x03)	//error in convert string
#define RC_ERR_DIAGENCDEC_OPEN_FILE_ERROR		(RC_ERR_DIAGENCDEC+0x04)
#define RC_ERR_DIAGENCDEC_UE_COMMAND_NOT_FOUND	(RC_ERR_DIAGENCDEC+0x05)
#define RC_ERR_DIAGENCDEC_DIAG_FILTER_BUILD_ERROR (RC_ERR_DIAGENCDEC+0x06)


#define RC_ERR_TIMEOUT						(RC_MODULE_DIAGENCDEC + 0x10 )	
#define	RC_ERR_WAITFAILED					(RC_MODULE_DIAGENCDEC + 0x11 )	
			
#define	RC_WARN_DIAGENCDEC	(RC_WARN_UNKNOWN + RC_MODULE_DIAGENCDEC)



#endif // __ReturnCode_H_INCLUDED__
