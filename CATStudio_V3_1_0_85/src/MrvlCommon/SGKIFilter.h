#pragma once
#include "ISFilter.h"
#include "CommonDefs.h"
#include <map>
using namespace std;
class CICATMessage;
class CATCORE_DLLEXPORT CSGKIFilter : public ISFilter
{
public:
  CSGKIFilter(void);
  virtual ~CSGKIFilter(void);

  void    LoadFilter(){};
  void    SaveFilter(){};
  char*   GetFilter(){return NULL;};

  void    SetAllPass(bool bPass);
  long    UpdateFilter( LPVOID lpMessageIdBuffer, int nMsgIdCount, int nMsgIdSize, bool bLetItPass);
  BOOL    IsPassFilter(CICATMessage* pMessage);

  DWORD   FindGKISignalID_DIAG(WORD diagSap, BYTE *pBuffer,int iLength);
  DWORD   FindGKISignalID_EMMI(BYTE signalType,BYTE *pBuffer,int iLength );
  DWORD   FindGKISignalID(BYTE *pBuffer, int iLength, BOOL bSide=kComm);
  DWORD   FindGKILoggedSignalID(BYTE *pBuffer, int iLength,BOOL bSide=kComm);
  DWORD   FindGKISpecialLoggedSignalID(BYTE *pBuffer,int iLength, BOOL bSide=kComm);

  char*   m_pFilter;

  typedef unsigned short uint16;
  typedef unsigned long uint32;
  typedef char int8;
  map<uint32, int8>  m_mapFilter;
  typedef map<uint32, int8>::iterator iter_t;
  int    m_nAllPass;

  enum FILED_SIZE{ eTaskIdSize=2, eAlignPolicy=eAlignMinimum, eSignalIdSize=4, eEnumSize=eEnumSizeAsNeeded/* default is 0 */};

};

#define _USE_MAP_FILTER 