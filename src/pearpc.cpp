#include <pearpc.hpp>

#include <fstream>

PearPC::PearPC()
{
	this->configuration = new Configuration::Configuration();
	
	this->initializeConfigurationEntries();
}

PearPC::~PearPC()
{
	
}

void PearPC::initializeConfigurationEntries()
{
	// Common entries
	this->configuration->addEntry<std::string>("ppc_start_resolution", true, std::string("800x600x15"));
	this->configuration->addEntry<int>("ppc_start_full_screen", true, 0);
	this->configuration->addEntry<int>("memory_size", true, 128*1024*1024);
	this->configuration->addEntry<int>("page_table_pa", true, 0x00300000);
	this->configuration->addEntry<int>("redraw_interval_msec", true, 20);
	this->configuration->addEntry<std::string>("key_compose_dialog", true, std::string("F11"));
	this->configuration->addEntry<std::string>("key_change_cd_0", true, std::string("none"));
	this->configuration->addEntry<std::string>("key_change_cd_1", true, std::string("none"));
	this->configuration->addEntry<std::string>("key_toggle_mouse_grab", true, std::string("F12"));
	this->configuration->addEntry<std::string>("key_toggle_full_screen", true, std::string("Ctrl+Alt+Return"));
	
	// Entries from other modules
	CPU::CPU::initializeConfigurationEntries(this->configuration);
		
	//prom_init_config();
	//io_init_config();
	//ppc_cpu_init_config();
	//debugger_init_config();
}

void PearPC::loadConfigurationFile(char* filePath)
{
	std::ifstream* configFile = new std::ifstream(filePath);

	if (configFile->is_open())
		this->configuration->parseStream(*configFile);

	delete configFile;
}

void PearPC::initializeModules()
{
	this->cpu = (CPU::ICPU*) new CPU::CPU(this->configuration);
}