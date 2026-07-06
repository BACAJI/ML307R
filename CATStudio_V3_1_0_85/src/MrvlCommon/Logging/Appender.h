#pragma once
#include "HtmlData.h"

//===============================================================
// Appender
struct LogMessage; 
class Appender
{
public:
  Appender(){};
  virtual ~Appender(){};

  // Overrides. 
  virtual bool  InitAppender()=0;
  virtual void  Append( LogMessage& message ) = 0;
};

#if 0
class Appender
{
protected:
  // user code must call Delete method to destroy the object.
  virtual ~Appender() {};

public:
  Appender():m_nRefCount(1){
  }

  // Overrides. 
  virtual void  Append( LogMessage& message ) = 0;

  // User code must call this method to decrement reference.
  void  Delete() {
    if ( DecRef()==0 ) {
      delete this;
    }
  }

  // Increment. Return incremented value.
  long AddRef() {
    return InterlockedIncrement(&m_nRefCount);
  }

  // Decrement. Return decremented value.
  long DecRef() {
    return InterlockedDecrement(&m_nRefCount);
  }

private:
  long  m_nRefCount;

};
#endif

class FileAppender : public Appender
{
public:
  FileAppender(){};
  ~FileAppender(){};
  virtual bool InitAppender()=0; 
  virtual BOOL Open(LPCTSTR lpszFilename, OldFileDeletionFlag flag=DELETE_OLD_FILE)=0;
  virtual VOID Close()=0;
  virtual UINT GetLength()=0;

protected:
   OldFileDeletionFlag m_oldFileDeletionFlag;
#ifdef _UNICODE
   std::wstring m_filename;
#else
   std::string  m_filename;
#endif
};
