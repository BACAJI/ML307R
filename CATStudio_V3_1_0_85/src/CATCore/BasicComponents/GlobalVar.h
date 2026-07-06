//#pragma once
#ifndef _CGlobalVar_
#define _CGlobalVar_
#include <vector>
#include "tlhelp32.h"
#include "singletondestroyer.h"


class CGlobalVar
{
private:
	CGlobalVar();
public:
	~CGlobalVar();

private:
	static CGlobalVar *m_pThis;
	static CSingletonDestroyer<CGlobalVar> m_Destroyer;

	BOOL m_bCloseAllLog;			//是否关闭所有log
	BOOL m_bEnableLockRecord;		//是否记录lock的记录到acat00.log中
	BOOL m_bEnableMessageFlowFIFO;	//是否记录消息流的处理流程
	BOOL m_bRWAsynchronous;			//异步读写
	BOOL m_bDataReplayMode;			//数据重播模式开关

public:
	static void GetAppPath(CString& strPath);
	static BOOL UnicodeToMultiByte(LPCWSTR lpcwszStr, LPSTR lpszStr, DWORD dwSize);
	static BOOL MultiByteToUnicode(LPWSTR lpwszStr, LPSTR lpszStr, DWORD dwSize);
	static void SystemTimeConvert(IN SYSTEMTIME st, OUT class CSystemTime* pSysTime);

public:
	static CGlobalVar* Instance();

	void SetIsLockRecord(BOOL bRecord);
	BOOL GetIsLockRecord();

	void SetRWModeIsAsyn(BOOL bRWAsynchronous);
	BOOL GetRWModeIsAsyn();

	void SetMsgFlowFIFORecord(BOOL bRecord);
	BOOL GetMsgFlowFIFORecord();

	void SetDataReplayMode(BOOL bDataReplayMode);
	BOOL GetDataReplayMode();

	void SetCloseAllLogRecord(BOOL bCloseAll);
	BOOL GetCloseAllLogRecord();
	int  FindProcessByName(LPCTSTR szFileName, std::vector<PROCESSENTRY32>& vpe);
	BOOL CompareFile(TCHAR strFirstFileName[MAX_PATH],TCHAR strSecondFileName[MAX_PATH]);
};
#endif