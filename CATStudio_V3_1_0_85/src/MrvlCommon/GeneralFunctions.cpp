#include "stdafx.h"
#include "GeneralFunctions.h"
#include "..\CATStudio\CATSVersion.h"
#include "Imc.h"

CString GetACATVersionString()
{
   return CString(_CATS_VERSION);
}

UINT GetACATVersionNumber()
{
   return (UINT)(_CATS_REV_NUM);
}

CString GetDumpFolderPath()
{
   CImc imc;
   CString strPath = imc.GetLoggingPath();
   return strPath;
}
