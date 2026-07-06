/*--------------------------------------------------------------------------------------------------------------------

 (C) Copyright 2006,2007 Marvell Semiconductor Israel Ltd. All Rights Reserved  

-------------------------------------------------------------------------------------------------------------------*/

#pragma once

//#include "GuiCommon.h"
#include "GeneralMacroDefine.h"
#include "ThemedTreeCtrl.h"

#define TYPE_CHECHED	-1
#define TYPE_UNCHECKED	-2

#define WM_TVN_ITEM_CHECKED WM_USER+83 //indicates that an item in the tree was checked/unchecked

class CTreeCtrlEx2;
typedef struct  
{
	CTreeCtrlEx2 * pTree;
	HTREEITEM item;

	BOOL bChecked;
	BOOL bByUser;
	BOOL bByParent;
	BOOL bByChild;
} TreeItemCheckedData;


class CATCORE_DLLEXPORT CTreeCtrlEx2 : public CThemedTreeCtrl
{
public:
	CTreeCtrlEx2();
	virtual ~CTreeCtrlEx2();

// Operations
public:
	BOOL SetItemImageEx(HTREEITEM hItem, int nImage, int nSelectedImage);
	BOOL SetCheckEx(HTREEITEM hItem, BOOL fCheck = TRUE);
	HTREEITEM GetNextItem(HTREEITEM hItem);
	HTREEITEM		GetFirstLeaf();
	HTREEITEM		GetNextLeaf(HTREEITEM hCurLeaf);
	int				GetNumberOfCheckedLeaves();

//	BOOL			SerializeData(CArchive &ar, BOOL &bNoFieldFound, int &nNumOfNotFoundFields);
	void			ClearAllNodes();

// Implementation
public:
	void LoadSelectedNodes(CStdioFile &file, int nType);
	void SaveSelectedNodes(CStdioFile &file, int nType);


	HTREEITEM GetNextNonDescendantItem(HTREEITEM hItem);
	void LoadCheckedNodes(CStdioFile &file, BOOL bHasExtraData = FALSE);
	void SaveCheckedNodes(CStdioFile &file);
	BOOL HasUncheckedDescendant(HTREEITEM hParent);
	HTREEITEM FindChildByName(HTREEITEM hParent, const CString &strChildName);
	void ExpandCollapseAll(BOOL bExpand);//Michal Bukai - add this ability to the Filter module
	HTREEITEM FindChild(const CString & strCat1, const CString & strCat2, const CString & strCat3, HTREEITEM hParent);
	HTREEITEM FindChildById(HTREEITEM hParent, DWORD dwId);

	virtual void Serialize(CArchive &ar);

	int GetNumberChildItems(HTREEITEM hParent);
	void UpdateItemStateAndImage(HTREEITEM hItem);
	void UpdateItemState(HTREEITEM hItem);

	// Generated message map functions
protected:
	//{{AFX_MSG(CTreeCtrlEx2)
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	void CheckParents(HTREEITEM hItem, BOOL bCheck);
	BOOL HasCheckedChild(HTREEITEM hParent);
	void CheckChildren(HTREEITEM hItem, BOOL bCheck);
	void UpdateParents(HTREEITEM hItem);
	BOOL SetCheckAndNotify(HTREEITEM hChild, BOOL bCheck, WPARAM flagByWhom ); //returns TRUE iff item was checked (regardless of notification to parent)

	int GetIndentLevel(HTREEITEM hItem);
	
	void BuildRecursiveItemText(HTREEITEM hItem, CString &strText);
	HTREEITEM FindRecursiveChild(CString &strText, HTREEITEM hParent, BOOL bHasExtraData);

	HTREEITEM FindChildByNameAndUpdateData(HTREEITEM hParent, const CString &strChildName, const CString &strNewData);

	void SetChildrenImage(HTREEITEM hItem, int nImage, int nSelectedImage);
	void UpdateParentsImage(HTREEITEM hItem);
	BOOL GetChildrenImag(HTREEITEM hParent, int & nImage, int & nSelectedImage);

	HTREEITEM FindRecursiveChild_(CString &strText, HTREEITEM hParent);
	void BuildRecursiveItemText_(HTREEITEM hItem, CString &strText);
	void UpdateItemStateAndImage(HTREEITEM hItem, BOOL & bState, int & nImage, int & nSelectedImage);
	void UpdateItemState(HTREEITEM hItem, BOOL & bState);
};
