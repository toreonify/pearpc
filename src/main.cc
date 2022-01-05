#include "pearpc.h"

PearPC* pearPcInstance;

int main (int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << "Usage: ppc <config_file>" << std::endl;
		return -1;
	}
	
	pearPcInstance = new PearPC();
	
	try {
		pearPcInstance->initializeConfigurationEntries();
		pearPcInstance->loadConfigurationFile(argv[1]);
	}
	catch (const std::exception& e)
	{
		std::cout << "Configuration: " << e.what() << std::endl;
		return 1;
	}
	
	return 0;
}