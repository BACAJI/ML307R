/*===============================================================================
* Copyright (C) 2008-2011 Marvell Technology Shanghai Ltd., HEFEI Branch.
* All right reserved.
*             
* File Name : widget.h
* Brief     : Header file of
* Version   : 1.0.0.1
* Author    : Hongliang
=================================================================================*/
#pragma once
#include <string>
#include <xstring>
using namespace std;

typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned short ushort;

#ifdef _UNICODE
typedef wstring tstring;
#else
typedef string  tstring;
#endif


//Remove blanks at the left of str.
inline void trimleft(string& str, char* delims=" \t")
{
  uint iStart(0);
  uint len(str.length());
  uint ndel(strlen(delims));

  if( ndel==0 ) return;

  for(; iStart<len; ++iStart)
  {
    uint j=0;
    while( j<ndel && str[iStart]!=delims[j] )
      ++j;

    if( j == ndel )
      break;
  }

  str.erase(0, iStart);

}

inline void trimright(string& str, char* delims=" \t")
{
  uint len(str.length());
  int  iStart(len-1);
  uint ndel(strlen(delims));

  if( ndel==0 ) return;

  for(; iStart>=0; --iStart)
  {
    uint j=0;
    while( j<ndel && str[iStart]!=delims[j] )
      ++j;

    if( j == ndel )
      break;
  }

  str.erase(iStart+1);

}

inline void trim(string& str, char* delims=" \t")
{
  trimleft(str);
  trimright(str);
}

inline void trimpathext(string& str)
{
  
  int iDotPos = str.rfind('.');



}


inline void Trim(CString& str)
{
  str.TrimLeft();
  str.TrimRight();
}

class CRLE
{
typedef unsigned char uchar;
public:
  inline void encode(uchar* data, int ndataLen, uchar* encData, int& nEncDataLen);
  inline void decode(uchar* encData, int nEncDataLen, uchar* decData, int& nDecDataLen);

};

void CRLE::encode(uchar* data, int ndataLen, uchar* encData, int& nEncDataLen)
{

  unsigned int runlen=1;
  unsigned char ch=data[0];
  runlen=1;
  nEncDataLen=0;

  if( !encData )
  {
    for(int i=1; i<ndataLen; ++i)
    {
      if(data[i]==ch && runlen<255 ) 
      {
        ++runlen;
        continue;
      }
      else
      {
        nEncDataLen +=2;
        ch = data[i];
        runlen = 1;
      }
    }

    nEncDataLen +=2;

    return ;
  }


  for(int i=1; i<ndataLen; ++i)
  {
    if(data[i]==ch && runlen<255 ) 
    {
      ++runlen;
      continue;
    }
    else
    {
      encData[nEncDataLen++] = (unsigned char) runlen;
      encData[nEncDataLen++] = ch;
      ch = data[i];
      runlen = 1;
    }
  }

  encData[nEncDataLen++]= (unsigned char)runlen;
  encData[nEncDataLen++]= ch;

}


void CRLE::decode(uchar* encData, int nEncDataLen, uchar* decData, int& nDecDataLen)
{
  nDecDataLen=0;

  if(!decData)
  {
    for(int i=0; i<nEncDataLen; i+=2)
      nDecDataLen += encData[i];
    return;
  }

  signed int runlen;
  for(int i=0; i<nEncDataLen; i+=2)
  {
    runlen=encData[i];
    do
    {
      decData[nDecDataLen++]=encData[i+1];
    }while(--runlen>0);
  }
}



class tissot
{
public:

  inline tissot();
  inline ~tissot(){};
  void	inline restart();
  uint	inline freqency();
  uint	inline elapsedmilli();
  uint	inline elapsedmicro();
  uint	inline elapsedticks();
  float inline compare();
  uint  inline substract();
  void  inline zerome();
  uint  inline static costtick();

  char  m_sztime[32];

private:
  LARGE_INTEGER m_nFreq;
  LARGE_INTEGER m_nStartTick;
  uint          m_nLastElapsed;
  uint          m_nElapsed;

};


tissot::tissot()
{
  m_nFreq.QuadPart=0;
  m_nElapsed = m_nLastElapsed = 0;
  QueryPerformanceFrequency(&m_nFreq);
  QueryPerformanceCounter(&m_nStartTick);
}

uint tissot::freqency()
{
  return m_nFreq.LowPart;
}

void tissot::restart()
{
  QueryPerformanceCounter(&m_nStartTick);
}

uint tissot::elapsedmilli()
{
  LARGE_INTEGER	nStopTick;
  QueryPerformanceCounter(&nStopTick);
  float fInterval = (float) (nStopTick.QuadPart - m_nStartTick.QuadPart);

  m_nLastElapsed = m_nElapsed;
  m_nElapsed = (uint) (fInterval*1000.0/m_nFreq.QuadPart);

  return  m_nElapsed;
}

uint tissot::elapsedmicro()
{
  LARGE_INTEGER	nStopTick;
  QueryPerformanceCounter(&nStopTick);
  double fInterval = (double) (nStopTick.QuadPart - m_nStartTick.QuadPart);

  m_nLastElapsed = m_nElapsed;
  m_nElapsed =(uint) (fInterval*1000000.0/m_nFreq.QuadPart);

  return  m_nElapsed;

}

uint tissot::elapsedticks()
{
  LARGE_INTEGER	nStopTick;
  QueryPerformanceCounter(&nStopTick);

  m_nLastElapsed = m_nElapsed;
  m_nElapsed =  (uint)(nStopTick.QuadPart - m_nStartTick.QuadPart);

  return (uint)(m_nElapsed);
}


float tissot::compare()
{
  return  m_nElapsed==0? 0 : m_nLastElapsed/(float)m_nElapsed;
}

uint tissot::substract()
{
  return m_nElapsed - m_nLastElapsed;
}

void tissot::zerome()
{
  m_nLastElapsed = m_nElapsed = 0;
  m_nStartTick.QuadPart = 0;
}

uint tissot::costtick()
{
  tissot timer;
  int iter=10000;
  uint cost=0;
  for(int i=0; i<iter; ++i)
  {
    timer.restart();
    cost +=timer.elapsedticks();
  }
  cost /=iter;

  return cost;

}


inline CString IntToString(int n)
{
  TCHAR buf[32]={0};
  _itot_s(n, buf, 31, 10);
  return CString(buf);
}

inline CString IntToString(UINT64 n)
{
  TCHAR buf[32]={0};
  _i64tot_s(n, buf, 31, 10);
  return CString(buf);

}

inline CString UintToString(UINT n)
{
  TCHAR buf[32];
  _itot_s(n, buf, 31, 10);
  return CString(buf);
}



inline CString AfxMessageBoxEx(UINT ui,  BOOL bShow = TRUE)
{
  CString str;
  str.Format(_T("%d"), ui);
  if( bShow )
    AfxMessageBox( str );
  return str;
}

inline CString AfxMessageBoxEx(LPCTSTR prefix, UINT ui, LPCTSTR suffix,  BOOL bShow = TRUE)
{
  CString str;
  str.Format(_T("%d"), ui);
  str = prefix + str + suffix;
  if( bShow )
    AfxMessageBox( str );
  return str;
}


inline CString AfxMessageBoxEx(float fl, BOOL bShow=TRUE)
{
  CString str;
  str.Format(_T("%f"), fl);
  if( bShow )
    AfxMessageBox( str );
  return str;
}

inline CString AfxMessageBoxEx(double fl, BOOL bShow=TRUE)
{
  CString str;
  str.Format(_T("%f"), fl);
  if( bShow )
    AfxMessageBox( str );
  return str;
}

inline CString AfxMessageBoxEx(LPCTSTR lpszText, BOOL bShow=TRUE)
{
  if( bShow )
    AfxMessageBox( lpszText );
  return CString(lpszText);
}

inline CString AfxMessageBoxEx(tstring str, BOOL bShow=TRUE)
{

#ifdef _UNICODE
  if( bShow )
    AfxMessageBox( str.c_str() );
  return CString( str.c_str() );

#else
  if( bShow )
    AfxMessageBox( str.c_str() );
  return CString( str.c_str() );
#endif

}


#define PRINT_NONE  0
#define PRINT_OPEN_FILE_FAILURE 1

template<typename T>
inline CString Printx(T inf, bool bShow=true)
{
  return AfxMessageBoxEx( inf, bShow );
}


