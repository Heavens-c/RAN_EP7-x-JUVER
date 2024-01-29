// DlgInventoryLockEdit.cpp : implementation file
//

#include "stdafx.h"
#include "GMTool.h"
#include "DlgInventoryLockEdit.h"
#include ".\DlgInventoryLockEdit.h"
#include "PageInventoryLock.h"
#include "HLibDataConvert.h"
#include "Logic/GMToolData.h"
#include "Logic/GMToolGlobal.h"
#include "Logic/GMToolOdbcBase.h"

#include "EtcFunction.h"

// CDlgInventoryLockEdit dialog

IMPLEMENT_DYNAMIC(CDlgInventoryLockEdit, CDialog)
CDlgInventoryLockEdit::CDlgInventoryLockEdit(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInventoryLockEdit::IDD, pParent)
	, m_pParentWnd(NULL)
	, m_nDialogID(-1)
	, m_dwNum(0)
	, m_pData( NULL )
{
}

CDlgInventoryLockEdit::CDlgInventoryLockEdit(int nDialogID, DWORD dwNum, CWnd* pParent /*= NULL*/)
: CDialog(CDlgInventoryLockEdit::IDD, pParent)
	, m_pParentWnd(pParent)
	, m_nDialogID(nDialogID)
	, m_dwNum(dwNum)
	, m_pData( NULL )
{
}

CDlgInventoryLockEdit::~CDlgInventoryLockEdit()
{
	SAFE_DELETE( m_pData );
}

void CDlgInventoryLockEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgInventoryLockEdit, CDialog)
	ON_BN_CLICKED(IDOK2, OnBnClickedOk2)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
END_MESSAGE_MAP()


// CDlgInventoryLockEdit message handlers
BOOL CDlgInventoryLockEdit::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_pData = new SGMTOOL_INVENTORY_LOCK_DATA_SIMPLE();

	int nRETURN = CGMToolOdbcBase::GetInstance()->InventoryLock_Get( m_dwNum, m_pData );
	if ( nRETURN != DB_OK ){
		CDebugSet::MsgBox( GetSafeHwnd(), "Failure to Read Data! Info( Num:%d )", m_dwNum );
		return TRUE;
	}

	if ( m_pData )
	{
		SetWin_Num_int( this, IDC_INVENTORY_LOCK_EDIT_NUM, m_pData->dwNum );
		SetWin_Num_int( this, IDC_INVENTORY_LOCK_EDIT_CHANUM, m_pData->dwChaNum );
		SetWin_Text( this, IDC_INVENTORY_LOCK_EDIT_CHANAME, m_pData->szChaName );
		SetWin_Text( this, IDC_INVENTORY_LOCK_EDIT_EPASS, m_pData->szEPin );
		SetWin_Text( this, IDC_INVENTORY_LOCK_EDIT_DATE, _HLIB::cstring_timet12( m_pData->tDate ).GetString() );

		CString strWindowText;
		strWindowText.Format( "Edit Inventory Lock:(%d) %s", m_pData->dwChaNum, m_pData->szChaName );
		SetWindowText( strWindowText.GetString() );
	}

	return TRUE;  
}

void CDlgInventoryLockEdit::PostNcDestroy()
{
	CDialog::PostNcDestroy();

	if ( m_pParentWnd ){
		((CPageInventoryLock*)m_pParentWnd)->DialogDeleteID(m_nDialogID);
	}

	delete this;
}

void CDlgInventoryLockEdit::OnOK()
{
	if(UpdateData(true)){
		DestroyWindow();
	}
}

void CDlgInventoryLockEdit::OnCancel()
{
	DestroyWindow();
}

void CDlgInventoryLockEdit::OnBnClickedOk2()
{
	if ( DataSave()){
		CDebugSet::MsgBox( GetSafeHwnd(), "Save Done!" );
	}
}

void CDlgInventoryLockEdit::OnBnClickedOk()
{
	if ( DataSave()){
		OnOK();
	}
}

void CDlgInventoryLockEdit::OnBnClickedCancel()
{
	OnCancel();
}

BOOL CDlgInventoryLockEdit::DataSave()
{
	if ( !m_pData ){
		return FALSE;
	}

	std::string strName = GetWin_Text( this, IDC_INVENTORY_LOCK_EDIT_CHANAME );
	std::string strPass = GetWin_Text( this, IDC_INVENTORY_LOCK_EDIT_EPASS ); 

	if ( strName.size() < MIN_CHAR_ID || strName.size() > MAX_CHAR_ID ){
		CDebugSet::MsgBox( GetSafeHwnd(), "ChaName can only have %d to %d characters", MIN_CHAR_ID, MAX_CHAR_ID );
		GotoDlgCtrl(GetDlgItem(IDC_INVENTORY_LOCK_EDIT_CHANAME)); 
		return FALSE;
	}

	if ( strPass.size() < CHAR_INVENTORY_LOCK_PASS_SIZE || strPass.size() > CHAR_INVENTORY_LOCK_PASS_SIZE ){
		CDebugSet::MsgBox( GetSafeHwnd(), "Pass can only have %d to %d characters", CHAR_INVENTORY_LOCK_PASS_SIZE, CHAR_INVENTORY_LOCK_PASS_SIZE );
		GotoDlgCtrl(GetDlgItem(IDC_INVENTORY_LOCK_EDIT_EPASS)); 
		return FALSE;
	}

	if ( GMTOOL_GLOBAL::IsBadString( strName.c_str() ) ){
		CDebugSet::MsgBox( GetSafeHwnd(), "ChaName contains invalid characters!" );
		GotoDlgCtrl(GetDlgItem(IDC_INVENTORY_LOCK_EDIT_CHANAME)); 
		return FALSE;
	}

	if ( GMTOOL_GLOBAL::IsBadString2( strName.c_str() ) ){
		CDebugSet::MsgBox( GetSafeHwnd(), "ChaName contains invalid characters!" );
		GotoDlgCtrl(GetDlgItem(IDC_INVENTORY_LOCK_EDIT_CHANAME)); 
		return FALSE;
	}

	if ( GMTOOL_GLOBAL::IsBadString( strPass.c_str() ) ){
		CDebugSet::MsgBox( GetSafeHwnd(), "ChaName contains invalid characters!" );
		GotoDlgCtrl(GetDlgItem(IDC_INVENTORY_LOCK_EDIT_EPASS)); 
		return FALSE;
	}

	if ( GMTOOL_GLOBAL::IsBadString2( strPass.c_str() ) ){
		CDebugSet::MsgBox( GetSafeHwnd(), "ChaName contains invalid characters!" );
		GotoDlgCtrl(GetDlgItem(IDC_INVENTORY_LOCK_EDIT_EPASS)); 
		return FALSE;
	}

	m_pData->dwChaNum = GetWin_Num_int( this, IDC_INVENTORY_LOCK_EDIT_CHANUM );
	StringCchCopy( m_pData->szChaName, CHR_ID_LENGTH+1, strName.c_str() );
	StringCchCopy( m_pData->szEPin, CHAR_INVENTORY_LOCK_PASS_SIZE+1, strPass.c_str() );

	int nRETURN = CGMToolOdbcBase::GetInstance()->InventoryLock_Save( m_pData );
	if( nRETURN != DB_OK ){
		CDebugSet::MsgBox( GetSafeHwnd(), "Failure to Save Data! Info( Num:%d )", m_dwNum );
		return FALSE;
	}

	return TRUE;
}