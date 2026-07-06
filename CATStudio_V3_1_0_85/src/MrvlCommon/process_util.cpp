#include "stdafx.h"
#include "process_util.h"
#include "tlhelp32.h"


BOOL LaunchProcess(PROCESS_INFORMATION& pi, LPCTSTR szModulePath, LPCTSTR szCmdline )
{
   ZeroMemory( &pi, sizeof(pi) );

   STARTUPINFO si;
   ZeroMemory( &si, sizeof(si) );
   si.cb = sizeof(si);

   CString str = _T(" ");
   str += szCmdline;

   if (!CreateProcess(szModulePath, (LPTSTR)str.GetBuffer(0), NULL,NULL,FALSE,0,NULL,NULL, &si, &pi))
   {
      DWORD nError = GetLastError();
      CString strErr;
      strErr.Format(_T("Create Process %s Failed! ErrorCode = %d"), szModulePath, nError);
      return FALSE;
   }

   return TRUE;
}

void NotifyProcessExit( PROCESS_INFORMATION& pi )
{
   HWND hMainWnd = NULL;
   hMainWnd = GetProcessMainWnd( pi.dwProcessId);
   if (NULL != hMainWnd)
   {
      ::PostMessage(hMainWnd, WM_CLOSE, 0, 0);
   }
}

BOOL WaitForProcess( HANDLE hProcess, DWORD dwTimeout )
{
   if( WaitForSingleObject(hProcess, dwTimeout)==WAIT_OBJECT_0 )
      return TRUE;
   return FALSE;
}

BOOL WaitForProcess( PROCESS_INFORMATION& pi, DWORD dwTimeout )
{
    return WaitForProcess(pi.hProcess, dwTimeout);
}

// Notify and Wait
BOOL WaitForProcessToExit( PROCESS_INFORMATION& pi, DWORD dwTimeout )
{
   NotifyProcessExit(pi);
   return WaitForProcess(pi, dwTimeout);
}

// Notify Wait Terminate
BOOL KillProcess( PROCESS_INFORMATION& pi, DWORD dwTimeout )
{
   if(!WaitForProcessToExit(pi, dwTimeout)) {
      TerminateProcess(pi.hProcess, 0);
      if( !WaitForProcess(pi.hProcess, 0) ) {
         return FALSE;
      }
      return TRUE;
   } 
   return TRUE;
}

BOOL CleanupProcess( PROCESS_INFORMATION& pi, DWORD dwTimeout)
{
   if( !KillProcess(pi, dwTimeout) ) {
      return FALSE;
   }
   CloseHandle(pi.hProcess);
   return TRUE;
}


HWND  GetProcessMainWnd(DWORD dwProcessId)   
{   
   WNDINFO   wi;   
   wi.dwProcessId = dwProcessId;   
   wi.hWnd = NULL;   

   ::EnumWindows(EnumWindowProc,(LPARAM)&wi);   

   return  wi.hWnd;   
} 

BOOL _stdcall EnumWindowProc(HWND hWnd, LPARAM lParam)   
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


CString GetCurrentModuleDirectory()
{
   CString strAppPath;
   TCHAR szFullExeName[MAX_PATH];
   DWORD nResult = ::GetModuleFileName(NULL, szFullExeName, MAX_PATH);
   if (0 == nResult)
   {
      return _T("");
   }

   CString strFullFileName(szFullExeName);
   UINT nIndex = strFullFileName.ReverseFind('\\');
   strAppPath = strFullFileName.Left(nIndex);

   return strAppPath;
}

int GetProcessThreadNum()
{
   DWORD dwThreadNum=0;
   ::GetProcessThreadNum(GetCurrentProcessId(), dwThreadNum);
   
   return (int)dwThreadNum;
}

void GetProcessThreadNum(DWORD dwProcessID,DWORD &dwThreadNum)
{
   HANDLE hProcessSnap;
   PROCESSENTRY32 pe32;

   hProcessSnap = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, dwProcessID );
   if( hProcessSnap == INVALID_HANDLE_VALUE )
   {
      AfxMessageBox(_T( "CreateToolhelp32Snapshot (of processes)" ));
      return;
   }

   // Set the size of the structure before using it.
   pe32.dwSize = sizeof( PROCESSENTRY32 );

   // Retrieve information about the first process,
   // and exit if unsuccessful
   if( !Process32First( hProcessSnap, &pe32 ) )
   {
      CloseHandle( hProcessSnap );     // Must clean up the snapshot object!
      return;
   }

   do
   {
      if (pe32.th32ProcessID == dwProcessID)
      {
         dwThreadNum  = pe32.cntThreads;
         break;
      }
   } while( Process32Next( hProcessSnap, &pe32 ) );

   CloseHandle( hProcessSnap );
}