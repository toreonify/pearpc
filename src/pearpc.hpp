#pragma once

#include <string>

#include "configuration/configuration.hpp"
#include "cpu/cpu.hpp"

class PearPC
{
private:
	Configuration::Configuration* configuration;
	
	CPU::ICPU* cpu;
	//Debug::Debugger* debugger;
	
	//std::map <std::string, Device*> ioDevices;
	
public:
	PearPC();
	~PearPC();
	
	bool initIO();
	
	void initializeConfigurationEntries();
	void loadConfigurationFile(char* filePath);
	
	void initializeModules();
};