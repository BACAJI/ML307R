#pragma once
#include "Appender.h"
#include "SystemInfo.h"

class CTxtFileAppender : public FileAppender
{
public:
  CTxtFileAppender(LPCTSTR lpszFilename, OldFileDeletionFlag flag=DELETE_OLD_FILE);
  virtual ~CTxtFileAppender(void);

  virtual bool  InitAppender();
  virtual void  Append( LogMessage& message );
  virtual BOOL  Open(LPCTSTR lpszFilename, OldFileDeletionFlag flag=DELETE_OLD_FILE);
  virtual void  Close();
  virtual UINT  GetLength();

private:
  void  WriteFileHeader();
  void  WriteSystemInfo();
  File* m_pf;
};
