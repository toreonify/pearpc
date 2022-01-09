#pragma once

#include "cpu/cpu.hpp"

#include "interpreter.hpp"
#include "structs.hpp"

#define CPU_KEY_PVR	"cpu_pvr"

namespace CPU
{
	class CPU : ICPU
	{
	private:
		CPUState state;
		Interpreter* interpreter;
		
	public:
		CPU(Configuration::Configuration* config);
		~CPU();
		
		static void initializeConfigurationEntries(Configuration::Configuration* config);

		void start();
		void stop();
		
		void executionLoop();
	};
}