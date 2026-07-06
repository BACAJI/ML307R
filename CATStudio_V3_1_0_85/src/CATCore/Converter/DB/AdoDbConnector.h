
/*--------------------------------------------------------------------------------------------------------------------

 (C) Copyright 2006,2007 Marvell Semiconductor Israel Ltd. All Rights Reserved  

-------------------------------------------------------------------------------------------------------------------*/



/******************************************************************
**
** File: CAdoDbConnector.h
**
** Programmers: Oren Frenkel
**
**
** Description: This file contains the interface functions between XDEV
** and the DB.
**
**
** Revision history:
** -----------------
** Date             Developer        Version        Changes
**--------------------------------------------------------------
**			        Oren Frenkel.	  0.1
**
//*****************************************************************/



/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
$$
$$ Instructions :	call OpenDb to initialize the db connection.
$$					send it the path of the db, otherwise it will
$$					take the default path, as defined in the macro defines.
$$
$$					Afterwards, use Execute to execute a sql query.
$$					Then, use the global recordset to access it's members.
$$					if you don't close the db connection, it will be doneby
$$					the destructor.
$$
$$
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/


#include "ado.h"

#if !defined(AFX_XDEVDBCONNECTOR_H__58B16642_00A8_43E9_82FD_5CAD7EE14EAC__INCLUDED_)
#define AFX_XDEVDBCONNECTOR_H__58B16642_00A8_43E9_82FD_5CAD7EE14EAC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define		ADO_CONNECTION_STRING				"Provider=Microsoft.Jet.OLEDB.4.0;Data Source="

#define		VALIDATE_UPDATE				1
#define		VALIDATE_INSERT				2


// these error codes are also defined in XDEVStructures.h.
// they must be competable with the other error definitions there,
// if XDEV is being used.
#define		DB_YES							-1
#define		DB_NO							0
#define		ITEM_NOT_FOUND					-1

#define		DB_ERROR						-20
#define		DB_BAD_PATH_ERROR				-21
#define		DB_CANT_OPEN_ERROR				-22
#define		DB_IS_CLOSED_ERROR				-25
#define		DB_QUERY_EXECUTION_ERROR		-26
#define		DB_GET_FIELD_VAL_ERROR			-27
#define		DB_NO_ITEMS_FOUND_ERROR			-28
#define		DB_ITEM_ALREADY_EXISTS_ERROR	-29


#ifndef	NO_ERRORS

#define		NO_ERRORS					0

#endif // defined NO_ERORRS

#ifndef		INVALID_ARGUMENTS

#define		INVALID_ARGUMENTS			-4

#endif // INVALID_ARGUMENTS

class CATCORE_DLLEXPORT CAdoDbConnector
{
public:
	static CString GetICATExecutablePath();
	BOOL IsOpen();
	BOOL ApproveDbPath(const CString *strDbPath);

    CAdoDbConnector();
    virtual ~CAdoDbConnector();

	int OpenDb();
	int OpenDb(const CString *dbPath);

	void CloseDb();

	int GetNewKey(const CString *strTable,const CString *strField);

	BOOL Execute(const CString *sqlQuery);
	BOOL Execute(CString tableName/*=_T("")*/, const CStringList *pFieldsToView/*=NULL*/,const CString *filterField/*=NULL*/, const CString *strFilterVal/*=NULL*/);
	BOOL Execute(CString tableName/*=_T("")*/,const  CStringList *pFieldsToView/*=NULL*/,
				const CString *filterField/*=NULL*/, int iFilterVal/*=NULL*/);

	BOOL ActionExecute(CString * strSqlQuery);

	int Delete(CString tableName/*=_T("")*/, const CStringList *pFieldsToDelete/*=NULL*/,const CString *filterField/*=NULL*/,const CString *strFilterVal/*=NULL*/);
	int Delete (CString tableName/*=_T("")*/, const CStringList *pFieldsToDelete/*=NULL*/,const CString *filterField/*=NULL*/, int iFilterVal/*=NULL*/);

	int SqlInsert(CString * strTable, CStringArray *arrStringFields/*=NULL*/,CStringArray *arrStringVals/*=NULL*/,
				  CStringArray *arrIntFields/*=NULL*/,CUIntArray *arrIntVals/*=NULL*/);
	int SqlUpdate(CString * strTable, CStringArray *arrStringFields,CStringArray *arrStringVals,CStringArray *arrIntFields,CUIntArray *arrIntVals ,
	     		  CString * strFilterField,CString * strFilterVal/*=NULL*/,int *piFilterVal/*=NULL*/);
	int SqlUpdate(CString * strTable, CStringArray *arrStringFields,CStringArray *arrStringVals,CStringArray *arrIntFields,CUIntArray *arrIntVals ,
	     		  CString * strFilter);
	int SqlUpdate(CString * strTable, CString *strField, CString *p_strVal/*=NULL*/,int *p_iVal/*=NULL*/,double *p_dVal /*=NULL*/,
	     		  CString * strFilter);

	int UpdateDb();

	CString GetLastErrorString();

	bool IsEOF();
	void MoveFirst();
	void MoveNext();
	BOOL DbBoolToViBool(BOOL &dbVal);

	int RecordsetToUINTArray(const CString *strField, CUIntArray *intValArray);
	int RecordsetToStrArray( const CString *strField, CStringArray *strArray);
	int StrArrayToRecordset(const CStringArray *strArrFields, CPtrArray *pArrValues);

	CADORecordset *m_pAdoRec;


protected:


	inline int ValidateActionQueryArgs(int queryType,CString *strTable, CStringArray *arrStringFields,
									 CStringArray *arrStringVals, CStringArray *arrIntFields,
									 CUIntArray *arrIntVals, CString *strFilterField,
									 CString *strFilterVal, int *piFilterVal);
	inline int ValidateActionQueryArgs(CString * strTable, CString *strField, CString *p_strVal/*=NULL*/,int *p_iVal/*=NULL*/,
								  double *p_dVal /*=NULL*/,CString * strFilter);

	inline CString GetInsertQuery(CString * strTable, CStringArray *arrStringFields/*=NULL*/,
							  CStringArray *arrStringVals/*=NULL*/,CStringArray *arrIntFields/*=NULL*/,
							  CUIntArray *arrIntVals/*=NULL*/);
	inline 	int GetDeleteQuery(CString *strQuery, CString tableName/*=_T("")*/,const CStringList *pFieldsToDelete/*=NULL*/,
								  const CString *filterField/*=NULL*/,const CString *strFilterVal/*=NULL*/,const int *iFilterVal/*=NULL*/);
	inline 	BOOL GetSqlQuery(CString *strQuery,CString tableName/*=_T("")*/, const CStringList *pFieldsToView/*=NULL*/,
					 const CString *filterField/*=NULL*/,const CString *filterVal/*=NULL*/,int *iFilterVal/*=NULL*/);
	inline 	CString GetUpdateQuery(CString * strTable, CStringArray *arrStringFields,
							  CStringArray *arrStringVals,CStringArray *arrIntFields,
							  CUIntArray *arrIntVals ,CString * strFilterField,
							  CString * strFilterVal/*=NULL*/,int *piFilterVal/*=NULL*/);
	inline 	CString GetUpdateQuery(CString * strTable, CStringArray *arrStringFields,CStringArray *arrStringVals,CStringArray *arrIntFields,
										 CUIntArray *arrIntVals ,CString * strFilter);
	inline 	CString GetUpdateQuery(CString * strTable, CString *strField, CString *p_strVal/*=NULL*/,int *p_iVal/*=NULL*/,
								  double *p_dVal /*=NULL*/,CString * strFilter);

	CString m_strDbPath;
	CADODatabase *m_pAdoDb;

};

#endif // !defined(AFX_XDEVDBCONNECTOR_H__58B16642_00A8_43E9_82FD_5CAD7EE14EAC__INCLUDED_)
