#include "interpreter.hpp"
#include <iostream>

namespace CPU
{
	Interpreter::Interpreter(CPUState* state)
	{
		this->state = state;
	}

	void Interpreter::testOpcodes()
	{
		this->state->gpr[0] = 0x10;
		this->state->gpr[1] = 0x20;
			
		std::cout << this->state->gpr[0] << std::endl;
		std::cout << this->state->gpr[1] << std::endl;
		std::cout << this->state->gpr[2] << std::endl;
		
		// addi
		// 0b011111 00010 00000 00001 0 100001010 0
		// 01111100010000000000101000010100
		this->state->current_opc = 0b01111100010000000000101000010100;
		
		(this->*opcodes[31])();
		
		std::cout << this->state->gpr[2] << std::endl;
	}

}