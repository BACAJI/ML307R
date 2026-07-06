/*--------------------------------------------------------------------------------------------------------------------

 (C) Copyright 2006,2007 Marvell Semiconductor Israel Ltd. All Rights Reserved  

-------------------------------------------------------------------------------------------------------------------*/



#ifndef CSINGLETON_DESTROYER
#define CSINGLETON_DESTROYER 



//#include "IFLExport.h" 


template<class T>
class   CSingletonDestroyer
{
public:
    CSingletonDestroyer( T* = 0 );
    ~CSingletonDestroyer();

    void Set( T* );

private:
    // prevent users from making copies of the destroyer
    // to avoid double deletion..
    CSingletonDestroyer( const CSingletonDestroyer<T>& );
    CSingletonDestroyer<T>& operator=( const CSingletonDestroyer<T>& );

private:
    T *m_Doomed;
};

template <class T>
inline CSingletonDestroyer<T>::CSingletonDestroyer( T *doomed ) :
    m_Doomed( doomed )
{
}

template <class T>
inline void CSingletonDestroyer<T>::Set( T *doomed )
{
    m_Doomed = doomed;
}

template <class T>
inline CSingletonDestroyer<T>::~CSingletonDestroyer()
{
	if(m_Doomed)
	{
		delete m_Doomed;
		m_Doomed=NULL;
	}
}

// should never be called
template <class T>
inline CSingletonDestroyer<T>::CSingletonDestroyer( const CSingletonDestroyer<T>& )
{
    // for safety reasons
    m_Doomed = 0;
}


//{SABOIA-PORT 4.2->5.0} The 5.0 compiler does not like this 
// declaration. Nobody calls it, so we can safely comment it out.
#if 0
// should never be called
template <class T>
inline CSingletonDestroyer<T>::operator=( const CSingletonDestroyer<T>& )
{
    // for safety reasons
    m_Doomed = 0;
}
#endif

#endif
