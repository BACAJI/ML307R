/*--------------------------------------------------------------------------------------------------------------------

 (C) Copyright 2006,2007 Marvell Semiconductor Israel Ltd. All Rights Reserved  

-------------------------------------------------------------------------------------------------------------------*/



// StringArrayEx.h: interface for the CStringArrayEx class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STRINGARRAYEX_H__AAF2A215_3260_4ED3_9E5C_F5DF19FC0DA3__INCLUDED_)
#define AFX_STRINGARRAYEX_H__AAF2A215_3260_4ED3_9E5C_F5DF19FC0DA3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class __declspec(dllexport) CStringArrayEx : public CStringArray  
{
public:
	CStringArrayEx();
	CStringArrayEx(CStringArrayEx &array);
	virtual ~CStringArrayEx();
	void operator = (CStringArrayEx &array);
	int Find (const CString& a_sSearchVal);
};

#endif // !defined(AFX_STRINGARRAYEX_H__AAF2A215_3260_4ED3_9E5C_F5DF19FC0DA3__INCLUDED_)
