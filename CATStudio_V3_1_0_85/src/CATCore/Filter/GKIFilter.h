#pragma once
#include "iFilter.h"
//#include "..\..\..\..\MrvlCommon\CommonDefs.h" //Modified by hlguo 2012.3.19 to integrate variables define to one.

class CICATMessage;
class CGKIFilter : public IFFilter
{
public:
  CGKIFilter(void);
  virtual ~CGKIFilter(void);

  void    LoadFilter(){};
  void    SaveFilter(){};
  char*   GetFilter(){return NULL;};

  void    UpdateFilter(LPVOID lpCmdData, int nCmdDataLen);
  BOOL    IsPassFilter(CICATMessage* pMessage);
  BOOL    IsPassFilterSeries(CICATMessage* pMessage);

  DWORD   FindGKISignalID_DIAG(WORD diagSap, BYTE *pBuffer,int iLength);
  DWORD   FindGKISignalID_EMMI(BYTE signalType,BYTE *pBuffer,int iLength );
  DWORD   FindGKISignalID(BYTE *pBuffer, int iLength, BOOL bSide=kComm);
  DWORD   FindGKILoggedSignalID(BYTE *pBuffer, int iLength,BOOL bSide=kComm);
  DWORD   FindGKISpecialLoggedSignalID(BYTE *pBuffer,int iLength, BOOL bSide=kComm);

  char*   m_pFilter;
  UINT    m_nFilterSize;


};
