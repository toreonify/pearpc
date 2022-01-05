/*
 *	PearPC
 *	configparser.cc
 *
 *	Copyright (C) 2003 Sebastian Biallas (sb@biallas.net)
 *
 *	This program is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License version 2 as
 *	published by the Free Software Foundation.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with this program; if not, write to the Free Software
 *	Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
 
#include "configuration.hpp"

namespace Configuration
{
	Configuration::Configuration()
	{
		
	}
	
	Configuration::~Configuration()
	{
		
	}
	
	Entry* Configuration::getEntry(std::string key)
	{
		std::map<std::string, Entry*>::iterator i = this->entries.find(key);
		
		if (i == this->entries.end())
			return NULL;
		
		return this->entries.at(i->first);
	}
	
	void Configuration::parseStream(std::istream& in)
	{
		for (std::string line; std::getline(in, line); )
		{
			if (line.length() > 0)
			{
				// Skip unwanted lines
				if (line[0] == '#')
					continue;
				
				if (line[0] == '\n' || line[0] == '\r')
					continue;
				
				// Extract values
				int nameStart = 0;
				bool nameStartSet = false;
				
				int nameEnd = 0;
				bool nameEndSet = false;
				
				int valueStart = 0;
				bool valueStartSet = false;
				
				int valueEnd = 0;
				bool valueEndSet = false;
				
				bool delimeterFound = false;
				bool skipSpaces = false;
				
				int i = 0;
				for (i = 0; i < line.length(); i++)
				{
					if (line[i] == ' ' || line[i] == '\t' || line[i] == '\r')
					{
						if (nameStartSet && !nameEndSet)
						{
							nameEnd = i - 1;
							nameEndSet = true;
							continue;
						}
						
						if (valueStartSet && !skipSpaces)
						{
							valueEnd = i - 1;
							valueEndSet = true;
							
							break;
						}
						
						continue;
					}
					
					if (!nameStartSet)
					{
						nameStart = i;
						nameStartSet = true;
						continue;
					}
					
					if (line[i] == '=' && !valueStartSet)
					{
						delimeterFound = true;
						continue;
					}
					
					if (!valueStartSet && delimeterFound)
					{
						valueStartSet = true;
						
						if (line[i] == '"')
						{
							valueStart = i + 1;
							skipSpaces = true;
						}
						else
						{
							valueStart = i;
						}
							
						continue;
					}
					
					if (line[i] == '"' && skipSpaces)
					{
						valueEnd = i - 1;
						valueEndSet = true;
						
						break;
					}
				}

				// If iteration ended on last symbol and it wasn't a string, value start found, set end as last symbol
				if ((i == line.length()) && !skipSpaces && valueStartSet && !valueEndSet)
				{
					valueEnd = i - 1;
					valueEndSet = true;
				}
				
				if (!(nameStartSet && nameEndSet && valueStartSet && valueEndSet))
				{
					throw std::invalid_argument("invalid line: " + line);
				}
				
				// Try to extract values
				std::string entryName;
				std::string entryValue;
				
				try
				{
					entryName = line.substr(nameStart, nameEnd - nameStart + 1);
					entryValue = line.substr(valueStart, valueEnd - valueStart + 1);
					
					std::cout << entryName << " === " << entryValue << std::endl;
				}
				catch (std::exception& e)
				{
					std::cout << "Configuration: parser error " << e.what() << std::endl;
				}
				
				// Check, if we have entry with this name
				Entry* entry = this->getEntry(entryName);
				if (entry == NULL)
				{
					std::cout << "Entry " << entryName << " not found, skipping" << std::endl;
					continue;
				}
				
				// Try to convert extracted value
				std::cout << entry->getType() << std::endl;
				
				//if (entry->getType() == "int")
				
			}
		}
		
	}
}