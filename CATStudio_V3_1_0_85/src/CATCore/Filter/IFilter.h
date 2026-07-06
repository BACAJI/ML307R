#pragma once


//class CICATMessage;
class IFFilter
{
public:
  IFFilter(void);
  virtual ~IFFilter(void);

  virtual void    LoadFilter()=0;
  virtual void    SaveFilter()=0;
  virtual char*   GetFilter()=0;

  virtual void    UpdateFilter(LPVOID lpCmdData, int nCmdDataLen)=0;
  virtual BOOL    IsPassFilter(class CICATMessage* pMessage)=0;
  virtual BOOL    IsPassFilterSeries(class CICATMessage* pMessage)=0;

  BOOL    m_bPassIfMSGIDNotFound;
  BOOL    m_bFilterUpdated;

};
