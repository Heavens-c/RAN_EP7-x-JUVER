#include "StdAfx.h"
#include "InventoryPageWear.h"
#include "ItemImage.h"
#include "GLGaeaClient.h"
#include "GLItemMan.h"
#include "InnerInterface.h"
#include "ItemMove.h"
#include "BasicButton.h"
#include "GameTextControl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const int CInventoryPageWear::nOUTOFRANGE = -1;

CInventoryPageWear::CInventoryPageWear () 
	: m_pMouseOver ( NULL )

	/*equipment lock, Juver, 2018/01/16 */
	, m_pButtonLock(NULL)
	, m_pButtonUnlock(NULL)
{
}

CInventoryPageWear::~CInventoryPageWear ()
{
}

void CInventoryPageWear::CreateSubControl ( int nClassType )
{
	CString	strInvenWearBack[GLCI_NUM_8CLASS] = 
	{
		"INVENTORY_PAGE_WEAR_FIGHTER_M",
		"INVENTORY_PAGE_WEAR_ARMS_M",
		"INVENTORY_PAGE_WEAR_ARCHER_W",
		"INVENTORY_PAGE_WEAR_SPIRIT_W",
		"INVENTORY_PAGE_WEAR_EXTREME_M",
		"INVENTORY_PAGE_WEAR_EXTREME_W",
		"INVENTORY_PAGE_WEAR_FIGHTER_W",
		"INVENTORY_PAGE_WEAR_ARMS_W",
		"INVENTORY_PAGE_WEAR_ARCHER_M",
		"INVENTORY_PAGE_WEAR_SPIRIT_M",
		"INVENTORY_PAGE_WEAR_SCIENTIST_M",
		"INVENTORY_PAGE_WEAR_SCIENTIST_W",
		"INVENTORY_PAGE_WEAR_ASSASSIN_M",
		"INVENTORY_PAGE_WEAR_ASSASSIN_W",
		"INVENTORY_PAGE_WEAR_TRICKER_M",
		"INVENTORY_PAGE_WEAR_TRICKER_W",
	};

	CreateControl ( strInvenWearBack[nClassType].GetString () );

	{
		CString strInvenWearItem[ITEM_IMAGE_SIZE] = 
		{
			"INVENTORY_WEAR_ITEM_IMAGE0",
			"INVENTORY_WEAR_ITEM_IMAGE1",
			"INVENTORY_WEAR_ITEM_IMAGE2",
			"INVENTORY_WEAR_ITEM_IMAGE3",
			"INVENTORY_WEAR_ITEM_IMAGE4",
			"INVENTORY_WEAR_ITEM_IMAGE5",
			"INVENTORY_WEAR_ITEM_IMAGE6",
			"INVENTORY_WEAR_ITEM_IMAGE7",
			"INVENTORY_WEAR_ITEM_IMAGE8",
			"INVENTORY_WEAR_ITEM_IMAGE9",
			"INVENTORY_WEAR_ITEM_IMAGE10",
			"INVENTORY_WEAR_ITEM_IMAGE11",
			"INVENTORY_WEAR_ITEM_IMAGE12",
			"INVENTORY_WEAR_ITEM_IMAGE13",
			"INVENTORY_WEAR_ITEM_IMAGE14",
			"INVENTORY_WEAR_ITEM_IMAGE15",
			"INVENTORY_WEAR_ITEM_IMAGE16",
		};

		CString strInvenWearOver[ITEM_IMAGE_SIZE] = 
		{
			"INVENTORY_WEAR_OVER_IMAGE0",
			"INVENTORY_WEAR_OVER_IMAGE1",
			"INVENTORY_WEAR_OVER_IMAGE2",
			"INVENTORY_WEAR_OVER_IMAGE3",
			"INVENTORY_WEAR_OVER_IMAGE4",
			"INVENTORY_WEAR_OVER_IMAGE5",
			"INVENTORY_WEAR_OVER_IMAGE6",
			"INVENTORY_WEAR_OVER_IMAGE7",
			"INVENTORY_WEAR_OVER_IMAGE8",
			"INVENTORY_WEAR_OVER_IMAGE9",
			"INVENTORY_WEAR_OVER_IMAGE10",
			"INVENTORY_WEAR_OVER_IMAGE11",
			"INVENTORY_WEAR_OVER_IMAGE12",
			"INVENTORY_WEAR_OVER_IMAGE13",
			"INVENTORY_WEAR_OVER_IMAGE14",
			"INVENTORY_WEAR_OVER_IMAGE15",
			"INVENTORY_WEAR_OVER_IMAGE16",

		};

		for ( int i = 0; i < ITEM_IMAGE_SIZE; i++ )
		{
			m_pItemImage[i] = CreateItemImage ( strInvenWearItem[i].GetString (), ITEM_IMAGE0 + i );
			m_pSlotDisplay[i] = CreateControl ( strInvenWearOver[i].GetString () );
			m_pSlotDisplay[i]->SetVisibleSingle ( FALSE );
		}
	}

	m_pMouseOver = CreateControl ( "ITEM_MOUSE_OVER" );
//	m_pSlotDisplay = CreateControl ( "TRADE_INVENTORY_OVER_0" );
//	m_pSlotBlockDisplay = CreateControl ( "TRADE_OVER_0" );


	/*equipment lock, Juver, 2018/01/16 */
	m_pButtonLock = new CBasicButton;
	m_pButtonLock->CreateSub ( this, "INVEN_BUTTON_LOCK", UI_FLAG_DEFAULT, BUTTON_KEY_LOCK );
	m_pButtonLock->CreateFlip ( "INVEN_BUTTON_LOCK_F", CBasicButton::CLICK_FLIP );
	m_pButtonLock->SetFlip(false);
	m_pButtonLock->SetVisibleSingle ( FALSE );
	RegisterControl ( m_pButtonLock );

	m_pButtonUnlock = new CBasicButton;
	m_pButtonUnlock->CreateSub ( this, "INVEN_BUTTON_UNLOCK", UI_FLAG_DEFAULT, BUTTON_KEY_UNLOCK );
	m_pButtonUnlock->CreateFlip ( "INVEN_BUTTON_UNLOCK_F", CBasicButton::CLICK_FLIP );
	m_pButtonUnlock->SetFlip(false);
	m_pButtonUnlock->SetVisibleSingle ( FALSE );
	RegisterControl ( m_pButtonUnlock );
}

CUIControl*	CInventoryPageWear::CreateControl ( const char* szControl )
{
	CUIControl* pControl = new CUIControl;
	pControl->CreateSub ( this, szControl );
	RegisterControl ( pControl );

	return pControl;
}

CItemImage*	CInventoryPageWear::CreateItemImage ( const char* szControl, UIGUID ControlID )
{
	CItemImage* pItemImage = new CItemImage;
	pItemImage->CreateSub ( this, szControl, UI_FLAG_DEFAULT, ControlID );
	pItemImage->CreateSubControl ();
	RegisterControl ( pItemImage );

	return pItemImage;
}

EMSLOT CInventoryPageWear::IMAGE2EMSLOT ( int nIndex )
{
	switch ( nIndex )
	{	
	case ITEM_IMAGE0:	return SLOT_HEADGEAR;	//	�Ӹ�
	case ITEM_IMAGE1:	return SLOT_NECK;		//	�����
	case ITEM_IMAGE2:	return SLOT_UPPER;		//	����
	case ITEM_IMAGE3:	return SLOT_LHAND;		//	�޼յ���
	case ITEM_IMAGE4:	return SLOT_WRIST;		//	�ո�
	case ITEM_IMAGE5:	return SLOT_HAND;		//	�尩
	case ITEM_IMAGE6:	return SLOT_LOWER;		//	����
	case ITEM_IMAGE7:	return SLOT_LFINGER;	//	�޼� �հ���
	case ITEM_IMAGE8:	return SLOT_RHAND;		//	�����յ���
	case ITEM_IMAGE9:	return SLOT_FOOT;		//	�Ź�
	case ITEM_IMAGE10:	return SLOT_RFINGER;	//	������ �հ���	
	case ITEM_IMAGE11:	return SLOT_VEHICLE;
	case ITEM_IMAGE14:	return SLOT_WING;
	case ITEM_IMAGE15:	return SLOT_BELT;
	case ITEM_IMAGE16:	return SLOT_LEARRING;
	case ITEM_IMAGE17:	return SLOT_REARRING;
	case ITEM_IMAGE18:	return SLOT_ACCESSORY;
	}

	GASSERT ( 0 && "������ ����ϴ�." );
	return SLOT_TSIZE;
}

void CInventoryPageWear::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	SetItemIndex ( nOUTOFRANGE );
	if ( m_pMouseOver ) m_pMouseOver->SetVisibleSingle ( FALSE );
//	if ( m_pSlotDisplay ) m_pSlotDisplay->SetVisibleSingle ( FALSE );
//	if ( m_pSlotBlockDisplay ) m_pSlotBlockDisplay->SetVisibleSingle ( FALSE );

	//	����, ��ų �̹��� ���̱�
	CItemMove* pItemMove = CInnerInterface::GetInstance().GetItemMove ();
	SNATIVEID sHOLD_ITEM_ID(false);
//	bool bFOUND_TOWEAR = false;
	if ( pItemMove ) sHOLD_ITEM_ID = pItemMove->GetItem();

	for ( int i = 0; i < SLOT_NSIZE; i++ )
	{
		const SITEMCUSTOM& sItemCustomOld = GetItem ( i );

		EMSLOT emSlot = IMAGE2EMSLOT ( i + ITEM_IMAGE0 );
		SITEMCUSTOM sItemCustom = GLGaeaClient::GetInstance().GetCharacter()->GET_SLOT_ITEM ( emSlot );

		//	NOTE
		//		���� �����Ӱ� ���Ͽ�,
		//		����Ÿ�� �޶��� ��쿡��,
		//		�ε�/��ε� �۾��� �����Ѵ�.
		if ( sItemCustom != sItemCustomOld )
		{		
			if ( sItemCustom.sNativeID != NATIVEID_NULL () )
			{
				LoadItem ( i, sItemCustom );
			}
			else
			{
				UnLoadItem ( i );
			}
		}

		m_pSlotDisplay[i]->SetVisibleSingle ( FALSE );

		//	NOTE
		//		������ ��ġ ǥ��
		if ( sHOLD_ITEM_ID != NATIVEID_NULL () /*&& !bFOUND_TOWEAR*/ )
		{
			if ( GLGaeaClient::GetInstance().GetCharacter()->CHECKSLOT_ITEM ( sHOLD_ITEM_ID, emSlot ) )
			{
				const UIRECT& rcImagePos = m_pItemImage[i]->GetGlobalPos ();
				D3DXVECTOR2 vPos ( rcImagePos.left, rcImagePos.top );

				if ( GLGaeaClient::GetInstance().GetCharacter()->ACCEPT_ITEM ( sHOLD_ITEM_ID ) )
				{
					m_pSlotDisplay[i]->SetVisibleSingle ( TRUE );
				}

//				bFOUND_TOWEAR = true;
			}
		}
	}
	
	/*puton lock, Juver, 2018/01/13 */
	BOOL bEnabled = GLGaeaClient::GetInstance().GetCharacter()->m_bEnableEquipmentLock;
	BOOL bLocked = GLGaeaClient::GetInstance().GetCharacter()->m_bEquipmentLockStatus;
	if ( m_pButtonLock )	m_pButtonLock->SetVisibleSingle( bEnabled && bLocked );
	if ( m_pButtonUnlock )	m_pButtonUnlock->SetVisibleSingle( bEnabled && !bLocked );

	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );
}

void CInventoryPageWear::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
	switch ( ControlID )
	{
	case ITEM_IMAGE0:
	case ITEM_IMAGE1:
	case ITEM_IMAGE2:
	case ITEM_IMAGE3:
	case ITEM_IMAGE4:
	case ITEM_IMAGE5:
	case ITEM_IMAGE6:
	case ITEM_IMAGE7:
	case ITEM_IMAGE8:
	case ITEM_IMAGE9:
	case ITEM_IMAGE10:
	case ITEM_IMAGE11:
	case ITEM_IMAGE12:
	case ITEM_IMAGE13:
	case ITEM_IMAGE14:
	case ITEM_IMAGE15:
	case ITEM_IMAGE16:
	case ITEM_IMAGE17:
	case ITEM_IMAGE18:

		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				int nIndex = ControlID - ITEM_IMAGE0;
				SetItemIndex ( nIndex );

				if ( !CInnerInterface::GetInstance().IsFirstItemSlot () ) return ;

				//	����, ��ų �̹��� ���̱�
				CItemMove* pItemMove = CInnerInterface::GetInstance().GetItemMove ();
				if ( !pItemMove )
				{
					GASSERT ( 0 && "CItemMove�� ���Դϴ�." );
					return ;
				}

				if ( pItemMove->GetItem () != NATIVEID_NULL () )
				{
					const UIRECT& rcSlotPos = m_pItemImage[nIndex]->GetGlobalPos ();
					pItemMove->SetGlobalPos ( rcSlotPos );						

					AddMessageEx ( UIMSG_MOUSEIN_WEARSLOT | UIMSG_TOTOPPARENT );
				}				

				//	���콺 ǥ�� �׵θ�
				if ( pItemMove->GetItem () == NATIVEID_NULL () && m_pItemImage[m_nIndex]->GetItem () != NATIVEID_NULL () )
				{
					const UIRECT& rcImagePos = m_pItemImage[nIndex]->GetGlobalPos ();
					m_pMouseOver->SetGlobalPos ( rcImagePos );
					m_pMouseOver->SetVisibleSingle ( TRUE );
				}
			}
		}
		break;

		/*puton lock, Juver, 2018/01/13 */
	case BUTTON_KEY_LOCK:
	case BUTTON_KEY_UNLOCK:
		{
			if( CHECK_MOUSEIN_LBUPLIKE( dwMsg ) )
				CInnerInterface::GetInstance().OpenEquipmentLockInput();
		}break;
	}
}

EMSLOT CInventoryPageWear::GetItemSlot ()
{
	return IMAGE2EMSLOT ( GetItemIndex () + ITEM_IMAGE0 );
}

void CInventoryPageWear::LoadItem ( int nIndex, SITEMCUSTOM& ref_sItemCustom )
{
	m_ItemCustomArray[nIndex] = ref_sItemCustom;

	SITEM* pItemData = GLItemMan::GetInstance().GetItem ( ref_sItemCustom.sNativeID );
	m_pItemImage[nIndex]->SetItem ( pItemData->sBasicOp.sICONID, pItemData->GetInventoryFile(), pItemData->sBasicOp.sNativeID );
}

SITEMCUSTOM& CInventoryPageWear::GetItem ( int nIndex )
{
	return m_ItemCustomArray[nIndex];
}

void CInventoryPageWear::UnLoadItem ( int nIndex )
{
	m_ItemCustomArray[nIndex].sNativeID = NATIVEID_NULL ();
	m_pItemImage[nIndex]->ResetItem ();
}