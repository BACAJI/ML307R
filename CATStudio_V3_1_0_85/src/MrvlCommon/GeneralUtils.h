#pragma once
#include <string>

using namespace std;
BOOL __declspec(dllexport) MByteToWChar(LPCSTR lpcszStr, LPWSTR lpwszStr, DWORD dwSize);
BOOL __declspec(dllexport) WCharToMByte(LPCWSTR lpcwszStr, LPSTR lpszStr, DWORD dwSize);
BOOL __declspec(dllexport) CStringTowstring(CString& tString, wstring& wstr);
void __declspec(dllexport) Num2Hex(BYTE Num, char Hex[2]);
void __declspec(dllexport) Data2HexString(BYTE* buf, int bufLen, char* HexString, bool bAddSpace=false);
void __declspec(dllexport) Data2HexWString(BYTE* buf, int bufLen, wchar_t* HexString, bool bAddSpace=false);
BOOL __declspec(dllexport) ClearDirectory(LPCTSTR lpszDirName);
ULONGLONG __declspec(dllexport) GetFolderSize(LPCTSTR lpszDirName, BOOL bIncludeSubDir=TRUE);
ULONGLONG __declspec(dllexport) GetSizeOfAllFile(LPCTSTR lpszDirName);
BOOL __declspec(dllexport) FindEarliestAccessedFile(LPCTSTR lpszDirName, FILETIME& ftLastAccess, CString& strFilePath );
BOOL __declspec(dllexport) DeleteOldestFile(LPCTSTR lpszDirName);



struct UECommand
{
   USHORT  length;
   USHORT  instanceId;
   BYTE    diagSAP;
   BYTE    serviceId;
   USHORT  moduleId;
   DWORD   commandId;
   DWORD   sourceId;
};