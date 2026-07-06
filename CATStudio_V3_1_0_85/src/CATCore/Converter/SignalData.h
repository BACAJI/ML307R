#ifndef _SIGNALDATA_H
#define _SIGNALDATA_H

#include <afxtempl.h>
#define MAX_SIG_NAME_LENGTH	100

struct tSignal
{
	DWORD		dwId;
	TCHAR		strName[MAX_SIG_NAME_LENGTH+1];
	TCHAR		strSigName[MAX_SIG_NAME_LENGTH+1];
	bool		bActive;
	COLORREF	Color;
	COLORREF	BackColor;
	BYTE		Attribute;

	tSignal():bActive(false)
	{
		Color = RGB(0,0,0);
		BackColor = RGB(255,255,255);
		Attribute = NULL;
		strName[0] = _T('\0');
		strSigName[0] = _T('\0');
	}
	tSignal(DWORD id, CString name):dwId(id),bActive(false)
	{
		Color = RGB(0,0,0);
		BackColor = RGB(255,255,255);
		Attribute = NULL;
		strSigName[0] = _T('\0');
		int length = name.GetLength();
		if (length > MAX_SIG_NAME_LENGTH)
			length = MAX_SIG_NAME_LENGTH;

#if VC6_BUILD
		strcpy(strName, name);
#else
		_tcsncpy_s(strName, name, length);
#endif

		strName[length] = _T('\0');
	}
};

typedef CArray <tSignal, tSignal &> SignalsArray;

//Attribute seting
#define MODE_BOLD		0x0001
#define MODE_ITALIC		0x0002
#define	MODE_UNDERLINE	0x0004

struct	tSignalGroup
{
	DWORD	dwId;
	CString	strName;
	SignalsArray	aSignalArray;
	int		nTotalSigmals;
	int		nActiveSignals;

	tSignalGroup():nTotalSigmals(0),nActiveSignals(0){}
	tSignalGroup(DWORD id, CString name):dwId(id),strName(name),nTotalSigmals(0),nActiveSignals(0){}

	tSignalGroup & operator = (const tSignalGroup & sg)
	{
		dwId = sg.dwId;
		strName = sg.strName;

		aSignalArray.Append(sg.aSignalArray);
		return *this;
	}
};


typedef CArray <tSignalGroup, tSignalGroup &> SignalGroupArray;

#endif