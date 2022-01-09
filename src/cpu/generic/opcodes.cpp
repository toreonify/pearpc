#include "system/types.h"
#include "cpu/common.hpp"
#include "interpreter.hpp"
#include "opcodes.hpp"

namespace CPU
{
	void Interpreter::initOpcodes()
	{
		this->opcodes[2] = &Interpreter::invalid; // (tdi on 64 bit platforms)
		//this->opcodes[3] = &Interpreter::twi;
		this->opcodes[4] = &Interpreter::invalid; // (altivec group 1)
		this->opcodes[7] = &Interpreter::mulli;
		this->opcodes[8] = &Interpreter::subfic;
		this->opcodes[10] = &Interpreter::cmpli;
		this->opcodes[11] = &Interpreter::cmpi;
		this->opcodes[12] = &Interpreter::addic;
		this->opcodes[13] = &Interpreter::addic_;
		this->opcodes[14] = &Interpreter::addi;
		this->opcodes[15] = &Interpreter::addis;
		//this->opcodes[16] = &Interpreter::bcx;
		//this->opcodes[17] = &Interpreter::sc;
		//this->opcodes[18] = &Interpreter::bx;
		//this->opcodes[19] = &Interpreter::group_1;
		this->opcodes[20] = &Interpreter::rlwimix;
		this->opcodes[21] = &Interpreter::rlwinmx;
		this->opcodes[23] = &Interpreter::rlwnmx;
		this->opcodes[24] = &Interpreter::ori;
		this->opcodes[25] = &Interpreter::oris;
		this->opcodes[26] = &Interpreter::xori;
		this->opcodes[27] = &Interpreter::xoris;
		this->opcodes[28] = &Interpreter::andi_;
		this->opcodes[29] = &Interpreter::andis_;
		this->opcodes[30] = &Interpreter::invalid; // (group_rld on 64 bit platforms)
		this->opcodes[31] = &Interpreter::opcodesGroup2Call;
		//this->opcodes[32] = &Interpreter::lwz;
		//this->opcodes[33] = &Interpreter::lwzu;
		//this->opcodes[34] = &Interpreter::lbz;
		//this->opcodes[35] = &Interpreter::lbzu;
		//this->opcodes[36] = &Interpreter::stw;
		//this->opcodes[37] = &Interpreter::stwu;
		//this->opcodes[38] = &Interpreter::stb;
		//this->opcodes[39] = &Interpreter::stbu;
		//this->opcodes[40] = &Interpreter::lhz;
		//this->opcodes[41] = &Interpreter::lhzu;
		//this->opcodes[42] = &Interpreter::lha;
		//this->opcodes[43] = &Interpreter::lhau;
		//this->opcodes[44] = &Interpreter::sth;
		//this->opcodes[45] = &Interpreter::sthu;
		//this->opcodes[46] = &Interpreter::lmw;
		//this->opcodes[47] = &Interpreter::stmw;
		//this->opcodes[48] = &Interpreter::lfs;
		//this->opcodes[49] = &Interpreter::lfsu;
		//this->opcodes[50] = &Interpreter::lfd;
		//this->opcodes[51] = &Interpreter::lfdu;
		//this->opcodes[52] = &Interpreter::stfs;
		//this->opcodes[53] = &Interpreter::stfsu;
		//this->opcodes[54] = &Interpreter::stfd;
		//this->opcodes[55] = &Interpreter::stfdu;
		this->opcodes[58] = &Interpreter::invalid; // (ld on 64 bit platforms)
		//this->opcodes[59] = &Interpreter::group_f1;
		//this->opcodes[63] = &Interpreter::group_f2;
		
		this->initOpcodesGroup2();
		
		if ((this->state->pvr & 0xffff0000) == 0x000c0000) {
			//this->opcodes[4] = &Interpreter::ppc_opc_group_v;
			this->initOpcodesGroupV();
		}
	}

	// main opcode 31
	void Interpreter::initOpcodesGroup2()
	{
		/*this->opcodesGroup2[0] = &Interpreter::cmp;
		this->opcodesGroup2[4] = &Interpreter::tw;
		this->opcodesGroup2[8] = &Interpreter::subfcx;//+
		this->opcodesGroup2[10] = &Interpreter::addcx;//+
		this->opcodesGroup2[11] = &Interpreter::mulhwux;
		this->opcodesGroup2[19] = &Interpreter::mfcr;
		this->opcodesGroup2[20] = &Interpreter::lwarx;
		this->opcodesGroup2[23] = &Interpreter::lwzx;
		this->opcodesGroup2[24] = &Interpreter::slwx;
		this->opcodesGroup2[26] = &Interpreter::cntlzwx;
		this->opcodesGroup2[28] = &Interpreter::andx;
		this->opcodesGroup2[32] = &Interpreter::cmpl;
		this->opcodesGroup2[40] = &Interpreter::subfx;
		this->opcodesGroup2[54] = &Interpreter::dcbst;
		this->opcodesGroup2[55] = &Interpreter::lwzux;
		this->opcodesGroup2[60] = &Interpreter::andcx;
		this->opcodesGroup2[75] = &Interpreter::mulhwx;
		this->opcodesGroup2[83] = &Interpreter::mfmsr;
		this->opcodesGroup2[86] = &Interpreter::dcbf;
		this->opcodesGroup2[87] = &Interpreter::lbzx;
		this->opcodesGroup2[104] = &Interpreter::negx;
		this->opcodesGroup2[119] = &Interpreter::lbzux;
		this->opcodesGroup2[124] = &Interpreter::norx;
		this->opcodesGroup2[136] = &Interpreter::subfex;//+
		this->opcodesGroup2[138] = &Interpreter::addex;//+
		this->opcodesGroup2[144] = &Interpreter::mtcrf;
		this->opcodesGroup2[146] = &Interpreter::mtmsr;
		this->opcodesGroup2[150] = &Interpreter::stwcx_;
		this->opcodesGroup2[151] = &Interpreter::stwx;
		this->opcodesGroup2[183] = &Interpreter::stwux;
		this->opcodesGroup2[200] = &Interpreter::subfzex;//+
		this->opcodesGroup2[202] = &Interpreter::addzex;//+
		this->opcodesGroup2[210] = &Interpreter::mtsr;
		this->opcodesGroup2[215] = &Interpreter::stbx;
		this->opcodesGroup2[232] = &Interpreter::subfmex;//+
		this->opcodesGroup2[234] = &Interpreter::addmex;
		this->opcodesGroup2[235] = &Interpreter::mullwx;//+
		this->opcodesGroup2[242] = &Interpreter::mtsrin;
		this->opcodesGroup2[246] = &Interpreter::dcbtst;
		this->opcodesGroup2[247] = &Interpreter::stbux;*/
		this->opcodesGroup2[266] = &Interpreter::addx;
		/*this->opcodesGroup2[278] = &Interpreter::dcbt;
		this->opcodesGroup2[279] = &Interpreter::lhzx;
		this->opcodesGroup2[284] = &Interpreter::eqvx;
		this->opcodesGroup2[306] = &Interpreter::tlbie;
		this->opcodesGroup2[310] = &Interpreter::eciwx;
		this->opcodesGroup2[311] = &Interpreter::lhzux;
		this->opcodesGroup2[316] = &Interpreter::xorx;
		this->opcodesGroup2[339] = &Interpreter::mfspr;
		this->opcodesGroup2[343] = &Interpreter::lhax;
		this->opcodesGroup2[370] = &Interpreter::tlbia;
		this->opcodesGroup2[371] = &Interpreter::mftb;
		this->opcodesGroup2[375] = &Interpreter::lhaux;
		this->opcodesGroup2[407] = &Interpreter::sthx;
		this->opcodesGroup2[412] = &Interpreter::orcx;
		this->opcodesGroup2[438] = &Interpreter::ecowx;
		this->opcodesGroup2[439] = &Interpreter::sthux;
		this->opcodesGroup2[444] = &Interpreter::orx;
		this->opcodesGroup2[459] = &Interpreter::divwux;//+
		this->opcodesGroup2[467] = &Interpreter::mtspr;
		this->opcodesGroup2[470] = &Interpreter::dcbi;
		this->opcodesGroup2[476] = &Interpreter::nandx;
		this->opcodesGroup2[491] = &Interpreter::divwx;//+
		this->opcodesGroup2[512] = &Interpreter::mcrxr;
		this->opcodesGroup2[533] = &Interpreter::lswx;
		this->opcodesGroup2[534] = &Interpreter::lwbrx;
		this->opcodesGroup2[535] = &Interpreter::lfsx;
		this->opcodesGroup2[536] = &Interpreter::srwx;
		this->opcodesGroup2[566] = &Interpreter::tlbsync;
		this->opcodesGroup2[567] = &Interpreter::lfsux;
		this->opcodesGroup2[595] = &Interpreter::mfsr;
		this->opcodesGroup2[597] = &Interpreter::lswi;
		this->opcodesGroup2[598] = &Interpreter::sync;
		this->opcodesGroup2[599] = &Interpreter::lfdx;
		this->opcodesGroup2[631] = &Interpreter::lfdux;
		this->opcodesGroup2[659] = &Interpreter::mfsrin;
		this->opcodesGroup2[661] = &Interpreter::stswx;
		this->opcodesGroup2[662] = &Interpreter::stwbrx;
		this->opcodesGroup2[663] = &Interpreter::stfsx;
		this->opcodesGroup2[695] = &Interpreter::stfsux;
		this->opcodesGroup2[725] = &Interpreter::stswi;
		this->opcodesGroup2[727] = &Interpreter::stfdx;
		this->opcodesGroup2[758] = &Interpreter::dcba;
		this->opcodesGroup2[759] = &Interpreter::stfdux;
		this->opcodesGroup2[790] = &Interpreter::lhbrx;
		this->opcodesGroup2[792] = &Interpreter::srawx;
		this->opcodesGroup2[824] = &Interpreter::srawix;
		this->opcodesGroup2[854] = &Interpreter::eieio;
		this->opcodesGroup2[918] = &Interpreter::sthbrx;
		this->opcodesGroup2[922] = &Interpreter::extshx;
		this->opcodesGroup2[954] = &Interpreter::extsbx;
		this->opcodesGroup2[982] = &Interpreter::icbi;
		this->opcodesGroup2[983] = &Interpreter::stfiwx;
		this->opcodesGroup2[1014] = &Interpreter::dcbz;*/

		if ((this->state->pvr & 0xffff0000) == 0x000c0000) {
			/* Added for Altivec support */
			/*this->opcodesGroup2[6] = &Interpreter::lvsl;
			this->opcodesGroup2[7] = &Interpreter::lvebx;
			this->opcodesGroup2[38] = &Interpreter::lvsr;
			this->opcodesGroup2[39] = &Interpreter::lvehx;
			this->opcodesGroup2[71] = &Interpreter::lvewx;
			this->opcodesGroup2[103] = &Interpreter::lvx;
			this->opcodesGroup2[135] = &Interpreter::stvebx;
			this->opcodesGroup2[167] = &Interpreter::stvehx;
			this->opcodesGroup2[199] = &Interpreter::stvewx;
			this->opcodesGroup2[231] = &Interpreter::stvx;
			this->opcodesGroup2[342] = &Interpreter::dst;
			this->opcodesGroup2[359] = &Interpreter::lvxl;
			this->opcodesGroup2[374] = &Interpreter::dstst;
			this->opcodesGroup2[487] = &Interpreter::stvxl;
			this->opcodesGroup2[822] = &Interpreter::dss;*/
		}
	}
	
	void Interpreter::initOpcodesGroupV()
	{
		
	}
	
	// main opcode 31
	void Interpreter::opcodesGroup2Call()
	{
		uint32 ext = PPC_OPC_EXT(this->state->current_opc);
		if (ext >= (sizeof opcodesGroup2 / sizeof opcodesGroup2[0])) {
			this->invalid();
		}
		(this->*opcodesGroup2[ext])();
	}
	
	void Interpreter::updateCR0(uint32 r)
	{
		this->state->cr &= 0x0fffffff;
		
		if (!r) {
			this->state->cr |= CR_CR0_EQ;
		} else if (r & 0x80000000) {
			this->state->cr |= CR_CR0_LT;
		} else {
			this->state->cr |= CR_CR0_GT;
		}
		
		if (this->state->xer & XER_SO)
			this->state->cr |= CR_CR0_SO;
	}
	
	
	void Interpreter::invalid()
	{
		
	}
}