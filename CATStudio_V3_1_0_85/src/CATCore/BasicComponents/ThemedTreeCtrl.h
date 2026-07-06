#pragma once

//#include "GuiCommon.h"
#include "GeneralMacroDefine.h"

// CThemedTreeCtrl

class CATCORE_DLLEXPORT CThemedTreeCtrl : public CTreeCtrl
{
	DECLARE_DYNAMIC(CThemedTreeCtrl)

public:
	CThemedTreeCtrl();
	virtual ~CThemedTreeCtrl();

protected:
	DECLARE_MESSAGE_MAP()

protected:
	virtual void PreSubclassWindow();
};


