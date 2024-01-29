// CharEditPageInven.cpp : implementation file
//

#include "stdafx.h"
#include "GMTool.h"
#include "CharEditPageInven.h"


#include "CharEditTab.h"
#include "EtcFunction.h"
#include "HLibDataConvert.h"
#include "GLCharData.h"
#include "GLInventory.h"
#include "GLItemMan.h"

#include "Logic/GMToolGlobal.h"
#include "DlgSItemCustomEdit.h"
#include "DlgItem.h"

// CCharEditPageInven dialog

IMPLEMENT_DYNAMIC(CCharEditPageInven, CPropertyPage)

CCharEditPageInven::CCharEditPageInven(LOGFONT logfont, SCHARDATA2* pData)
	: CPropertyPage(CCharEditPageInven::IDD)
	, m_pFont ( NULL )
	, m_pData( NULL )
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);

	m_pData = pData;
}

CCharEditPageInven::~CCharEditPageInven()
{
	SAFE_DELETE ( m_pFont );
}

void CCharEditPageInven::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHAREDIT_INVEN_LIST, m_List);
}


BEGIN_MESSAGE_MAP(CCharEditPageInven, CPropertyPage)
	ON_BN_CLICKED(IDC_CHAREDIT_INVEN_BUTTON_ADD, OnBnClickedChareditInvenButtonAdd)
	ON_BN_CLICKED(IDC_CHAREDIT_INVEN_BUTTON_EDIT, OnBnClickedChareditInvenButtonEdit)
	ON_BN_CLICKED(IDC_CHAREDIT_INVEN_BUTTON_DELETE, OnBnClickedChareditInvenButtonDelete)
	ON_BN_CLICKED(IDC_CHAREDIT_INVEN_BUTTON_CLEAR, OnBnClickedChareditInvenButtonClear)
	ON_NOTIFY(NM_DBLCLK, IDC_CHAREDIT_INVEN_LIST, OnNMDblclkChareditInvenList)
END_MESSAGE_MAP()


// CCharEditPageInven message handlers
BOOL CCharEditPageInven::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	m_pSheetTab->ChangeDialogFont( this, m_pFont, CDF_TOPLEFT );
	m_bDlgInit = TRUE;

	RECT rectCtrl;
	m_List.SetExtendedStyle ( m_List.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES );
	m_List.GetClientRect ( &rectCtrl );
	m_List.InsertColumn( 0, "", LVCFMT_LEFT, ( 5* ( rectCtrl.right - rectCtrl.left ) ) / 100 );
	m_List.InsertColumn( 1, "Pos[X/Y]", LVCFMT_LEFT, ( 20* ( rectCtrl.right - rectCtrl.left ) ) / 100 );
	m_List.InsertColumn( 2, "Num", LVCFMT_LEFT, ( 10* ( rectCtrl.right - rectCtrl.left ) ) / 100 );
	m_List.InsertColumn( 3, "Item", LVCFMT_LEFT, ( 60* ( rectCtrl.right - rectCtrl.left ) ) / 100 );

	SetWin_Text( this, IDC_CHAREDIT_INVEN_EDIT_TOTAL, "" );

	ShowData();

	return TRUE;  
}

void CCharEditPageInven::ShowData()
{
	m_List.DeleteAllItems();

	if ( !m_pData ){
		return;
	}

	m_List.SetRedraw( FALSE );

	GLInventory::CELL_MAP *pItemList = m_pData->m_cInventory.GetItemList();
	GLInventory::CELL_MAP_ITER iter_start = pItemList->begin();
	for ( int i=0; iter_start != pItemList->end(); ++iter_start, ++i )
	{
		const SINVENITEM* pInvenItem = (*iter_start).second;

		std::string strNAME = "Unknown Item";
		SITEM* pITEM = GLItemMan::GetInstance().GetItem( pInvenItem->sItemCustom.sNativeID );
		if ( pITEM )
			strNAME = pITEM->GetName();

		m_List.InsertItem( i, "" );
		m_List.SetItemText( i, 1, _HLIB::cstringformat( "[%02d/%02d]", pInvenItem->wPosX, pInvenItem->wPosY ).GetString() );
		m_List.SetItemText( i, 2, _HLIB::cstring_dword( pInvenItem->sItemCustom.wTurnNum ).GetString() );
		m_List.SetItemText( i, 3, _HLIB::cstringformat( "[%03d/%03d] %s", pInvenItem->sItemCustom.sNativeID.wMainID, pInvenItem->sItemCustom.sNativeID.wSubID, strNAME.c_str() ).GetString() );
		SNATIVEID sPOS( pInvenItem->wPosX, pInvenItem->wPosY );
		m_List.SetItemData ( i, sPOS.dwID );
	}

	m_List.SetRedraw( TRUE );

	CString strTotal;
	strTotal.Format( "Total Items:%d", m_pData->m_cInventory.GetNumItems() );
	SetWin_Text( this, IDC_CHAREDIT_INVEN_EDIT_TOTAL, strTotal.GetString() );
}

void CCharEditPageInven::OnBnClickedChareditInvenButtonAdd()
{
	if ( !m_pData ){
		return;
	}

	SINVENITEM sINVENITEM;
	sINVENITEM.sItemCustom.tBORNTIME = CTime::GetCurrentTime().GetTime();
	sINVENITEM.sItemCustom.wTurnNum = 1;
	sINVENITEM.sItemCustom.cGenType = EMGEN_DEFAULT;
	sINVENITEM.sItemCustom.cChnID = 0;
	sINVENITEM.sItemCustom.cFieldID = 0;
	sINVENITEM.sItemCustom.lnGenNum = 0;

	CDlgItem dlg( this );
	if ( dlg.DoModal() != IDOK ){
		return;
	}

	sINVENITEM.sItemCustom.sNativeID.wMainID = dlg.m_SELECTED.wMainID;
	sINVENITEM.sItemCustom.sNativeID.wSubID = dlg.m_SELECTED.wSubID;

	/*item color, Juver, 2018/01/08 */
	SITEM* pitem_data_check = GLItemMan::GetInstance().GetItem( sINVENITEM.sItemCustom.sNativeID );
	if ( pitem_data_check && pitem_data_check->sBasicOp.bItemColor )
	{
		sINVENITEM.sItemCustom.wColor1 = pitem_data_check->sBasicOp.wItemColor1;
		sINVENITEM.sItemCustom.wColor2 = pitem_data_check->sBasicOp.wItemColor2;
	}

	SITEM* pITEM = GLItemMan::GetInstance().GetItem ( sINVENITEM.sItemCustom.sNativeID );
	if ( !pITEM ) {
		CDebugSet::MsgBox( GetSafeHwnd(), "Invalid Item! ( %d %d )", 
			sINVENITEM.sItemCustom.sNativeID.wMainID,
			sINVENITEM.sItemCustom.sNativeID.wSubID );
		return;
	}

	WORD wPosX(0), wPosY(0);
	BOOL bOk = m_pData->m_cInventory.FindInsrtable ( pITEM->sBasicOp.wInvenSizeX, pITEM->sBasicOp.wInvenSizeY, wPosX, wPosY );
	if ( !bOk ){
		CDebugSet::MsgBox( GetSafeHwnd(), "No space to insert item!" );
		return;
	}

	BOOL bINSERT = m_pData->m_cInventory.InsertItem( sINVENITEM.sItemCustom, wPosX, wPosY );
	if ( !bINSERT ){
		CDebugSet::MsgBox( "Unable to insert item! Report this bug!" );
		return;
	}

	SINVENITEM* pInvenItem = m_pData->m_cInventory.FindPosItem( wPosX, wPosY );
	if ( pInvenItem && pInvenItem->sItemCustom.sNativeID == sINVENITEM.sItemCustom.sNativeID ){
		if ( CDebugSet::MsgBoxYesNo( GetSafeHwnd(), "Edit Inserted Item?") == IDYES ){
			CDlgSItemCustomEdit dlgItemEdit( 
				&pInvenItem->sItemCustom, 
				EMITEMEDIT_TYPE_INVEN_ITEM_EDIT,
				SLOT_NSIZE,
				pInvenItem->wPosX,
				pInvenItem->wPosY,
				this );

			if ( dlgItemEdit.DoModal() == IDOK ){
			}
		}
	}

	ShowData();

	for( int nItem=0; nItem<m_List.GetItemCount(); nItem++){
		DWORD dwID = m_List.GetItemData( nItem );
		if( dwID == SNATIVEID( wPosX, wPosY ).dwID ){
			m_List.EnsureVisible( nItem, TRUE );
			m_List.SetItemState( nItem, LVIS_SELECTED, LVIS_SELECTED );
			GotoDlgCtrl(GetDlgItem(m_List.GetDlgCtrlID())); 
		}
	}
}

void CCharEditPageInven::OnBnClickedChareditInvenButtonEdit()
{
	EditItem();
}

void CCharEditPageInven::OnBnClickedChareditInvenButtonDelete()
{
	if ( !m_pData ){
		return;
	}

	int nCHECKED = 0;
	for( int nItem=0; nItem<m_List.GetItemCount(); nItem++ ){
		BOOL bChecked = m_List.GetCheck( nItem );
		if( bChecked){
			DWORD dwID = (DWORD) m_List.GetItemData ( nItem );
			SNATIVEID sPos( dwID );
			m_pData->m_cInventory.DeleteItem( sPos.wMainID, sPos.wSubID );
			nCHECKED ++;
		}
	}

	if ( nCHECKED == 0 ){
		CDebugSet::MsgBox( GetSafeHwnd(), "Nothing selected Use Check boxes to select" );
	}

	ShowData();
}

void CCharEditPageInven::OnBnClickedChareditInvenButtonClear()
{
	if ( !m_pData ){
		return;
	}

	if ( CDebugSet::MsgBoxYesNo( GetSafeHwnd(), "Delete All Items?" ) == IDYES ){
		m_pData->m_cInventory.DeleteItemAll();
		ShowData();
	}
}

void CCharEditPageInven::OnNMDblclkChareditInvenList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	EditItem();
}

void CCharEditPageInven::EditItem()
{
	if ( !m_pData ){
		return;
	}

	int nSelect = m_List.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if( nSelect == -1 ){
		return;
	}

	DWORD dwID = (DWORD) m_List.GetItemData ( nSelect );
	SNATIVEID sPos( dwID );

	SINVENITEM* pINVENITEM = m_pData->m_cInventory.FindPosItem( sPos.wMainID, sPos.wSubID );
	if ( pINVENITEM ){
		CDlgSItemCustomEdit dlgItemEdit( 
			&pINVENITEM->sItemCustom, 
			EMITEMEDIT_TYPE_INVEN_ITEM_EDIT,
			SLOT_NSIZE,
			pINVENITEM->wPosX,
			pINVENITEM->wPosY,
			this );

		if ( dlgItemEdit.DoModal() == IDOK ){
			ShowData();

			for( int nItem=0; nItem<m_List.GetItemCount(); nItem++){
				DWORD dwID = m_List.GetItemData( nItem );
				if( dwID == SNATIVEID( pINVENITEM->wPosX, pINVENITEM->wPosY ).dwID ){
					m_List.EnsureVisible( nItem, TRUE );
					m_List.SetItemState( nItem, LVIS_SELECTED, LVIS_SELECTED );
					GotoDlgCtrl(GetDlgItem(m_List.GetDlgCtrlID())); 
				}
			}
		}
	}
}