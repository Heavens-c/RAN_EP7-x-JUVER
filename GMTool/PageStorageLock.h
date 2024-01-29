#pragma once

class	CsheetWithTab;
// CPageStorageLock dialog

class CPageStorageLock : public CPropertyPage
{
	DECLARE_DYNAMIC(CPageStorageLock)

public:
	CPageStorageLock(LOGFONT logfont);
	virtual ~CPageStorageLock();

// Dialog Data
	enum { IDD = IDD_MAINPAGE_STORAGE_LOCK };
	enum { MAX_PAGE_STORAGE_LOCK_MODAL_DIALOG = 10 };

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
	CDialog*	m_pToolDialog[MAX_PAGE_STORAGE_LOCK_MODAL_DIALOG];

public:
	int		DialogNewID();
	void	DialogDeleteID( int nDialogID );
	int		DialogGetTotalActive();

public:
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedStorageLockPageButtonAdd();
	afx_msg void OnBnClickedStorageLockPageButtonEdit();
	afx_msg void OnBnClickedStorageLockPageButtonDelete();
	afx_msg void OnBnClickedStorageLockPageButtonSearch();
	afx_msg void OnNMDblclkListStorageLock(NMHDR *pNMHDR, LRESULT *pResult);
};
