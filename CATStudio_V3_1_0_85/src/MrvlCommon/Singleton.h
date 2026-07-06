#pragma once

template<class T>
class CSingleton
{
public:
    CSingleton();
    ~CSingleton();

	T& GetObj();

private:
    // prevent users from making copies of the singleton to avoid double deletion.
    CSingleton(const CSingleton<T>&);
    CSingleton<T>& operator= (const CSingleton<T>& );

private:
    T* m_pObject;
	CRITICAL_SECTION m_CritSec;
};

template <class T>
inline CSingleton<T>::CSingleton() 
: m_pObject(NULL)
{
	InitializeCriticalSection(&m_CritSec);
}

template <class T>
inline T& CSingleton<T>::GetObj()
{
	if ( m_pObject == NULL )
	{
		EnterCriticalSection(&m_CritSec);

		if ( m_pObject == NULL )
		{
#ifdef _DEBUG
			m_pObject = DEBUG_NEW T;
#else
			m_pObject = new T;
#endif
		}

		LeaveCriticalSection(&m_CritSec);
	}

	return (*m_pObject);
}

template <class T>
inline CSingleton<T>::~CSingleton()
{
	delete m_pObject;
	DeleteCriticalSection(&m_CritSec);
}


#define DECLARE_SINGLETON(class_name)				\
	private:										\
		static CSingleton<class_name> m_Singleton;	\
		friend class CSingleton<class_name>;		\
		class_name(const class_name&);				\
		class_name& operator= (const class_name&);	\
	public:											\
		static class_name& Instance();				


#define IMPLEMENT_SINGLETON(class_name)				\
	CSingleton<class_name> class_name::m_Singleton; \
	class_name& class_name::Instance() 	{ return m_Singleton.GetObj(); }	