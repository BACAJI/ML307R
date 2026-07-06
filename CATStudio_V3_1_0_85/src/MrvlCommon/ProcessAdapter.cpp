
#include "stdafx.h"
#include "ProcessAdapter.h"

BOOL CProcessAdapter::StartSingleProcess(PROCESS_INFORMATION& pi, LPCTSTR lpAppName,  LPTSTR lpCmdLine)
{
	STARTUPINFO si;
	ZeroMemory( &si, sizeof(si) );
	si.cb = sizeof(si);
	ZeroMemory( &pi, sizeof(pi) );

	if (!CreateProcess(lpAppName, lpCmdLine, NULL,NULL,FALSE,0,NULL,NULL, &si, &pi))
	{
		DWORD nError = GetLastError();
		CString strErr;
		strErr.Format(_T("Create Process %s Failed!ErrorCode = %d"), lpAppName, nError);
		//AfxMessageBox(strErr);

		return FALSE;
	}


	return TRUE;
}


void CProcessAdapter::StopSingleProcess(DWORD dwProcessID)
{
	HWND hMainWnd = NULL;
	hMainWnd = GetProcessMainWnd(dwProcessID);
	if (NULL != hMainWnd)
	{
		::PostMessage(hMainWnd, WM_CLOSE, 0, 0);
	} 

	HANDLE hProcess = ::OpenProcess(SYNCHRONIZE | PROCESS_TERMINATE, FALSE, dwProcessID);
	if (NULL != hProcess)
	{
		if (WAIT_OBJECT_0 != WaitForSingleObject(hProcess, 5000))
		{
			//a u still alived?
			TerminateProcess(hProcess, 0);
		}
		::CloseHandle(hProcess);
	}
}

HWND  CProcessAdapter::GetProcessMainWnd(DWORD dwProcessId)   
{   
	WNDINFO   wi;   
	wi.dwProcessId = dwProcessId;   
	wi.hWnd = NULL;   
	::EnumWindows(CProcessAdapter::EnumWindowProc,(LPARAM)&wi);   

	return  wi.hWnd;   
}

BOOL CALLBACK CProcessAdapter::EnumWindowProc(HWND hWnd, LPARAM lParam)   
{   
	LONG nStyle = GetWindowLong(hWnd, GWL_STYLE);
	if ((nStyle & WS_VISIBLE) && !(nStyle & WS_CHILD) && (NULL == ::GetParent(hWnd)))
	{
		DWORD dwProcessId;   
		::GetWindowThreadProcessId(hWnd, &dwProcessId);   
		LPWNDINFO pInfo = (LPWNDINFO)lParam;   
		if(dwProcessId == pInfo->dwProcessId)   
		{   
			pInfo->hWnd = hWnd;   
			return FALSE;   
		}   
	}

	return TRUE;   
} 
