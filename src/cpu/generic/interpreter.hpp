#pragma once

#include "system/types.h"

#include "structs.hpp"


// Temporary macros
#include <stdio.h>
#define PPC_ALU_ERR(x) printf(x);
#define PPC_ALU_WARN(x, y) printf(x, y);

#define SINGLESTEP(x) ;

namespace CPU
{
	class Interpreter
	{
	private:
		CPUState* state;

		typedef void (Interpreter::*OpCode)();

		// Opcode lists
		OpCode opcodes[64] = { &Interpreter::invalid };
		OpCode opcodesGroup2[1015] = { &Interpreter::invalid };
		OpCode opcodesGroupV[965] = { &Interpreter::invalid };
		
		void opcodesGroup2Call();
		
		// Common methods for opcodes
		void updateCR0(uint32 r);
		
		// Invalid opcode
		void invalid();
		
		// ALU opcodes
		void addx();
		void addox();
		void addcx();
		void addcox();
		void addex();
		void addeox();
		void addi();
		void addic();
		void addic_();
		void addis();
		void addmex();
		void addmeox();
		void addzex();
		void addzeox();

		void andx();
		void andcx();
		void andi_();
		void andis_();

		void cmp();
		void cmpi();
		void cmpl();
		void cmpli();

		void cntlzwx();

		void crand();
		void crandc();
		void creqv();
		void crnand();
		void crnor();
		void cror();
		void crorc();
		void crxor();

		void divwx();
		void divwox();
		void divwux();
		void divwuox();

		void eqvx();

		void extsbx();
		void extshx();

		void mulhwx();
		void mulhwux();
		void mulli();
		void mullwx();

		void nandx();

		void negx();
		void negox();
		void norx();

		void orx();
		void orcx();
		void ori();
		void oris();

		void rlwimix();
		void rlwinmx();
		void rlwnmx();

		void slwx();
		void srawx();
		void srawix();
		void srwx();

		void subfx();
		void subfox();
		void subfcx();
		void subfcox();
		void subfex();
		void subfeox();
		void subfic();
		void subfmex();
		void subfmeox();
		void subfzex();
		void subfzeox();

		void xorx();
		void xori();
		void xoris();
		
		// ??? opcodes
		
	public:
		Interpreter(CPUState* state);
		~Interpreter();
		
		void execute();
		
		void initOpcodes();
		void initOpcodesGroup2();
		void initOpcodesGroupV();
		
		void testOpcodes();
	};
}