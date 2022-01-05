#include <string>

#include "configuration/configuration.hpp"

class PearPC
{
private:
	Configuration::Configuration* configuration;
	
	//CPU::CPU* cpu;
	//Debug::Debugger* debugger;
	
	//std::map <std::string, Device*> ioDevices;
	
public:
	PearPC();
	~PearPC();
	
	bool initIO();
	
	void initializeConfigurationEntries();
	void loadConfigurationFile(char* filePath);
};