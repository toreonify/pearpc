/*
 *	PearPC
 *	ppc_tools.h
 *
 *	Copyright (C) 2003 Sebastian Biallas (sb@biallas.net)
 *
 *	This program is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License version 2 as
 *	published by the Free Software Foundation.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with this program; if not, write to the Free Software
 *	Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#pragma once 

#include "system/types.h"

static inline FUNCTION_CONST bool ppc_carry_3(uint32 a, uint32 b, uint32 c)
{
	if ((a+b) < a) {
		return true;
	}
	if ((a+b+c) < c) {
		return true;
	}
	return false;
}

static inline FUNCTION_CONST uint32 ppc_word_rotl(uint32 data, int n)
{
	n &= 0x1f;
	return (data << n) | (data >> (32-n));
}

static inline uint32 ppc_mask(int MB, int ME)
{
	uint32 mask;
	if (MB <= ME) {
		if (ME-MB == 31) {
			mask = 0xffffffff;
		} else {
			mask = ((1<<(ME-MB+1))-1)<<(31-ME);
		}
	} else {
		mask = ppc_word_rotl((1<<(32-MB+ME+1))-1, 31-ME);
	}
	return mask;
}