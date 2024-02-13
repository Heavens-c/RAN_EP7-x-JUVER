//	�⺻ ���� ǥ��
//
//	���� �ۼ��� : ���⿱
//	���� ������ : 
//	�α�
//		[2003.11.21]
//			@ �ۼ�
//

#pragma	once

#include "../Lib_Engine/GUInterface/UIGroup.h"

class	CBasicTextBox;
class	CBasicTextButton;
class	CSelectCharacterUserPanelPage;
class	CSelectCharacterUserPanelButton;

const DWORD UIMSG_MOUSEIN_SELECT_USERPANEL = UIMSG_USER1;

class CSelectCharacterUserPanel : public CUIGroup
{
private:
	enum
	{
		SELECT_CHARACTER_USERPANEL_BTN = NO_ID + 1,
	};
public:
	CSelectCharacterUserPanel ();
	virtual	~CSelectCharacterUserPanel ();

public:
	void	CreateSubControl ();

public:
	virtual void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );
	virtual	void TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg );

private:
	CSelectCharacterUserPanelPage*	m_pSelectCharacterUserPanelPage;
	CSelectCharacterUserPanelButton*	m_pSelectCharacterUserPanelButton;
};