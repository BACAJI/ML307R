/*--------------------------------------------------------------------------------------------------------------------

 (C) Copyright 2006,2007 Marvell Semiconductor Israel Ltd. All Rights Reserved  

-------------------------------------------------------------------------------------------------------------------*/



#if !defined(AFX_CONFIGPARAMS_H__732E39B3_6448_4F24_B3B2_901C1839B336__INCLUDED_)
#define AFX_CONFIGPARAMS_H__732E39B3_6448_4F24_B3B2_901C1839B336__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XDEVStructures.h"

class CATCORE_DLLEXPORT CConfigParams  
{
public:
	CConfigParams();
	virtual ~CConfigParams();
	CConfigParams(const CConfigParams& oConfigParams);
	void operator=(const CConfigParams& oConfigParams);
	void Clear();
	int GetDeviceIndex(const CString &strDevName);
	void Serialize(CArchive &ar);

	CString m_strConfigName;
	CString m_strConfigGroup;

	CArray<sConfigDevParams,sConfigDevParams&> arrConfigDevices;

};

#endif // !defined(AFX_CONFIGPARAMS_H__732E39B3_6448_4F24_B3B2_901C1839B336__INCLUDED_)
