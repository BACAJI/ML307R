#pragma once
#include "LoggingFile.h"

class CHtmlTagString
{
public:
  CHtmlTagString(CHtmlTagString* root, File* pf, CString* pString, int nRootPadding);
  virtual ~CHtmlTagString();
  
  void Write();
  void AddChild(CHtmlTagString* pChild);
  void RemoveChild();
  CHtmlTagString* GetRoot();
  CHtmlTagString* GetChild();

  int  GetBasePadding();
  int  GetLevel();
  CString  GetTagName();


  // Overrides
  virtual void AddHoriLine();
  virtual void AddData(LPCTSTR szData);
  virtual void Begin(LPCTSTR szName, LPCTSTR szProperty=NULL);
  virtual void End();

  virtual void BeginContent(){IncPadding();};
  virtual void EndContent(){DecPadding();};

  void AddComment(LPCTSTR szComment);
  void AddNewLine(){ NewLine();}
  void AddLineBreak(){AddString(_T("<br />"));};
  void IncPadding();
  
protected:
  
  void DecPadding();
  void NewLine();
  void AddString(LPCTSTR lpszString);
  void ClearString();
  CHtmlTagString* m_pRoot;
  File*    m_pf;
  CString* m_pString;
  int      m_nRootPadding;
  CString  m_sLinePadding;
  CString  m_sName;
  CHtmlTagString* m_pChild;

};


class CHtmlTable : public CHtmlTagString
{
public:
  CHtmlTable(CHtmlTagString* root, File* pf, CString* pString, int nRootPadding);
  virtual ~CHtmlTable();

  void BeginTable(LPCTSTR szProperty=NULL);
  void EndTable();
  void BeginRow(LPCTSTR sztrProperty=NULL);
  void EndRow();

  // Overrides
  virtual void AddData(LPCTSTR szData);
  virtual void Begin(LPCTSTR szName, LPCTSTR szProperty);
  virtual void End();


  void AddHeader(LPCTSTR szth, LPCTSTR szthProperty=NULL);
  void AddItem(LPCTSTR szItem, LPCTSTR sztdProperty=NULL);

private:
  int     m_nColumn;
  int     m_iCurCol;
};


class CHtmlString
{
public:
  CHtmlString(int nRootPadding);

  CString& GetString();
  void ClearString();
  void AddComment(LPCTSTR szComment);
  void AddNewLine(){NewLine();};
protected:
  void IncPadding();
  void DecPadding();
  void NewLine();
  void AddString(LPCTSTR lpszString);
  
  CString  m_String;
  CString  m_sLinePadding;
};

class CCss : public CHtmlString
{
public:
  CCss(int nRootPadding);
  ~CCss();

  void Begin(LPCTSTR szSelector);
  void End();

  void SetPaddingLeft(LPCTSTR sz);
  void SetPaddingRight(LPCTSTR sz);

  void SetTextAlign(LPCTSTR sz);

  void SetFont(LPCTSTR sz);
  void SetFontSize(LPCTSTR sz);
  void SetFontFamily(LPCTSTR sz);

  void SetLineHeight(LPCTSTR sz);

  void SetBorder(LPCTSTR sz);
  void SetBorderCollapse(LPCTSTR sz);

  void SetColor(LPCTSTR sz);
  void SetBackgroundColor(LPCTSTR sz);

  void SetWidth(LPCTSTR sz);

};