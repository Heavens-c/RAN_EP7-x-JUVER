//	�⺻ ���� ǥ��
//
//	���� �ۼ��� : ���⿱
//	���� ������ : 
//	�α�
//		[2003.11.21]
//			@ �ۼ�
//

#pragma	once

#include "UIOuterWindow.h"

class	CBasicTextBox;
class	CBasicTextButton;


class CSelectCharacterUserPanelPage : public CUIOuterWindow
{
public:
	CSelectCharacterUserPanelPage ();
	virtual	~CSelectCharacterUserPanelPage ();

public:
	void	CreateSubControl ();

public:
	virtual void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );

private:
    CBasicTextBox* m_pEmailTextBox;
    CBasicTextBox* m_pBattlePointTextBox;
    CBasicTextBox* m_pGameTimeTextBox;
    CBasicTextBox* m_pUserPointTextBox;
    CBasicTextBox* m_pPasswordTextBox;
    CBasicTextBox* m_pPinTextBox;
private:
	USHORT m_uUserPoint;
	DWORD m_dwGameTime;
	USHORT m_uBattlePoint;
	CString m_strEmail;
};