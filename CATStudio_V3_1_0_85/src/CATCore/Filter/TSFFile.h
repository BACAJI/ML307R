/*--------------------------------------------------------------------------------------------------------------------

 (C) Copyright 2006,2007 Marvell Semiconductor Israel Ltd. All Rights Reserved  

-------------------------------------------------------------------------------------------------------------------*/



#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ConfigFile.h"

//IFLVC9_Inc_Export_H_Begin************************************
//#include "..\IFLExport.h" 
//IFLVC9_Inc_Export_H_End**************************************

enum TextMode
{	
	None = 0,
	Bold,
	Italic,
	BoldItalic,
	Underline,
	BoldUnderline,
	ItalicUnderline,
	ItalicUnderlineBold
};

typedef struct SignalData
{
	CString strSignalName;
	BOOL	bIsSignaled;
	COLORREF cTextColor;
	COLORREF cBGColor;
	TextMode textMode;
}sSignalData;

class CTSFFile : public CConfigFile 
{
public:
	CTSFFile();
	virtual ~CTSFFile();
	
	BOOL OpenTSFFile(const CString &strTSFFile);

	BOOL GetSignals(CArray<sSignalData, sSignalData&> &arrSigData); //this function will return array of all signals and their state.
	BOOL SetSignal(CString strSignalName, BOOL bIsSignaled, COLORREF cTextColor, COLORREF cBGColor, TextMode textMode);
	BOOL IsSignaled(CString strSignalName);
	COLORREF GetSignalTextColor(CString strSignalName);
	COLORREF GetSignalBGColor(CString strSignalName);
	TextMode GetSignalTextMode(CString strSignalName); //will return if signal is Bold\Italic\underline

private:
	CString			m_TSFFileName;	// Name of the TSF file.
//	CString			m_TSFPath;		// Path of the TSF file.

	// Profile settings (to the app specific .TSF file, or registry)
	UINT GetProfileInt(LPCTSTR lpszSection, LPCTSTR lpszEntry, int nDefault);
	BOOL WriteProfileInt(LPCTSTR lpszSection, LPCTSTR lpszEntry, int nValue);
	CString GetProfileString(LPCTSTR lpszSection, LPCTSTR lpszEntry, LPCTSTR lpszDefault = NULL);
	BOOL WriteProfileString(LPCTSTR lpszSection, LPCTSTR lpszEntry, LPCTSTR lpszValue);

 	BOOL FlushData();
};