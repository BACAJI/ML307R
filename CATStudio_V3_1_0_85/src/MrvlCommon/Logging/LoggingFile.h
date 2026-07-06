#pragma once
#include <fstream>



enum OldFileDeletionFlag{
  DELETE_OLD_FILE,
  APPEND_TO_OLD_FILE
};

class File
{
public:
  File(){};
  virtual ~File(){};
  virtual BOOL Open(LPCTSTR lpszName, OldFileDeletionFlag flag=DELETE_OLD_FILE)=0;
  virtual void Close()=0;
  virtual UINT Read(void* lpBuf, UINT nBytes)=0;
  virtual UINT Write(void* lpBytes, UINT nBytes)=0;
  virtual UINT GetLength()=0;
};

class CStlFile : public File
{
public:

  CStlFile() {
  };

  ~CStlFile() {
  };

  BOOL Open(LPCTSTR lpszName, OldFileDeletionFlag flag=DELETE_OLD_FILE) {
    try{
      std::ios_base::openmode mode = std::ios_base::in|std::ios_base::out;
      mode |=flag==DELETE_OLD_FILE? 0:std::ios_base::app;
      m_Impl.open(lpszName, mode);
    }
    catch (...)
    {
      return FALSE;
    }
    return m_Impl.fail()? FALSE:TRUE;
  };

  void Close(){
    m_Impl.close();
  }

  UINT Write(void* lpBuf, UINT nBytes) {
    m_Impl.write((const char*)lpBuf, nBytes);
    return nBytes;
  };

  UINT Read(void* lpBuf, UINT nBytes) {
    m_Impl.read((char*)lpBuf, nBytes);
    return (UINT)m_Impl.gcount();
  }

  UINT GetLength() { return 0; }

private:
  std::fstream m_Impl;
};


class CMfcFile : public File
{
public:
  CMfcFile() {
  };

  ~CMfcFile() {
  };

  BOOL Open(LPCTSTR lpszName, OldFileDeletionFlag flag=DELETE_OLD_FILE) {
     UINT openFlags = CFile::modeCreate|CFile::modeReadWrite|CFile::shareDenyWrite;
    openFlags |= flag==DELETE_OLD_FILE? 0:CFile::modeNoTruncate;
    openFlags |= CFile::modeNoInherit;
    return m_Impl.Open(lpszName, openFlags);
  };

  void Close(){
    m_Impl.Close();
  }

  UINT Write(void* lpBuf, UINT nBytes) {
    m_Impl.Write(lpBuf, nBytes);
    return nBytes;
  };

  UINT Read(void* lpBuf, UINT nBytes) {
    return m_Impl.Read(lpBuf, nBytes);
  }

  UINT GetLength() {
    return (UINT)m_Impl.GetLength();
  }

private:
  CFile m_Impl;
};
