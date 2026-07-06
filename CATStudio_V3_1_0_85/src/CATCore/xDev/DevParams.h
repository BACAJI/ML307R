/*--------------------------------------------------------------------------------------------------------------------

 (C) Copyright 2006,2007 Marvell Semiconductor Israel Ltd. All Rights Reserved  

-------------------------------------------------------------------------------------------------------------------*/



#if !defined(AFX_DEVPARAMS_H__DA4C4914_CBDB_4469_A2ED_DE33A5154037__INCLUDED_)
#define AFX_DEVPARAMS_H__DA4C4914_CBDB_4469_A2ED_DE33A5154037__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XDEVStructures.h"

class CATCORE_DLLEXPORT CDevParams  
{
public:
	CDevParams();
	virtual ~CDevParams();
	CDevParams(const CDevParams& oDevParams);
	void operator=(const CDevParams& oDevParams);
	void Clear();
	int GetDeviceAttenuationIndex(const CString &strPort,const CString &strBandOrFreqArea);
	int GetDeviceSecAddressIndex(const int iSecAddress);
	void Serialize(CArchive &ar);
	
	CString m_strDevName;
	CString m_strDllName;
	CString m_strInitFunc;
	CString m_strCloseFunc;
	CString m_strResetFunc;
	CString m_strDevGruop;
	CString m_strIDNString;
	CString m_strProtocol;
	int m_iGPIB;
	int m_iAddress;
	BOOL m_bIsIDNable;
	BOOL m_bIsResetable;
	BOOL m_bHasSecAddress;
	BOOL m_bHasAttenuationSetting;


	CArray<sSecAddressParams,sSecAddressParams&> arrSecAddress;
	CArray<sAttenuationParams,sAttenuationParams&> arrAttenuation;	
};

#endif // !defined(AFX_DEVPARAMS_H__DA4C4914_CBDB_4469_A2ED_DE33A5154037__INCLUDED_)
