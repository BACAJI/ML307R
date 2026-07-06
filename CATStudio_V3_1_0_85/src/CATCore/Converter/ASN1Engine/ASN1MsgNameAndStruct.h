/*--------------------------------------------------------------------------------------------------------------------

 (C) Copyright 2006,2007 Marvell Semiconductor Israel Ltd. All Rights Reserved  

-------------------------------------------------------------------------------------------------------------------*/

// ASN1MsgNameAndStruct.h: interface for the CASN1MsgNameAndStruct class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ASN1MSGNAMEANDSTRUCT_H__9BD7C79A_7F7B_4D80_B874_9055D403F5B4__INCLUDED_)
#define AFX_ASN1MSGNAMEANDSTRUCT_H__9BD7C79A_7F7B_4D80_B874_9055D403F5B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef enum
{
	ASN1_MESSAGE_NAME = 0,
	ASN1_STRUCT_NAME = 1
} 
RequiredDataType;

class CASN1MsgNameAndStruct
{
public:
	CString m_Name;
	CString m_Struct;
#if _UNICODE
	CASN1MsgNameAndStruct(LPCTSTR name = NULL, LPCTSTR structName = NULL) 
#else
	CASN1MsgNameAndStruct(LPCSTR name = NULL, LPCSTR structName = NULL) 
#endif
		: m_Name(name), m_Struct(structName) {;}

	CASN1MsgNameAndStruct(CASN1MsgNameAndStruct& org)
		: m_Name(org.m_Name), m_Struct(org.m_Struct) {;}

	virtual ~CASN1MsgNameAndStruct();
};

#endif // !defined(AFX_ASN1MSGNAMEANDSTRUCT_H__9BD7C79A_7F7B_4D80_B874_9055D403F5B4__INCLUDED_)
