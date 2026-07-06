#pragma once

class TaskBase
{
protected:
   virtual ~TaskBase() {
   };

public:
   enum TaskState{
      success = 0,
      executing,
      cancelled,
      timeout,
      failed
   };

   TaskBase() : m_nRef(1) {
   };

   void Delete() {
      if(0==InterlockedDecrement(&m_nRef))
         delete this;
   };

   int  AddRef() {
      return InterlockedIncrement(&m_nRef);
   }

   virtual void Execute()=0;
   virtual void Cancel()=0;
   virtual DWORD WaitTaskFinished(DWORD dwTimeout=INFINITE)=0;
   virtual TaskState  GetTaskState()=0;
private:
   long  m_nRef;
};

