/*--------------------------------------------------------------------------------------------------------------------

 (C) Copyright 2006,2007 Marvell Semiconductor Israel Ltd. All Rights Reserved  

-------------------------------------------------------------------------------------------------------------------*/


#if !defined(AFX_CONNECTIONSWITCHER_H__A28405BA_9373_4B83_9575_7B0653E30690__INCLUDED_)
#define AFX_CONNECTIONSWITCHER_H__A28405BA_9373_4B83_9575_7B0653E30690__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XDEVStructures.h"
#include "XDEVReporter.h"
#include "../Converter/db/AdoDbConnector.h"

class CInitializationStatusDlg;

class CConnectionSwitcher
{
public:
	void TerminateSingleConnection(sXDEVSession *pXdevSession);
	void SetReporter(CXDEVReporter *pReporter);
	void SetOverNightTest(bool  isOverNightTest);
	void TerminateConnections(CPtrArray *sessionPtrArray);
	void InitializeConnections(sInitialization *sInit);

	CConnectionSwitcher();
	CConnectionSwitcher(CXDEVReporter *pReporter);
	virtual ~CConnectionSwitcher();

protected:
	int InitSpecificDeviceWithSecAddr(sXDEVSession *xdevSession, CString *strErrMsg);
	inline int LoadDeviceDriver(sXDEVSession *xdevSession);
	int InitSpecificDevice(sXDEVSession *xdevSession);
	
	BOOL m_OverNightTest;
	CXDEVReporter *m_pReporter,m_DefaultReporter;

};

#endif // !defined(AFX_CONNECTIONSWITCHER_H__A28405BA_9373_4B83_9575_7B0653E30690__INCLUDED_)
