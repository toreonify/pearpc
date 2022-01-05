#include "configuration/configuration.hpp"

class PearPC
{
private:
	Configuration::Configuration* configuration;
	
	//std::map <std::string, IODevice> ioDevices;
public:
	PearPC();
	~PearPC();
	
	bool initIO();
};