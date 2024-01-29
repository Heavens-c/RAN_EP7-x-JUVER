#ifndef GLCROWDATA_H_
#define GLCROWDATA_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include <string>
#include "./GLCharData.h"
#include "./GLCharDefine.h"
#include "./GLInventory.h"
#include "../NpcTalk/NpcDialogueSet.h"

#include "../../Lib_Engine/G-Logic/GLDefine.h"
#include "../../Lib_Engine/Meshs/SAnimation.h"
#include "../../Lib_Engine/NaviMesh/NavigationPath.h"
 
#include "./GLCrowDataBasic.h"
#include "./GLCrowDataAction.h"
#include "./GLCrowDataGen.h"
#include "./GLCrowDataAttack.h"

/*npc shop, Juver, 2017/07/25 */
#include "./GLCrowDataNPCShop.h" 

/*pvp tyranny, Juver, 2017/08/25 */
#include "./GLPVPTyrannyDefine.h" 

/*item exchange, Juver, 2017/10/11 */
#include "./GLCrowDataItemExchange.h"

//	Note : �ټ� ������ �߻��� ó�� ����.
//
struct SGENITEM
{
	enum
	{
		EMGNUM		= 5,
		EMGSPEC		= 30,
		EMSPEC_NULL	= -1
	};

	struct SGNUM	//	�߻� ������ Ȯ��.
	{
		WORD	wNum;
		float	fRateL;
		float	fRateH;

		SGNUM () :
			wNum(0),
			fRateL(100.0f),
			fRateH(100.0f)
		{
		}
	};

	struct SGITEMSPEC	//	�߻� �����۱��� Ȯ��.
	{
		DWORD	dwSPECID;
		float	fRateL;
		float	fRateH;
		bool	bSPECID;

		SGITEMSPEC () :
			dwSPECID(EMSPEC_NULL),
			fRateL(100.0f),
			fRateH(100.0f),
			bSPECID( false )
		{
		}
	};

	float		m_fGenRate;				//	�߻� Ȯ��.
	SGNUM		m_sGenNum[EMGNUM];		//	�߻� ������ Ȯ�� ����.
	SGITEMSPEC	m_sItemSpec[EMGSPEC];	//	�߻� ������ ��.

	SGENITEM() :
		m_fGenRate(0)
	{
	}

	BOOL LOADFILE ( const char* szFileName );

	BOOL ISGEN ( float fGenRate = 1.0f );							//	�߻� Ȯ��.
	WORD SELECTNUM ();						//	�߻� ����.
	DWORD SELECTSPECID ( float fGEN_RATE, bool& bSPECID );	//	�߻� ��.
};

//	Note : Question ������ �߻��� ó�� ���� by ���
//
struct SQTGENITEM
{
	enum { EMQTMAX = 20 };

	struct ITEM
	{
		SNATIVEID	m_sGenItemID;
		float		m_fGenRate;

		ITEM() : m_sGenItemID(false), m_fGenRate(0)
		{
		}
	};

	ITEM	m_sItem[EMQTMAX];
	int		m_nItemNum;

	SQTGENITEM() : m_nItemNum(0)
	{
	}

	BOOL LOADFILE ( const char * szFileName );

	SNATIVEID SELECTITEM(); // ������ �߻�
};

typedef std::map<DWORD,LONGLONG>	NPCSELL_PRICE_MAP;
typedef NPCSELL_PRICE_MAP::iterator NPCSELL_PRICE_MAP_ITER;

struct SCROWDATA
{
	enum
	{
		VERSION = 0x0101,
		EMMAXATTACK = SCROWACTION::ACTION_MAXATTACK,

		FILE_SBASIC			= 1,
		FILE_SACTION		= 2,
		FILE_SGEN			= 3,
		FILE_SATTACK		= 4,
		FILE_END_DATA		= 0xEDEDEDED,
	};

	union
	{
		struct
		{
			SCROWBASIC			m_sBasic;
		};

		//changes to SCROWBASIC structure or variable type/arrangement must be also applied here
		struct
		{
			SNATIVEID			sNativeID;					//	���� ID.
			EMCROW				m_emCrow;					//	Npc, Mob.
			EMTRIBE				m_emTribe;					//	����.
			EMBRIGHT			m_emBright;					//	�Ӽ� (��/��)
			char				m_szName[CHAR_SZNAME];		//	�̸�.
			WORD				m_wLevel;					//	����.
			DWORD				m_dwHP;						//	HP
			WORD				m_wMP;						//	MP
			WORD				m_wSP;						//	SP
			float				m_fIncHP;					//	HP ȸ����.
			float				m_fIncMP;					//	MP ȸ����.
			float				m_fIncSP;					//	SP ȸ����.
			WORD				m_wDefense;					//	����.
			WORD				m_wViewRange;				//	�þ� �Ÿ�.
			WORD				m_wAvoidRate;				//	ȸ����.
			WORD				m_wHitRate;					//	������.
			DWORD				m_dwBonusExp;				//	�߰�����ġ.
			WORD				m_wBonusCP;
			SRESIST				m_sResist;					//	���װ�.
			bool				m_bOverlapAttack;			//  �������� ���� ���� ����
			DWORD				m_dwGenTime;
			WORD				m_wGatherTimeLow;			// ä���ð�(Low)
			WORD				m_wGatherTimeHigh;			// ä���ð�(High)
			float				m_fGatherRate;				// ä�� Ȯ��
			WORD				m_wGatherAnimation;			// �ִϸ��̼�
			PETTYPE				m_emPetType;
			SUMMON_TYPE			m_emSummonType;
			EMNPC_TYPE			m_emNPCType;
			bool				m_bHideName;				/*hide crow name, Juver, 2017/09/01 */
			DWORD				m_dwNotice;					/*crow notice, Juver, 2017/11/25 */
			DWORD				dummy_var_0;
			bool				dummy_var_1;
			bool				dummy_var_2;
			EMNPC_CTF_FLAG_TYPE	m_emCTFType;				/*pvp capture the flag, Juver, 2018/02/03 */
		};
	};

	SCROWACTION				m_sAction;
	SCROWGEN				m_sGenerate;

	//	npc talk ����.
	CNpcDialogueSet			m_sNpcTalkDlg;

	//	����, Skill ����.
	SCROWATTACK				m_sCrowAttack[EMMAXATTACK];

	//	���� �����۱� ���� [server ������ �ʿ��� ����]
	SGENITEM				m_sGenItem;
	SQTGENITEM				m_sQtGenItem; // Question Item ���� by ���

	//	�Ǹ� ���.
	std::string				m_strSaleType[SCROWACTION::SALENUM];
	GLInventory				m_sSaleItems[SCROWACTION::SALENUM];
	//  �Ǹ� NPC���� �Էµ� ����
	NPCSELL_PRICE_MAP		m_mapNpcSellPrice;

	//	���ϸ��̼� ����. ( �ð�/���� ) [server ������ �ʿ��� ����]
	//	
	VECANIATTACK*			m_pANIMATION;

	VECANIATTACK&			GetAnimation ( EMANI_MAINTYPE emMType, EMANI_SUBTYPE emSType );

	/*npc shop, Juver, 2017/07/25 */
	SNPC_SHOP				m_sNPCShop;

	/*item exchange, Juver, 2017/10/11 */
	SNPC_ITEM_EXCHANGE		m_sNPCItemExchange;

	BOOL IsCdCertify ()		{ return m_sAction.m_dwActFlag&EMCROWACT_CDCERTIFY; }
	BOOL IsBusUnit ()		{ return m_sAction.m_dwActFlag&EMCROWACT_BUSUNIT; }
	BOOL IsTarShort ()		{ return m_sAction.m_dwActFlag&EMCROWACT_TARSHORT; }
	BOOL IsIgnoreShock()	{ return m_sAction.m_dwActFlag&EMCROWACT_IGNORE_SHOCK; }

	BOOL IsInVisible ()		{ return m_sAction.m_dwActFlag&EMCROWACT_INVISIBLE; }
	BOOL IsRecVisible ()	{ return m_sAction.m_dwActFlag&EMCROWACT_RECVISIBLE; }

	BOOL IsBarrier ()		{ return m_sAction.m_dwActFlag&EMCROWACT_BARRIER; }
	BOOL IsPosHold ()		{ return m_sAction.m_dwActFlag&EMCROWACT_POSHOLD; }
	BOOL IsDirHold ()		{ return m_sAction.m_dwActFlag&EMCROWACT_DIRHOLD; }

	DWORD GetSaleNum () { return SCROWACTION::SALENUM; }
	GLInventory* GetSaleInven ( DWORD dwIndex )
	{
		if ( GetSaleNum() <= dwIndex )	return NULL;
		return &m_sSaleItems[dwIndex];
	}
	std::string GetSaleType ( DWORD dwIndex )
	{
		if ( GetSaleNum() <= dwIndex )	return "";
		return m_strSaleType[dwIndex];
	}
	LONGLONG GetNpcSellPrice ( DWORD dwID )
	{
		NPCSELL_PRICE_MAP_ITER it = m_mapNpcSellPrice.find(dwID);
		if( it == m_mapNpcSellPrice.end() )
		{
			return 0;
		}
		return it->second;
	}

	const char* GetName();
	const char* GetTalkFile ()		{ return m_sAction.m_strTalkFile.c_str(); }
	const char* GetSkinObjFile ()	{ return m_sAction.m_strSkinObj.c_str(); }

	void LoadAniSet ( const char* szSkinObj );
	SCROWDATA& Assign ( SCROWDATA &Data );

	HRESULT LoadFile ( basestream &SFile, BOOL bServer, bool bPastLoad );
	HRESULT SaveFile ( CSerialFile &SFile );

	static VOID SaveCsvHead ( std::fstream &SFile );
	VOID SaveCsv ( std::fstream &SFile );
	VOID LoadCsv ( CStringArray &StrArray );

	SCROWDATA () :
		m_pANIMATION(NULL)
	{
		for ( int i=0; i<SCROWACTION::SALENUM; ++i )
		{
			m_sSaleItems[i].SetState ( SALE_INVEN_X, SALE_INVEN_Y );
			m_mapNpcSellPrice.clear();
		}
	}

	~SCROWDATA ()
	{
		SAFE_DELETE_ARRAY(m_pANIMATION);
	}
};
typedef SCROWDATA*		PCROWDATA;

BOOL SaleInvenLoadFile ( const char* szFileName, GLInventory &_sINVENTORY, std::string &_strSaleType, NPCSELL_PRICE_MAP &_mapNpcSellPrice );

class GLCrowDataMan
{
public:
	enum
	{
		ENCODE_VER_OLD	= 0x0102,
		ENCODE_VER		= 0x0200,
		VERSION			= 0x0200,
		MAX_CROW_MID	= 1024,
		MAX_CROW_SID	= 1024
	};

public:
	static const char*	_FILEHEAD;
	static const char*	_LOGFILE;
	static const char*	_STRINGTABLE;

protected:
	char				m_szFileName[MAX_PATH];

	PCROWDATA**			m_ppPCROWDATA;
	bool				m_bModify;

	LPDIRECT3DDEVICEQ	m_pd3dDevice;

public:
	PCROWDATA GetMainCrowData ( WORD wMainID );

	PCROWDATA GetCrowData ( WORD wMID, WORD wSID );
	PCROWDATA GetCrowData ( SNATIVEID sNativeID );

	bool	ValidData ();
	bool	IsModify ()								{ return m_bModify; }

public:
	WORD FindFreeCrowDataMID ();
	WORD FindFreeCrowDataSID ( WORD wMainID );

public:
	BOOL InsertCrowData ( WORD wMID, WORD wSID, PCROWDATA pCrowData, bool binner=false );
	BOOL InsertCrowData ( SNATIVEID sNativeID, PCROWDATA pCrowData, bool binner=false )
	{
		return InsertCrowData ( sNativeID.wMainID, sNativeID.wSubID, pCrowData, binner );
	}

public:
	BOOL DeleteCrowData ( WORD wMID, WORD wSID );
	BOOL DeleteCrowData ( SNATIVEID sNativeID );

public:
	HRESULT OneTimeSceneInit ();
	HRESULT FinalCleanup ();

public:
	HRESULT	SyncStringTable();
	HRESULT SyncUpdateData ();
	HRESULT SaveCsvFile( CWnd* pWnd );
	HRESULT LoadCsvFile( CWnd* pWnd );

public:
	HRESULT LoadFile ( const char* szFile, BOOL bServer, bool bPastLoad );
	HRESULT SaveFile ( const char* szFile );

public:
	GLCrowDataMan ();

public:
	~GLCrowDataMan ();

public:
	static GLCrowDataMan& GetInstance();
};

struct SDROP_CROW
{
	enum { CROW_GEM=0x0001, };

	SNATIVEID			sNativeID;	//	Crow ���� ID.

	SNATIVEID			sMapID;		//	�� ID.
	DWORD				dwCeID;		//	�� ID.
	DWORD				dwGlobID;	//	���� �޸� �ε�����.
	D3DXVECTOR3			vPos;		//	��ġ.
	D3DXVECTOR3			vDir;		//	����.
	FLOAT				fScale;		//  ũ��.

	// ���� Ŭ���̾�Ʈ�� ���� ��ġ ����ȭ�� ����
	D3DXVECTOR3			vStartPos;  // �̵��� ������ġ. �߰��Ȱ�
	NavigationPath::WAYPOINT sNextWaypoint; // ���� ��������Ʈ. �߰��Ȱ�

	DWORD				dwNowHP;	//	������.
	WORD				wNowMP;		//	���ŷ�.

	DWORD				dwFLAGS;	//	��Ÿ �Ӽ�.
	EMACTIONTYPE		emAction;	//	�ൿ.
	DWORD				dwActState;	//	�ൿ ����.

	STARGETID			TargetID;	//	��ǥ ����, ��ġ.

	SDROP_SKILLFACT		sSKILLFACT[SKILLFACT_SIZE];
	SDROP_STATEBLOW		sSTATEBLOWS[EMBLOW_MULTI];

	/*pvp tyranny, Juver, 2017/08/25 */
	WORD				m_wTyrannyOwner;
	float				m_fTyrannyDamage[TYRANNY_SCHOOL_SIZE];

	/*pvp capture the flag, Juver, 2018/02/06 */
	bool				m_bCaptureTheFlagCrowHide;

	SDROP_CROW () 
		: sMapID(NATIVEID_NULL())
		, dwCeID(0)
		, dwGlobID(0)
		, vPos(0,0,0)
		, vDir(1,0,0)
		, dwNowHP(0)
		, wNowMP(0)
		, dwFLAGS(NULL)
		, emAction(GLAT_IDLE)
		, dwActState(0)
		, m_wTyrannyOwner(TYRANNY_SCHOOL_SIZE)	/*pvp tyranny, Juver, 2017/08/25 */
		, m_bCaptureTheFlagCrowHide(false)		/*pvp capture the flag, Juver, 2018/02/06 */
	{
		/*pvp tyranny, Juver, 2017/08/25 */
		for ( int i=0; i<TYRANNY_SCHOOL_SIZE; ++ i )
			m_fTyrannyDamage[i] = 0.0f;
	}
};

struct SDROP_MATERIAL
{
	enum { CROW_GEM=0x0001, };

	SNATIVEID			sNativeID;	//	Crow ���� ID.

	SNATIVEID			sMapID;		//	�� ID.
	DWORD				dwCeID;		//	�� ID.
	DWORD				dwGlobID;	//	���� �޸� �ε�����.
	D3DXVECTOR3			vPos;		//	��ġ.
	D3DXVECTOR3			vDir;		//	����.

	DWORD				dwFLAGS;	//	��Ÿ �Ӽ�.
	EMACTIONTYPE		emAction;	//	�ൿ.
	DWORD				dwActState;	//	�ൿ ����.

	SDROP_MATERIAL () 
		: sMapID(NATIVEID_NULL())
		, dwCeID(0)
		, dwGlobID(0)
		, vPos(0,0,0)
		, vDir(1,0,0)
		, dwFLAGS(NULL)
		, emAction(GLAT_IDLE)
		, dwActState(0)
	{
	}
};


#endif // GLCROWDATA_H_
