// TokensMap.h: interface for the CTokensMap class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TOKENSMAP_H__E3C3AB09_E49B_461C_8908_84BC768A32A9__INCLUDED_)
#define AFX_TOKENSMAP_H__E3C3AB09_E49B_461C_8908_84BC768A32A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef UNICODE				//Richard added for fixing the error of "SetAt" 2012-01-05
class CTokensMap : public CMap<INT64, INT64, CString, LPCWSTR>
#else
class CTokensMap : public CMap<INT64, INT64, CString, LPCSTR>
#endif
{
public:
	CTokensMap();
	virtual ~CTokensMap();

};

#endif // !defined(AFX_TOKENSMAP_H__E3C3AB09_E49B_461C_8908_84BC768A32A9__INCLUDED_)
