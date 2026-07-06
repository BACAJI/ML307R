// Cat2ToCat3Map.h: interface for the CCat2ToCat3Map class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CAT2TOCAT3MAP_H__3486C778_F845_4B8C_BD79_D01ABC1EDE29__INCLUDED_)
#define AFX_CAT2TOCAT3MAP_H__3486C778_F845_4B8C_BD79_D01ABC1EDE29__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "Cat3ToRecMap.h"


class CCat2ToCat3Map : public CMap <CString, LPCTSTR, CCat3ToRecMap*, CCat3ToRecMap*>  
{
public:
	CCat2ToCat3Map();
	virtual ~CCat2ToCat3Map();

	void DeleteTree();
};

#endif // !defined(AFX_CAT2TOCAT3MAP_H__3486C778_F845_4B8C_BD79_D01ABC1EDE29__INCLUDED_)
