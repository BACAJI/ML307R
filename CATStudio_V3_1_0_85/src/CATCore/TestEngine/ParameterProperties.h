// ParameterProperties.h: interface for the CParameterProperties class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARAMETERPROPERTIES_H__81E7B72F_FD1A_4A4D_BDE9_DC541D12AA68__INCLUDED_)
#define AFX_PARAMETERPROPERTIES_H__81E7B72F_FD1A_4A4D_BDE9_DC541D12AA68__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CScriptParamsDB;

class __declspec(dllexport) CParameterProperties : CObject 
{
public:
	CParameterProperties();
	CParameterProperties(CScriptParamsDB *pDB);
	void operator =(CParameterProperties &paramProp);

	virtual ~CParameterProperties();

public:
	CString m_ParameterName;
	CString m_ParameterValue;
	long	m_ParameterType;
	CString m_MaxValue;
	CString m_MinValue;
	CString m_StringValues;
	CString m_Description;

	void Serialize(CArchive &ar);
};


#endif // !defined(AFX_PARAMETERPROPERTIES_H__81E7B72F_FD1A_4A4D_BDE9_DC541D12AA68__INCLUDED_)
