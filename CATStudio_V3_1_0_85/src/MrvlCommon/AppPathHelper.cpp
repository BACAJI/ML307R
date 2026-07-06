
#include "stdafx.h"
#include "AppPathHelper.h"
#include "..\CATCore\Converter\ConverterManager.h"

BOOL CAppPathHelper::GetCurrentAppPath(CString& strAppPath)
{
	TCHAR szFullExeName[MAX_PATH];
	DWORD nResult = ::GetModuleFileName(NULL, szFullExeName, MAX_PATH);
	if (0 == nResult)
	{
		return FALSE;
	}

	CString strFullFileName(szFullExeName);
	UINT nIndex = strFullFileName.ReverseFind('\\');
	strAppPath = strFullFileName.Left(nIndex+1);

	return TRUE;
}

//d:\..\DB\Offline0\\Device0
CString CAppPathHelper::GetDBFolderPath(int nDevice)
{
	CString strDev;
	strDev.Format(_T("\\Device%d"), nDevice);
	CString strDbPath = CConverterManager::Instance(nDevice)->GetDBPath();
	strDbPath += strDev;

	return strDbPath;
}