/*--------------------------------------------------------------------------------------------------------------------

 (C) Copyright 2006,2007 Marvell Semiconductor Israel Ltd. All Rights Reserved  

-------------------------------------------------------------------------------------------------------------------*/

 


#if !defined(AFX_TREECTRLEX_H__BF52F9BD_2851_40EB_826B_7FA49243C420__INCLUDED_)
#define AFX_TREECTRLEX_H__BF52F9BD_2851_40EB_826B_7FA49243C420__INCLUDED_

#include "ThemedTreeCtrl.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TreeCtrlEx.h : header file

/////////////////////////////////////////////////////////////////////////////
// CTreeCtrlEx window

class CATCORE_DLLEXPORT CTreeCtrlEx : public CThemedTreeCtrl
{
// Construction
public:
    CTreeCtrlEx();

// Attributes
public:

// Operations
public:
	static HTREEITEM FindChildItem(CTreeCtrlEx& treeControl, HTREEITEM parentItem, CString childName);
	BOOL SetCheckEx(HTREEITEM hItem, BOOL fCheck = TRUE);
	HTREEITEM GetNextItem(HTREEITEM hItem);
	HTREEITEM		GetFirstLeaf();
	HTREEITEM		GetNextLeaf(HTREEITEM hCurLeaf);
	int				GetNumberOfCheckedLeaves();

//  BOOL            SerializeData(CArchive &ar, BOOL &bNoFieldFound, int &nNumOfNotFoundFields);
    void            ClearAllNodes();

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CTreeCtrlEx)
    //}}AFX_VIRTUAL

// Implementation
public:
    HTREEITEM GetNextNonDescendantItem(HTREEITEM hItem);
    void LoadCheckedNodes(CStdioFile &file, BOOL bHasExtraData = FALSE);
    void SaveCheckedNodes(CStdioFile &file);
    BOOL HasUncheckedDescendant(HTREEITEM hParent);
    HTREEITEM FindChildByName(HTREEITEM hParent, const CString &strChildName);
    void ExpandCollapseAll(BOOL bExpand);//Michal Bukai - add this ability to the Filter module

    virtual void Serialize(CArchive &ar);
    virtual ~CTreeCtrlEx();

    int GetNumberChildItems(HTREEITEM hParent);

	void UpdateItemState(HTREEITEM hItem);
   // Generated message map functions
protected:
    //{{AFX_MSG(CTreeCtrlEx)
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()

private:
    void CheckParents(HTREEITEM hItem, BOOL bCheck);
    BOOL HasCheckedChild(HTREEITEM hParent);
    void CheckChildren(HTREEITEM hItem, BOOL bCheck);
    void UpdateParents(HTREEITEM hItem);

    int GetIndentLevel(HTREEITEM hItem);

    void BuildRecursiveItemText(HTREEITEM hItem, CString &strText);
    HTREEITEM FindRecursiveChild(CString &strText, HTREEITEM hParent, BOOL bHasExtraData);

    HTREEITEM FindChildByNameAndUpdateData(HTREEITEM hParent, const CString &strChildName, const CString &strNewData);
	void UpdateItemState(HTREEITEM hItem, BOOL & bState);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TREECTRLEX_H__BF52F9BD_2851_40EB_826B_7FA49243C420__INCLUDED_)
