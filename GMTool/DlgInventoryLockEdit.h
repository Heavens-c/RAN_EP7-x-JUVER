#pragma once

#include "Logic/GMToolData.h"
// CDlgInventoryLockEdit dialog

class CDlgInventoryLockEdit : public CDialog
{
	DECLARE_DYNAMIC(CDlgInventoryLockEdit)

public:
	CDlgInventoryLockEdit(CWnd* pParent = NULL);   // standard constructor
	CDlgInventoryLockEdit(int nDialogID, DWORD dwNum, CWnd* pParent = NULL);
	virtual ~CDlgInventoryLockEdit();

	BOOL Create(CWnd * pWnd){ 
		return CDialog::Create( CDlgInventoryLockEdit::IDD, pWnd );
	}

// Dialog Data
	enum { IDD = IDD_DLG_INVENTORY_LOCK_EDIT };

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
	SGMTOOL_INVENTORY_LOCK_DATA_SIMPLE*		m_pData;

public:
	BOOL	DataSave();

public:
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedOk2();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
