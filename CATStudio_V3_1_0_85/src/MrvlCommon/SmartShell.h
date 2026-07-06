#pragma once


#define  LPOBJECT	(OBJECT*);


#include <afxtempl.h>


template<class OBJECT>
class SmartShell  
{
public:
	SmartShell(int nIndex = 0, OBJECT* pObject = NULL);
	~SmartShell();
	int  IsEmpty();
	BOOL IsAlive(int nIndex);
	void DestroyAt(int nItem);
	void Destruct();
	void Set(int nIndex, OBJECT* pObject);
	void SetSize(int nSize);
	int GetSize();
	OBJECT* operator [] (int nIndex);


private:
	CArray<OBJECT*, OBJECT*&> m_ObjectArray;
};


template <class OBJECT>
inline BOOL SmartShell<OBJECT>::IsAlive(int nIndex)
{
	if(nIndex < GetSize())
		return (m_ObjectArray[nIndex] != NULL);
	else
		return FALSE;
}


template <class OBJECT>
inline BOOL SmartShell<OBJECT>::IsEmpty()
{
	int rc, size = m_ObjectArray.GetSize();
	for ( int i = rc = 0; i < size; i ++ ){
		if ( m_ObjectArray[i] == NULL )
			rc++;
	}
	return (!size)? true:(size == rc)? true: false;
}


template <class OBJECT>
inline OBJECT* SmartShell<OBJECT>::operator [] (int nIndex)
{
	return m_ObjectArray[nIndex]; 
}


template <class OBJECT>
inline void SmartShell<OBJECT>::SetSize(int nSize)
{
	m_ObjectArray.SetSize(nSize);
}


template <class OBJECT>
inline int SmartShell<OBJECT>::GetSize()
{
	return m_ObjectArray.GetSize();
}


template <class OBJECT>
inline SmartShell<OBJECT>::SmartShell(int nIndex, OBJECT* pObject)
{
	m_ObjectArray.SetAtGrow( nIndex, pObject );
}	    


template <class OBJECT>
inline void SmartShell<OBJECT>::Set(int nIndex, OBJECT* pObject)
{
	m_ObjectArray.SetAtGrow( nIndex, pObject );
}


template <class OBJECT>
inline void SmartShell<OBJECT>::DestroyAt(int nItem)
{
	if(nItem < GetSize())
	{
		if ( m_ObjectArray[nItem] == NULL )
		return;

		delete m_ObjectArray[nItem];
		m_ObjectArray[nItem] = NULL;
	}
}


template <class OBJECT>
inline void SmartShell<OBJECT>::Destruct()
{
	int size = m_ObjectArray.GetUpperBound();

	for ( int i = 0; i <= size; i ++ ){
		DestroyAt(i);
	}

	m_ObjectArray.RemoveAll();
}


template <class OBJECT>
inline SmartShell<OBJECT>::~SmartShell()
{
	this->Destruct();
}

