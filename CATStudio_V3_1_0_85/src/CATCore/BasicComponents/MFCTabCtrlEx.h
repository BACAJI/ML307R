#pragma once
#include "GeneralMacroDefine.h"
class CATCORE_DLLEXPORT CMFCTabCtrlEx:public CMFCTabCtrl
{
	DECLARE_DYNCREATE(CMFCTabCtrlEx)
public:
	CMFCTabCtrlEx();
	virtual ~CMFCTabCtrlEx(){};
	void CloseActiveTab();
	BOOL SetActiveTab(int iTab);
	void SetCloseBtnToUpRight();
	void RecalcLayout();
	virtual BOOL RemoveTab(int iTab, BOOL bRecalcLayout = TRUE);
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};