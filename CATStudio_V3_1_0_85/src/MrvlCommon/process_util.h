#pragma once
#include "GeneralMacroDefine.h"

typedef struct tagWNDINFO   
{   
   DWORD dwProcessId;   
   HWND  hWnd;   
}  WNDINFO,   *LPWNDINFO; 


// Launch Process
BOOL  CATCORE_DLLEXPORT LaunchProcess(PROCESS_INFORMATION& pi, LPCTSTR szModulePath, LPCTSTR szCmdline);

// Only notify process to exit
void  CATCORE_DLLEXPORT NotifyProcessExit(PROCESS_INFORMATION& pi);

// Only wait process exited
BOOL  CATCORE_DLLEXPORT WaitForProcess(HANDLE hProcess, DWORD dwTimeout);
BOOL  CATCORE_DLLEXPORT WaitForProcess(PROCESS_INFORMATION& pi, DWORD dwTimeout);

// Notify process exit and wait it exited
BOOL  CATCORE_DLLEXPORT WaitForProcessToExit(PROCESS_INFORMATION& pi, DWORD dwTimeout);

// Notify Wait Terminate
BOOL  CATCORE_DLLEXPORT KillProcess(PROCESS_INFORMATION& pi, DWORD dwTimeout);

// Notify Wait Terminate CloseHandle
BOOL  CATCORE_DLLEXPORT CleanupProcess( PROCESS_INFORMATION& pi, DWORD dwTimeout);

HWND CATCORE_DLLEXPORT GetProcessMainWnd(DWORD dwProcessId);

BOOL CATCORE_DLLEXPORT _stdcall  EnumWindowProc(HWND hWnd, LPARAM lParam);

int  CATCORE_DLLEXPORT GetProcessThreadNum();
void CATCORE_DLLEXPORT GetProcessThreadNum(DWORD dwProcessID,DWORD &dwThreadNum);

// 
CString CATCORE_DLLEXPORT GetCurrentModuleDirectory();