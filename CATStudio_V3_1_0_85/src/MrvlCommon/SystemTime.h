/*--------------------------------------------------------------------------------------------------------------------

 (C) Copyright 2006,2007 Marvell Semiconductor Israel Ltd. All Rights Reserved  

-------------------------------------------------------------------------------------------------------------------*/


// SystemTime.h: interface for the CSystemTime class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSTEMTIME_H__2B5A7CFD_2214_4B52_AA37_501919D41B68__INCLUDED_)
#define AFX_SYSTEMTIME_H__2B5A7CFD_2214_4B52_AA37_501919D41B68__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef _CATCORE_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT 
#endif
class DLL_EXPORT CSystemTime : public SYSTEMTIME
{
public:
	void Serialize(CArchive &ar);
	void Serialize(void* pv);
	CSystemTime();
	virtual ~CSystemTime();
	//void operator = (CSystemTime &sysTime);

};

#endif // !defined(AFX_SYSTEMTIME_H__2B5A7CFD_2214_4B52_AA37_501919D41B68__INCLUDED_)
