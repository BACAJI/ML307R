// Cat3ToRecMap.h: interface for the CCat3ToRecMap class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CAT3TORECMAP_H__7E394669_CE1E_4F4E_B99A_0F4B6B008AD3__INCLUDED_)
#define AFX_CAT3TORECMAP_H__7E394669_CE1E_4F4E_B99A_0F4B6B008AD3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//#include "UE_Rec.h"
#include "DiagCommDef.h"


//class CCat3ToRecMap : public CMap <CString, LPCTSTR, CUE_Rec*, CUE_Rec*>  
class CCat3ToRecMap : public CMap <CString, LPCTSTR, EnumValsRecord*, EnumValsRecord*>  
{
public:
	void DeleteTree();

	CCat3ToRecMap();
	virtual ~CCat3ToRecMap();

};

#endif // !defined(AFX_CAT3TORECMAP_H__7E394669_CE1E_4F4E_B99A_0F4B6B008AD3__INCLUDED_)
