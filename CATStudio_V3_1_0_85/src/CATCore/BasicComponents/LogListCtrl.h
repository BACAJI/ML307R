#pragma once
#include "GeneralMacroDefine.h"
// CLogListCtrl

class CATCORE_DLLEXPORT CLogListCtrl : public CMFCListCtrl
{
	DECLARE_DYNCREATE(CLogListCtrl)

public:
	CLogListCtrl();
	virtual ~CLogListCtrl();

protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()
public:
	void InitFontAndHeight();
	void ClearAllSelections(void);
	COLORREF GetRowColor( int nRow);
	void SetRowColor(int nRow, COLORREF color);
	virtual COLORREF OnGetCellBkColor (int nRow, int nColumn);
private:
	HFONT m_hFont;
	CImageList m_imagelist;
};


