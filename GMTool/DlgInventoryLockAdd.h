#pragma once


// CDlgInventoryLockAdd dialog

class CDlgInventoryLockAdd : public CDialog
{
	DECLARE_DYNAMIC(CDlgInventoryLockAdd)

public:
	CDlgInventoryLockAdd(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgInventoryLockAdd();

// Dialog Data
	enum { IDD = IDD_DLG_INVENTORY_LOCK_ADD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk2();
	afx_msg void OnBnClickedCancel();
};
