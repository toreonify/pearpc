#include "entry.hpp"

namespace Configuration
{
	Entry::Entry(bool mandatory)
	{
		this->mandatory = mandatory;
		this->initialized = false;
		this->set = false;
	}

	Entry::~Entry()
	{
		
	}

	bool Entry::isSet()
	{
		return this->set;
	}

	bool Entry::isInitialized()
	{
		return this->initialized;
	}
	
	bool Entry::isMandatory()
	{
		return this->mandatory;
	}
}