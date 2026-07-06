#pragma once

#include "Singleton.h"

class CThemeManager
{
	DECLARE_SINGLETON(CThemeManager)

public:
	bool IsThemed() const;

private:
	CThemeManager();
	virtual ~CThemeManager();

	void Init();

	DWORD m_dwMajorVer;
	DWORD m_dwMinorVer;
};

#define ThemeMan	CThemeManager::Instance()