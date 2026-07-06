// MinimumStandardDB.cpp : implementation file
//

#include "stdafx.h"
#include "MinimumStandardDB.h"
#include "ApplicationINI.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CMinimumStandardDB

CMinimumStandardDB::CMinimumStandardDB()
{
	//{{AFX_FIELD_INIT(CMinimumStandardDB)
	m_Minimum_Standard_Name = _T("");
	m_ms_Test_Name = _T("");
	m_ms_Sub_Test_Name = _T("");
	m_Minimum_standard_sub = _T("");
	m_Min = 0.0f;
	m_Max = 0.0f;
	m_Range_ID = 0;
	m_Notes = _T("");
	m_Section = _T("");
	//}}AFX_FIELD_INIT
}

CMinimumStandardDB::~CMinimumStandardDB()
{
	if ( IsOpen() )
		Close();
}

CString CMinimumStandardDB::GetDefaultDBName()
{

	if ( AppIni()->GetProfileInt(_T("TestEngineSettings"), _T("DatabaseType"), 0) == 1 )
		return AppIni()->GetProfileString(_T("TestEngineSettings"), _T("DatabasePath"), _T(""));

	return AppPath() + _T("\\DB\\MinimumStandard.mdb");
}

CString CMinimumStandardDB::GetDefaultSQL()
{
	return _T("[TB_Minimum_Standard]");
}

void CMinimumStandardDB::DoFieldExchange(BOOL bLoad/*=TRUE*/)
{
	if ( bLoad )
	{
		GetFieldValue(_T("Minimum_Standard_Name"), m_Minimum_Standard_Name);
		GetFieldValue(_T("ms_Test_Name"), m_ms_Test_Name);
		GetFieldValue(_T("ms_Sub_Test_Name"), m_ms_Sub_Test_Name);
		GetFieldValue(_T("Minimum_standard_sub"), m_Minimum_standard_sub);
		GetFieldValue(_T("Min"), m_Min);
		GetFieldValue(_T("Max"), m_Max);
		GetFieldValue(_T("Range_ID"), m_Range_ID);
		GetFieldValue(_T("Notes"), m_Notes);
		GetFieldValue(_T("Section"), m_Section);
	}
	else
	{
		SetFieldValue(_T("Minimum_Standard_Name"), m_Minimum_Standard_Name);
		SetFieldValue(_T("ms_Test_Name"), m_ms_Test_Name);
		SetFieldValue(_T("ms_Sub_Test_Name"), m_ms_Sub_Test_Name);
		SetFieldValue(_T("Minimum_standard_sub"), m_Minimum_standard_sub);
		SetFieldValue(_T("Min"), m_Min);
		SetFieldValue(_T("Max"), m_Max);
		SetFieldValue(_T("Range_ID"), m_Range_ID);
		SetFieldValue(_T("Notes"), m_Notes);
		SetFieldValue(_T("Section"), m_Section);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMinimumStandardDB diagnostics
