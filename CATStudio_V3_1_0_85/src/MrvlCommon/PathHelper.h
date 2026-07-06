#pragma once


class CPathHelper
{
public:
	static BOOL GetCurrentAppPath(CString& strAppPath);
	static void GetCfgDirectory(CString& strcfgPath);
	static BOOL CopyFiles(LPCTSTR lpszFrom, LPCTSTR lpszTo);
	static BOOL GetBrowsePath(HWND hwndParent,LPITEMIDLIST pidl, TCHAR *pOutSelectedPath, TCHAR*pDisplayString);
	
	static void RemoveReadonlyAttribute(CString& strFileName);
	
	static HRESULT SHPathToPIDL(LPCTSTR szPath, LPITEMIDLIST* ppidl);
};