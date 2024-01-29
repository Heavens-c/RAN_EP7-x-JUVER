// PageInventoryLock.cpp : implementation file
//

#include "stdafx.h"
#include "GMTool.h"
#include "PageInventoryLock.h"

#include "SheetWithTab.h"
#include "Logic/GMToolGlobal.h"
#include "Logic/GMToolOdbcBase.h"
#include ".\pageequipmentlock.h"

#include "EtcFunction.h"
#include "HLibDataConvert.h"
#include "DlgInventoryLockEdit.h"
#include "DlgInventoryLockAdd.h"

// CPageInventoryLock dialog

IMPLEMENT_DYNAMIC(CPageInventoryLock, CPropertyPage)
CPageInventoryLock::CPageInventoryLock(LOGFONT logfont)
	: CPropertyPage(CPageInventoryLock::IDD)
	, m_pFont ( NULL )
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);

	for ( int i=0; i<MAX_PAGE_INVENTORY_LOCK_MODAL_DIALOG; ++i ){
		m_pToolDialog[i] = NULL;
	}
}

CPageInventoryLock::~CPageInventoryLock()
{
	SAFE_DELETE ( m_pFont );
}

void CPageInventoryLock::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_INVENTORY_LOCK, m_List );
}


BEGIN_MESSAGE_MAP(CPageInventoryLock, CPropertyPage)
	ON_BN_CLICKED(IDC_INVENTORY_LOCK_PAGE_BUTTON_ADD, OnBnClickedInventoryLockPageButtonAdd)
	ON_BN_CLICKED(IDC_INVENTORY_LOCK_PAGE_BUTTON_EDIT, OnBnClickedInventoryLockPageButtonEdit)
	ON_BN_CLICKED(IDC_INVENTORY_LOCK_PAGE_BUTTON_DELETE, OnBnClickedInventoryLockPageButtonDelete)
	ON_BN_CLICKED(IDC_INVENTORY_LOCK_PAGE_BUTTON_SEARCH, OnBnClickedInventoryLockPageButtonSearch)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_INVENTORY_LOCK, OnNMDblclkListInventoryLock)
END_MESSAGE_MAP()


// CPageInventoryLock message handlers
BOOL CPageInventoryLock::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	m_pSheetTab->ChangeDialogFont( this, m_pFont, CDF_TOPLEFT );
	m_bDlgInit = TRUE;

	RECT rectCtrl;
	m_List.SetExtendedStyle ( m_List.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );
	m_List.GetClientRect ( &rectCtrl );
	m_List.InsertColumn( 0, "Num", LVCFMT_LEFT, ( 10* ( rectCtrl.right - rectCtrl.left ) ) / 100 );
	m_List.InsertColumn( 1, "ChaNum", LVCFMT_LEFT, ( 15* ( rectCtrl.right - rectCtrl.left ) ) / 100 );
	m_List.InsertColumn( 2, "ChaName", LVCFMT_LEFT, ( 30* ( rectCtrl.right - rectCtrl.left ) ) / 100 );
	m_List.InsertColumn( 3, "InvenPass", LVCFMT_LEFT, ( 15* ( rectCtrl.right - rectCtrl.left ) ) / 100 );
	m_List.InsertColumn( 4, "Date", LVCFMT_LEFT, ( 30* ( rectCtrl.right - rectCtrl.left ) ) / 100 );

	SetWin_Combo_Init( this, IDC_INVENTORY_LOCK_PAGE_COMBO_SEARCH, GMTOOL_GLOBAL::strInventoryLockPageSearchType, EMINVENTORY_LOCK_PAGE_SEARCH_TYPE_SIZE );
	SetWin_Combo_Init( this, IDC_INVENTORY_LOCK_PAGE_COMBO_SEARCH_LIMITNUM, GMTOOL_GLOBAL::strSearchLimit, EMSEARCH_LIMIT_SIZE );

	return TRUE;  
}

int CPageInventoryLock::DialogNewID()
{
	int nNewDlg = MAX_PAGE_INVENTORY_LOCK_MODAL_DIALOG;
	for ( int i=0; i<MAX_PAGE_INVENTORY_LOCK_MODAL_DIALOG; ++i ){
		if ( !m_pToolDialog[i] ){
			nNewDlg = i;
			break;
		}
	}

	return nNewDlg;
}

void CPageInventoryLock::DialogDeleteID( int nDialogID )
{
	if ( nDialogID < 0 || nDialogID >= MAX_PAGE_INVENTORY_LOCK_MODAL_DIALOG ){
		return;
	}

	m_pToolDialog[nDialogID] = NULL;
}

int CPageInventoryLock::DialogGetTotalActive()
{
	int nDlg = 0;
	for ( int i=0; i<MAX_PAGE_INVENTORY_LOCK_MODAL_DIALOG; ++i ){
		if ( m_pToolDialog[i] ){
			nDlg ++;
		}
	}

	return nDlg;
}

void CPageInventoryLock::OnBnClickedInventoryLockPageButtonAdd()
{
	CDlgInventoryLockAdd dlg(this);
	if ( dlg.DoModal() == IDOK ){

	}
}

void CPageInventoryLock::OnBnClickedInventoryLockPageButtonEdit()
{
	int nSelect = m_List.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if( nSelect == -1 ) {
		CDebugSet::MsgBoxAfx( "Nothing Selected!" );
		return;
	}

	DWORD dwNum = (DWORD)m_List.GetItemData( nSelect );

	int nDialogID = DialogNewID();
	if ( nDialogID == MAX_PAGE_INVENTORY_LOCK_MODAL_DIALOG ){
		CDebugSet::MsgBoxAfx( "Max dialog used!" );
		return;
	}

	CDlgInventoryLockEdit* pdlg;
	pdlg = new CDlgInventoryLockEdit( nDialogID, dwNum, this );
	pdlg->Create( CWnd::GetDesktopWindow() );
	m_pToolDialog[nDialogID] = pdlg;
}

void CPageInventoryLock::OnBnClickedInventoryLockPageButtonDelete()
{
	int nSelect = m_List.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if( nSelect == -1 ) {
		CDebugSet::MsgBoxAfx( "Nothing Selected!" );
		return;
	}

	if ( CDebugSet::MsgBoxYesNo( GetSafeHwnd(), "Delete Selected?" ) == IDYES ){
		DWORD dwNum = (DWORD)atoi( m_List.GetItemText ( nSelect, 0 ) );
		DWORD dwChaNum = (DWORD)atoi( m_List.GetItemText ( nSelect, 1 ) );

		int nReturn = CGMToolOdbcBase::GetInstance()->InventoryLock_Delete( dwNum );
		if ( nReturn != DB_OK )
		{
			CDebugSet::MsgBox( GetSafeHwnd(), "failure to delete equipment lock :%d", dwNum );
			return;
		}
		else 
		{
			nReturn =  CGMToolOdbcBase::GetInstance()->InventoryLock_Delete_To_Char( dwChaNum );
			if ( nReturn != DB_OK )
			{
				CDebugSet::MsgBox( GetSafeHwnd(), "failure to delete equipment lock to char :%d", dwChaNum );
				return;
			}
			else
			{
				m_List.DeleteAllItems();
				CDebugSet::MsgBox( "Delete Done" );
			}
		}
	}
}

void CPageInventoryLock::OnBnClickedInventoryLockPageButtonSearch()
{
	std::string strSearch = GetWin_Text( this, IDC_INVENTORY_LOCK_PAGE_EDIT_SEARCH );
	EMINVENTORY_LOCK_PAGE_SEARCH_TYPE emType = static_cast<EMINVENTORY_LOCK_PAGE_SEARCH_TYPE> ( GetWin_Combo_Sel( this, IDC_INVENTORY_LOCK_PAGE_COMBO_SEARCH ) );
	EMSEARCH_LIMIT emLIMIT = static_cast<EMSEARCH_LIMIT> ( GetWin_Combo_Sel( this, IDC_INVENTORY_LOCK_PAGE_COMBO_SEARCH_LIMITNUM ) );

	SGMTOOL_INVENTORY_LOCK_DATA_SIMPLE_MAP mapResult;

	switch( emType )
	{
	case EMINVENTORY_LOCK_PAGE_SEARCH_TYPE_CHANUM:
		{
			if( strSearch.size() <= 0 ){
				CDebugSet::MsgBoxAfx( "Invalid Search!" );
				GotoDlgCtrl(GetDlgItem(IDC_INVENTORY_LOCK_PAGE_EDIT_SEARCH)); 
				return;
			}

			if ( GMTOOL_GLOBAL::IsBadNumber( strSearch.c_str() ) ){
				CDebugSet::MsgBoxAfx( "Use numbers only!" );
				GotoDlgCtrl(GetDlgItem(IDC_INVENTORY_LOCK_PAGE_EDIT_SEARCH)); 
				return;
			}

			int nSEARCH = atoi( strSearch.c_str() );
			CGMToolOdbcBase::GetInstance()->InventoryLock_Find_ChaNum( nSEARCH, mapResult, GetSearchLimitNum( emLIMIT ) );
		}break;


	case EMINVENTORY_LOCK_PAGE_SEARCH_TYPE_CHANAME:
		{
			if( strSearch.size() <= 0 ){
				CDebugSet::MsgBoxAfx( "Invalid Search!" );
				GotoDlgCtrl(GetDlgItem(IDC_INVENTORY_LOCK_PAGE_EDIT_SEARCH)); 
				return;
			}

			if ( GMTOOL_GLOBAL::IsBadString( strSearch.c_str() ) ){
				CDebugSet::MsgBoxAfx( "Search contains invalid characters!" );
				GotoDlgCtrl(GetDlgItem(IDC_INVENTORY_LOCK_PAGE_EDIT_SEARCH)); 
				return;
			}

			if( strSearch.size() < MIN_STRING_SEARCH ){
				CDebugSet::MsgBoxAfx( "Search string too short!" );
				GotoDlgCtrl(GetDlgItem(IDC_INVENTORY_LOCK_PAGE_EDIT_SEARCH)); 
				return;
			}

			CGMToolOdbcBase::GetInstance()->InventoryLock_Find_ChaName( strSearch.c_str(), mapResult, GetSearchLimitNum( emLIMIT ) );
		}break;

	case EMINVENTORY_LOCK_PAGE_SEARCH_TYPE_EPIN:
		{
			if( strSearch.size() <= 0 ){
				CDebugSet::MsgBoxAfx( "Invalid Search!" );
				GotoDlgCtrl(GetDlgItem(IDC_INVENTORY_LOCK_PAGE_EDIT_SEARCH)); 
				return;
			}

			if ( GMTOOL_GLOBAL::IsBadString( strSearch.c_str() ) ){
				CDebugSet::MsgBoxAfx( "Search contains invalid characters!" );
				GotoDlgCtrl(GetDlgItem(IDC_INVENTORY_LOCK_PAGE_EDIT_SEARCH)); 
				return;
			}

			if( strSearch.size() < MIN_STRING_SEARCH ){
				CDebugSet::MsgBoxAfx( "Search string too short!" );
				GotoDlgCtrl(GetDlgItem(IDC_INVENTORY_LOCK_PAGE_EDIT_SEARCH)); 
				return;
			}

			CGMToolOdbcBase::GetInstance()->InventoryLock_Find_EPin( strSearch.c_str(), mapResult, GetSearchLimitNum( emLIMIT ) );
		}break;
	};

	if ( mapResult.size() <=0 ){
		CDebugSet::MsgBoxAfx( "No Results" );
		return;
	}

	m_List.DeleteAllItems();

	m_List.SetRedraw( FALSE );

	SGMTOOL_INVENTORY_LOCK_DATA_SIMPLE_MAP_ITER mapiter = mapResult.begin();
	for( int i=0; mapiter != mapResult.end(); ++mapiter, ++i ){
		const SGMTOOL_INVENTORY_LOCK_DATA_SIMPLE sDATA = (*mapiter).second;

		m_List.InsertItem( i, _HLIB::cstring_dword( sDATA.dwNum ).GetString() );
		m_List.SetItemText( i, 1, _HLIB::cstring_dword( sDATA.dwChaNum ).GetString() );
		m_List.SetItemText( i, 2, sDATA.szChaName );
		m_List.SetItemText( i, 3, sDATA.szEPin );
		m_List.SetItemText( i, 4, _HLIB::cstring_timet12( sDATA.tDate ).GetString() );
		m_List.SetItemData ( i, sDATA.dwNum );
	}

	m_List.SetRedraw( TRUE );
}

void CPageInventoryLock::OnNMDblclkListInventoryLock(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;

	int nSelect = m_List.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if( nSelect == -1 ) {
		return;
	}

	DWORD dwNum = (DWORD)m_List.GetItemData( nSelect );

	int nDialogID = DialogNewID();
	if ( nDialogID == MAX_PAGE_INVENTORY_LOCK_MODAL_DIALOG ){
		CDebugSet::MsgBoxAfx( "Max dialog used!" );
		return;
	}

	CDlgInventoryLockEdit* pdlg;
	pdlg = new CDlgInventoryLockEdit( nDialogID, dwNum, this );
	pdlg->Create( CWnd::GetDesktopWindow() );
	m_pToolDialog[nDialogID] = pdlg;
}
