#pragma once

#include <afxtempl.h>
#include "TreeCtrlEx2.h"
//#include "GuiCommon.h"

class CATCORE_DLLEXPORT CColorTreeCtrl : public CTreeCtrlEx2
{
// Construction
public:
	CColorTreeCtrl();
	virtual ~CColorTreeCtrl();

// Operations
public:
	void SetItemTextColor(HTREEITEM hItem, COLORREF color);
	BOOL GetItemTextColor(HTREEITEM hItem, COLORREF &color);

	void SetItemBgColor(HTREEITEM hItem, COLORREF color);
	BOOL GetItemBgColor(HTREEITEM hItem, COLORREF &color);

	void RemoveItemBgColor(HTREEITEM hItem);

	// Generated message map functions
protected:
	afx_msg void OnPaint();

	DECLARE_MESSAGE_MAP()

private:
	CMap <HTREEITEM, HTREEITEM, COLORREF, COLORREF> m_TextColorMap;
	CMap <HTREEITEM, HTREEITEM, COLORREF, COLORREF> m_BgColorMap;
};