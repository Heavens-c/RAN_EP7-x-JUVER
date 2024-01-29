#pragma once

#include "Logic/GMToolData.h"
// CDlgStorageLockEdit dialog

class CDlgStorageLockEdit : public CDialog
{
	DECLARE_DYNAMIC(CDlgStorageLockEdit)

public:
	CDlgStorageLockEdit(CWnd* pParent = NULL);   // standard constructor
	CDlgStorageLockEdit(int nDialogID, DWORD dwNum, CWnd* pParent = NULL);
	virtual ~CDlgStorageLockEdit();

	BOOL Create(CWnd * pWnd){ 
		return CDialog::Create( CDlgStorageLockEdit::IDD, pWnd );
	}

// Dialog Data
	enum { IDD = IDD_DLG_STORAGE_LOCK_EDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	virtual void OnOK();
	virtual void OnCancel();

	DECLARE_MESSAGE_MAP()

public:
	CWnd*		m_pParentWnd;

private:
	int			m_nDialogID;
	DWORD		m_dwNum;

public:
	SGMTOOL_STORAGE_LOCK_DATA_SIMPLE*		m_pData;

public:
	BOOL	DataSave();

public:
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedOk2();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
