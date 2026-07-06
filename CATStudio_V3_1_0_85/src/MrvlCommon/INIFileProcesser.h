

#pragma once

class CIniFileProcesser
{
public:
	CIniFileProcesser(LPCTSTR lpszIniFilePath);
	~CIniFileProcesser();

public:
	// Read api
	int ReadIntValue(LPCTSTR lpszSection, LPCTSTR lpszKey, int nDefault);
	CString ReadStringValue(LPCTSTR lpszSection, LPCTSTR lpszKey, LPCTSTR lpszDefault);

	// Write api
	BOOL WriteIntValue(LPCTSTR lpszSection, LPCTSTR lpszKey, int nValue);
	BOOL WriteStringValue(LPCTSTR lpszSection, LPCTSTR lpszKey, LPCTSTR lpszValue);


private:
	CString m_strIniFilePath;
};