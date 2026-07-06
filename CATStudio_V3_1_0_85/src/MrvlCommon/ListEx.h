/*--------------------------------------------------------------------------------------------------------------------

 (C) Copyright 2006,2007 Marvell Semiconductor Israel Ltd. All Rights Reserved  

-------------------------------------------------------------------------------------------------------------------*/



// ListEx.h: interface for the CListEx class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LISTEX_H__68DD8435_AF48_45F8_A09D_48EB91DF758A__INCLUDED_)
#define AFX_LISTEX_H__68DD8435_AF48_45F8_A09D_48EB91DF758A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>

template<class TYPE, class ARG_TYPE>
class CListEx : public CList <TYPE, ARG_TYPE> 
{
public:
	CListEx() :
	  CList<TYPE, ARG_TYPE>() { ; }

	virtual ~CListEx() { ; }

	ARG_TYPE GetAtIndex(int index)
	{
		ASSERT (index < GetCount());

		POSITION pos = FindIndex(index);
		return GetAt(pos);
	}

	void SetAtIndex(int index, ARG_TYPE arg)
	{
		ASSERT (index < GetCount());
	
		POSITION pos = FindIndex(index);
		SetAt(pos, arg);
	}

	ARG_TYPE RemoveAtIndex(int index)
	{
		ASSERT (index < GetCount());
	
		POSITION pos = FindIndex(index);
		ARG_TYPE arg = GetAt(pos);
		RemoveAt(pos);

		return arg;
	}

	void InsertAtIndex(int index, ARG_TYPE arg)
	{
		ASSERT (index <= GetCount());

		if ( index == GetCount() )
		{
			AddTail(arg);
			return;
		}

		CListEx<TYPE, ARG_TYPE> tempList;
		tempList.AddTail(this);
		RemoveAll();

		POSITION pos = tempList.GetHeadPosition();
		for (int i=0; i<tempList.GetCount(); i++)
		{
			if ( i == index )
				AddTail(arg);
			AddTail(tempList.GetNext(pos));
		}
		
	}

};

#endif // !defined(AFX_LISTEX_H__68DD8435_AF48_45F8_A09D_48EB91DF758A__INCLUDED_)
