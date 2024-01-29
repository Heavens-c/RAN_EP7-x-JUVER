#pragma once


// CDlgStorageLockAdd dialog

class CDlgStorageLockAdd : public CDialog
{
	DECLARE_DYNAMIC(CDlgStorageLockAdd)

public:
	CDlgStorageLockAdd(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgStorageLockAdd();

// Dialog Data
	enum { IDD = IDD_DLG_STORAGE_LOCK_ADD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk2();
	afx_msg void OnBnClickedCancel();
};
