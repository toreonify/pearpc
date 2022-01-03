#include <fstream>

#include "configparser.h"

#include "pearpc.h"

PearPC* pearPcInstance;

int main (int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << "Usage: ppc <config_file>" << std::endl;
		return -1;
	}
	
	// Configuration
	ConfigParser* config = new ConfigParser();
	
	try
	{
		std::ifstream* configFile = new std::ifstream(argv[1]);
		
		if (configFile->is_open())
			config->loadConfig(*configFile);
		
		delete configFile;
	}
	catch (const Exception &e)
	{
		std::string res;
		e.reason(res);
		std::cout << "Configuration file error: " << res << std::endl;

		return 1;
	}
	
	// Emulator instance
	pearPcInstance = new PearPC();
	
	// Emulation thread
	
	// UI
	
	// Start emulation
	
	// Event loop
	//SDL_Event event;
	//while (SDL_WaitEvent(&event))
	{
		
	}
	
	return 0;
}