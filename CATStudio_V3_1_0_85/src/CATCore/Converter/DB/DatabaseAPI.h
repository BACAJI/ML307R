// DatabaseAPI.h: interface for the CDatabaseAPI class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATABASEAPI_H__A93FF1B1_3914_4097_8EA7_6CF850C833BC__INCLUDED_)
#define AFX_DATABASEAPI_H__A93FF1B1_3914_4097_8EA7_6CF850C833BC__INCLUDED_
/*--------------------------------------------------------------------------------------------------------------------

 (C) Copyright 2006,2007 Marvell Semiconductor Israel Ltd. All Rights Reserved  

-------------------------------------------------------------------------------------------------------------------*/

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class __declspec(dllexport) CDatabaseAPI  
{
public:
#ifdef _UNICODE
	static BOOL GetEnumValue(const CString &strEnumType, const CString &strEnum, long &nEnumValue,const CString strDBFile);// Add strDBFile to transfer CP DB path & name to support multi - CP processor.
	static BOOL GetEnumValue(const CString &strEnumType, const CString &strEnum, long &nEnumValue, bool bAppSide,const CString strDBFile);// Add strDBFile to transfer CP DB path & name to support multi - CP processor.
#endif // _UNICODE

	static BOOL GetEnumValue(const CStringA &strEnumType, const CStringA &strEnum, long &nEnumValue,const CStringA strDBFile);// Add strDBFile to transfer CP DB path & name to support multi - CP processor.
	static BOOL GetEnumValue(const CStringA &strEnumType, const CStringA &strEnum, long &nEnumValue, bool bAppSide,const CStringA strDBFile);// Add strDBFile to transfer CP DB path & name to support multi - CP processor.

};

#endif // !defined(AFX_DATABASEAPI_H__A93FF1B1_3914_4097_8EA7_6CF850C833BC__INCLUDED_)
