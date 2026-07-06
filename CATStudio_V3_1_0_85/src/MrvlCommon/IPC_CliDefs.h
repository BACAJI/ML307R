#pragma once
#include <vector>
static void CStringToArray(CString str,CStringArray & strArray, TCHAR delimiter = _T('|'))
{
	const TCHAR *p = (TCHAR *)str.GetBuffer();
	TCHAR buf[800];
	int count = 0;

	strArray.RemoveAll();
	while ( *p != _T('\0') )
	{
		while (*p != _T('\0') && *p != delimiter)
			buf[count++] = *p++;
		buf[count] = _T('\0');
		count = 0;
		strArray.Add(CString(buf));
		if (*p != _T('\0'))
			p++;
	}
	str.ReleaseBuffer();
}

struct IPC_UE_PARAMS
{
	enum  {nUsbRecStrLen = 128,nScriptRecStrLen = 256};
	enum  {eNotAlive=0, eAlive=1};
	long  nDevice;
	long  CommType;
	long  ProtType;
	long  nComNum;
	long  nBaudRate;
	long  bUnicode;
	TCHAR sUsbRecStr[nUsbRecStrLen]; // In Character (NOT Bytes)
	TCHAR sScriptPath[nScriptRecStrLen];
	long  nStatus; //0:disconnected, 1:connected(alive).

	CString ToString(TCHAR chr = _T('|'))
	{
		CString strParams;
		strParams.Format(_T("%d%c%d%c%d%c%d%c%d%c%d%c%s%c%s%c%d"),nDevice,chr,CommType,chr,ProtType,chr,nComNum,chr,nBaudRate,chr,bUnicode,chr,sUsbRecStr,chr,sScriptPath,chr,nStatus);
		return strParams;
	}
	void FromString(CString& strParams,TCHAR chr = _T('|'))
	{
		CStringArray strArray;
		CStringToArray(strParams,strArray,chr);
		nDevice   = _tstol(strArray[0]);
		CommType  = _tstol(strArray[1]);
		ProtType  = _tstol(strArray[2]);
		nComNum   = _tstol(strArray[3]);
		nBaudRate = _tstol(strArray[4]);
		bUnicode  = _tstol(strArray[5]);
		memset(sUsbRecStr,0,nUsbRecStrLen * sizeof(TCHAR));
		_tcscpy_s(sUsbRecStr,nUsbRecStrLen,strArray[6].GetBuffer(0)); 
		strArray[6].ReleaseBuffer();
		memset(sScriptPath,0,nScriptRecStrLen * sizeof(TCHAR));
		_tcscpy_s(sScriptPath,nScriptRecStrLen,strArray[7].GetBuffer(0)); 
		strArray[7].ReleaseBuffer();
		nStatus   = _tstol(strArray[8]);
	}
};

class IPC_PARAMS_PROC
{
public:
	CString ToString(IPC_UE_PARAMS & ipcUEParams,TCHAR chr = _T('*'))
	{
		strParams += ipcUEParams.ToString() + chr;
		return strParams;
	}

	std::vector<IPC_UE_PARAMS>& FromString(CString& strParams,TCHAR chr = _T('*'))
	{
		IPC_UE_PARAMS ipcUEParams;
		CStringArray strParamsArray;
		CStringToArray(strParams,strParamsArray,chr);
		for(int i = 0; i < strParamsArray.GetCount(); i++)
		{
			ipcUEParams.FromString(strParamsArray[i]);
			ipcUEParamsArray.push_back(ipcUEParams);
		}
		return ipcUEParamsArray;
	}
	CString & GetString()
	{
		return strParams;
	}
	std::vector<IPC_UE_PARAMS>& GetUEParamsArray()
	{
		return ipcUEParamsArray;
	}
private:
	CString strParams;
	std::vector<IPC_UE_PARAMS> ipcUEParamsArray;
};