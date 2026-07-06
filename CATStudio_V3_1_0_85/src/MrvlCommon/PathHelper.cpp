
#include "stdafx.h"
#include "PathHelper.h"

BOOL CPathHelper::GetCurrentAppPath(CString& strAppPath)
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

void CPathHelper::GetCfgDirectory(CString& strcfgPath)
{
	GetCurrentAppPath(strcfgPath);
	strcfgPath += _T("cfg\\");
}


// Tested: Chinese path (including space char) passed.
HRESULT CPathHelper::SHPathToPIDL(LPCTSTR szPath, LPITEMIDLIST* ppidl)
{
	LPSHELLFOLDER pShellFolder = NULL;
	ULONG nCharsParsed = 0;
	DWORD dwAttribs = SFGAO_COMPRESSED;

	// Get an IShellFolder interface pointer
	HRESULT hr = SHGetDesktopFolder(&pShellFolder);
	if(FAILED(hr))
		return hr;

	// Convert the path name to Unicode
	// Call ParseDisplayName() to do the job
	hr = pShellFolder->ParseDisplayName(NULL, NULL, (LPWSTR)szPath, &nCharsParsed, ppidl, &dwAttribs);

	// Clean up
	pShellFolder->Release();
	return hr;
}

BOOL CPathHelper::GetBrowsePath(HWND hwndParent, LPITEMIDLIST pidl, TCHAR *pOutSelectedPath, TCHAR*pDisplayString)
{
	BROWSEINFO bi = {0};
	LPITEMIDLIST  pUserSelected = NULL;
	TCHAR szUserSelect[MAX_PATH] = {0};

	bi.hwndOwner = hwndParent;
	bi.pidlRoot = pidl;
	bi.pszDisplayName = szUserSelect;
	bi.lpszTitle = pDisplayString;
	bi.ulFlags |= BIF_NEWDIALOGSTYLE;

	pUserSelected = SHBrowseForFolder(&bi); 
	if(NULL != pUserSelected)
	{
		// after this function call,the szUserSelect from reletive path to absolute path.
		if(SHGetPathFromIDList(pUserSelected, szUserSelect))
		{
			// copy absolute path to caller for return value.
			_tcscpy(pOutSelectedPath, szUserSelect);
			return TRUE;
		}
	}

	return FALSE;
}


BOOL CPathHelper::CopyFiles(LPCTSTR lpszFrom, LPCTSTR lpszTo)
{
	TCHAR szFrom[MAX_PATH] = {0};
	TCHAR szTo[MAX_PATH] = {0};
	_tcscpy(szFrom, lpszFrom);
	_tcscpy(szTo, lpszTo);

	TCHAR* pTempFrom = szFrom;
	while(*pTempFrom++ != '\0');
	*pTempFrom = '\0';

	TCHAR* pTempTo = szTo;
	while(*pTempTo++ != '\0');
	*pTempTo = '\0';


	SHFILEOPSTRUCT FileOp={0}; 
	FileOp.fFlags = FOF_NOCONFIRMATION|		// No confirm information.
		FOF_NOCONFIRMMKDIR|		// Create folder directly,not confirm.
		FOF_FILESONLY ;			// Copy file only, not folder.

	FileOp.pFrom = szFrom; 
	FileOp.pTo = szTo; 
	FileOp.wFunc = FO_COPY; 

	return SHFileOperation(&FileOp) == 0 ;
}

void CPathHelper::RemoveReadonlyAttribute(CString& strFileName) // -r file
{
	CFileStatus Status;

	if (CFile::GetStatus(strFileName,Status)==FALSE) 
		return;
	Status.m_mtime=0;
	if(Status.m_attribute &0x01==0x01)// read only
	{ 
		Status.m_attribute &=(~0x01);// write read  
		CFile::SetStatus(strFileName,Status );
	}	
}
