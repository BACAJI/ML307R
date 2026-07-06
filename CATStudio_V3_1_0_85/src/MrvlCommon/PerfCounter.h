#pragma once

class PerfCounter
{
public:
   PerfCounter(int cn=4);
   ~PerfCounter(void);

   void Start(int i=0);
   void Stop(int i=0);
   UINT GetSecond(int i=0);
   UINT GetMilli(int i=0);
   UINT GetMicro(int i=0);
   CString GetSecondString(int i=0);
   CString GetMilliString(int i=0);
   CString GetMicroString(int i=0);
   CString GetMilliMicroString(int i=0);
   double  Compare(int i, int j);

private:
   LARGE_INTEGER* m_StartCounter;
   LARGE_INTEGER* m_EndCounter;
   LARGE_INTEGER  m_PerfFreq;
   int            m_cn;
};
