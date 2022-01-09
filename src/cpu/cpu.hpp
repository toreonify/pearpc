#pragma once

#include "config.h"
#include "configuration/configuration.hpp"

namespace CPU
{
	class ICPU
	{
	public:
		ICPU() {};
		virtual ~ICPU() {};
		
		static void initializeConfigurationEntries(Configuration::Configuration* config) {};
		
		virtual void start() = 0;
		virtual void stop() = 0;
		
		virtual void executionLoop() = 0;
	};
}

// Dynamically include correct CPU header based on autotools argument
#include CPU_INCLUDE_DIR
