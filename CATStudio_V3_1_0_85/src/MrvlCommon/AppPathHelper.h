
#pragma once

#ifdef _CATCORE_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT 
#endif
class DLL_EXPORT CAppPathHelper
{
public:
	static BOOL GetCurrentAppPath(CString& strAppPath);
	static CString GetDBFolderPath(int nDevice);
};