/*--------------------------------------------------------------------------------------*
 | (C) Copyright 2006,2007 Marvell Semiconductor Israel Ltd. All Rights Reserved		|
 *--------------------------------------------------------------------------------------*/

// ScriptData.h: interface for the CScriptData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCRIPTDATA_H__4E8F39D0_4757_4513_A0B5_274636E1274F__INCLUDED_)
#define AFX_SCRIPTDATA_H__4E8F39D0_4757_4513_A0B5_274636E1274F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "ListEx.h"
#include "ConfigFile.h"
#include "ParameterMap.h"
#include "ScriptParamsDB.h"
#include "GeneralMacroDefine.h"

#define SCRIPT_ENABLED	0
#define SCRIPT_DISABLED	1
#define HW_CONFIG_MISMATCH	2


class CScriptsDB;
class CTestEngine;

class  CATCORE_DLL_STATIC_EXPORT CScriptData : public CObject  
{
public:
	CScriptData();
	CScriptData(CScriptsDB *pDB);
	CScriptData(CScriptData &data);
	virtual ~CScriptData();

	long		m_ScriptID;			// The script's unique ID.
	CString		m_ScriptName;		// The name of the script.
	CString		m_ScriptVersion;	// The script's version.
	CString		m_GroupName;		// The script's group.
	CString		m_DllName;			// The script's DLL.	
	UINT		m_bEnabled;			// Run the script, or not.

	CListEx <CParameterMap *, CParameterMap *> m_ParamSets;	// Script parameters map.

	BOOL	m_bModified;
	/*CArray<BOOL, BOOL> m_ParamSetsEnabled;*/ // Committed by hlguo 2011.12.30, could not be BOOL, will lead to load Scripts error.
	CArray<bool, bool> m_ParamSetsEnabled;
	static CString m_ResultString[];
public:
	void RemoveParamSets();
	int GetParameterCount();
	int GetTotalCurrentScriptIterations();
	BOOL IsLastScriptAndIteration(CTestEngine *pTestEngine);
	BOOL IsLastScript(CTestEngine *pTestEngine);
	virtual void Serialize(CArchive &ar);
	BOOL RunScript(CTestEngine *pTestEngine);
	void SetFailureReason(const CString &strReason);
	void ConvertParameter(const CString &strValue, CString &tValue){tValue = strValue;};
#ifdef UNICODE
	void ConvertParameter(const CString &strValue, int &tValue){tValue = _tstol(strValue);};
	void ConvertParameter(const CString &strValue, UINT &tValue){tValue = (UINT)_tstol(strValue);};
	void ConvertParameter(const CString &strValue, bool &tValue){tValue = ( strValue.CompareNoCase(_T("True")) == 0 ) ? true : false;};
	void ConvertParameter(const CString &strValue, double &tValue){tValue = _tstof(strValue);};
	template <class T> bool SetParameter(const CString &strName, T &tValue)
	{
		CString strValue;
		switch(CScriptParamsDB::GetParameterType(m_ScriptID, strName))
		{
		case paramTypeFile:
		case paramTypeString:
			strValue.Format(_T("%s"), tValue);	
			break;
		case paramTypeInt:
			strValue.Format(_T("%d"), tValue);	
			break;
// 		case paramTypeEnum:
// 			{
// 				CString strIntVal;
// 				if(CScriptParamsDB::GetEnumValue(m_ScriptID, strName,strValue,strIntVal))
// 				{
// 					ConvertParameter(strIntVal,tValue);	
// 					return true;
// 				}
// 			}
// 			break;
		case paramTypeUint:
			strValue.Format(_T("%lu"), tValue);	
			break;
		case paramTypeDouble:
			strValue.Format(_T("%f"), tValue);	
			break;
		case paramTypeBoolean:
			strValue = tValue ? _T("True") : _T("False");	
			break;
		}
		if ( !CScriptParamsDB::CheckValidParameter(m_ScriptID, strName, strValue) )
			return false;

		m_CurrentParameterMap.SetAt(strName, strValue);
		return true;

	};
	template <class T> BOOL GetParameter(const CString &strName, T &tValue)
	{
		CString strValue;
		if (! m_CurrentParameterMap.Lookup(strName, strValue) )
			return false;
		else
			switch(CScriptParamsDB::GetParameterType(m_ScriptID, strName))
			{
			case paramTypeFile:
			case paramTypeString:
				ConvertParameter(strValue,tValue);	
				break;
			case paramTypeInt:
				ConvertParameter(strValue,tValue);	
				break;
			case paramTypeEnum:
				{
					CString strIntVal;
					if(CScriptParamsDB::GetEnumValue(m_ScriptID, strName,strValue,strIntVal))
					{
						ConvertParameter(strIntVal,tValue);	
						return true;
					}
				}
				break;
			case paramTypeUint:
				ConvertParameter(strValue,tValue);	
				break;
			case paramTypeDouble:
				ConvertParameter(strValue,tValue);	
				break;
			case paramTypeBOOLean:
				ConvertParameter(strValue,tValue);	
				break;
			}

		return true;
	};
#else
#endif

	BOOL GetParameter(const CString &strName, bool &bValue);
	BOOL GetParameter(const CString &strName, double &fValue);
	BOOL GetParameter(const CString &strName, int &nValue);
	BOOL GetParameter(const CString &strName, UINT &unValue);
	BOOL GetParameter(const CString &strName, CString &strValue);

	void SaveToText(CConfigFile &IniFile, int index);
	void LoadFromText(CConfigFile &IniFile, int index);
	DECLARE_SERIAL(CScriptData)
private:
	int m_CurrentIteration;
	int m_CurrentScriptResultID;
	CParameterMap m_CurrentParameterMap;
	int m_nIterations; // The number of times to run the script.
	CWordArray m_Results; // The script's result/state for each iteration.
	CStringArray m_FailureReasons;
	CArray <COleDateTimeSpan, COleDateTimeSpan&> m_ScriptDurations;

public:
	void SetIterationsCount(int iterationsCount);
	void CScriptData::SetIterationsCount(CScriptData& scriptData);
	inline int GetIterationsCount() { return m_nIterations; };
	inline WORD GetResult(int iteration) { return m_Results[iteration]; };
	inline CString* GetFailureReason(int iteration) { return &(m_FailureReasons[iteration]); };
	inline COleDateTimeSpan* GetDuration(int iteration) { return &(m_ScriptDurations[iteration]); };

	int GetCurrentScriptIteration() { return m_CurrentIteration; } // Richard added 2011-11-23
	int GetCurrentScriptResultID() { return m_CurrentScriptResultID; } // Richard added 2011-11-23
	BOOL SetParameter(const CString &strName, CString &strValue); // Richard added 2011-11-23
	BOOL SetParameter(const CString &strName, int &nValue); // Richard added 2011-11-23
	BOOL SetParameter(const CString &strName, UINT &unValue); // Richard added 2011-11-23
	BOOL SetParameter(const CString &strName, double &fValue); // Richard added 2011-11-23
	BOOL SetParameter(const CString &strName, bool &bValue); // Richard added 2011-11-23
};


class SE_Exception
{
private:
    unsigned int nSE;
public:
    SE_Exception() {}
    SE_Exception( unsigned int n ) : nSE( n ) {}
    ~SE_Exception() {}
    unsigned int getSeNumber() { return nSE; }
};


#endif // !defined(AFX_SCRIPTDATA_H__4E8F39D0_4757_4513_A0B5_274636E1274F__INCLUDED_)
