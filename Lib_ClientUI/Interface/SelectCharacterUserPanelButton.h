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


class CSelectCharacterUserPanelButton : public CUIGroup
{
private:
	enum
	{
		SELECT_CHARACTER_USERPANEL_CP = NO_ID + 1,
		SELECT_CHARACTER_USERPANEL_CPN,
		SELECT_CHARACTER_USERPANEL_CE,
		SELECT_CHARACTER_USERPANEL_GTCVT,
		SELECT_CHARACTER_USERPANEL_PPCVT,
	};
public:
	CSelectCharacterUserPanelButton ();
	virtual	~CSelectCharacterUserPanelButton ();

public:
	void	CreateSubControl ();

public:
	virtual void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );
	virtual	void TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg );

private:
	CBasicTextButton* m_pButtonCE;
	CBasicTextButton* m_pButtonCP;
	CBasicTextButton* m_pButtonCPN;
	CBasicTextButton* m_pButtonGTCVT;
	CBasicTextButton* m_pButtonPPCVT;
};