/*
 *	PearPC
 *	ppc_alu.cc
 *
 *	Copyright (C) 2003, 2004 Sebastian Biallas (sb@biallas.net)
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

//#include "debug/tracers.h"
//#include "cpu/debug.h"
//#include "ppc_alu.h"
//#include "ppc_dec.h"
//#include "ppc_exc.h"
//#include "ppc_cpu.h"
//#include "ppc_opc.h"
//#include "ppc_tools.h"

#include "system/types.h"

#include "interpreter.hpp"
#include "opcodes.hpp"
#include "tools.hpp"

namespace CPU
{
	/*
	 *	addx		Add
	 *	.422
	 */
	void Interpreter::addx()
	{
		int rD, rA, rB;
		PPC_OPC_TEMPL_XO(this->state->current_opc, rD, rA, rB);
		
		this->state->gpr[rD] = this->state->gpr[rA] + this->state->gpr[rB];
		
		if (this->state->current_opc & PPC_OPC_Rc) {
			// update cr0 flags
			this->updateCR0(this->state->gpr[rD]);
		}
	}
	/*
	 *	addox		Add with Overflow
	 *	.422
	 */
	void Interpreter::addox()
	{
		int rD, rA, rB;
		PPC_OPC_TEMPL_XO(this->state->current_opc, rD, rA, rB);
		this->state->gpr[rD] = this->state->gpr[rA] + this->state->gpr[rB];
		if (this->state->current_opc & PPC_OPC_Rc) {
			// update cr0 flags
			this->updateCR0(this->state->gpr[rD]);
		}
		// update XER flags
		PPC_ALU_ERR("addox unimplemented\n");
	}
	/*
	 *	addcx		Add Carrying
	 *	.423
	 */
	void Interpreter::addcx()
	{
		int rD, rA, rB;
		PPC_OPC_TEMPL_XO(this->state->current_opc, rD, rA, rB);
		uint32 a = this->state->gpr[rA];
		this->state->gpr[rD] = a + this->state->gpr[rB];
		// update xer
		if (this->state->gpr[rD] < a) {
			this->state->xer |= XER_CA;
		} else {
			this->state->xer &= ~XER_CA;
		}
		if (this->state->current_opc & PPC_OPC_Rc) {
			// update cr0 flags
			this->updateCR0(this->state->gpr[rD]);
		}
	}
	/*
	 *	addcox		Add Carrying with Overflow
	 *	.423
	 */
	void Interpreter::addcox()
	{
		int rD, rA, rB;
		PPC_OPC_TEMPL_XO(this->state->current_opc, rD, rA, rB);
		uint32 a = this->state->gpr[rA];
		this->state->gpr[rD] = a + this->state->gpr[rB];
		// update xer
		if (this->state->gpr[rD] < a) {
			this->state->xer |= XER_CA;
		} else {
			this->state->xer &= ~XER_CA;
		}
		if (this->state->current_opc & PPC_OPC_Rc) {
			// update cr0 flags
			this->updateCR0(this->state->gpr[rD]);
		}
		// update XER flags
		PPC_ALU_ERR("addcox unimplemented\n");
	}
	/*
	 *	addex		Add Extended
	 *	.424
	 */
	void Interpreter::addex()
	{
		int rD, rA, rB;
		PPC_OPC_TEMPL_XO(this->state->current_opc, rD, rA, rB);
		uint32 a = this->state->gpr[rA];
		uint32 b = this->state->gpr[rB];
		uint32 ca = ((this->state->xer&XER_CA)?1:0);
		this->state->gpr[rD] = a + b + ca;
		// update xer
		if (ppc_carry_3(a, b, ca)) {
			this->state->xer |= XER_CA;
		} else {
			this->state->xer &= ~XER_CA;
		}
		if (this->state->current_opc & PPC_OPC_Rc) {
			// update cr0 flags
			this->updateCR0(this->state->gpr[rD]);
		}
	}
	/*
	 *	addeox		Add Extended with Overflow
	 *	.424
	 */
	void Interpreter::addeox()
	{
		int rD, rA, rB;
		PPC_OPC_TEMPL_XO(this->state->current_opc, rD, rA, rB);
		uint32 a = this->state->gpr[rA];
		uint32 b = this->state->gpr[rB];
		uint32 ca = ((this->state->xer&XER_CA)?1:0);
		this->state->gpr[rD] = a + b + ca;
		// update xer
		if (ppc_carry_3(a, b, ca)) {
			this->state->xer |= XER_CA;
		} else {
			this->state->xer &= ~XER_CA;
		}
		if (this->state->current_opc & PPC_OPC_Rc) {
			// update cr0 flags
			this->updateCR0(this->state->gpr[rD]);
		}
		// update XER flags
		PPC_ALU_ERR("addeox unimplemented\n");
	}
	/*
	 *	addi		Add Immediate
	 *	.425
	 */
	void Interpreter::addi()
	{
		int rD, rA;
		uint32 imm;
		PPC_OPC_TEMPL_D_SImm(this->state->current_opc, rD, rA, imm);
		this->state->gpr[rD] = (rA ? this->state->gpr[rA] : 0) + imm;
	}
	/*
	 *	addic		Add Immediate Carrying
	 *	.426
	 */
	void Interpreter::addic()
	{
		int rD, rA;
		uint32 imm;
		PPC_OPC_TEMPL_D_SImm(this->state->current_opc, rD, rA, imm);
		uint32 a = this->state->gpr[rA];
		this->state->gpr[rD] = a + imm;	
		// update XER
		if (this->state->gpr[rD] < a) {
			this->state->xer |= XER_CA;
		} else {
			this->state->xer &= ~XER_CA;
		}
	}
	/*
	 *	addic.		Add Immediate Carrying and Record
	 *	.427
	 */
	void Interpreter::addic_()
	{
		int rD, rA;
		uint32 imm;
		PPC_OPC_TEMPL_D_SImm(this->state->current_opc, rD, rA, imm);
		uint32 a = this->state->gpr[rA];
		this->state->gpr[rD] = a + imm;
		// update XER
		if (this->state->gpr[rD] < a) {
			this->state->xer |= XER_CA;
		} else {
			this->state->xer &= ~XER_CA;
		}
		// update cr0 flags
		this->updateCR0(this->state->gpr[rD]);
	}
	/*
	 *	addis		Add Immediate Shifted
	 *	.428
	 */
	void Interpreter::addis()
	{
		int rD, rA;
		uint32 imm;
		PPC_OPC_TEMPL_D_Shift16(this->state->current_opc, rD, rA, imm);
		this->state->gpr[rD] = (rA ? this->state->gpr[rA] : 0) + imm;
	}
	/*
	 *	addmex		Add to Minus One Extended
	 *	.429
	 */
	void Interpreter::addmex()
	{
		int rD, rA, rB;
		PPC_OPC_TEMPL_XO(this->state->current_opc, rD, rA, rB);
		PPC_OPC_ASSERT(rB == 0);
		uint32 a = this->state->gpr[rA];
		uint32 ca = ((this->state->xer&XER_CA)?1:0);
		this->state->gpr[rD] = a + ca + 0xffffffff;
		if (a || ca) {
			this->state->xer |= XER_CA;
		} else {
			this->state->xer &= ~XER_CA;
		}
		if (this->state->current_opc & PPC_OPC_Rc) {
			// update cr0 flags
			this->updateCR0(this->state->gpr[rD]);
		}
	}
	/*
	 *	addmeox		Add to Minus One Extended with Overflow
	 *	.429
	 */
	void Interpreter::addmeox()
	{
		int rD, rA, rB;
		PPC_OPC_TEMPL_XO(this->state->current_opc, rD, rA, rB);
		PPC_OPC_ASSERT(rB == 0);
		uint32 a = this->state->gpr[rA];
		uint32 ca = ((this->state->xer&XER_CA)?1:0);
		this->state->gpr[rD] = a + ca + 0xffffffff;
		if (a || ca) {
			this->state->xer |= XER_CA;
		} else {
			this->state->xer &= ~XER_CA;
		}
		if (this->state->current_opc & PPC_OPC_Rc) {
			// update cr0 flags
			this->updateCR0(this->state->gpr[rD]);
		}
		// update XER flags
		PPC_ALU_ERR("addmeox unimplemented\n");
	}
	/*
	 *	addzex		Add to Zero Extended
	 *	.430
	 */
	void Interpreter::addzex()
	{
		int rD, rA, rB;
		PPC_OPC_TEMPL_XO(this->state->current_opc, rD, rA, rB);
		PPC_OPC_ASSERT(rB == 0);
		uint32 a = this->state->gpr[rA];
		uint32 ca = ((this->state->xer&XER_CA)?1:0);
		this->state->gpr[rD] = a + ca;
		if ((a == 0xffffffff) && ca) {
			this->state->xer |= XER_CA;
		} else {
			this->state->xer &= ~XER_CA;
		}
		// update xer
		if (this->state->current_opc & PPC_OPC_Rc) {
			// update cr0 flags
			this->updateCR0(this->state->gpr[rD]);
		}
	}
	/*
	 *	addzeox		Add to Zero Extended with Overflow
	 *	.430
	 */
	void Interpreter::addzeox()
	{
		int rD, rA, rB;
		PPC_OPC_TEMPL_XO(this->state->current_opc, rD, rA, rB);
		PPC_OPC_ASSERT(rB == 0);
		uint32 a = this->state->gpr[rA];
		uint32 ca = ((this->state->xer&XER_CA)?1:0);
		this->state->gpr[rD] = a + ca;
		if ((a == 0xffffffff) && ca) {
			this->state->xer |= XER_CA;
		} else {
			this->state->xer &= ~XER_CA;
		}
		// update xer
		if (this->state->current_opc & PPC_OPC_Rc) {
			// update cr0 flags
			this->updateCR0(this->state->gpr[rD]);
		}
		// update XER flags
		PPC_ALU_ERR("addzeox unimplemented\n");
	}

	/*
	 *	andx		AND
	 *	.431
	 */
	void Interpreter::andx()
	{
		int rS, rA, rB;
		PPC_OPC_TEMPL_X(this->state->current_opc, rS, rA, rB);
		this->state->gpr[rA] = this->state->gpr[rS] & this->state->gpr[rB];
		if (this->state->current_opc & PPC_OPC_Rc) {
			// update cr0 flags
			this->updateCR0(this->state->gpr[rA]);
		}
	}
	/*
	 *	andcx		AND with Complement
	 *	.432
	 */
	void Interpreter::andcx()
	{
		int rS, rA, rB;
		PPC_OPC_TEMPL_X(this->state->current_opc, rS, rA, rB);
		this->state->gpr[rA] = this->state->gpr[rS] & ~this->state->gpr[rB];
		if (this->state->current_opc & PPC_OPC_Rc) {
			// update cr0 flags
			this->updateCR0(this->state->gpr[rA]);
		}
	}
	/*
	 *	andi.		AND Immediate
	 *	.433
	 */
	void Interpreter::andi_()
	{
		int rS, rA;
		uint32 imm;
		PPC_OPC_TEMPL_D_UImm(this->state->current_opc, rS, rA, imm);
		this->state->gpr[rA] = this->state->gpr[rS] & imm;
		// update cr0 flags
		this->updateCR0(this->state->gpr[rA]);
	}
	/*
	 *	andis.		AND Immediate Shifted
	 *	.434
	 */
	void Interpreter::andis_()
	{
		int rS, rA;
		uint32 imm;
		PPC_OPC_TEMPL_D_Shift16(this->state->current_opc, rS, rA, imm);
		this->state->gpr[rA] = this->state->gpr[rS] & imm;
		// update cr0 flags
		this->updateCR0(this->state->gpr[rA]);
	}

	/*
	 *	cmp		Compare
	 *	.442
	 */
	static uint32 ppc_cmp_and_mask[8] = {
		0xfffffff0,
		0xffffff0f,
		0xfffff0ff,
		0xffff0fff,
		0xfff0ffff,
		0xff0fffff,
		0xf0ffffff,
		0x0fffffff,
	};

	void Interpreter::cmp()
	{
		uint32 cr;
		int rA, rB;
		PPC_OPC_TEMPL_X(this->state->current_opc, cr, rA, rB);
		cr >>= 2;
		sint32 a = this->state->gpr[rA];
		sint32 b = this->state->gpr[rB];
		uint32 c;
		if (a < b) {
			c = 8;
		} else if (a > b) {
			c = 4;
		} else {
			c = 2;
		}
		if (this->state->xer & XER_SO) c |= 1;
		cr = 7-cr;
		this->state->cr &= ppc_cmp_and_mask[cr];
		this->state->cr |= c<<(cr*4);
	}
	/*
	 *	cmpi		Compare Immediate
	 *	.443
	 */
	void Interpreter::cmpi()
	{
		uint32 cr;
		int rA;
		uint32 imm;
		PPC_OPC_TEMPL_D_SImm(this->state->current_opc, cr, rA, imm);
		cr >>= 2;
		sint32 a = this->state->gpr[rA];
		sint32 b = imm;
		uint32 c;
	/*	if (!VALGRIND_CHECK_READABLE(a, sizeof a)) {
			ht_printf("%08x <--i\n", this->state->pc);
	//		SINGLESTEP("");
		}*/
		if (a < b) {
			c = 8;
		} else if (a > b) {
			c = 4;
		} else {
			c = 2;
		}
		if (this->state->xer & XER_SO) c |= 1;
		cr = 7-cr;
		this->state->cr &= ppc_cmp_and_mask[cr];
		this->state->cr |= c<<(cr*4);
	}
	/*
	 *	cmpl		Compare Logical
	 *	.444
	 */
	void Interpreter::cmpl()
	{
		uint32 cr;
		int rA, rB;
		PPC_OPC_TEMPL_X(this->state->current_opc, cr, rA, rB);
		cr >>= 2;
		uint32 a = this->state->gpr[rA];
		uint32 b = this->state->gpr[rB];
		uint32 c;
		if (a < b) {
			c = 8;
		} else if (a > b) {
			c = 4;
		} else {
			c = 2;
		}
		if (this->state->xer & XER_SO) c |= 1;
		cr = 7-cr;
		this->state->cr &= ppc_cmp_and_mask[cr];
		this->state->cr |= c<<(cr*4);
	}
	/*
	 *	cmpli		Compare Logical Immediate
	 *	.445
	 */
	void Interpreter::cmpli()
	{
		uint32 cr;
		int rA;
		uint32 imm;
		PPC_OPC_TEMPL_D_UImm(this->state->current_opc, cr, rA, imm);
		cr >>= 2;
		uint32 a = this->state->gpr[rA];
		uint32 b = imm;
		uint32 c;
		if (a < b) {
			c = 8;
		} else if (a > b) {
			c = 4;
		} else {
			c = 2;
		}
		if (this->state->xer & XER_SO) c |= 1;
		cr = 7-cr;
		this->state->cr &= ppc_cmp_and_mask[cr];
		this->state->cr |= c<<(cr*4);
	}

	/*
	 *	cntlzwx		Count Leading Zeros Word
	 *	.447
	 */
	void Interpreter::cntlzwx()
	{
		int rS, rA, rB;
		PPC_OPC_TEMPL_X(this->state->current_opc, rS, rA, rB);
		PPC_OPC_ASSERT(rB==0);
		uint32 n=0;
		uint32 x=0x80000000;
		uint32 v=this->state->gpr[rS];
		while (!(v & x)) {
			n++;
			if (n==32) break;
			x>>=1;
		}
		this->state->gpr[rA] = n;
		if (this->state->current_opc & PPC_OPC_Rc) {
			// update cr0 flags
			this->updateCR0(this->state->gpr[rA]);
		}
	}

	/*
	 *	crand		Condition Register AND
	 *	.448
	 */
	void Interpreter::crand()
	{
		int crD, crA, crB;
		PPC_OPC_TEMPL_X(this->state->current_opc, crD, crA, crB);
		if ((this->state->cr & (1<<(31-crA))) && (this->state->cr & (1<<(31-crB)))) {
			this->state->cr |= (1<<(31-crD));
		} else {
			this->state->cr &= ~(1<<(31-crD));
		}
	}
	/*
	 *	crandc		Condition Register AND with Complement
	 *	.449
	 */
	void Interpreter::crandc()
	{
		int crD, crA, crB;
		PPC_OPC_TEMPL_X(this->state->current_opc, crD, crA, crB);
		if ((this->state->cr & (1<<(31-crA))) && !(this->state->cr & (1<<(31-crB)))) {
			this->state->cr |= (1<<(31-crD));
		} else {
			this->state->cr &= ~(1<<(31-crD));
		}
	}
	/*
	 *	creqv		Condition Register Equivalent
	 *	.450
	 */
	void Interpreter::creqv()
	{
		int crD, crA, crB;
		PPC_OPC_TEMPL_X(this->state->current_opc, crD, crA, crB);
		if (((this->state->cr & (1<<(31-crA))) && (this->state->cr & (1<<(31-crB))))
		  || (!(this->state->cr & (1<<(31-crA))) && !(this->state->cr & (1<<(31-crB))))) {
			this->state->cr |= (1<<(31-crD));
		} else {
			this->state->cr &= ~(1<<(31-crD));
		}
	}
	/*
	 *	crnand		Condition Register NAND
	 *	.451
	 */
	void Interpreter::crnand()
	{
		int crD, crA, crB;
		PPC_OPC_TEMPL_X(this->state->current_opc, crD, crA, crB);
		if (!((this->state->cr & (1<<(31-crA))) && (this->state->cr & (1<<(31-crB))))) {
			this->state->cr |= (1<<(31-crD));
		} else {
			this->state->cr &= ~(1<<(31-crD));
		}
	}
	/*
	 *	crnor		Condition Register NOR
	 *	.452
	 */
	void Interpreter::crnor()
	{
		int crD, crA, crB;
		PPC_OPC_TEMPL_X(this->state->current_opc, crD, crA, crB);
		uint32 t = (1<<(31-crA)) | (1<<(31-crB));
		if (!(this->state->cr & t)) {
			this->state->cr |= (1<<(31-crD));
		} else {
			this->state->cr &= ~(1<<(31-crD));
		}
	}
	/*
	 *	cror		Condition Register OR
	 *	.453
	 */
	void Interpreter::cror()
	{
		int crD, crA, crB;
		PPC_OPC_TEMPL_X(this->state->current_opc, crD, crA, crB);
		uint32 t = (1<<(31-crA)) | (1<<(31-crB));
		if (this->state->cr & t) {
			this->state->cr |= (1<<(31-crD));
		} else {
			this->state->cr &= ~(1<<(31-crD));
		}
	}
	/*
	 *	crorc		Condition Register OR with Complement
	 *	.454
	 */
	void Interpreter::crorc()
	{
		int crD, crA, crB;
		PPC_OPC_TEMPL_X(this->state->current_opc, crD, crA, crB);
		if ((this->state->cr & (1<<(31-crA))) || !(this->state->cr & (1<<(31-crB)))) {
			this->state->cr |= (1<<(31-crD));
		} else {
			this->state->cr &= ~(1<<(31-crD));
		}
	}
	/*
	 *	crxor		Condition Register XOR
	 *	.448
	 */
	void Interpreter::crxor()
	{
		int crD, crA, crB;
		PPC_OPC_TEMPL_X(this->state->current_opc, crD, crA, crB);
		if ((!(this->state->cr & (1<<(31-crA))) && (this->state->cr & (1<<(31-crB))))
		  || ((this->state->cr & (1<<(31-crA))) && !(this->state->cr & (1<<(31-crB))))) {
			this->state->cr |= (1<<(31-crD));
		} else {
			this->state->cr &= ~(1<<(31-crD));
		}
	}

	/*
	 *	divwx		Divide Word
	 *	.470
	 */
	void Interpreter::divwx()
	{
		int rD, rA, rB;
		PPC_OPC_TEMPL_XO(this->state->current_opc, rD, rA, rB);
		if (!this->state->gpr[rB]) {
			PPC_ALU_WARN("division by zero @%08x\n", this->state->pc);
			SINGLESTEP("");
		}
		sint32 a = this->state->gpr[rA];
		sint32 b = this->state->gpr[rB];
		this->state->gpr[rD] = a / b;
		if (this->state->current_opc & PPC_OPC_Rc) {
			// update cr0 flags
			this->updateCR0(this->state->gpr[rD]);
		}
	}
	/*
	 *	divwox		Divide Word with Overflow
	 *	.470
	 */
	void Interpreter::divwox()
	{
		int rD, rA, rB;
		PPC_OPC_TEMPL_XO(this->state->current_opc, rD, rA, rB);
		if (!this->state->gpr[rB]) {
			PPC_ALU_ERR("division by zero\n");
		}
		sint32 a = this->state->gpr[rA];
		sint32 b = this->state->gpr[rB];
		this->state->gpr[rD] = a / b;
		if (this->state->current_opc & PPC_OPC_Rc) {
			// update cr0 flags
			this->updateCR0(this->state->gpr[rD]);
		}
		// update XER flags
		PPC_ALU_ERR("divwox unimplemented\n");
	}
	/*
	 *	divwux		Divide Word Unsigned
	 *	.472
	 */
	void Interpreter::divwux()
	{
		int rD, rA, rB;
		PPC_OPC_TEMPL_XO(this->state->current_opc, rD, rA, rB);
		if (!this->state->gpr[rB]) {
			PPC_ALU_WARN("division by zero @%08x\n", this->state->pc);
			SINGLESTEP("");
		}
		this->state->gpr[rD] = this->state->gpr[rA] / this->state->gpr[rB];
		if (this->state->current_opc & PPC_OPC_Rc) {
			// update cr0 flags
			this->updateCR0(this->state->gpr[rD]);
		}
	}
	/*
	 *	divwuox		Divide Word Unsigned with Overflow
	 *	.472
	 */
	void Interpreter::divwuox()
	{
		int rD, rA, rB;
		PPC_OPC_TEMPL_XO(this->state->current_opc, rD, rA, rB);
		if (!this->state->gpr[rB]) {
	//		PPC_ALU_ERR("division by zero\n");
		}
		this->state->gpr[rD] = this->state->gpr[rA] / this->state->gpr[rB];
		if (this->state->current_opc & PPC_OPC_Rc) {
			// update cr0 flags
			this->updateCR0(this->state->gpr[rD]);
		}
		// update XER flags
		PPC_ALU_ERR("divwuox unimplemented\n");
	}

	/*
	 *	eqvx		Equivalent
	 *	.480
	 */
	void Interpreter::eqvx()
	{
		int rS, rA, rB;
		PPC_OPC_TEMPL_X(this->state->current_opc, rS, rA, rB);
		this->state->gpr[rA] = ~(this->state->gpr[rS] ^ this->state->gpr[rB]);
		if (this->state->current_opc & PPC_OPC_Rc) {
			// update cr0 flags
			this->updateCR0(this->state->gpr[rA]);
		}
	}

	/*
	 *	extsbx		Extend Sign Byte
	 *	.481
	 */
	void Interpreter::extsbx()
	{
		int rS, rA, rB;
		PPC_OPC_TEMPL_X(this->state->current_opc, rS, rA, rB);
		PPC_OPC_ASSERT(rB==0);
		this->state->gpr[rA] = this->state->gpr[rS];
		if (this->state->gpr[rA] & 0x80) {
			this->state->gpr[rA] |= 0xffffff00;
		} else {
			this->state->gpr[rA] &= ~0xffffff00;
		}
		if (this->state->current_opc & PPC_OPC_Rc) {
			// update cr0 flags
			this->updateCR0(this->state->gpr[rA]);
		}
	}
	/*
	 *	extshx		Extend Sign Half Word
	 *	.482
	 */
	void Interpreter::extshx()
	{
		int rS, rA, rB;
		PPC_OPC_TEMPL_X(this->state->current_opc, rS, rA, rB);
		PPC_OPC_ASSERT(rB==0);
		this->state->gpr[rA] = this->state->gpr[rS];
		if (this->state->gpr[rA] & 0x8000) {
			this->state->gpr[rA] |= 0xffff0000;
		} else {
			this->state->gpr[rA] &= ~0xffff0000;
		}
		if (this->state->current_opc & PPC_OPC_Rc) {
			// update cr0 flags
			this->updateCR0(this->state->gpr[rA]);
		}
	}

	/*
	 *	mulhwx		Multiply High Word
	 *	.595
	 */
	void Interpreter::mulhwx()
	{
		int rD, rA, rB;
		PPC_OPC_TEMPL_XO(this->state->current_opc, rD, rA, rB);
		sint64 a = (sint32)this->state->gpr[rA];
		sint64 b = (sint32)this->state->gpr[rB];
		sint64 c = a*b;
		this->state->gpr[rD] = ((uint64)c)>>32;
		if (this->state->current_opc & PPC_OPC_Rc) {
			// update cr0 flags
			this->updateCR0(this->state->gpr[rD]);
	//		PPC_ALU_WARN("mulhw. correct?\n");
		}
	}
	/*
	 *	mulhwux		Multiply High Word Unsigned
	 *	.596
	 */
	void Interpreter::mulhwux()
	{
		int rD, rA, rB;
		PPC_OPC_TEMPL_XO(this->state->current_opc, rD, rA, rB);
		uint64 a = this->state->gpr[rA];
		uint64 b = this->state->gpr[rB];
		uint64 c = a*b;
		this->state->gpr[rD] = c>>32;
		if (this->state->current_opc & PPC_OPC_Rc) {
			// update cr0 flags
			this->updateCR0(this->state->gpr[rD]);
		}
	}
	/*
	 *	mulli		Multiply Low Immediate
	 *	.598
	 */
	void Interpreter::mulli()
	{
		int rD, rA;
		uint32 imm;
		PPC_OPC_TEMPL_D_SImm(this->state->current_opc, rD, rA, imm);
		// FIXME: signed / unsigned correct?
		this->state->gpr[rD] = this->state->gpr[rA] * imm;
	}
	/*
	 *	mullwx		Multiply Low Word
	 *	.599
	 */
	void Interpreter::mullwx()
	{
		int rD, rA, rB;
		PPC_OPC_TEMPL_XO(this->state->current_opc, rD, rA, rB);
		this->state->gpr[rD] = this->state->gpr[rA] * this->state->gpr[rB];
		if (this->state->current_opc & PPC_OPC_Rc) {
			// update cr0 flags
			this->updateCR0(this->state->gpr[rD]);
		}
		if (this->state->current_opc & PPC_OPC_OE) {
			// update XER flags
			PPC_ALU_ERR("mullwx unimplemented\n");
		}
	}

	/*
	 *	nandx		NAND
	 *	.600
	 */
	void Interpreter::nandx()
	{
		int rS, rA, rB;
		PPC_OPC_TEMPL_X(this->state->current_opc, rS, rA, rB);
		this->state->gpr[rA] = ~(this->state->gpr[rS] & this->state->gpr[rB]);
		if (this->state->current_opc & PPC_OPC_Rc) {
			// update cr0 flags
			this->updateCR0(this->state->gpr[rA]);
		}
	}

	/*
	 *	negx		Negate
	 *	.601
	 */
	void Interpreter::negx()
	{
		int rD, rA, rB;
		PPC_OPC_TEMPL_XO(this->state->current_opc, rD, rA, rB);
		PPC_OPC_ASSERT(rB == 0);
		this->state->gpr[rD] = -this->state->gpr[rA];
		if (this->state->current_opc & PPC_OPC_Rc) {
			// update cr0 flags
			this->updateCR0(this->state->gpr[rD]);
		}
	}
	/*
	 *	negox		Negate with Overflow
	 *	.601
	 */
	void Interpreter::negox()
	{
		int rD, rA, rB;
		PPC_OPC_TEMPL_XO(this->state->current_opc, rD, rA, rB);
		PPC_OPC_ASSERT(rB == 0);
		this->state->gpr[rD] = -this->state->gpr[rA];
		if (this->state->current_opc & PPC_OPC_Rc) {
			// update cr0 flags
			this->updateCR0(this->state->gpr[rD]);
		}
		// update XER flags
		PPC_ALU_ERR("negox unimplemented\n");
	}
	/*
	 *	norx		NOR
	 *	.602
	 */
	void Interpreter::norx()
	{
		int rS, rA, rB;
		PPC_OPC_TEMPL_X(this->state->current_opc, rS, rA, rB);
		this->state->gpr[rA] = ~(this->state->gpr[rS] | this->state->gpr[rB]);
		if (this->state->current_opc & PPC_OPC_Rc) {
			// update cr0 flags
			this->updateCR0(this->state->gpr[rA]);
		}
	}

	/*
	 *	orx		OR
	 *	.603
	 */
	void Interpreter::orx()
	{
		int rS, rA, rB;
		PPC_OPC_TEMPL_X(this->state->current_opc, rS, rA, rB);
		this->state->gpr[rA] = this->state->gpr[rS] | this->state->gpr[rB];
		if (this->state->current_opc & PPC_OPC_Rc) {
			// update cr0 flags
			this->updateCR0(this->state->gpr[rA]);
		}
	}
	/*
	 *	orcx		OR with Complement
	 *	.604
	 */
	void Interpreter::orcx()
	{
		int rS, rA, rB;
		PPC_OPC_TEMPL_X(this->state->current_opc, rS, rA, rB);
		this->state->gpr[rA] = this->state->gpr[rS] | ~this->state->gpr[rB];
		if (this->state->current_opc & PPC_OPC_Rc) {
			// update cr0 flags
			this->updateCR0(this->state->gpr[rA]);
		}
	}
	/*
	 *	ori		OR Immediate
	 *	.605
	 */
	void Interpreter::ori()
	{
		int rS, rA;
		uint32 imm;
		PPC_OPC_TEMPL_D_UImm(this->state->current_opc, rS, rA, imm);
		this->state->gpr[rA] = this->state->gpr[rS] | imm;
	}
	/*
	 *	oris		OR Immediate Shifted
	 *	.606
	 */
	void Interpreter::oris()
	{
		int rS, rA;
		uint32 imm;
		PPC_OPC_TEMPL_D_Shift16(this->state->current_opc, rS, rA, imm);
		this->state->gpr[rA] = this->state->gpr[rS] | imm;
	}

	/*
	 *	rlwimix		Rotate Left Word Immediate then Mask Insert
	 *	.617
	 */
	void Interpreter::rlwimix()
	{
		int rS, rA, SH, MB, ME;
		PPC_OPC_TEMPL_M(this->state->current_opc, rS, rA, SH, MB, ME);
		uint32 v = ppc_word_rotl(this->state->gpr[rS], SH);
		uint32 mask = ppc_mask(MB, ME);
		this->state->gpr[rA] = (v & mask) | (this->state->gpr[rA] & ~mask);
		if (this->state->current_opc & PPC_OPC_Rc) {
			// update cr0 flags
			this->updateCR0(this->state->gpr[rA]);
		}
	}

	/*
	 *	rlwinmx		Rotate Left Word Immediate then AND with Mask
	 *	.618
	 */
	void Interpreter::rlwinmx()
	{
		int rS, rA, SH, MB, ME;
		PPC_OPC_TEMPL_M(this->state->current_opc, rS, rA, SH, MB, ME);
		uint32 v = ppc_word_rotl(this->state->gpr[rS], SH);
		uint32 mask = ppc_mask(MB, ME);
		this->state->gpr[rA] = v & mask;
		if (this->state->current_opc & PPC_OPC_Rc) {
			// update cr0 flags
			this->updateCR0(this->state->gpr[rA]);
		}
	}
	/*
	 *	rlwnmx		Rotate Left Word then AND with Mask
	 *	.620
	 */
	void Interpreter::rlwnmx()
	{
		int rS, rA, rB, MB, ME;
		PPC_OPC_TEMPL_M(this->state->current_opc, rS, rA, rB, MB, ME);
		uint32 v = ppc_word_rotl(this->state->gpr[rS], this->state->gpr[rB]);
		uint32 mask = ppc_mask(MB, ME);
		this->state->gpr[rA] = v & mask;
		if (this->state->current_opc & PPC_OPC_Rc) {
			// update cr0 flags
			this->updateCR0(this->state->gpr[rA]);
		}
	}

	/*
	 *	slwx		Shift Left Word
	 *	.625
	 */
	void Interpreter::slwx()
	{
		int rS, rA, rB;
		PPC_OPC_TEMPL_X(this->state->current_opc, rS, rA, rB);
		uint32 s = this->state->gpr[rB] & 0x3f;
		if (s > 31) {
			this->state->gpr[rA] = 0;
		} else {
			this->state->gpr[rA] = this->state->gpr[rS] << s;
		}
		if (this->state->current_opc & PPC_OPC_Rc) {
			// update cr0 flags
			this->updateCR0(this->state->gpr[rA]);
		}
	}
	/*
	 *	srawx		Shift Right Algebraic Word
	 *	.628
	 */
	void Interpreter::srawx()
	{
		int rS, rA, rB;
		PPC_OPC_TEMPL_X(this->state->current_opc, rS, rA, rB);
		uint32 SH = this->state->gpr[rB] & 0x3f;
		this->state->gpr[rA] = this->state->gpr[rS];
		this->state->xer &= ~XER_CA;
		if (this->state->gpr[rA] & 0x80000000) {
			uint32 ca = 0;
			for (uint i=0; i < SH; i++) {
				if (this->state->gpr[rA] & 1) ca = 1;
				this->state->gpr[rA] >>= 1;
				this->state->gpr[rA] |= 0x80000000;
			}
			if (ca) this->state->xer |= XER_CA;
		} else {
			if (SH > 31) {
				this->state->gpr[rA] = 0;
			} else {
				this->state->gpr[rA] >>= SH;
			}
		}     
		if (this->state->current_opc & PPC_OPC_Rc) {
			// update cr0 flags
			this->updateCR0(this->state->gpr[rA]);
		}
	}
	/*
	 *	srawix		Shift Right Algebraic Word Immediate
	 *	.629
	 */
	void Interpreter::srawix()
	{
		int rS, rA;
		uint32 SH;
		PPC_OPC_TEMPL_X(this->state->current_opc, rS, rA, SH);
		this->state->gpr[rA] = this->state->gpr[rS];
		this->state->xer &= ~XER_CA;
		if (this->state->gpr[rA] & 0x80000000) {
			uint32 ca = 0;
			for (uint i=0; i < SH; i++) {
				if (this->state->gpr[rA] & 1) ca = 1;
				this->state->gpr[rA] >>= 1;
				this->state->gpr[rA] |= 0x80000000;
			}
			if (ca) this->state->xer |= XER_CA;
		} else {
			if (SH > 31) {
				this->state->gpr[rA] = 0;
			} else {
				this->state->gpr[rA] >>= SH;
			}
		}     
		if (this->state->current_opc & PPC_OPC_Rc) {
			// update cr0 flags
			this->updateCR0(this->state->gpr[rA]);
		}
	}
	/*
	 *	srwx		Shift Right Word
	 *	.631
	 */
	void Interpreter::srwx()
	{
		int rS, rA, rB;
		PPC_OPC_TEMPL_X(this->state->current_opc, rS, rA, rB);
		uint32 v = this->state->gpr[rB] & 0x3f;
		if (v > 31) {
			this->state->gpr[rA] = 0;
		} else {
			this->state->gpr[rA] = this->state->gpr[rS] >> v;
		}
		if (this->state->current_opc & PPC_OPC_Rc) {
			// update cr0 flags
			this->updateCR0(this->state->gpr[rA]);
		}
	}

	/*
	 *	subfx		Subtract From
	 *	.666
	 */
	void Interpreter::subfx()
	{
		int rD, rA, rB;
		PPC_OPC_TEMPL_XO(this->state->current_opc, rD, rA, rB);
		this->state->gpr[rD] = ~this->state->gpr[rA] + this->state->gpr[rB] + 1;
		if (this->state->current_opc & PPC_OPC_Rc) {
			// update cr0 flags
			this->updateCR0(this->state->gpr[rD]);
		}
	}
	/*
	 *	subfox		Subtract From with Overflow
	 *	.666
	 */
	void Interpreter::subfox()
	{
		int rD, rA, rB;
		PPC_OPC_TEMPL_XO(this->state->current_opc, rD, rA, rB);
		this->state->gpr[rD] = ~this->state->gpr[rA] + this->state->gpr[rB] + 1;
		if (this->state->current_opc & PPC_OPC_Rc) {
			// update cr0 flags
			this->updateCR0(this->state->gpr[rD]);
		}
		// update XER flags
		PPC_ALU_ERR("subfox unimplemented\n");
	}
	/*
	 *	subfcx		Subtract From Carrying
	 *	.667
	 */
	void Interpreter::subfcx()
	{
		int rD, rA, rB;
		PPC_OPC_TEMPL_XO(this->state->current_opc, rD, rA, rB);
		uint32 a = this->state->gpr[rA];
		uint32 b = this->state->gpr[rB];
		this->state->gpr[rD] = ~a + b + 1;
		// update xer
		if (ppc_carry_3(~a, b, 1)) {
			this->state->xer |= XER_CA;
		} else {
			this->state->xer &= ~XER_CA;
		}
		if (this->state->current_opc & PPC_OPC_Rc) {
			// update cr0 flags
			this->updateCR0(this->state->gpr[rD]);
		}
	}
	/*
	 *	subfcox		Subtract From Carrying with Overflow
	 *	.667
	 */
	void Interpreter::subfcox()
	{
		int rD, rA, rB;
		PPC_OPC_TEMPL_XO(this->state->current_opc, rD, rA, rB);
		uint32 a = this->state->gpr[rA];
		uint32 b = this->state->gpr[rB];
		this->state->gpr[rD] = ~a + b + 1;
		// update xer
		if (ppc_carry_3(~a, b, 1)) {
			this->state->xer |= XER_CA;
		} else {
			this->state->xer &= ~XER_CA;
		}
		if (this->state->current_opc & PPC_OPC_Rc) {
			// update cr0 flags
			this->updateCR0(this->state->gpr[rD]);
		}
		// update XER flags
		PPC_ALU_ERR("subfcox unimplemented\n");
	}
	/*
	 *	subfex		Subtract From Extended
	 *	.668
	 */
	void Interpreter::subfex()
	{
		int rD, rA, rB;
		PPC_OPC_TEMPL_XO(this->state->current_opc, rD, rA, rB);
		uint32 a = this->state->gpr[rA];
		uint32 b = this->state->gpr[rB];
		uint32 ca = ((this->state->xer&XER_CA)?1:0);
		this->state->gpr[rD] = ~a + b + ca;
		// update xer
		if (ppc_carry_3(~a, b, ca)) {
			this->state->xer |= XER_CA;
		} else {
			this->state->xer &= ~XER_CA;
		}
		if (this->state->current_opc & PPC_OPC_Rc) {
			// update cr0 flags
			this->updateCR0(this->state->gpr[rD]);
		}
	}
	/*
	 *	subfeox		Subtract From Extended with Overflow
	 *	.668
	 */
	void Interpreter::subfeox()
	{
		int rD, rA, rB;
		PPC_OPC_TEMPL_XO(this->state->current_opc, rD, rA, rB);
		uint32 a = this->state->gpr[rA];
		uint32 b = this->state->gpr[rB];
		uint32 ca = ((this->state->xer&XER_CA)?1:0);
		this->state->gpr[rD] = ~a + b + ca;
		// update xer
		if (ppc_carry_3(~a, b, ca)) {
			this->state->xer |= XER_CA;
		} else {
			this->state->xer &= ~XER_CA;
		}
		if (this->state->current_opc & PPC_OPC_Rc) {
			// update cr0 flags
			this->updateCR0(this->state->gpr[rD]);
		}
		// update XER flags
		PPC_ALU_ERR("subfeox unimplemented\n");
	}
	/*
	 *	subfic		Subtract From Immediate Carrying
	 *	.669
	 */
	void Interpreter::subfic()
	{
		int rD, rA;
		uint32 imm;
		PPC_OPC_TEMPL_D_SImm(this->state->current_opc, rD, rA, imm);
		uint32 a = this->state->gpr[rA];
		this->state->gpr[rD] = ~a + imm + 1;
		// update XER
		if (ppc_carry_3(~a, imm, 1)) {
			this->state->xer |= XER_CA;
		} else {
			this->state->xer &= ~XER_CA;
		}
	}
	/*
	 *	subfmex		Subtract From Minus One Extended
	 *	.670
	 */
	void Interpreter::subfmex()
	{
		int rD, rA, rB;
		PPC_OPC_TEMPL_XO(this->state->current_opc, rD, rA, rB);
		PPC_OPC_ASSERT(rB == 0);
		uint32 a = this->state->gpr[rA];
		uint32 ca = ((this->state->xer&XER_CA)?1:0);
		this->state->gpr[rD] = ~a + ca + 0xffffffff;
		// update XER
		if ((a!=0xffffffff) || ca) {
			this->state->xer |= XER_CA;
		} else {
			this->state->xer &= ~XER_CA;
		}
		if (this->state->current_opc & PPC_OPC_Rc) {
			// update cr0 flags
			this->updateCR0(this->state->gpr[rD]);
		}
	}
	/*
	 *	subfmeox	Subtract From Minus One Extended with Overflow
	 *	.670
	 */
	void Interpreter::subfmeox()
	{
		int rD, rA, rB;
		PPC_OPC_TEMPL_XO(this->state->current_opc, rD, rA, rB);
		PPC_OPC_ASSERT(rB == 0);
		uint32 a = this->state->gpr[rA];
		uint32 ca = ((this->state->xer&XER_CA)?1:0);
		this->state->gpr[rD] = ~a + ca + 0xffffffff;
		// update XER
		if ((a!=0xffffffff) || ca) {
			this->state->xer |= XER_CA;
		} else {
			this->state->xer &= ~XER_CA;
		}
		if (this->state->current_opc & PPC_OPC_Rc) {
			// update cr0 flags
			this->updateCR0(this->state->gpr[rD]);
		}
		// update XER flags
		PPC_ALU_ERR("subfmeox unimplemented\n");
	}
	/*
	 *	subfzex		Subtract From Zero Extended
	 *	.671
	 */
	void Interpreter::subfzex()
	{
		int rD, rA, rB;
		PPC_OPC_TEMPL_XO(this->state->current_opc, rD, rA, rB);
		PPC_OPC_ASSERT(rB == 0);
		uint32 a = this->state->gpr[rA];
		uint32 ca = ((this->state->xer&XER_CA)?1:0);
		this->state->gpr[rD] = ~a + ca;
		if (!a && ca) {
			this->state->xer |= XER_CA;
		} else {
			this->state->xer &= ~XER_CA;
		}
		if (this->state->current_opc & PPC_OPC_Rc) {
			// update cr0 flags
			this->updateCR0(this->state->gpr[rD]);
		}
	}
	/*
	 *	subfzeox	Subtract From Zero Extended with Overflow
	 *	.671
	 */
	void Interpreter::subfzeox()
	{
		int rD, rA, rB;
		PPC_OPC_TEMPL_XO(this->state->current_opc, rD, rA, rB);
		PPC_OPC_ASSERT(rB == 0);
		uint32 a = this->state->gpr[rA];
		uint32 ca = ((this->state->xer&XER_CA)?1:0);
		this->state->gpr[rD] = ~a + ca;
		if (!a && ca) {
			this->state->xer |= XER_CA;
		} else {
			this->state->xer &= ~XER_CA;
		}
		if (this->state->current_opc & PPC_OPC_Rc) {
			// update cr0 flags
			this->updateCR0(this->state->gpr[rD]);
		}
		// update XER flags
		PPC_ALU_ERR("subfzeox unimplemented\n");
	}

	/*
	 *	xorx		XOR
	 *	.680
	 */
	void Interpreter::xorx()
	{
		int rS, rA, rB;
		PPC_OPC_TEMPL_X(this->state->current_opc, rS, rA, rB);
		this->state->gpr[rA] = this->state->gpr[rS] ^ this->state->gpr[rB];
		if (this->state->current_opc & PPC_OPC_Rc) {
			// update cr0 flags
			this->updateCR0(this->state->gpr[rA]);
		}
	}
	/*
	 *	xori		XOR Immediate
	 *	.681
	 */
	void Interpreter::xori()
	{
		int rS, rA;
		uint32 imm;
		PPC_OPC_TEMPL_D_UImm(this->state->current_opc, rS, rA, imm);
		this->state->gpr[rA] = this->state->gpr[rS] ^ imm;
	}
	/*
	 *	xoris		XOR Immediate Shifted
	 *	.682
	 */
	void Interpreter::xoris()
	{
		int rS, rA;
		uint32 imm;
		PPC_OPC_TEMPL_D_Shift16(this->state->current_opc, rS, rA, imm);
		this->state->gpr[rA] = this->state->gpr[rS] ^ imm;
	}

}
