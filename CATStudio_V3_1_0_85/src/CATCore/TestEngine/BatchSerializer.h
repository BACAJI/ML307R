/*--------------------------------------------------------------------------------------*
 | (C) Copyright 2006,2007 Marvell Semiconductor Israel Ltd. All Rights Reserved		|
 *--------------------------------------------------------------------------------------*/


// BatchSerializer.h: interface for the CBatchSerializer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BATCHSERIALIZER_H__3817DAB0_79E2_4EC6_9250_B98666EB3FA9__INCLUDED_)
#define AFX_BATCHSERIALIZER_H__3817DAB0_79E2_4EC6_9250_B98666EB3FA9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTestEngine;
class CScriptData;

class __declspec(dllexport) CBatchSerializer  
{
private:
	CBatchSerializer();
	virtual ~CBatchSerializer();

public:
	static BOOL GetScriptList(const CString &strPath, CStringList *pScriptList);
	static BOOL LoadBatch(CTestEngine *pTestEngine, const CString &strPath);
	static BOOL SaveBatch(CTestEngine *pTestEngine, const CString &strPath);
	static BOOL IsValidScript(CScriptData *pData);

	static BOOL SaveBatchToText(CTestEngine *pTestEngine, const CString &strPath);
	static BOOL LoadBatchFromText(CTestEngine *pTestEngine, const CString &strPath);

private:
	static void ValidateBatchParamsDescriptions(CTestEngine *pTestEngine);
	static HINSTANCE m_hDll;
	static CString m_strDllName;
};

#endif // !defined(AFX_BATCHSERIALIZER_H__3817DAB0_79E2_4EC6_9250_B98666EB3FA9__INCLUDED_)
