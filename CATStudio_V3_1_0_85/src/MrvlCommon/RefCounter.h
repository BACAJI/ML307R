#pragma once

class __declspec (dllexport) RefCounter
{
public:
   RefCounter():m_nRefCount(1)
   {
   };

   // The function returns the resulting incremented value.
   int AddRef() 
   { 
      return InterlockedIncrement(&m_nRefCount); 
   }

   void Release() 
   {
      if(0==InterlockedDecrement(&m_nRefCount))
      {
         delete this;
      }
   }


protected:
   virtual ~RefCounter() {};

private:
   long  m_nRefCount;
};