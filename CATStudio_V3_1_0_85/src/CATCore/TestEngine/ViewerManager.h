#pragma once
#include "singletondestroyer.h"

struct ViewerOwnerRecord {
	void	*m_pOwner;
	CViewer *m_pViewer;

	ViewerOwnerRecord (CViewer *pViewer=NULL, void *pOwner=NULL)
	{
		m_pOwner = pOwner;
		m_pViewer = pViewer;
	}
};

class __declspec(dllexport) CViewerManager
{
public:
	CViewerManager();           
	virtual ~CViewerManager();
	static CViewerManager * Instance();
	BOOL CloseScriptViewer(CViewer *pViewer = NULL);
	void ClearScriptViewerList(void *pOwner);
#ifdef _UNICODE
	CViewer * AddScriptViewer(const CString &ViewerName, void *pOwner,BOOL bIsOpenedOutsideACAT =FALSE);
#endif
	CViewer * AddScriptViewer(const CStringA &ViewerName, void *pOwner,BOOL bIsOpenedOutsideACAT =FALSE);
	CViewer * AddScriptViewer(const CString &ViewerName, BOOL bOffLine, void *pOwner,BOOL bIsOpenedOutsideACAT =FALSE);
protected:
	static CViewerManager *m_pThis;
	static CSingletonDestroyer<CViewerManager> m_Destroyer;	
	friend class CSingletonDestroyer<CViewerManager>;
private:
//	CList <ViewerOwnerRecord, ViewerOwnerRecord &> m_ScriptViewerList;	//List of open viewers through scripts.
};