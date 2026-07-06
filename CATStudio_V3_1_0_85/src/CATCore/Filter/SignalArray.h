// SignalArray.h: interface for the CSignalArray class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIGNALARRAY_H__F28AAC36_F0B0_42A5_A8B6_E4C86DC4EF92__INCLUDED_)
#define AFX_SIGNALARRAY_H__F28AAC36_F0B0_42A5_A8B6_E4C86DC4EF92__INCLUDED_


//IFLVC9_Inc_Export_H_Begin************************************
//#include "..\IFLExport.h" 
//IFLVC9_Inc_Export_H_End**************************************


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\converter\SignalData.h"

class  /*IFLAPI*/ CSignalArray  
{

public:
	static int BuildSignalArray(int nDevice, SignalGroupArray & aSignalArray);

	static DWORD GetSignalID(int nDevice, const CString &strSignalName);
};

#endif // !defined(AFX_SIGNALARRAY_H__F28AAC36_F0B0_42A5_A8B6_E4C86DC4EF92__INCLUDED_)
