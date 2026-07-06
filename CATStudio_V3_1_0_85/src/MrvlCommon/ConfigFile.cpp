#include "stdafx.h"
#include "ConfigFile.h"
#include <fcntl.h>
#include <io.h>
#include <locale.h>
#include <locale>
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CConfigFile::CConfigFile()
{
	m_bIsTSFFile = false;
}

CConfigFile::~CConfigFile()
{
	RemoveAll();
}

void CConfigFile::SetTSFFile(bool bIsTSFFile)
{
	m_bIsTSFFile = bIsTSFFile;
}

//#ifdef _IFL
void CConfigFile::SetFlashFile(bool bIsFlashFile)
{
	SetTSFFile(bIsFlashFile);
}
//#endif

bool CConfigFile::ReadUtf8(LPCTSTR cFileName)
{
	RemoveAll();

	if ( !Open(cFileName, CFile::modeRead|CFile::modeCreate|CFile::modeNoTruncate) )
		return false;
	
	_setmode(_fileno(m_pStream), _O_U8TEXT);

	CString line;	
	while ( ReadString(line) )
		m_Array.Add(line);
   
	Close();

	return true;
}

bool CConfigFile::Read(LPCTSTR cFileName)
{
	RemoveAll();

	if ( !Open(cFileName, CFile::modeRead|CFile::modeCreate|CFile::modeNoTruncate) )
		return false;
	
   lconv* lc0 = localeconv();//获得Locale信息
   std::locale::global(std::locale(""));//将全局区域设为操作系统默认区域

	CString line;	
	while ( ReadString(line) )
		m_Array.Add(line);
   
   lconv* lc = localeconv();//获得Locale信息
   std::locale::global(std::locale("C"));//还原全局区域设定

	Close();

	return true;
}

bool CConfigFile::Read( LPCSTR cFileName )
{
	CString _cFileName = CString(cFileName);
	return Read(_cFileName);
}

bool CConfigFile::WriteUtf8(LPCTSTR cFileName)
{
	ASSERT(cFileName);
	
   if ( !Open(cFileName, CFile::modeWrite|CFile::modeCreate/*|CFile::modeNoTruncate*/) )
		return false;
   
	_setmode(_fileno(m_pStream), _O_U8TEXT);

	int size = m_Array.GetSize();
	for (int i=0; i<size; i++)
		WriteString(m_Array.GetAt(i)+_T("\n") );
  
	Close();

	return true;
}

bool CConfigFile::Write(LPCTSTR cFileName)
{
	ASSERT(cFileName);
	
   if ( !Open(cFileName, CFile::modeWrite|CFile::modeCreate/*|CFile::modeNoTruncate*/) )
		return false;
   
   lconv* lc0 = localeconv();//获得Locale信息
   std::locale::global(std::locale(""));//将全局区域设为操作系统默认区域

	int size = m_Array.GetSize();
	for (int i=0; i<size; i++)
		WriteString(m_Array.GetAt(i)+_T("\n") );
  
   lconv* lc = localeconv();//获得Locale信息
   std::locale::global(std::locale("C"));//还原全局区域设定


	Close();

	return true;
}

bool CConfigFile::Write( LPCSTR cFileName )
{
	CString _cFileName = CString(cFileName);
	return Write(_cFileName);
}

// **********************************************************************************

void CConfigFile::RemoveAll()
{
	m_Array.RemoveAll();
}

// **********************************************************************************

int CConfigFile::FindSection(LPCTSTR cSection)
{
	int size = m_Array.GetSize();
	CString csSection, strListItem;
	csSection.Format(_T("[%s]"), cSection);

	for (int t = 0; t < size; t++)
	{
		strListItem = m_Array.GetAt(t); 
		if (strListItem == csSection) 
			return t;
	}
	return -1;
}

int CConfigFile::InsertSection(LPCTSTR cSection)
{
	ASSERT(cSection);
	if (!cSection) return -1;

	int idx = FindSection(cSection);
	if (idx < 0)
	{
		CString csSection;
		csSection.Format(_T("[%s]"), cSection);
		idx = m_Array.Add(csSection);
	}
	return idx;
}

int CConfigFile::FindItem(const int iSection, LPCTSTR cItem, CString &csVal)
{
	ASSERT(iSection >= 0);
	ASSERT(cItem);

	int size = m_Array.GetSize();
	CString csItem(cItem), csLook;
	if(m_bIsTSFFile)
		csItem += "=";
	else
		csItem += " = ";
	int iLen = csItem.GetLength();

	for (int t = iSection; t < size; t++)
	{
		if (!DoesSectionExist(t))
		{
			csLook = m_Array.GetAt(t);
			if (csLook.GetLength() >= iLen)
			{
				if (csLook.Left(iLen) == csItem) 
				{
					if (csLook.GetLength() == iLen) csVal = "";
					else csVal = csLook.Right(csLook.GetLength() - iLen);
					return t;
				}
			}
		}
		else return -1;
	}
	return -1;
}

bool CConfigFile::DoesSectionExist(const int iSection)
{
	ASSERT(iSection >= 0 && iSection < m_Array.GetSize());
	if (iSection >= 0 && iSection < m_Array.GetSize())
	{
		CString csItem = m_Array.GetAt(iSection);
		if (csItem.GetLength() > 2)
			if (csItem.GetAt(0) == '[')
				if (csItem.GetAt(csItem.GetLength()-1) == ']') 
					return true;
	}
	return false;
}

bool CConfigFile::RemoveSection(LPCTSTR cSection)
{
	int idx = FindSection(cSection);
	if (idx >= 0)
	{
		for (;;)
		{
			m_Array.RemoveAt(idx);
			if (idx >= m_Array.GetSize()) return true;
			if (DoesSectionExist(idx)) return true;
		}
	}
	return true;
}

bool CConfigFile::RemoveItem(LPCTSTR cSection, LPCTSTR cItem)
{
	ASSERT(cSection);
	ASSERT(cItem);

	int idx = FindSection(cSection);
	if ( idx > -1 )
	{
		CString csVal;
		int iIdx = FindItem(idx+1, cItem, csVal);
		if ( iIdx >= 0 )
		{
			m_Array.RemoveAt(iIdx);
			return true;
		}
	}
	return false;
}

// **********************************************************************************

bool CConfigFile::SetValue(LPCTSTR cSection, LPCTSTR cItem, const bool bVal)
{
	int idx = InsertSection(cSection);
	if (idx >= 0)
	{
		CString csVal;
		int iIdx = FindItem(idx+1, cItem, csVal);
		csVal.Format(_T("%s = %s"), cItem, bVal ? _T("true") : _T("false"));
		if (iIdx >= 0) m_Array.SetAt(iIdx, csVal);
		else m_Array.InsertAt(idx+1, csVal);
		return true;
	}
	return false;
}

bool CConfigFile::SetValue(LPCTSTR cSection, LPCTSTR cItem, const COLORREF crVal)
{
	int idx = InsertSection(cSection);
	if (idx >= 0)
	{
		CString csVal;
		int iIdx = FindItem(idx+1, cItem, csVal);
		csVal.Format(_T("%s = %d"), cItem, (DWORD) crVal);
		if (iIdx >= 0) m_Array.SetAt(iIdx, csVal);
		else m_Array.InsertAt(idx+1, csVal);
		return true;
	}
	return false;
}

bool CConfigFile::SetValue(LPCTSTR cSection, LPCTSTR cItem, LPCTSTR cVal)
{
	int idx = InsertSection(cSection);
	if (idx >= 0)
	{
		CString csVal;
		int iIdx = FindItem(idx+1, cItem, csVal);
		if(m_bIsTSFFile)
			csVal.Format(_T("%s=%s"), cItem, cVal);
		else
			csVal.Format(_T("%s = %s"), cItem, cVal);
		if (iIdx >= 0) m_Array.SetAt(iIdx, csVal);
		else m_Array.InsertAt(idx+1, csVal);
		return true;
	}
	return false;
}

bool CConfigFile::SetValue(LPCTSTR cSection, LPCTSTR cItem, const double dbVal)
{
	int idx = InsertSection(cSection);
	if (idx >= 0)
	{
		CString csVal;
		int iIdx = FindItem(idx+1, cItem, csVal);
		csVal.Format(_T("%s = %f"), cItem, dbVal);
		if (iIdx >= 0) m_Array.SetAt(iIdx, csVal);
		else m_Array.InsertAt(idx+1, csVal);
		return true;
	}
	return false;
}

bool CConfigFile::SetValue(LPCTSTR cSection, LPCTSTR cItem, UINT uiVal)
{
	int idx = InsertSection(cSection);
	if (idx >= 0)
	{
		CString csVal;
		int iIdx = FindItem(idx+1, cItem, csVal);
		csVal.Format(_T("%s = %u"), cItem, uiVal);
		if (iIdx >= 0) m_Array.SetAt(iIdx, csVal);
		else m_Array.InsertAt(idx+1, csVal);
		return true;
	}
	return false;
}
bool CConfigFile::SetValue(LPCTSTR cSection, LPCTSTR cItem, const float fVal)
{
	int idx = InsertSection(cSection);
	if (idx >= 0)
	{
		CString csVal;
		int iIdx = FindItem(idx+1, cItem, csVal);
		csVal.Format(_T("%s = %f"), cItem, fVal);
		if (iIdx >= 0) m_Array.SetAt(iIdx, csVal);
		else m_Array.InsertAt(idx+1, csVal);
		return true;
	}
	return false;
}

bool CConfigFile::SetValue(LPCTSTR cSection, LPCTSTR cItem, const long lVal)
{
	int idx = InsertSection(cSection);
	if (idx >= 0)
	{
		CString csVal;
		int iIdx = FindItem(idx+1, cItem, csVal);
		csVal.Format(_T("%s = %d"), cItem, lVal);
		if (iIdx >= 0) m_Array.SetAt(iIdx, csVal);
		else m_Array.InsertAt(idx+1, csVal);
		return true;
	}
	return false;
}

bool CConfigFile::SetValue(LPCTSTR cSection, LPCTSTR cItem, const int iVal)
{
	int idx = InsertSection(cSection);
	if (idx >= 0)
	{
		CString csVal;
		int iIdx = FindItem(idx+1, cItem, csVal);
		csVal.Format(_T("%s = %d"), cItem, iVal);
		if (iIdx >= 0) m_Array.SetAt(iIdx, csVal);
		else m_Array.InsertAt(idx+1, csVal);
		return true;
	}
	return false;
}


bool CConfigFile::SetValue(LPCTSTR cSection, LPCTSTR cItem, const CRect rcVal)
{
	int idx = InsertSection(cSection);
	if (idx >= 0)
	{
		CString csVal;
		int iIdx = FindItem(idx+1, cItem, csVal);
		csVal.Format(_T("%s = RECT(%d,%d,%d,%d)"), cItem, rcVal.left, rcVal.top, rcVal.right, rcVal.bottom);
		if (iIdx >= 0) m_Array.SetAt(iIdx, csVal);
		else m_Array.InsertAt(idx+1, csVal);
		return true;
	}
	return false;
}

bool CConfigFile::SetValue(LPCTSTR cSection, LPCTSTR cItem, const CPoint ptVal)
{
	int idx = InsertSection(cSection);
	if (idx >= 0)
	{
		CString csVal;
		int iIdx = FindItem(idx+1, cItem, csVal);
		csVal.Format(_T("%s = POINT(%d,%d)"), cItem, ptVal.x, ptVal.y);
		if (iIdx >= 0) m_Array.SetAt(iIdx, csVal);
		else m_Array.InsertAt(idx+1, csVal);
		return true;
	}
	return false;
}


// **********************************************************************************

bool CConfigFile::GetValue(LPCTSTR cSection, LPCTSTR cItem, COLORREF &crVal)
{
	int idx = FindSection(cSection);
	if (idx >= 0)
	{
		CString csVal;
		if (FindItem(idx+1, cItem, csVal) > 0)
		{
			crVal = (COLORREF) (DWORD) _ttol(csVal);
			return true;
		}
	}
	return false;
}

bool CConfigFile::GetValue(LPCTSTR cSection, LPCTSTR cItem, bool &bVal)
{
	int idx = FindSection(cSection);
	if (idx >= 0)
	{
		CString csVal;
		if (FindItem(idx+1, cItem, csVal) > 0)
		{
			if (csVal.Find(_T("true")) >= 0) bVal = true; else bVal = false;
			return true;
		}
	}
	return false;
}

bool CConfigFile::GetValue(LPCTSTR cSection, LPCTSTR cItem, CString &cVal)
{
	int idx = FindSection(cSection);
	if (idx >= 0)
	{
		if (FindItem(idx+1, cItem, cVal) > 0)
			return true;
	}
	return false;
}

bool CConfigFile::GetValue(LPCTSTR cSection, LPCTSTR cItem, double &dbVal)
{
	int idx = FindSection(cSection);
	if (idx >= 0)
	{
		CString csVal;
		if (FindItem(idx+1, cItem, csVal) > 0)
		{
			dbVal = (double) _tstof(csVal);
			return true;
		}
	}
	return false;
}

bool CConfigFile::GetValue(LPCTSTR cSection, LPCTSTR cItem, float &fVal)
{
	int idx = FindSection(cSection);
	if (idx >= 0)
	{
		CString csVal;
		if (FindItem(idx+1, cItem, csVal) > 0)
		{
			fVal = (float) _tstof(csVal);
			return true;
		}
	}
	return false;
}

bool CConfigFile::GetValue(LPCTSTR cSection, LPCTSTR cItem, long &lVal)
{
	int idx = FindSection(cSection);
	if (idx >= 0)
	{
		CString csVal;
		if (FindItem(idx+1, cItem, csVal) > 0)
		{
			lVal = (long) _ttol(csVal);
			return true;
		}
	}
	return false;
}

bool CConfigFile::GetValue(LPCTSTR cSection, LPCTSTR cItem, int &iVal)
{
	int idx = FindSection(cSection);
	if (idx >= 0)
	{
		CString csVal;
		if (FindItem(idx+1, cItem, csVal) > 0)
		{
			iVal = (int) _ttoi(csVal);
			return true;
		}
	}
	return false;
}

bool CConfigFile::GetValue(LPCTSTR cSection, LPCTSTR cItem, CRect &rcVal)
{
	int idx = InsertSection(cSection);
	if (idx >= 0)
	{
		CString csVal;
		if (FindItem(idx+1, cItem, csVal) > 0)
		{
			TCHAR * pt = csVal.LockBuffer();
			int pf, t = 0, l = 0, r = 0, b = 0;
			pf = _stscanf_s(csVal, _T("RECT(%d,%d,%d,%d)"), &l, &t, &r, &b);
			ASSERT(pf == 4);
			csVal.UnlockBuffer();
			rcVal.SetRect(l, t, r, b);
			return true;
		}
	}
	return false;
}

bool CConfigFile::GetValue(LPCTSTR cSection, LPCTSTR cItem, CPoint &ptVal)
{
	int idx = InsertSection(cSection);
	if (idx >= 0)
	{
		CString csVal;
		if (FindItem(idx+1, cItem, csVal) > 0)
		{
			TCHAR * pt = csVal.LockBuffer();
			int pf, x = 0, y = 0;
			pf = _stscanf_s(csVal, _T("POINT(%d,%d)"), &x, &y);
			ASSERT(pf == 2);
			csVal.UnlockBuffer();
			ptVal.x = x;
			ptVal.y = y;
			return true;
		}
	}
	return false;
}

bool CConfigFile::GetValue(LPCTSTR cSection, LPCTSTR cItem, UINT &uiVal)
{
	int idx = FindSection(cSection);
	if (idx >= 0)
	{
		CString csVal;
		if (FindItem(idx+1, cItem, csVal) > 0)
		{
			uiVal = (UINT) _ttoi(csVal);
			return true;
		}
	}
	return false;
}

bool CConfigFile::GetEntireSection(LPCTSTR cSection, CMapStringToString &cMap)
{
	cMap.RemoveAll();

	int idx = FindSection(cSection), size = m_Array.GetSize();
	if (idx >= 0)
	{
		CString csItem, csVal, csLine;

		for (idx+=1; idx<size; idx++)
		{
			if (idx >= m_Array.GetSize()) break;
			if (DoesSectionExist(idx)) break;
				
			csLine = m_Array.GetAt(idx);
			if (csLine.GetLength() < 5) continue;

			int t;
			if(m_bIsTSFFile)
				t = csLine.Find(_T("="));
			else
				t = csLine.Find(_T(" = "));
			if (t < 1) continue;
			csItem = csLine.Left(t);
			if(m_bIsTSFFile)
				csVal = csLine.Mid(t+1);
			else
				csVal = csLine.Mid(t+3);
			cMap.SetAt(csItem, csVal);
		}		
		return true;
	}
	return false;
}

bool CConfigFile::SetEntireSection(LPCTSTR cSection, CMapStringToString &cMap)
{
	RemoveSection(cSection);

	int idx = InsertSection(cSection);
	if (idx >= 0)
	{	
		CString csVal, csKey, csLine;
		int iIdx = idx+1; // FindItem(idx+1, cItem, csVal);
		
		for ( POSITION pos = cMap.GetStartPosition(); pos != NULL; )
		{
			cMap.GetNextAssoc(pos, csKey, csVal);
			csLine.Format(_T("%s = %s"), csKey, csVal);
			m_Array.InsertAt(iIdx++, csLine);
		}
		
		return true;
	}
	return false;
}


bool CConfigFile::GetEntireSection(LPCTSTR cSection, CMap<CString, LPCTSTR, COLORREF, COLORREF> &cMap)
{
	cMap.RemoveAll();
	
	int idx = FindSection(cSection), size = m_Array.GetSize();
	if (idx >= 0)
	{
		CString csItem, csVal, csLine;
		COLORREF clrVal;

		for (idx+=1; idx<size; idx++)
		{
			if (idx >= m_Array.GetSize()) break;
			if (DoesSectionExist(idx)) break;
				
			csLine = m_Array.GetAt(idx);
			if (csLine.GetLength() < 5) continue;

			int t = csLine.Find(_T(" = "));
			if (t < 1) continue;
			csItem = csLine.Left(t);
			csVal = csLine.Mid(t+3);
			clrVal = (COLORREF)_ttol(csVal);
			cMap.SetAt(csItem, clrVal);
		}		
		return true;
	}
	return false;
}


bool CConfigFile::SetEntireSection(LPCTSTR cSection, CMap<CString, LPCTSTR, COLORREF, COLORREF> &cMap)
{
	RemoveSection(cSection);

	int idx = InsertSection(cSection);
	if (idx >= 0)
	{	
		CString csVal, csKey;
		COLORREF clrVal;
		int iIdx = idx+1; // FindItem(idx+1, cItem, csVal);
		
		for ( POSITION pos = cMap.GetStartPosition(); pos != NULL; )
		{
			cMap.GetNextAssoc(pos, csKey, clrVal);
			csVal.Format(_T("%s = %d"), csKey, (DWORD)clrVal);	
			m_Array.InsertAt(iIdx++, csVal);
		}
		
		return true;
	}
	return false;
}


bool CConfigFile::GetEntireSection(LPCTSTR cSection, CMap<DWORD, DWORD, COLORREF, COLORREF> &cMap)
{
	cMap.RemoveAll();

	int idx = FindSection(cSection), size = m_Array.GetSize();
	if (idx >= 0)
	{
		CString csItem, csVal, csLine;
		COLORREF clrVal;
		DWORD dwItem;

		for (idx+=1; idx<size; idx++)
		{
			if (idx >= m_Array.GetSize()) break;
			if (DoesSectionExist(idx)) break;
				
			csLine = m_Array.GetAt(idx);
			if (csLine.GetLength() < 5) continue;

			int t = csLine.Find(_T(" = "));
			if (t < 1) continue;
			csItem = csLine.Left(t);
			dwItem = _ttol(csItem);
			csVal = csLine.Mid(t+3);
			clrVal = (COLORREF)_ttol(csVal);
			cMap.SetAt(dwItem, clrVal);
		}		
		return true;
	}
	return false;
}


bool CConfigFile::SetEntireSection(LPCTSTR cSection, CMap<DWORD, DWORD, COLORREF, COLORREF> &cMap)
{
	RemoveSection(cSection);

	int idx = InsertSection(cSection);
	if (idx >= 0)
	{	
		CString csVal, csKey;
		COLORREF clrVal;
		DWORD dwItem;
		int iIdx = idx+1; // FindItem(idx+1, cItem, csVal);
		
		for ( POSITION pos = cMap.GetStartPosition(); pos != NULL; )
		{
			cMap.GetNextAssoc(pos, dwItem, clrVal);
			csKey.Format(_T("%lu"), dwItem);
			csVal.Format(_T("%s = %d"), csKey, (DWORD)clrVal);	
			m_Array.InsertAt(iIdx++, csVal);
		}
		
		return true;
	}
	return false;
}


bool CConfigFile::GetEntireSection(LPCTSTR cSection, CArray<sStringVal, sStringVal&> &cArrString)
{
	cArrString.RemoveAll();
	sStringVal strVal;

	int idx = FindSection(cSection), size = m_Array.GetSize();
	if (idx >= 0)
	{
		CString csItem, csVal, csLine;

		for (idx+=1; idx<size; idx++)
		{
			if (idx >= m_Array.GetSize()) break;
			if (DoesSectionExist(idx)) break;
				
			csLine = m_Array.GetAt(idx);
			if (csLine.GetLength() < 5) continue;

			int t;
			if(m_bIsTSFFile)
				t = csLine.Find(_T("="));
			else
				t = csLine.Find(_T(" = "));
			if (t < 1) continue;
			csItem = csLine.Left(t);
			if(m_bIsTSFFile)
				csVal = csLine.Mid(t+1);
			else
				csVal = csLine.Mid(t+3);
			strVal.strKey = csItem;
			strVal.strVal = csVal;
			cArrString.Add(strVal);
		}		
		return true;
	}
	return false;
}

void CConfigFile::GetAllSection( CStringArray& array )
{
   for (int i=0; i<m_Array.GetSize(); ++i)
   {
      const CString& strTemp = m_Array.GetAt(i);
      array.Add(strTemp);
   }
}
