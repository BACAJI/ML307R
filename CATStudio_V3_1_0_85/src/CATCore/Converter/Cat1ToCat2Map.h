// Cat1ToCat2Map.h: interface for the CCat1ToCat2Map class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CAT1TOCAT2MAP_H__3486C778_F845_4B8C_BD79_D01ABC1EDE29__INCLUDED_)
#define AFX_CAT1TOCAT2MAP_H__3486C778_F845_4B8C_BD79_D01ABC1EDE29__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "Cat2ToCat3Map.h"


class CCat1ToCat2Map : public CMap <CString, LPCTSTR, CCat2ToCat3Map*, CCat2ToCat3Map*>  
{
public:
	CCat1ToCat2Map();
	virtual ~CCat1ToCat2Map();

	void DeleteTree();
};

#endif // !defined(AFX_CAT1TOCAT2MAP_H__3486C778_F845_4B8C_BD79_D01ABC1EDE29__INCLUDED_)
