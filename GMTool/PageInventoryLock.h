#pragma once

class	CsheetWithTab;
// CPageInventoryLock dialog

class CPageInventoryLock : public CPropertyPage
{
	DECLARE_DYNAMIC(CPageInventoryLock)

public:
	CPageInventoryLock(LOGFONT logfont);
	virtual ~CPageInventoryLock();

// Dialog Data
	enum { IDD = IDD_MAINPAGE_INVENTORY_LOCK };
	enum { MAX_PAGE_INVENTORY_LOCK_MODAL_DIALOG = 10 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	CsheetWithTab*	m_pSheetTab;
	int				m_CallPage;
	BOOL			m_bDlgInit;
	CFont*			m_pFont;

public:
	void	SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void	SetSheetTab ( CsheetWithTab* pSheetTab ) { m_pSheetTab = pSheetTab; }

public:
	CListCtrl	m_List;

public:
	CDialog*	m_pToolDialog[MAX_PAGE_INVENTORY_LOCK_MODAL_DIALOG];

public:
	int		DialogNewID();
	void	DialogDeleteID( int nDialogID );
	int		DialogGetTotalActive();

public:
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedInventoryLockPageButtonAdd();
	afx_msg void OnBnClickedInventoryLockPageButtonEdit();
	afx_msg void OnBnClickedInventoryLockPageButtonDelete();
	afx_msg void OnBnClickedInventoryLockPageButtonSearch();
	afx_msg void OnNMDblclkListInventoryLock(NMHDR *pNMHDR, LRESULT *pResult);
};
