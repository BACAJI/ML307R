/*--------------------------------------------------------------------------------------*
 | (C) Copyright 2006,2007 Marvell Semiconductor Israel Ltd. All Rights Reserved		|
 *--------------------------------------------------------------------------------------*/

// ParameterMap.h: interface for the CParameterMap class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARAMETERMAP_H__53929AE3_7BEC_48F2_9102_B502FB017323__INCLUDED_)
#define AFX_PARAMETERMAP_H__53929AE3_7BEC_48F2_9102_B502FB017323__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "ConfigFile.h"
#include "GeneralMacroDefine.h"

class CATCORE_DLLEXPORT CParameterMap : public CMapStringToString
{
public:
	CParameterMap();
	CParameterMap(CParameterMap &map);
	virtual ~CParameterMap();

public:
	void operator = (CParameterMap &map);

	void SaveToText(CConfigFile &IniFile, const CString &strSection);
	void LoadFromText(CConfigFile &IniFile, const CString &strSection);

};

#endif // !defined(AFX_PARAMETERMAP_H__53929AE3_7BEC_48F2_9102_B502FB017323__INCLUDED_)
