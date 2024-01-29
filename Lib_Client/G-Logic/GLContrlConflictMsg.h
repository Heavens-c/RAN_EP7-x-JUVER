#pragma once

#include "GLContrlBaseMsg.h"

namespace GLMSG
{
	#pragma pack(1)

	//---------------------------------------------------------------------------NET
	struct SNETPC_REQ_CONFRONT
	{
		NET_MSG_GENERIC		nmg;
		EMCONFT_TYPE		emTYPE;
		DWORD				dwID;

		SCONFT_OPTION		sOption;

		SNETPC_REQ_CONFRONT () 
			: emTYPE(EMCONFT_ONE)
			, dwID(GAEAID_NULL)
		{
			nmg.dwSize = sizeof(SNETPC_REQ_CONFRONT);
			nmg.nType = NET_MSG_GCTRL_CONFRONT;
			GASSERT(nmg.dwSize<=NET_DATA_BUFSIZE);
		}
	};

	//---------------------------------------------------------------------------NET
	struct SNETPC_REQ_CONFRONT_TAR
	{
		NET_MSG_GENERIC		nmg;
		EMCONFT_TYPE		emTYPE;
		DWORD				dwID;

		SCONFT_OPTION		sOption;

		SNETPC_REQ_CONFRONT_TAR () 
			: emTYPE(EMCONFT_ONE)
			, dwID(GAEAID_NULL)
		{
			nmg.dwSize = sizeof(SNETPC_REQ_CONFRONT_TAR);
			nmg.nType = NET_MSG_GCTRL_CONFRONT_TAR;
			GASSERT(nmg.dwSize<=NET_DATA_BUFSIZE);
		}
	};

	//---------------------------------------------------------------------------NET
	struct SNETPC_REQ_CONFRONT_ANS
	{
		NET_MSG_GENERIC		nmg;
		EMCONFT_TYPE		emTYPE;
		DWORD				dwID;
		EMCONFRONT_FB		emFB;

		SCONFT_OPTION		sOption;

		SNETPC_REQ_CONFRONT_ANS () 
			: emTYPE(EMCONFT_ONE)
			, dwID(GAEAID_NULL)
			, emFB(EMCONFRONT_FAIL)
		{
			nmg.dwSize = sizeof(SNETPC_REQ_CONFRONT_ANS);
			nmg.nType = NET_MSG_GCTRL_CONFRONT_ANS;
			GASSERT(nmg.dwSize<=NET_DATA_BUFSIZE);
		}
	};

	//---------------------------------------------------------------------------NET
	struct SNETPC_REQ_CONFRONT_FB
	{
		NET_MSG_GENERIC		nmg;
		EMCONFT_TYPE		emTYPE;
		DWORD				dwID;
		EMCONFRONT_FB		emFB;
		float				fTIME;

		SNETPC_REQ_CONFRONT_FB () 
			: emTYPE(EMCONFT_ONE)
			, dwID(GAEAID_NULL)
			, emFB(EMCONFRONT_FAIL)
			, fTIME(0.0f)
		{
			nmg.dwSize = sizeof(SNETPC_REQ_CONFRONT_FB);
			nmg.nType = NET_MSG_GCTRL_CONFRONT_FB;
			GASSERT(nmg.dwSize<=NET_DATA_BUFSIZE);
		}
	};

	struct SNETPC_CONFRONT_START2_FLD
	{
		NET_MSG_GENERIC		nmg;
		EMCONFT_TYPE		emTYPE;
		DWORD				dwTARID;

		SCONFT_OPTION		sOption;

		SNETPC_CONFRONT_START2_FLD () 
			: emTYPE(EMCONFT_ONE)
			, dwTARID(GAEAID_NULL)
		{
			nmg.dwSize = sizeof(SNETPC_CONFRONT_START2_FLD);
			nmg.nType = NET_MSG_GCTRL_CONFRONT_START2_FLD;
			GASSERT(nmg.dwSize<=NET_DATA_BUFSIZE);
		}
	};

	struct SNETPC_CONFRONT_START2_CLT
	{
		NET_MSG_GENERIC		nmg;
		EMCONFT_TYPE		emTYPE;
		DWORD				dwTARID;

		D3DXVECTOR3			vPosition;
		SCONFT_OPTION		sOption;

		SNETPC_CONFRONT_START2_CLT () 
			: emTYPE(EMCONFT_ONE)
			, dwTARID(GAEAID_NULL)
			, vPosition(FLT_MAX,FLT_MAX,FLT_MAX)
		{
			nmg.dwSize = sizeof(SNETPC_CONFRONT_START2_CLT);
			nmg.nType = NET_MSG_GCTRL_CONFRONT_START2_CLT;
			GASSERT(nmg.dwSize<=NET_DATA_BUFSIZE);
		}
	};

	struct SNETPC_CONFRONT_FIGHT2_CLT
	{
		NET_MSG_GENERIC		nmg;

		SNETPC_CONFRONT_FIGHT2_CLT ()
		{
			nmg.dwSize = sizeof(SNETPC_CONFRONT_FIGHT2_CLT);
			nmg.nType = NET_MSG_GCTRL_CONFRONT_FIGHT2_CLT;
			GASSERT(nmg.dwSize<=NET_DATA_BUFSIZE);
		}
	};

	struct SNETPC_CONFRONT_END2_FLD
	{
		NET_MSG_GENERIC		nmg;
		EMCONFRONT_END		emEND;

		SNETPC_CONFRONT_END2_FLD() 
			: emEND(EMCONFRONT_END_FAIL)
		{
			nmg.dwSize = sizeof(SNETPC_CONFRONT_END2_FLD);
			nmg.nType = NET_MSG_GCTRL_CONFRONT_END2_FLD;
			GASSERT(nmg.dwSize<=NET_DATA_BUFSIZE);
		}
	};

	struct SNETPC_CONFRONT_END2_CLT
	{
		NET_MSG_GENERIC		nmg;
		EMCONFRONT_END		emEND;

		SNETPC_CONFRONT_END2_CLT() 
			: emEND(EMCONFRONT_END_FAIL)
		{
			nmg.dwSize = sizeof(SNETPC_CONFRONT_END2_CLT);
			nmg.nType = NET_MSG_GCTRL_CONFRONT_END2_CLT;
			GASSERT(nmg.dwSize<=NET_DATA_BUFSIZE);
		}
	};

	struct SNETPC_CONFRONT_END2_CLT_MBR
	{
		NET_MSG_GENERIC		nmg;
		DWORD				dwID;

		SNETPC_CONFRONT_END2_CLT_MBR() 
			: dwID(0)
		{
			nmg.dwSize = sizeof(SNETPC_CONFRONT_END2_CLT_MBR);
			nmg.nType = NET_MSG_GCTRL_CONFRONT_END2_CLT_MBR;
			GASSERT(nmg.dwSize<=NET_DATA_BUFSIZE);
		}
	};

	struct SNETPC_CONFRONT_END2_CLT_BRD : public SNETPC_BROAD
	{
		EMCONFRONT_END		emEND;

		SNETPC_CONFRONT_END2_CLT_BRD() :
			emEND(EMCONFRONT_END_FAIL)
		{
			nmg.dwSize = sizeof(SNETPC_CONFRONT_END2_CLT_BRD);
			nmg.nType = NET_MSG_GCTRL_CONFRONT_END2_CLT_BRD;
			GASSERT(nmg.dwSize<=NET_DATA_BUFSIZE);
		}
	};

	struct SNETPC_CONFRONT_END2_AGT
	{
		NET_MSG_GENERIC		nmg;
		EMCONFRONT_END		emEND;

		SNETPC_CONFRONT_END2_AGT() 
			: emEND(EMCONFRONT_END_FAIL)
		{
			nmg.dwSize = sizeof(SNETPC_CONFRONT_END2_AGT);
			nmg.nType = NET_MSG_GCTRL_CONFRONT_END2_AGT;
			GASSERT(nmg.dwSize<=NET_DATA_BUFSIZE);
		}
	};

	struct SNETPC_CONFRONTPTY_CHECKMBR2_FLD
	{
		NET_MSG_GENERIC		nmg;
		SNATIVEID			sMapID;

		DWORD				dwPARTY_A;
		DWORD				dwPARTY_B;

		SCONFT_OPTION		sOption;

		SNETPC_CONFRONTPTY_CHECKMBR2_FLD () 
			: sMapID(false)
			, dwPARTY_A(PARTY_NULL)
			, dwPARTY_B(PARTY_NULL)
		{
			nmg.dwSize = sizeof(SNETPC_CONFRONTPTY_CHECKMBR2_FLD);
			nmg.nType = NET_MSG_GCTRL_CONFRONTPTY_CHECKMBR_FLD;
			GASSERT(nmg.dwSize<=NET_DATA_BUFSIZE);
		}
	};

	struct SNETPC_CONFRONTPTY_CHECKMBR2_AGT
	{
		NET_MSG_GENERIC		nmg;

		SNATIVEID			sMapID;

		D3DXVECTOR3			vPosition;
		DWORD				dwPARTY_A;
		DWORD				dwPARTY_B;

		DWORD				dwPARTY_A_MEMBER[MAXPARTY];
		DWORD				dwPARTY_B_MEMBER[MAXPARTY];

		SCONFT_OPTION		sOption;

		SNETPC_CONFRONTPTY_CHECKMBR2_AGT () 
			: sMapID(false)
			, vPosition(0,0,0)
			, dwPARTY_A(PARTY_NULL)
			, dwPARTY_B(PARTY_NULL)
		{
			nmg.dwSize = sizeof(SNETPC_CONFRONTPTY_CHECKMBR2_AGT);
			nmg.nType = NET_MSG_GCTRL_CONFRONTPTY_CHECKMBR_AGT;
			GASSERT(nmg.dwSize<=NET_DATA_BUFSIZE);

			memset(dwPARTY_A_MEMBER, 0xff, sizeof(DWORD)*MAXPARTY );
			memset(dwPARTY_B_MEMBER, 0xff, sizeof(DWORD)*MAXPARTY );
		}
	};

	struct SNETPC_CONFRONTPTY_START2_FLD
	{
		NET_MSG_GENERIC		nmg;
		SNATIVEID			sMapID;

		DWORD				dwPARTY_A;
		DWORD				dwPARTY_B;

		DWORD				dwPARTY_A_MEMBER[MAXPARTY];
		DWORD				dwPARTY_B_MEMBER[MAXPARTY];

		D3DXVECTOR3			vPos;
		SCONFT_OPTION		sOption;

		SNETPC_CONFRONTPTY_START2_FLD () 
			: sMapID(SNATIVEID(false))
			, dwPARTY_A(PARTY_NULL)
			, dwPARTY_B(PARTY_NULL)
			, vPos(0,0,0)
		{
			nmg.dwSize = sizeof(SNETPC_CONFRONTPTY_START2_FLD);
			nmg.nType = NET_MSG_GCTRL_CONFRONTPTY_START2_FLD;
			GASSERT(nmg.dwSize<=NET_DATA_BUFSIZE);

			memset(dwPARTY_A_MEMBER, 0xff, sizeof(DWORD)*MAXPARTY );
			memset(dwPARTY_B_MEMBER, 0xff, sizeof(DWORD)*MAXPARTY );
		}
	};

	struct SNETPC_CONFRONTPTY_START2_CLT
	{
		NET_MSG_GENERIC		nmg;

		CHAR				szName[CHR_ID_LENGTH+1];

		DWORD				dwconftPARTY;
		DWORD				dwCONFRONT_MY_MEMBER[MAXPARTY];
		DWORD				dwCONFRONT_TAR_MEMBER[MAXPARTY];

		D3DXVECTOR3			vPosition;
		SCONFT_OPTION		sOption;

		SNETPC_CONFRONTPTY_START2_CLT () 
			: dwconftPARTY(PARTY_NULL)
			, vPosition(FLT_MAX,FLT_MAX,FLT_MAX)
		{
			nmg.dwSize = sizeof(SNETPC_CONFRONTPTY_START2_CLT);
			nmg.nType = NET_MSG_GCTRL_CONFRONTPTY_START2_CLT;
			GASSERT(nmg.dwSize<=NET_DATA_BUFSIZE);

			memset(szName, 0, sizeof(CHAR) * (CHR_ID_LENGTH+1));
		}
	};

	struct SNETPC_CONFRONTPTY_END2_FLD
	{
		NET_MSG_GENERIC		nmg;

		DWORD				dwPARTY_A;
		DWORD				dwPARTY_B;

		EMCONFRONT_END		emEND_A;
		EMCONFRONT_END		emEND_B;

		SNETPC_CONFRONTPTY_END2_FLD() 
			: dwPARTY_A(PARTY_NULL)
			, dwPARTY_B(PARTY_NULL)
			, emEND_A(EMCONFRONT_END_PLOSS)
			, emEND_B(EMCONFRONT_END_PLOSS)
		{
			nmg.dwSize = sizeof(SNETPC_CONFRONTPTY_END2_FLD);
			nmg.nType = NET_MSG_GCTRL_CONFRONTPTY_END2_FLD;
			GASSERT(nmg.dwSize<=NET_DATA_BUFSIZE);
		}
	};

	struct SNETPC_CONFRONTPTY_END2_CLT
	{
		NET_MSG_GENERIC		nmg;
		EMCONFRONT_END		emEND;

		SNETPC_CONFRONTPTY_END2_CLT() 
			: emEND(EMCONFRONT_END_PLOSS)
		{
			nmg.dwSize = sizeof(SNETPC_CONFRONTPTY_END2_CLT);
			nmg.nType = NET_MSG_GCTRL_CONFRONTPTY_END2_CLT;
			GASSERT(nmg.dwSize<=NET_DATA_BUFSIZE);
		}
	};

	struct SNETPC_CONFRONT_RECOVE
	{
		NET_MSG_GENERIC		nmg;
		WORD				wRECOVER;

		SNETPC_CONFRONT_RECOVE() 
			: wRECOVER(0)
		{
			nmg.dwSize = sizeof(SNETPC_CONFRONT_RECOVE);
			nmg.nType = NET_MSG_GCTRL_CONFRONT_RECOVE;
			GASSERT(nmg.dwSize<=NET_DATA_BUFSIZE);
		}
	};

	struct SNET_CONFRONTCLB_CHECKMBR_FLD
	{
		NET_MSG_GENERIC		nmg;

		SNATIVEID			sMapID;

		DWORD				dwCLUB_A;
		DWORD				dwCLUB_B;

		SCONFT_OPTION		sOption;

		SNET_CONFRONTCLB_CHECKMBR_FLD () 
			: dwCLUB_A(0)
			, dwCLUB_B(0)
		{
			nmg.dwSize = sizeof(SNET_CONFRONTCLB_CHECKMBR_FLD);
			nmg.nType = NET_MSG_GCTRL_CONFRONTCLB_CHECKMBR_FLD;
			GASSERT(nmg.dwSize<=NET_DATA_BUFSIZE);
		}
	};

	struct SNET_CONFRONTCLB_CHECKMBR_AGT
	{
		NET_MSG_GENERIC		nmg;

		SNATIVEID			sMapID;

		D3DXVECTOR3			vPosition;
		DWORD				dwCLUB_A;
		DWORD				dwCLUB_B;

		DWORD				dwCLUB_A_NUM;
		DWORD				dwCLUB_A_MEMBER[EMMAX_CLUB_NUM];
		
		DWORD				dwCLUB_B_NUM;
		DWORD				dwCLUB_B_MEMBER[EMMAX_CLUB_NUM];

		SCONFT_OPTION		sOption;

		SNET_CONFRONTCLB_CHECKMBR_AGT () 
			: vPosition(0,0,0)
			, dwCLUB_A(0)
			, dwCLUB_B(0)
			, dwCLUB_A_NUM(0)
			, dwCLUB_B_NUM(0)
		{
			nmg.dwSize = sizeof(SNET_CONFRONTCLB_CHECKMBR_AGT);
			nmg.nType = NET_MSG_GCTRL_CONFRONTCLB_CHECKMBR_AGT;
			GASSERT(nmg.dwSize<=NET_DATA_BUFSIZE);
			memset(dwCLUB_A_MEMBER, 0, sizeof(DWORD) * EMMAX_CLUB_NUM);
			memset(dwCLUB_B_MEMBER, 0, sizeof(DWORD) * EMMAX_CLUB_NUM);
		}
	};

	struct SNETPC_CONFRONTCLB_START2_FLD
	{
		NET_MSG_GENERIC		nmg;
		SNATIVEID			sMapID;

		DWORD				dwCLUB_A;
		DWORD				dwCLUB_B;

		DWORD				dwCLUB_A_NUM;
		DWORD				dwCLUB_A_MEMBER[EMMAX_CLUB_NUM];
		
		DWORD				dwCLUB_B_NUM;
		DWORD				dwCLUB_B_MEMBER[EMMAX_CLUB_NUM];

		D3DXVECTOR3			vPos;
		SCONFT_OPTION		sOption;

		SNETPC_CONFRONTCLB_START2_FLD () 
			: sMapID(SNATIVEID(false))
			, dwCLUB_A(CLUB_NULL)
			, dwCLUB_B(CLUB_NULL)
			, dwCLUB_A_NUM(0)
			, dwCLUB_B_NUM(0)
			, vPos(0,0,0)
		{
			nmg.dwSize = sizeof(SNETPC_CONFRONTCLB_START2_FLD);
			nmg.nType = NET_MSG_GCTRL_CONFRONTCLB_START2_FLD;
			GASSERT(nmg.dwSize<=NET_DATA_BUFSIZE);

			memset(dwCLUB_A_MEMBER, 0, sizeof(DWORD) * EMMAX_CLUB_NUM);
			memset(dwCLUB_B_MEMBER, 0, sizeof(DWORD) * EMMAX_CLUB_NUM);
		}
	};

	struct SNETPC_CONFRONTCLB_START2_CLT
	{
		NET_MSG_GENERIC		nmg;

		CHAR				szName[CHR_ID_LENGTH+1];

		DWORD				dwconftCLUB;

		DWORD				dwCLUB_MY_NUM;
		DWORD				dwCONFRONT_MY_MEMBER[EMMAX_CLUB_NUM];

		DWORD				dwCLUB_TAR_NUM;
		DWORD				dwCONFRONT_TAR_MEMBER[EMMAX_CLUB_NUM];

		D3DXVECTOR3			vPosition;
		SCONFT_OPTION		sOption;

		SNETPC_CONFRONTCLB_START2_CLT () 
			: dwconftCLUB(PARTY_NULL)
			, vPosition(FLT_MAX,FLT_MAX,FLT_MAX)
			, dwCLUB_MY_NUM(0)
			, dwCLUB_TAR_NUM(0)
		{
			nmg.dwSize = sizeof(SNETPC_CONFRONTCLB_START2_CLT);
			nmg.nType = NET_MSG_GCTRL_CONFRONTCLB_START2_CLT;
			GASSERT(nmg.dwSize<=NET_DATA_BUFSIZE);
			memset(szName, 0, sizeof(CHAR) * (CHR_ID_LENGTH+1));
			memset(dwCONFRONT_MY_MEMBER, 0, sizeof(DWORD) * EMMAX_CLUB_NUM);
			memset(dwCONFRONT_TAR_MEMBER, 0, sizeof(DWORD) * EMMAX_CLUB_NUM);
		}
	};

	struct SNETPC_CONFRONTCLB_END2_FLD
	{
		NET_MSG_GENERIC		nmg;

		DWORD				dwCLUB_A;
		DWORD				dwCLUB_B;

		EMCONFRONT_END		emEND_A;
		EMCONFRONT_END		emEND_B;

		SNETPC_CONFRONTCLB_END2_FLD() 
			: dwCLUB_A(PARTY_NULL)
			, dwCLUB_B(PARTY_NULL)
			, emEND_A(EMCONFRONT_END_CLOSS)
			, emEND_B(EMCONFRONT_END_CLOSS)
		{
			nmg.dwSize = sizeof(SNETPC_CONFRONTCLB_END2_FLD);
			nmg.nType = NET_MSG_GCTRL_CONFRONTCLB_END2_FLD;
			GASSERT(nmg.dwSize<=NET_DATA_BUFSIZE);
		}
	};

	struct SNETPC_CONFRONTCLB_END2_CLT
	{
		NET_MSG_GENERIC		nmg;
		EMCONFRONT_END		emEND;

		SNETPC_CONFRONTCLB_END2_CLT() 
			: emEND(EMCONFRONT_END_CLOSS)
		{
			nmg.dwSize = sizeof(SNETPC_CONFRONTCLB_END2_CLT);
			nmg.nType = NET_MSG_GCTRL_CONFRONTCLB_END2_CLT;
			GASSERT(nmg.dwSize<=NET_DATA_BUFSIZE);
		}
	};

	// Revert to default structure packing
	#pragma pack()
};