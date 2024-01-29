// DlgStorageLockEdit.cpp : implementation file
//

#include "stdafx.h"
#include "GMTool.h"
#include "DlgStorageLockEdit.h"
#include ".\DlgStorageLockEdit.h"
#include "PageStorageLock.h"
#include "HLibDataConvert.h"
#include "Logic/GMToolData.h"
#include "Logic/GMToolGlobal.h"
#include "Logic/GMToolOdbcBase.h"

#include "EtcFunction.h"

// CDlgStorageLockEdit dialog

IMPLEMENT_DYNAMIC(CDlgStorageLockEdit, CDialog)
CDlgStorageLockEdit::CDlgStorageLockEdit(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgStorageLockEdit::IDD, pParent)
	, m_pParentWnd(NULL)
	, m_nDialogID(-1)
	, m_dwNum(0)
	, m_pData( NULL )
{
}

CDlgStorageLockEdit::CDlgStorageLockEdit(int nDialogID, DWORD dwNum, CWnd* pParent /*= NULL*/)
: CDialog(CDlgStorageLockEdit::IDD, pParent)
	, m_pParentWnd(pParent)
	, m_nDialogID(nDialogID)
	, m_dwNum(dwNum)
	, m_pData( NULL )
{
}

CDlgStorageLockEdit::~CDlgStorageLockEdit()
{
	SAFE_DELETE( m_pData );
}

void CDlgStorageLockEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgStorageLockEdit, CDialog)
	ON_BN_CLICKED(IDOK2, OnBnClickedOk2)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
END_MESSAGE_MAP()


// CDlgStorageLockEdit message handlers
BOOL CDlgStorageLockEdit::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_pData = new SGMTOOL_STORAGE_LOCK_DATA_SIMPLE();

	int nRETURN = CGMToolOdbcBase::GetInstance()->StorageLock_Get( m_dwNum, m_pData );
	if ( nRETURN != DB_OK ){
		CDebugSet::MsgBox( GetSafeHwnd(), "Failure to Read Data! Info( Num:%d )", m_dwNum );
		return TRUE;
	}

	if ( m_pData )
	{
		SetWin_Num_int( this, IDC_STORAGE_LOCK_EDIT_NUM, m_pData->dwNum );
		SetWin_Num_int( this, IDC_STORAGE_LOCK_EDIT_CHANUM, m_pData->dwChaNum );
		SetWin_Text( this, IDC_STORAGE_LOCK_EDIT_CHANAME, m_pData->szChaName );
		SetWin_Text( this, IDC_STORAGE_LOCK_EDIT_EPASS, m_pData->szEPin );
		SetWin_Text( this, IDC_STORAGE_LOCK_EDIT_DATE, _HLIB::cstring_timet12( m_pData->tDate ).GetString() );

		CString strWindowText;
		strWindowText.Format( "Edit Storage Lock:(%d) %s", m_pData->dwChaNum, m_pData->szChaName );
		SetWindowText( strWindowText.GetString() );
	}

	return TRUE;  
}

void CDlgStorageLockEdit::PostNcDestroy()
{
	CDialog::PostNcDestroy();

	if ( m_pParentWnd ){
		((CPageStorageLock*)m_pParentWnd)->DialogDeleteID(m_nDialogID);
	}

	delete this;
}

void CDlgStorageLockEdit::OnOK()
{
	if(UpdateData(true)){
		DestroyWindow();
	}
}

void CDlgStorageLockEdit::OnCancel()
{
	DestroyWindow();
}

void CDlgStorageLockEdit::OnBnClickedOk2()
{
	if ( DataSave()){
		CDebugSet::MsgBox( GetSafeHwnd(), "Save Done!" );
	}
}

void CDlgStorageLockEdit::OnBnClickedOk()
{
	if ( DataSave()){
		OnOK();
	}
}

void CDlgStorageLockEdit::OnBnClickedCancel()
{
	OnCancel();
}

BOOL CDlgStorageLockEdit::DataSave()
{
	if ( !m_pData ){
		return FALSE;
	}

	std::string strName = GetWin_Text( this, IDC_STORAGE_LOCK_EDIT_CHANAME );
	std::string strPass = GetWin_Text( this, IDC_STORAGE_LOCK_EDIT_EPASS ); 

	if ( strName.size() < MIN_CHAR_ID || strName.size() > MAX_CHAR_ID ){
		CDebugSet::MsgBox( GetSafeHwnd(), "ChaName can only have %d to %d characters", MIN_CHAR_ID, MAX_CHAR_ID );
		GotoDlgCtrl(GetDlgItem(IDC_STORAGE_LOCK_EDIT_CHANAME)); 
		return FALSE;
	}

	if ( strPass.size() < CHAR_STORAGE_LOCK_PASS_SIZE || strPass.size() > CHAR_STORAGE_LOCK_PASS_SIZE ){
		CDebugSet::MsgBox( GetSafeHwnd(), "Pass can only have %d to %d characters", CHAR_STORAGE_LOCK_PASS_SIZE, CHAR_STORAGE_LOCK_PASS_SIZE );
		GotoDlgCtrl(GetDlgItem(IDC_STORAGE_LOCK_EDIT_EPASS)); 
		return FALSE;
	}

	if ( GMTOOL_GLOBAL::IsBadString( strName.c_str() ) ){
		CDebugSet::MsgBox( GetSafeHwnd(), "ChaName contains invalid characters!" );
		GotoDlgCtrl(GetDlgItem(IDC_STORAGE_LOCK_EDIT_CHANAME)); 
		return FALSE;
	}

	if ( GMTOOL_GLOBAL::IsBadString2( strName.c_str() ) ){
		CDebugSet::MsgBox( GetSafeHwnd(), "ChaName contains invalid characters!" );
		GotoDlgCtrl(GetDlgItem(IDC_STORAGE_LOCK_EDIT_CHANAME)); 
		return FALSE;
	}

	if ( GMTOOL_GLOBAL::IsBadString( strPass.c_str() ) ){
		CDebugSet::MsgBox( GetSafeHwnd(), "ChaName contains invalid characters!" );
		GotoDlgCtrl(GetDlgItem(IDC_STORAGE_LOCK_EDIT_EPASS)); 
		return FALSE;
	}

	if ( GMTOOL_GLOBAL::IsBadString2( strPass.c_str() ) ){
		CDebugSet::MsgBox( GetSafeHwnd(), "ChaName contains invalid characters!" );
		GotoDlgCtrl(GetDlgItem(IDC_STORAGE_LOCK_EDIT_EPASS)); 
		return FALSE;
	}

	m_pData->dwChaNum = GetWin_Num_int( this, IDC_STORAGE_LOCK_EDIT_CHANUM );
	StringCchCopy( m_pData->szChaName, CHR_ID_LENGTH+1, strName.c_str() );
	StringCchCopy( m_pData->szEPin, CHAR_STORAGE_LOCK_PASS_SIZE+1, strPass.c_str() );

	int nRETURN = CGMToolOdbcBase::GetInstance()->StorageLock_Save( m_pData );
	if( nRETURN != DB_OK ){
		CDebugSet::MsgBox( GetSafeHwnd(), "Failure to Save Data! Info( Num:%d )", m_dwNum );
		return FALSE;
	}

	return TRUE;
}