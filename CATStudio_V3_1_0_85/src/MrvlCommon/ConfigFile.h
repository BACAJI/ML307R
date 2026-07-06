/*===============================================================================
* Copyright (C) 2008-2011 Marvell Technology Shanghai Ltd., HEFEI Branch.
* All right reserved.
*             
* File Name : ConfigFile.h
* Brief     : Header file of
* Version   : 1.0.0.1
* Author    : 
=================================================================================*/

#pragma once

#include <afxtempl.h>
#include "GeneralMacroDefine.h"

typedef struct StringVal
{
	CString strKey;
	CString strVal;
}sStringVal;


class CATCORE_DLLEXPORT CConfigFile : public CStdioFile 
{
public:
	CConfigFile();
	virtual ~CConfigFile();

	void SetTSFFile(bool bIsTSFFile);
	void SetFlashFile(bool bIsFlashFile);

	bool RemoveSection(LPCTSTR cSection);
	bool RemoveItem(LPCTSTR cSection, LPCTSTR cItem);

	bool SetValue(LPCTSTR cSection, LPCTSTR cItem, const COLORREF crVal);
	bool SetValue(LPCTSTR cSection, LPCTSTR cItem, const bool bVal);
	bool SetValue(LPCTSTR cSection, LPCTSTR cItem, LPCTSTR cVal);
	bool SetValue(LPCTSTR cSection, LPCTSTR cItem, const double dbVal);
	bool SetValue(LPCTSTR cSection, LPCTSTR cItem, const float fVal);
	bool SetValue(LPCTSTR cSection, LPCTSTR cItem, const long lVal);
	bool SetValue(LPCTSTR cSection, LPCTSTR cItem, const int iVal);
	bool SetValue(LPCTSTR cSection, LPCTSTR cItem, const CRect rcVal);
	bool SetValue(LPCTSTR cSection, LPCTSTR cItem, const CPoint ptVal);
	bool SetValue(LPCTSTR cSection, LPCTSTR cItem, UINT uiVal);

	bool GetValue(LPCTSTR cSection, LPCTSTR cItem, COLORREF &crVal);
	bool GetValue(LPCTSTR cSection, LPCTSTR cItem, CRect &rcVal);
	bool GetValue(LPCTSTR cSection, LPCTSTR cItem, CPoint &ptVal);
	bool GetValue(LPCTSTR cSection, LPCTSTR cItem, bool &bVal);
	bool GetValue(LPCTSTR cSection, LPCTSTR cItem, CString &cVal);
	bool GetValue(LPCTSTR cSection, LPCTSTR cItem, double &dbVal);
	bool GetValue(LPCTSTR cSection, LPCTSTR cItem, float &fVal);
	bool GetValue(LPCTSTR cSection, LPCTSTR cItem, long &lVal);
	bool GetValue(LPCTSTR cSection, LPCTSTR cItem, int &iVal);
	bool GetValue(LPCTSTR cSection, LPCTSTR cItem, UINT &uiVal);

	bool GetEntireSection(LPCTSTR cSection, CMapStringToString &cMap);
	bool SetEntireSection(LPCTSTR cSection, CMapStringToString &cMap);
	bool GetEntireSection(LPCTSTR cSection, CMap<CString, LPCTSTR, COLORREF, COLORREF> &cMap);
	bool SetEntireSection(LPCTSTR cSection, CMap<CString, LPCTSTR, COLORREF, COLORREF> &cMap);
	bool GetEntireSection(LPCTSTR cSection, CMap<DWORD, DWORD, COLORREF, COLORREF> &cMap);
	bool SetEntireSection(LPCTSTR cSection, CMap<DWORD, DWORD, COLORREF, COLORREF> &cMap);

	bool GetEntireSection(LPCTSTR cSection, CArray<sStringVal, sStringVal&> &cArrString);

	void RemoveAll();

	bool ReadUtf8(LPCTSTR cFileName);
	bool WriteUtf8(LPCTSTR cFileName);
#ifdef _UNICODE
	bool Read(LPCTSTR cFileName);
	bool Write(LPCTSTR cFileName);
#endif
	bool Read(LPCSTR cFileName);
	bool Write(LPCSTR cFileName);
   void GetAllSection(CStringArray& array);

private:
	CStringArray	m_Array;
	
	bool m_bIsTSFFile; //for support of TSF files.

	bool DoesSectionExist(const int iSection);
	int InsertSection(LPCTSTR cSection);
	int FindSection(LPCTSTR cSection);
	int FindItem(const int iSection, LPCTSTR cItem, CString &csVal);

};
