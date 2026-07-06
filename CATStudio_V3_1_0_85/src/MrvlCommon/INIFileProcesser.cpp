
#include "stdafx.h"
#include "INIFileProcesser.h"

CIniFileProcesser::CIniFileProcesser(LPCTSTR lpszIniFilePath)
: m_strIniFilePath(lpszIniFilePath)
{

}

CIniFileProcesser::~CIniFileProcesser()
{
	
}

int CIniFileProcesser::ReadIntValue(LPCTSTR lpszSection, LPCTSTR lpszKey, int nDefault)
{
	if (m_strIniFilePath.IsEmpty())
	{
		return nDefault;
	}

	int nResult;
	nResult = ::GetPrivateProfileInt(lpszSection, lpszKey, nDefault, m_strIniFilePath);
	
	return nResult;

}

CString CIniFileProcesser::ReadStringValue(LPCTSTR lpszSection, LPCTSTR lpszKey, LPCTSTR lpszDefault)
{
	if (m_strIniFilePath.IsEmpty())
	{
		return lpszDefault;
	}

	CString strResult;
	::GetPrivateProfileString(lpszSection, lpszKey, lpszDefault, 
		strResult.GetBuffer(MAX_PATH), MAX_PATH, m_strIniFilePath);
	strResult.ReleaseBuffer();
	
	return strResult;
}

BOOL CIniFileProcesser::WriteIntValue(LPCTSTR lpszSection, LPCTSTR lpszKey, int nValue)
{
	//if section does not exist, call ::WritePrivateProfileSection()?!
	CString strValue;
	strValue.Format(_T("%d"), nValue);
	return ::WritePrivateProfileString(lpszSection, lpszKey, strValue.GetBuffer(),
		m_strIniFilePath.GetBuffer());
}

BOOL CIniFileProcesser::WriteStringValue(LPCTSTR lpszSection, LPCTSTR lpszKey, LPCTSTR lpszValue)
{
	return ::WritePrivateProfileString(lpszSection, lpszKey, lpszValue, 
		m_strIniFilePath.GetBuffer());
}