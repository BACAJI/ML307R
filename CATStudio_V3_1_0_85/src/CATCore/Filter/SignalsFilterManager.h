// SignalsFilterManager.h: interface for the CSignalsFilterManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIGNALSFILTERMANAGER_H__421688D6_B372_4EFE_AB0D_FB2B7684AAFA__INCLUDED_)
#define AFX_SIGNALSFILTERMANAGER_H__421688D6_B372_4EFE_AB0D_FB2B7684AAFA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>
#include "..\Converter\SignalData.h"

class CTSFFile;

typedef CMap<DWORD, DWORD&, int , int &> CMapIdToIndex;

#ifdef UNICODE
typedef CMap<CString, LPCWSTR, DWORD, DWORD&> CMapStringToDword;
#else
typedef CMap<CString, LPCTSTR, DWORD, DWORD&> CMapStringToDword;
#endif


class CSignalsFilterManager  
{
public:

	static CSignalsFilterManager * Instance(int nDevice);

	CSignalsFilterManager(int nDevice);
	virtual ~CSignalsFilterManager();

	int Signals(){return m_nSignals;}
	int Groups() {return m_nGroups;}

	void Clear();
	void Reset();

	tSignalGroup * GetFirstGroup();
	tSignalGroup * GetNextGroup();

	tSignal * GetFirstSignal(DWORD Id);
	tSignal * GetNextSignal();
	tSignal * GetLastSignal(tSignalGroup * pSignalGroup);

	tSignal * GetSignal(DWORD Id);
	tSignalGroup * GetSignalGroup(DWORD Id);

	void	UpdateSignal(tSignal * pSignal);

	void	SetTSFFileName(CString strName){m_strTSFFileName = strName;}

	CString GetTSFFileName(){return m_strTSFFileName;}

	BOOL FilterSignal(DWORD Id);
	BOOL UnFilterSignal(DWORD Id);
	BOOL FilterSignalsGroup(DWORD Id);
	BOOL UnFilterSignalsGroup(DWORD Id);

	BOOL	SaveTSF();
	BOOL	LoadTSF();

private:

	int m_nDevice;

	SignalGroupArray	m_aSignalGroup;

	int		m_nSignals;
	int		m_nGroups;

	CMapIdToIndex		m_MapIdToIndex;
	CMapIdToIndex		m_MapIdToSignalIndex;

	int		m_nLastGroup;

	int		m_nLastGroupIndex;
	int		m_nLastSignal;

	CTSFFile	*	m_pTSFFile;
	CString		m_strTSFFileName;

	CMapStringToDword	m_MapNameToId;

	static int compareSignals( const void *arg1, const void *arg2 );
	static int compareGroup( const void *arg1, const void *arg2 );
};

#endif // !defined(AFX_SIGNALSFILTERMANAGER_H__421688D6_B372_4EFE_AB0D_FB2B7684AAFA__INCLUDED_)
