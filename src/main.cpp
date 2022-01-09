#include "pearpc.hpp"

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
		pearPcInstance->loadConfigurationFile(argv[1]);
	}
	catch (const std::exception& e)
	{
		std::cout << "Configuration: " << e.what() << std::endl;
		return 1;
	}
	
	pearPcInstance->initializeModules();
	
	return 0;
}