// MessageIDToRecMap.h: interface for the CMessageIDToRecMap class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MESSAGEIDTORECMAP_H__CEE9250F_1EAB_44E6_92C1_DB7D2B8AB0B9__INCLUDED_)
#define AFX_MESSAGEIDTORECMAP_H__CEE9250F_1EAB_44E6_92C1_DB7D2B8AB0B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CUE_Rec;

class CMessageIDToRecMap : public CMap<int, int, CUE_Rec *, CUE_Rec *>  
{
public:
	void DeleteTree();
	
	CMessageIDToRecMap();
	virtual ~CMessageIDToRecMap();

};

#endif // !defined(AFX_MESSAGEIDTORECMAP_H__CEE9250F_1EAB_44E6_92C1_DB7D2B8AB0B9__INCLUDED_)
