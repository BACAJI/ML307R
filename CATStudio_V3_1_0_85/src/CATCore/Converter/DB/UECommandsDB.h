#pragma once
#include "adorecordsetex.h"
#include "..\Cat1ToCat2Map.h"
#include "..\Cat2ToCat3Map.h"
#include "./../DiagCommDef.h"
#include <map>


#ifdef _CATCORE_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif


class DLL_EXPORT CUECommandsDB : public CADORecordsetEx
{
public:
	CUECommandsDB(CADODatabase* pDatabase = NULL);

// 	long	m_FileId;
// 	long	m_EnumVal;
// 	BYTE	m_EnumType;
// 	long	m_UniqEnumID;
// 	CString	m_ReportLine;
// 	CString m_Cat1;
// 	CString m_Cat2;
// 	CString m_Cat3;
// 	CString m_DefaultData;
// 	BOOL	m_bIsExtCommand;
// 	CString	m_DefaultExtOpcode;
	EnumValsRecord m_evr;
	CString m_strDBFile;
	//	BYTE	m_Level;

	void AddRecord(CUECommandsDB &rec);
	void ChangeRecord(CUECommandsDB &rec, BOOL	changeDefData);
	void AddRecord(long lFileId, long lEnumVal, int nEnumType, CString strReportLine,
		CString strCat1, CString strCat2, CString strCat3, BOOL bIsExt);
	void SetDBName(const CString strDBFile);

	BOOL LoadCategorizedSignalsToMap(std::multimap<long,EnumValsRecord*>& mapCategoryIdToSignalInfo, std::multimap<CString,EnumValsRecord*>& mapCategoryNameToSignalInfo, CCat1ToCat2Map& mapCommandCat1ToCat2, CCat1ToCat2Map& mapReportCat1ToCat2);
public:
	virtual CString GetDefaultDBName();		// Default database name
	virtual CString GetDefaultSQL();		// Default SQL for Recordset
	virtual void DoFieldExchange(BOOL bLoad = TRUE);
};

//#if MICL_BUILD
class DLL_EXPORT CUEAppsCommandsDB : public CUECommandsDB
{
public:
	virtual CString GetDefaultDBName();
};
//#endif