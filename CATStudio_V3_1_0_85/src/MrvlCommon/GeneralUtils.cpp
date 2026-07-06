#include "stdafx.h"
#include "GeneralUtils.h"



//-------------------------------------------------------------------------------------
//Description:
// This function maps a character string to a wide-character (Unicode) string
//
//Parameters:
// lpcszStr: [in] Pointer to the character string to be converted 
// lpwszStr: [out] Pointer to a buffer that receives the translated string. 
// dwSize: [in] Size of the buffer
//
//Return Values:
// TRUE: Succeed
// FALSE: Failed
// 
//Example:
// MByteToWChar(szA,szW,sizeof(szW)/sizeof(szW[0]));
//---------------------------------------------------------------------------------------
BOOL MByteToWChar(LPCSTR lpcszStr, LPWSTR lpwszStr, DWORD dwSize)
{
  // Get the required size of the buffer that receives the Unicode 
  // string. 
  DWORD dwMinSize;
  dwMinSize = MultiByteToWideChar (CP_ACP, 0, lpcszStr, -1, NULL, 0);

  if(dwSize < dwMinSize)
  {
    return FALSE;
  }


  // Convert headers from ASCII to Unicode.
  MultiByteToWideChar (CP_ACP, 0, lpcszStr, -1, lpwszStr, dwMinSize);  
  return TRUE;
}



//-------------------------------------------------------------------------------------
//Description:
// This function maps a wide-character string to a new character string
//
//Parameters:
// lpcwszStr: [in] Pointer to the character string to be converted 
// lpszStr: [out] Pointer to a buffer that receives the translated string. 
// dwSize: [in] Size of the buffer
//
//Return Values:
// TRUE: Succeed
// FALSE: Failed
// 
//Example:
// MByteToWChar(szW,szA,sizeof(szA)/sizeof(szA[0]));
//---------------------------------------------------------------------------------------
BOOL WCharToMByte(LPCWSTR lpcwszStr, LPSTR lpszStr, DWORD dwSize)
{
  DWORD dwMinSize;
  dwMinSize = WideCharToMultiByte(CP_OEMCP,NULL,lpcwszStr,-1,NULL,0,NULL,FALSE);
  if(dwSize < dwMinSize)
  {
    return FALSE;
  }
  WideCharToMultiByte(CP_OEMCP,NULL,lpcwszStr,-1,lpszStr,dwSize,NULL,FALSE);
  return TRUE;
}

BOOL CStringTowstring( CString& tString, wstring& wstr )
{
   
#ifdef _UNICODE
   wstr.assign(tString.GetBuffer(0), tString.GetLength());
   return TRUE;
#else
  try
  {
    wchar_t* pwc = new wchar_t[tString.GetLength()];
    BOOL b = MByteToWChar(tString.GetBuffer(0), pwc, tString.GetLength() );
    wstr.assign(pwc, tString.GetLength());
    delete []pwc;
    pwc = NULL;
    return TRUE;
  }
  catch (CMemoryException* e)
  {
  	return FALSE;
  }
  catch (...)
  {
    return FALSE;
  }
#endif
}

void Num2Hex(BYTE Num, char Hex[2])
{
   static char Lut[16]={'0', '1','2','3','4','5','6','7','8','9', 'A', 'B', 'C', 'D', 'E', 'F'};
   Hex[0] = Lut[(Num>>4)];
   Hex[1] = Lut[(Num&0x0F)];
}

void Num2HexW(BYTE Num, wchar_t Hex[2])
{
   static TCHAR LutW[16]={'0', '1','2','3','4','5','6','7','8','9', 'A', 'B', 'C', 'D', 'E', 'F'};
   Hex[0] = LutW[(Num>>4)];
   Hex[1] = LutW[(Num&0x0F)];
}

void Data2HexString(BYTE* buf, int bufLen, char* HexString, bool bAddSpace)
{
   for(int i=0; i<bufLen; ++i)
   {
      Num2Hex(buf[i], HexString+2*i);
   }

   char chHex[2];
   const int nStep = bAddSpace? 3:2;
   for(int i=0; i<bufLen; ++i)
   {
      Num2Hex(buf[i], chHex);
      HexString[i*nStep] = chHex[0];
      HexString[i*nStep+1] = chHex[1];
      if( bAddSpace )
         HexString[i*nStep+2] = ' ';
   }
}

void Data2HexWString(BYTE* buf, int bufLen, wchar_t* HexString, bool bAddSpace)
{
   wchar_t wc[2]={0,0};
   const int nStep = bAddSpace? 3:2;
   for(int i=0; i<bufLen; ++i)
   {
      Num2HexW(buf[i], wc);
      HexString[i*nStep] = wc[0];
      HexString[i*nStep+1] = wc[1];
      if( bAddSpace )
         HexString[i*nStep+2] = ' ';
   }
}

BOOL ClearDirectory(LPCTSTR lpszDirName) 
{ 
   CFileFind tempFind; 
   CString sTempFileFind = lpszDirName + CString(_T("\\*.*"));
   BOOL IsFinded = tempFind.FindFile(sTempFileFind); 

   while (IsFinded) 
   { 
      IsFinded = tempFind.FindNextFile(); 

      if (!tempFind.IsDots()) 
      { 
         CString sFoundFileName = tempFind.GetFileName();
         if (tempFind.IsDirectory()) 
         { 
            //Do not delete files in sub folder
            //CString sTempDir = lpszDirName + CString(_T("\\")) + sFoundFileName;
            //ClearDirectory(sTempDir); 
         } 
         else 
         { 
            CString sTempFileName = lpszDirName + CString(_T("\\")) + sFoundFileName;
            ::DeleteFile(sTempFileName); 
         } 
      } 
   } 
   tempFind.Close(); 
   
   return TRUE; 
} 


ULONGLONG GetFolderSize(LPCTSTR lpszDirName, BOOL bIncludeSubDir) 
{ 
   ULONGLONG  nFolderSize=0;
   CFileFind tempFind; 
   CString sTempFileFind = lpszDirName + CString(_T("\\*.*"));
   BOOL IsFinded = tempFind.FindFile(sTempFileFind); 
   

   while (IsFinded) 
   { 
      IsFinded = tempFind.FindNextFile(); 

      if (!tempFind.IsDots()) 
      { 
         CString sFoundFileName = tempFind.GetFileName();
         if (bIncludeSubDir && tempFind.IsDirectory()) 
         { 
            CString sTempDir = lpszDirName + CString(_T("\\")) + sFoundFileName;
            nFolderSize += GetFolderSize(sTempDir); 
         } 
         else 
         { 
            CString sTempFileName = lpszDirName + CString(_T("\\")) + sFoundFileName;
            nFolderSize += tempFind.GetLength();
         } 
      } 
   } 
   tempFind.Close(); 

   return nFolderSize; 
} 

ULONGLONG GetSizeOfAllFile(LPCTSTR lpszDirName) 
{ 
   ULONGLONG  nSizeOfAllFile = GetFolderSize(lpszDirName, FALSE);
   return nSizeOfAllFile;
} 
