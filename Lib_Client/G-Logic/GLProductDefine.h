/*!
 * \file GLProductDefine.h
 *
 * \author Juver
 * \date October 2017
 *
 * 
 */

#ifndef GLPRODUCT_DEFINE_H_
#define GLPRODUCT_DEFINE_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum PRODUCT_TYPE
{
	PRODUCT_TYPE_HAT_HAIR		= 0,
	PRODUCT_TYPE_UPPER			= 1,
	PRODUCT_TYPE_LOWER			= 2,
	PRODUCT_TYPE_GLOVES			= 3,
	PRODUCT_TYPE_SHOES			= 4,
	PRODUCT_TYPE_WEAPON			= 5,
	PRODUCT_TYPE_NECK_EARRING	= 6,
	PRODUCT_TYPE_BRACELET_BELT	= 7,
	PRODUCT_TYPE_RING_ACCE		= 8,
	PRODUCT_TYPE_ETC			= 9,
	PRODUCT_TYPE_BOX			= 10,
	PRODUCT_TYPE_COSTUME		= 11,
	PRODUCT_TYPE_SIZE			= 12,
};

namespace COMMENT
{
	extern std::string PRODUCT_TYPE_NAME[PRODUCT_TYPE_SIZE];
};

#endif // GLPRODUCT_DEFINE_H_
