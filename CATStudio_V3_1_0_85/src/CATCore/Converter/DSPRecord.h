/*--------------------------------------------------------------------------------------------------------------------

 (C) Copyright 2006,2007 Marvell Semiconductor Israel Ltd. All Rights Reserved  

-------------------------------------------------------------------------------------------------------------------*/

// DSPRecord.h: interface for the CDSPRecord class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DSPRECORD_H__FECB40DB_E945_47E1_AD18_B63758771F91__INCLUDED_)
#define AFX_DSPRECORD_H__FECB40DB_E945_47E1_AD18_B63758771F91__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>
#include <map>
using namespace std;

class CDSPRecord : public CStringArray  
{
public:
	CDSPRecord();
	CDSPRecord(const CString &strSetName, const CString &strSubOpName);
	virtual ~CDSPRecord();

	void operator = (CDSPRecord &rec);
	bool operator == (CDSPRecord &rec);

};


typedef CMap<WORD, WORD, CDSPRecord, CDSPRecord &> CDSPRecordMap;

struct DSPMsgItem
{
	USHORT uSetID;
	USHORT uOpcode;
	CString strSetName;
	CString strOpName;
};

typedef map<CString, DSPMsgItem> MapOpName2DSPItem;


#endif // !defined(AFX_DSPRECORD_H__FECB40DB_E945_47E1_AD18_B63758771F91__INCLUDED_)
