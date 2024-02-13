//	���� ������
//
//	���� �ۼ��� : ���⿱
//	���� ������ : 
//	�α�
//		[2003.12.6]
//			@ �ۼ�
//

#pragma	once

#include "../Lib_Engine/GUInterface/UIGroup.h"
#include "GLInventory.h"

class	CItemSlotEx;
class	CBasicScrollBarEx;
struct	SINVENITEM;

//inven page
class	CBasicButton;
class	CBasicTextBox;

class	CTradeInventoryPage : public CUIGroup
{
private:
static	const	int	nSTARTLINE;
static	const	int	nOUTOFRANGE;

protected:
	enum
	{
		nONE_VIEW_SLOT_DEFAULT = 4,
		nMAX_ONE_VIEW_SLOT = 10,
		//inven page
		nMAX_PAGES = 3,
	};

	enum
	{
		ITEM_SLOT0 = NO_ID + 1,
		ITEM_SLOT1,
		ITEM_SLOT2,
		ITEM_SLOT3,
		ITEM_SLOT4,
		ITEM_SLOT5,
		ITEM_SLOT6,
		ITEM_SLOT7,
		ITEM_SLOT8,
		ITEM_SLOT9,
		ITEM_SLOT_END = ITEM_SLOT0 + EM_INVENSIZE_Y,
		//inven page
		PAGE_BUTTON0,
		PAGE_BUTTON1,
		PAGE_BUTTON2,
	};

public:
	CTradeInventoryPage ();
	virtual	~CTradeInventoryPage ();

public:
	void	CreateSubControl ();

	void	UpdateBLOCK ();

public:
	virtual void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );
	virtual	void TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg );

protected:
	void	ResetAllItemSlotRender ( int index, int nTotal );
	void	SetItemSlotRender ( int nStartIndex, int nTotal );

protected:
	CItemSlotEx*	CreateItemSlot ( CString strKeyword, UIGUID ControlID );
	CUIControl*	CreateControl ( const char* szControl );

public:
	void	SetOneViewSlot ( const int& nMAX_ONE_VIEW );
	const int& GetOneViewSlot () const						{ return m_nONE_VIEW_SLOT; }

public:
	void	SetItemIndex ( int nPosX, int nPosY );
	void	GetItemIndex ( int* pnPosX, int* pnPosY );

public:
	void	LoadItemPage ( GLInventory &ItemData );
	void	LoadItem ( SINVENITEM& ref_InvenItem );

	SINVENITEM&	GetItem ( int nPosX, int nPosY );

public:
	void	UnLoadItemPage ();
	void	UnLoadItem ( int nPosX, int nPosY );
	void	OpenPage ( int nPage );

public:
	void	ResetAllFlipItem ();
	void	UpdateFlipItem ( GLInventory& ref_TradeInventory );

private:
	CItemSlotEx*	m_pItemSlotArray[EM_INVENSIZE_Y];
	CUIControl*		m_pItemSlotArrayDummy[nMAX_ONE_VIEW_SLOT];
	//inven page
	CBasicButton*			m_pPages[nMAX_PAGES];
	CBasicTextBox*			m_pPagesText[nMAX_PAGES];

	CBasicScrollBarEx*	m_pScrollBar;

private:
	int		m_nCurPos;
	int		m_nPosX;
	int		m_nPosY;

private:
	int		m_nONE_VIEW_SLOT;
};