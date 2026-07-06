/*--------------------------------------------------------------------------------------------------------------------

 (C) Copyright 2006,2007 Marvell Semiconductor Israel Ltd. All Rights Reserved  

-------------------------------------------------------------------------------------------------------------------*/


#ifndef __MENUEX_H__
#define __MENUEX_H__

#include <afxtempl.h>

// CMenuExData class. Fill this class structure to define a single menu item:
class CMenuExData
{
	TCHAR *m_szMenuText;
public:
	CMenuExData () {menuIconNormal=-1;xoffset=-1;bitmap=NULL;pContext=NULL;
	nFlags=0;nID=0;syncflag=0;m_szMenuText=NULL;global_offset=-1;};
	void SetString(const TCHAR * szAnsiString);
	~CMenuExData ();
	TCHAR* GetString(void);
	int xoffset,global_offset;
	int menuIconNormal;
	UINT nFlags,nID,syncflag;
	CImageList *bitmap;
	void *pContext; // used to attach user data
};

//struct CMenuItemInfo : public MENUITEMINFO {
struct CMenuItemInfo : public 
//MENUITEMINFO 
#ifndef UNICODE   
tagMENUITEMINFOA
#else
tagMENUITEMINFOW
#endif
{
	CMenuItemInfo()
	{
		memset(this, 0, sizeof(MENUITEMINFO));
		cbSize = sizeof(MENUITEMINFO);
	}
};

// how the menu's are drawn, either original or XP style
typedef enum {MENUEX_DRAWMODE_ORIGINAL,MENUEX_DRAWMODE_XP} MenuEx_MenuDrawMode;

typedef enum {MENUEX_NONE, MENUEX_HEAD, MENUEX_TAIL, MENUEX_BOTH} MenuEx_Seperator;

#ifdef _CATCORE_DLL
#define CATCORE_DLLMENUEXEXPORT __declspec(dllexport)
#else					
#define CATCORE_DLLMENUEXEXPORT
#endif

class CATCORE_DLLMENUEXEXPORT CMenuEx : public CMenu
{
	DECLARE_DYNAMIC( CMenuEx )
public:
	CMenuEx(); 
	virtual ~CMenuEx();

	// Functions for loading and applying bitmaps to menus (see example application)
	virtual BOOL LoadMenu(LPCTSTR lpszResourceName);
	virtual BOOL LoadMenu(int nResource);
	BOOL LoadToolbar(UINT nToolBar, UINT nBitmapRes = 0);
	BOOL LoadToolbars(const UINT *arID,int n);
	void AddFromToolBar(CToolBar* pToolBar, int nResourceID);
	BOOL LoadFromToolBar(UINT nID,UINT nToolBar,int& xoffset);
	BOOL AddBitmapToImageList(CImageList *list,UINT nResourceID);
	static HBITMAP LoadSysColorBitmap(int nResourceId);
	void LoadCheckmarkBitmap(int unselect,int select); // custom check mark bitmaps
	
	// functions for appending a menu option, use the AppendMenu call (see above define)
	BOOL AppendMenu(UINT nFlags,UINT nIDNewItem=0,LPCTSTR lpszNewItem=NULL,int nIconNormal=-1);
	BOOL AppendMenu(UINT nFlags,UINT nIDNewItem,LPCTSTR lpszNewItem,CImageList *il,int xoffset);
	BOOL AppendMenu(UINT nFlags,UINT nIDNewItem,LPCTSTR lpszNewItem,CBitmap *bmp);
	BOOL AppendODMenu(LPCTSTR lpstrText,UINT nFlags = MF_OWNERDRAW,UINT nID = 0,int nIconNormal = -1);  
	BOOL AppendODMenu(LPCTSTR lpstrText,UINT nFlags,UINT nID,CImageList *il,int xoffset);
	
	// for appending a popup menu (see example application)
	CMenuEx* AppendODPopupMenu(LPCTSTR lpstrText);

	// functions for inserting a menu option, use the InsertMenu call (see above define)
	BOOL InsertMenu(UINT nPosition,UINT nFlags,UINT nIDNewItem=0,LPCTSTR lpszNewItem=NULL,int nIconNormal=-1);
	BOOL InsertMenu(UINT nPosition,UINT nFlags,UINT nIDNewItem,LPCTSTR lpszNewItem,CImageList *il,int xoffset);
	BOOL InsertMenu(UINT nPosition,UINT nFlags,UINT nIDNewItem,LPCTSTR lpszNewItem,CBitmap *bmp);
	BOOL InsertODMenu(UINT nPosition,LPCTSTR lpstrText,UINT nFlags = MF_OWNERDRAW,UINT nID = 0,int nIconNormal = -1); 
	BOOL InsertODMenu(UINT nPosition,LPCTSTR lpstrText,UINT nFlags,UINT nID,CImageList *il,int xoffset);
	
	// functions for modifying a menu option, use the ModifyODMenu call (see above define)
	BOOL ModifyODMenu(LPCTSTR lpstrText,UINT nID=0,int nIconNormal=-1);
	BOOL ModifyODMenu(LPCTSTR lpstrText,UINT nID,CImageList *il,int xoffset);
	BOOL ModifyODMenu(LPCTSTR lpstrText,UINT nID,CBitmap *bmp);
	BOOL ModifyODMenu(LPCTSTR lpstrText,LPCTSTR OptionText,int nIconNormal);
	// use this method for adding a solid/hatched colored square beside a menu option
	// courtesy of Warren Stevens
	BOOL ModifyODMenu(LPCTSTR lpstrText,UINT nID,COLORREF fill,COLORREF border,int hatchstyle=-1,CSize *pSize=NULL);
	
	// for deleting and removing menu options
	BOOL	RemoveMenu(UINT uiId,UINT nFlags);
	BOOL	DeleteMenu(UINT uiId,UINT nFlags);
	// sPos means Seperator's position, since we have no way to find the seperator's position in the menu
	// we have to specify them when we call the RemoveMenu to make sure the unused seperators are removed;
	// sPos  = None no seperator removal;
	//       = Head  seperator in front of this menu item;
	//       = Tail  seperator right after this menu item;
	//       = Both  seperators at both ends;
	// remove the menu item based on their text, return -1 if not found, otherwise return the menu position;
	int RemoveMenu(LPCTSTR pText, MenuEx_Seperator sPos=MENUEX_NONE);
	int DeleteMenu(LPCTSTR pText, MenuEx_Seperator sPos=MENUEX_NONE);
	
	// Destroying
	virtual BOOL DestroyMenu();

	// function for retrieving and setting a menu options text (use this function
	// because it is ownerdrawn)
	BOOL GetMenuText(UINT id,CString &string,UINT nFlags = MF_BYPOSITION);
	BOOL SetMenuText(UINT id,CString string, UINT nFlags = MF_BYPOSITION);

	// Getting a submenu from it's name or position
	CMenuEx* GetSubBCMenu(LPCTSTR lpszSubMenuName);
	CMenu* GetSubMenu (LPCTSTR lpszSubMenuName);
	CMenu* GetSubMenu (int nPos);
	int GetMenuPosition(LPCTSTR pText);
	
	// Drawing: 
	virtual void DrawItem( LPDRAWITEMSTRUCT);  // Draw an item
	virtual void MeasureItem( LPMEASUREITEMSTRUCT );  // Measure an item

	// Static functions used for handling menu's in the mainframe
	static void UpdateMenu(CMenu *pmenu);
	static BOOL IsMenu(CMenu *submenu);
	static BOOL IsMenu(HMENU submenu);
	static LRESULT FindKeyboardShortcut(UINT nChar,UINT nFlags,CMenu *pMenu);

	static void SetMenuDrawMode(UINT mode);
	static void SetSelectDisableMode(BOOL mode);

	static int GetMenuDrawMode(void);
	static BOOL GetSelectDisableMode(void);

	static void SetXPBitmap3D(BOOL val);
	static BOOL GetXPBitmap3D(void);

	// Customizing:
	// Set icon size
	static void SetIconSize (int, int); 
	// set the color in the bitmaps that is the background transparent color
	void SetBitmapBackground(COLORREF color);
	void UnSetBitmapBackground(void);
	// obsolete functions for setting how menu images are dithered for disabled menu options
	BOOL GetDisableOldStyle(void);
	void SetDisableOldStyle(void);
	void UnSetDisableOldStyle(void);
	static COLORREF LightenColor(COLORREF col,double factor);
	static COLORREF DarkenColor(COLORREF col,double factor);

// Miscellaneous Protected Member functions
protected:
	static BOOL IsNewShell(void);
	static BOOL IsWinXPLuna(void);
	static BOOL IsLunaMenuStyle(void);
	static BOOL IsWindowsClassicTheme(void);
	CMenuExData *FindMenuItem(UINT nID);
	CMenuEx *FindMenuOption(int nId,int& nLoc);
	CMenuEx *FindAnotherMenuOption(int nId,int& nLoc,CArray<CMenuEx*,CMenuEx*>&bcsubs,
								  CArray<int,int&>&bclocs);
	CMenuExData *FindMenuOption(LPCTSTR lpstrText);
	void InsertSpaces(void);
	void DrawCheckMark(CDC* pDC,int x,int y,COLORREF color,BOOL narrowflag=FALSE);
	void DrawRadioDot(CDC *pDC,int x,int y,COLORREF color);
	CMenuExData *NewODMenu(UINT pos,UINT nFlags,UINT nID,CString string);
	void SynchronizeMenu(void);
	void InitializeMenuList(int value);
	void DeleteMenuList(void);
	CMenuExData *FindMenuList(UINT nID);
	void DrawItem_Win9xNT2000 (LPDRAWITEMSTRUCT lpDIS);
	void DrawItem_WinXP (LPDRAWITEMSTRUCT lpDIS);
	BOOL Draw3DCheckmark(CDC *dc, const CRect& rc,BOOL bSelected,HBITMAP hbmCheck);
	BOOL DrawXPCheckmark(CDC *dc, const CRect& rc, HBITMAP hbmCheck,COLORREF &colorout,BOOL selected);
	void DitherBlt(HDC hdcDest, int nXDest, int nYDest, int nWidth, 
		int nHeight, HBITMAP hbm, int nXSrc, int nYSrc,COLORREF bgcolor);
	void DitherBlt2(CDC *drawdc, int nXDest, int nYDest, int nWidth, 
		int nHeight, CBitmap &bmp, int nXSrc, int nYSrc,COLORREF bgcolor);
	void DitherBlt3(CDC *drawdc, int nXDest, int nYDest, int nWidth, 
		int nHeight, CBitmap &bmp,COLORREF bgcolor);
	BOOL GetBitmapFromImageList(CDC* pDC,CImageList *imglist,int nIndex,CBitmap &bmp);
	BOOL ImageListDuplicate(CImageList *il,int xoffset,CImageList *newlist);
	static WORD NumBitmapColors(LPBITMAPINFOHEADER lpBitmap);
	void ColorBitmap(CDC* pDC, CBitmap& bmp,CSize bitmap_size,CSize icon_size,COLORREF fill,COLORREF border,int hatchstyle=-1);
	void RemoveTopLevelOwnerDraw(void);
	int GetMenuStart(void);
	void GetFadedBitmap(CBitmap &bmp);
	void GetTransparentBitmap(CBitmap &bmp);
	void GetDisabledBitmap(CBitmap &bmp,COLORREF background=0);
	void GetShadowBitmap(CBitmap &bmp);
	int AddToGlobalImageList(CImageList *il,int xoffset,int nID);
	int GlobalImageListOffset(int nID);
	BOOL CanDraw3DImageList(int offset);
	
// Member Variables
protected:
	CTypedPtrArray<CPtrArray, CMenuExData*> m_MenuList;  // Stores list of menu items 
	// When loading an owner-drawn menu using a Resource, CMenuEx must keep track of
	// the popup menu's that it creates. Warning, this list *MUST* be destroyed
	// last item first :)
	CTypedPtrArray<CPtrArray, HMENU>  m_SubMenus;  // Stores list of sub-menus 
	// Stores a list of all CMenuEx's ever created 
	static CTypedPtrArray<CPtrArray, HMENU>  m_AllSubMenus;
	// Global ImageList
	static CImageList m_AllImages;
	static CArray<int,int&> m_AllImagesID;
	// icon size
	static int m_iconX;
	static int m_iconY;
	COLORREF m_bitmapBackground;
	BOOL m_bitmapBackgroundFlag;
	BOOL disable_old_style;
	
	CImageList *checkmaps;
	BOOL checkmapsshare;
	int m_selectcheck;
	int m_unselectcheck;
	BOOL m_bDynIcons;
	BOOL m_loadmenu;
}; 

#define MENUEX_USE_MEMDC

#ifdef MENUEX_USE_MEMDC

class CMenuExMemDC : public CDC
{
public:

    // constructor sets up the memory DC
    CMenuExMemDC(CDC* pDC,LPCRECT lpSrcRect) : CDC()
    {
        ASSERT(pDC != NULL);

		m_rect.CopyRect(lpSrcRect);
        m_pDC = pDC;
        m_pOldBitmap = NULL;
        m_bMemDC = !pDC->IsPrinting();
              
        if (m_bMemDC)    // Create a Memory DC
        {
            CreateCompatibleDC(pDC);
            m_bitmap.CreateCompatibleBitmap(pDC, m_rect.Width(), m_rect.Height());
            m_pOldBitmap = SelectObject(&m_bitmap);
            SetWindowOrg(m_rect.left, m_rect.top);
        }
        else        // Make a copy of the relevent parts of the current DC for printing
        {
            m_bPrinting = pDC->m_bPrinting;
            m_hDC       = pDC->m_hDC;
            m_hAttribDC = pDC->m_hAttribDC;
        }
    }
    
    // Destructor copies the contents of the mem DC to the original DC
    ~CMenuExMemDC()
    {
        if (m_bMemDC) 
        {    
            // Copy the offscreen bitmap onto the screen.
            m_pDC->BitBlt(m_rect.left, m_rect.top, m_rect.Width(), m_rect.Height(),
                          this, m_rect.left, m_rect.top, SRCCOPY);

            //Swap back the original bitmap.
            SelectObject(m_pOldBitmap);
        } else {
            // All we need to do is replace the DC with an illegal value,
            // this keeps us from accidently deleting the handles associated with
            // the CDC that was passed to the constructor.
            m_hDC = m_hAttribDC = NULL;
        }
    }

    // Allow usage as a pointer
    CMenuExMemDC* operator->() {return this;}
        
    // Allow usage as a pointer
    operator CMenuExMemDC*() {return this;}

private:
    CBitmap  m_bitmap;      // Offscreen bitmap
    CBitmap* m_pOldBitmap;  // bitmap originally found in CMenuExMemDC
    CDC*     m_pDC;         // Saves CDC passed in constructor
    CRect    m_rect;        // Rectangle of drawing area.
    BOOL     m_bMemDC;      // TRUE if CDC really is a Memory DC.
};

#endif

#endif // __MENUEX_H__

//*************************************************************************
