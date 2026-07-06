// UeHwComponentsDB.cpp: implementation of the CUeHwComponentsDB class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UeHwComponentsDB.h"
#include "ApplicationINI.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUeHwComponentsDB::CUeHwComponentsDB()
{
	m_Component_Serial_ID = 0;
	m_Batch_Result_ID = 0;
	m_Batch_Iteration = 0;
	m_Conf_Name = _T("");
	m_Board_Serial_Number = _T("");
	m_Board_Name = _T("");
	m_Board_Version = _T("");
	m_Board_ECO = _T("");
}

CUeHwComponentsDB::~CUeHwComponentsDB()
{
	if ( IsOpen() )
		Close();
}

CString CUeHwComponentsDB::GetDefaultDBName()
{

	if ( AppIni()->GetProfileInt(_T("TestEngineSettings"), _T("DatabaseType"), 0) == 1 )
		return AppIni()->GetProfileString(_T("TestEngineSettings"), _T("DatabasePath"), _T(""));

	return AppPath() + _T("\\DB\\TestResults.mdb");
}

CString CUeHwComponentsDB::GetDefaultSQL()
{
	return _T("[TB_UE_HW_Components_Serial]");
}

void CUeHwComponentsDB::DoFieldExchange(BOOL bLoad/*=TRUE*/)
{
	if ( bLoad )
	{
		GetFieldValue(_T("Component_Serial_ID"), m_Component_Serial_ID);
		GetFieldValue(_T("Batch_Result_ID"), m_Batch_Result_ID);
		GetFieldValue(_T("Batch_Iteration"), m_Batch_Iteration);
		GetFieldValue(_T("Conf_Name"), m_Conf_Name);
		GetFieldValue(_T("Board_Serial_Number"), m_Board_Serial_Number);
		GetFieldValue(_T("Board_Name"), m_Board_Name);
		GetFieldValue(_T("Board_Version"), m_Board_Version);
		GetFieldValue(_T("Board_ECO"), m_Board_ECO);
	}
	else
	{
		SetFieldValue(_T("Component_Serial_ID"), m_Component_Serial_ID);
		SetFieldValue(_T("Batch_Result_ID"), m_Batch_Result_ID);
		SetFieldValue(_T("Batch_Iteration"), m_Batch_Iteration);
		SetFieldValue(_T("Conf_Name"), m_Conf_Name);
		SetFieldValue(_T("Board_Serial_Number"), m_Board_Serial_Number);
		SetFieldValue(_T("Board_Name"), m_Board_Name);
		SetFieldValue(_T("Board_Version"), m_Board_Version);
		SetFieldValue(_T("Board_ECO"), m_Board_ECO);
	}
}
