#pragma once
#include "HtmlData.h"
#include "Appender.h"


class CHtmlAppender : public FileAppender
{
public:
  CHtmlAppender(LPCTSTR lpszFilename, OldFileDeletionFlag flag=DELETE_OLD_FILE);
  virtual ~CHtmlAppender(void);

  // Overrides
  virtual bool  InitAppender();
  virtual void  Append( LogMessage& message );

private:

  BOOL    Open(LPCTSTR lpszFilename, OldFileDeletionFlag flag=DELETE_OLD_FILE);
  void    Close();
  UINT    GetLength();
  void    FinalAppender();
  void    Begin();
  void    End();

  void    BeginLogMessage();
  void    EndLogMessage();



  CHtmlTagString* TheNode(){return m_pNode;};
  CHtmlTagString* NewBrotherNode();
  CHtmlTagString* NewChildNode();
  void  AddCSS();
  
private:
  File* m_pf;
  CString*  m_pString;
  CHtmlTagString*  m_pRootNode;
  CHtmlTagString*  m_pNode; // Current Node
  CString   m_sFileTitle;
  size_t    m_nAppended;
  size_t    m_nMaxSize;
  size_t    m_nFileNum;
  CString   m_strFilename;
};
