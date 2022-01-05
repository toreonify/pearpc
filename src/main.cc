#include <fstream>

#include "pearpc.h"


PearPC* pearPcInstance;

int main (int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << "Usage: ppc <config_file>" << std::endl;
		return -1;
	}
	
	Configuration::Configuration* config = new Configuration::Configuration();
	
	try {
		config->addEntry<std::string>("ppc_start_resolution", true, std::string("800x600x15"));
		config->addEntry<int>("ppc_start_full_screen", true, 0);
	}
	catch (const std::exception& e)
	{
		std::cout << "Configuration: " << e.what() << std::endl;
		exit(1);
	}
	
	// config->acceptConfigEntryIntDef("ppc_start_full_screen", 0);
// 	config->acceptConfigEntryIntDef("memory_size", 128*1024*1024);
// 	config->acceptConfigEntryIntDef("page_table_pa", 0x00300000);
// 	config->acceptConfigEntryIntDef("redraw_interval_msec", 20);
// 	config->acceptConfigEntryStringDef("key_compose_dialog", "F11");
// 	config->acceptConfigEntryStringDef("key_change_cd_0", "none");
// 	config->acceptConfigEntryStringDef("key_change_cd_1", "none");
// 	config->acceptConfigEntryStringDef("key_toggle_mouse_grab", "F12");
// 	config->acceptConfigEntryStringDef("key_toggle_full_screen", "Ctrl+Alt+Return");

	//prom_init_config();
	//io_init_config();
	//ppc_cpu_init_config();
	//debugger_init_config();
	
	try
	{
		std::ifstream* configFile = new std::ifstream(argv[1]);

		if (configFile->is_open())
			config->parseStream(*configFile);

		delete configFile;
	}
	catch (const std::exception& e)
	{
		std::cout << "Configuration: " << e.what() << std::endl;

		return 1;
	}
	
	std::cout << "ppc_start_resolution " << config->getEntry<std::string>("ppc_start_resolution")->getValue() << std::endl;
	std::cout << "ppc_start_full_screen " << config->getEntry<int>("ppc_start_full_screen")->getValue() << std::endl;
	
	return 0;
}