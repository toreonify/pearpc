#include "cpu.hpp"

#include "common/arch/endianness.h"

#include <iostream>

namespace CPU
{
	CPU::CPU(Configuration::Configuration* config)
	{
		this->state.pvr = config->getEntry<int>(CPU_KEY_PVR)->getValue();
		
		this->interpreter = new Interpreter(&this->state);
	
		this->interpreter->initOpcodes();
				
		// initialize srs (mostly for prom)
		for (int i=0; i<16; i++) {
			this->state.sr[i] = 0x2aa*i;
		}
		
		//sys_create_mutex(&exception_mutex);
		
		// Test
		
		std::cout << "CPU testing routine" << std::endl;
		
		this->interpreter->testOpcodes();
		
		std::cout << "CPU testing done" << std::endl;
		
		// End of test
	}
	
	CPU::~CPU()
	{
		
	}

	void CPU::initializeConfigurationEntries(Configuration::Configuration* config)
	{
		config->addEntry<int>(CPU_KEY_PVR, true, 0x000c0201);
	}

	void CPU::start()
	{

	}
	
	void CPU::executionLoop()
	{

	}
	
	void CPU::stop()
	{
		
		
	}
}