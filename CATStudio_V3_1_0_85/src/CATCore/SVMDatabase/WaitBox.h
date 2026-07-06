#pragma once

#include "../resource.h"

// CWaitBox dialog

class CWaitBox : public CDialog
{
	DECLARE_DYNAMIC(CWaitBox)

public:
	CWaitBox(CWnd* pParent = NULL);   // standard constructor
	virtual ~CWaitBox();

	BOOL Create(CWnd* pParent);
	int SetPos(int nPos);

	static HWND m_hwndThis;
	static HWND	m_hMainFrame;

	CString m_cWindowText;

// Dialog Data
	enum { IDD = IDD_WAITMESSAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
