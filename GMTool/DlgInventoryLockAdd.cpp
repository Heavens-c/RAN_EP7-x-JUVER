// DlgInventoryLockAdd.cpp : implementation file
//

#include "stdafx.h"
#include "GMTool.h"
#include "DlgInventoryLockAdd.h"
#include ".\dlgequipmentlockadd.h"
#include "Logic/GMToolData.h"
#include "Logic/GMToolGlobal.h"
#include "Logic/GMToolOdbcBase.h"

#include "EtcFunction.h"

// CDlgInventoryLockAdd dialog

IMPLEMENT_DYNAMIC(CDlgInventoryLockAdd, CDialog)
CDlgInventoryLockAdd::CDlgInventoryLockAdd(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInventoryLockAdd::IDD, pParent)
{
}

CDlgInventoryLockAdd::~CDlgInventoryLockAdd()
{
}

void CDlgInventoryLockAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgInventoryLockAdd, CDialog)
	ON_BN_CLICKED(IDOK2, OnBnClickedOk2)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
END_MESSAGE_MAP()


// CDlgInventoryLockAdd message handlers

void CDlgInventoryLockAdd::OnBnClickedOk2()
{
	std::string strName = GetWin_Text( this, IDC_INVENTORY_LOCK_EDIT_CHANAME );
	std::string strPass = GetWin_Text( this, IDC_INVENTORY_LOCK_EDIT_EPASS ); 
	DWORD dwChaNum = GetWin_Num_int( this, IDC_INVENTORY_LOCK_EDIT_CHANUM );

	if ( strName.size() < MIN_CHAR_ID || strName.size() > MAX_CHAR_ID ){
		CDebugSet::MsgBox( GetSafeHwnd(), "ChaName can only have %d to %d characters", MIN_CHAR_ID, MAX_CHAR_ID );
		GotoDlgCtrl(GetDlgItem(IDC_INVENTORY_LOCK_EDIT_CHANAME)); 
		return;
	}

	if ( strPass.size() < CHAR_INVENTORY_LOCK_PASS_SIZE || strPass.size() > CHAR_INVENTORY_LOCK_PASS_SIZE ){
		CDebugSet::MsgBox( GetSafeHwnd(), "Pass can only have %d to %d characters", CHAR_INVENTORY_LOCK_PASS_SIZE, CHAR_INVENTORY_LOCK_PASS_SIZE );
		GotoDlgCtrl(GetDlgItem(IDC_INVENTORY_LOCK_EDIT_EPASS)); 
		return;
	}

	if ( GMTOOL_GLOBAL::IsBadString( strName.c_str() ) ){
		CDebugSet::MsgBox( GetSafeHwnd(), "ChaName contains invalid characters!" );
		GotoDlgCtrl(GetDlgItem(IDC_INVENTORY_LOCK_EDIT_CHANAME)); 
		return;
	}

	if ( GMTOOL_GLOBAL::IsBadString2( strName.c_str() ) ){
		CDebugSet::MsgBox( GetSafeHwnd(), "ChaName contains invalid characters!" );
		GotoDlgCtrl(GetDlgItem(IDC_INVENTORY_LOCK_EDIT_CHANAME)); 
		return;
	}

	if ( GMTOOL_GLOBAL::IsBadString( strPass.c_str() ) ){
		CDebugSet::MsgBox( GetSafeHwnd(), "ChaName contains invalid characters!" );
		GotoDlgCtrl(GetDlgItem(IDC_INVENTORY_LOCK_EDIT_EPASS)); 
		return;;
	}

	if ( GMTOOL_GLOBAL::IsBadString2( strPass.c_str() ) ){
		CDebugSet::MsgBox( GetSafeHwnd(), "ChaName contains invalid characters!" );
		GotoDlgCtrl(GetDlgItem(IDC_INVENTORY_LOCK_EDIT_EPASS)); 
		return;
	}

	if ( dwChaNum <= 0 )
	{
		CDebugSet::MsgBox( GetSafeHwnd(), "Invalid ChaNum!" );
		GotoDlgCtrl(GetDlgItem(IDC_INVENTORY_LOCK_EDIT_CHANUM)); 
		return;
	}

	SGMTOOL_INVENTORY_LOCK_DATA_SIMPLE sData;
	sData.dwChaNum = GetWin_Num_int( this, IDC_INVENTORY_LOCK_EDIT_CHANUM );
	StringCchCopy( sData.szChaName, CHR_ID_LENGTH+1, strName.c_str() );
	StringCchCopy( sData.szEPin, CHAR_INVENTORY_LOCK_PASS_SIZE+1, strPass.c_str() );

	int nRETURN = CGMToolOdbcBase::GetInstance()->InventoryLock_New( &sData );
	if ( nRETURN == 1 )
	{
		CDebugSet::MsgBox( GetSafeHwnd(), "Data Exist" );
		return;
	}
	else if ( nRETURN == 2 )
	{
		CDebugSet::MsgBox( GetSafeHwnd(), "Character Not Exist" );
		return;
	}
	else if( nRETURN != DB_OK ){
		CDebugSet::MsgBox( GetSafeHwnd(), "Failure to Create New Data" );
		return;
	}

	OnOK();
}

void CDlgInventoryLockAdd::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}
