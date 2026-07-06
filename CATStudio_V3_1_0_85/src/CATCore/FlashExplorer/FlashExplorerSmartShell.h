#pragma once
/*#include "singletondestroyer.h"*/
#include "FlashExplorerData.h"
#include <map>
using std::map;

class CFlashExplorerData;
class CFlashExplorerSmartShell  
{
// private:
// 	friend class CSingletonDestroyer<CFlashExplorerSmartShell>;
// 	static CSingletonDestroyer<CFlashExplorerSmartShell> 	m_Destroyer;
// 	static CFlashExplorerSmartShell*			m_pThis;

public:
	CFlashExplorerSmartShell();

public:
	map<CString, CFlashExplorerData*>	m_mapFlashExInstance;
// 	static CFlashExplorerSmartShell*	Instance();
 	void						Terminate();

	virtual ~CFlashExplorerSmartShell();

	CFlashExplorerData* GetFlashExDataInstance (const CString& a_sInstanceName);
	void DeleteFlashExDataInstance(const CString& a_sInstanceName);
	bool IsEmpty();
};

