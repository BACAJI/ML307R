#pragma once
#include "MrvlCommon/CommonDefs.h"
#include <vector>
#include <map>
using namespace std;

class CCacheStrTable
{
public:
	CCacheStrTable(void);
	~CCacheStrTable(void);
private:
	vector<CString> m_vTableList;
	long			m_nCurLineNo;
	vector<CString>::iterator m_iter;
	map<CString, sMdbTableItem> m_MapHeaderDBTable;
	CStdioFile m_txtFile;
public:
	CString MoveNext();
	CString MovePrev();
	CString MoveFirst();
	CString Move(long nMove);
	BOOL OpenFile( __in LPCTSTR lpFileName);
	BOOL IsEOF();
	BOOL IsBOF();
	BOOL OpenTable( __in LPCTSTR lpTableName);

	long GetPosition();
	CString SetPosition(long pos);
	CString MoveLast();
	//BOOL FindString(__in LPCTSTR lpName);
};
