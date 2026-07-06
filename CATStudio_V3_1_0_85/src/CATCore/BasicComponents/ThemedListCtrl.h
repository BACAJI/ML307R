#pragma once

//#include "GuiCommon.h"
#include "GeneralMacroDefine.h"

#ifdef __BCGCBPROINC_H
	#define CThemedListCtrl_Base CBCGPListCtrl 
#else
	#define CThemedListCtrl_Base CMFCListCtrl
#endif // __BCGCBPROINC_H


class CATCORE_DLLEXPORT CThemedListCtrl : public CThemedListCtrl_Base
{
	DECLARE_DYNAMIC(CThemedListCtrl)

public:
	CThemedListCtrl();
	virtual ~CThemedListCtrl();

protected:
	DECLARE_MESSAGE_MAP()

protected:
	virtual void PreSubclassWindow();
};


