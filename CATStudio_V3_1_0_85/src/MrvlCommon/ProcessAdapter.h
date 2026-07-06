#pragma once

typedef struct tagWNDINFO   
{   
	DWORD dwProcessId;   
	HWND  hWnd;   
}  WNDINFO,   *LPWNDINFO;   


class CProcessAdapter
{
public:
	BOOL StartSingleProcess(PROCESS_INFORMATION& pi, LPCTSTR lpAppName,  LPTSTR lpCmdLine);
	void StopSingleProcess(DWORD dwProcessID);
	HWND GetProcessMainWnd(DWORD dwProcessId);

	static BOOL CALLBACK EnumWindowProc(HWND hWnd, LPARAM lParam); 
};