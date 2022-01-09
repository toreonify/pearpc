#pragma once

#include "cpu/common.hpp"
#include "system/types.h"

namespace CPU
{
	struct CPUState {
		// * uisa
		uint32 gpr[32];
		uint64 fpr[32];
		uint32 cr;
		uint32 fpscr;
		uint32 xer;	// spr 1
		uint32 xer_ca;  // carry from xer
		uint32 lr;	// spr 8
		uint32 ctr;	// spr 9
		// * oea
		uint32 msr;
		uint32 pvr;	// spr 287

		//    * memory managment
		uint32 ibatu[4];	// spr 528, 530, 532, 534
		uint32 ibatl[4];	// spr 529, 531, 533, 535
		uint32 ibat_bl17[4];	// for internal use

		uint32 dbatu[4];	// spr 536, 538, 540, 542
		uint32 dbatl[4];	// spr 537, 539, 541, 543
		uint32 dbat_bl17[4];	// for internal use

		uint32 sdr1;	// spr 25       (page table base address)

		uint32 sr[16];
	
		//    * exception handling
		uint32 dar;	// spr 19
		uint32 dsisr;	// spr 18
		uint32 sprg[4]; // spr 272-275
		uint32 srr[2];	// spr 26-27
	
		//    * misc
		uint32 dec;	// spr 22
		uint32 ear;	// spr 282 .101
		uint32 pir;	// spr 1032
		uint64 tb;	// .75 spr 284(l)/285(u)
	
		uint32 hid[16];
		// * internal
	
		uint32 pc;
		uint32 npc;
		uint32 current_opc;
		bool   exception_pending;
		bool   dec_exception;
		bool   ext_exception;
		bool   stop_exception;
		bool   singlestep_ignore;

		uint32 pagetable_base;
		int    pagetable_hashmask;
		uint32 reserve;
		bool   have_reservation;
	
		// for generic cpu core
		uint32 effective_code_page;
		byte  *physical_code_page;
		uint64 pdec;	// more precise version of dec
		uint64 ptb;	// more precise version of tb

		// for altivec
		uint32 vscr;
		uint32 vrsave;	// spr 256
		Vector_t vr[36];		// <--- this MUST be 16-byte alligned
		uint32 vtemp;
	};
}