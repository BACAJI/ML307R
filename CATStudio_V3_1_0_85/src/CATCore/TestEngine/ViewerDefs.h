/*----------------------------------------------------------------------------*\
|* (C)Copyright 2007-2009 Marvell Technology Shanghai Ltd., Hefei Branch.     *|
|* All Rights Reserved.							      *|
\*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * ViewerDefs.h: 
 *   Header file of ViewerDefs.
 *   Common definitions of Viewer module.
 *   It is used to clean header files depenency.
 *   DO NOT include other header files in it.
 *   It MUST ONLY depend on StdAfx.h.
 *----------------------------------------------------------------------------*/

#ifndef __ViewerDefs_H_INCLUDED__
#define __ViewerDefs_H_INCLUDED__


// FilesList is used by "ExportLogFileDlg.h" and "Viewer1.h".
typedef struct
{
	BOOL	bChecked;
	CString	strFileName;
	CString strOutputFile;
} FilesList;


#endif // __ViewerDefs_H_INCLUDED__
