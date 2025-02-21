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

#pragma once

#include <string>
#include <iostream>
#include <map>

#include "entry.hpp"

namespace Configuration
{
	// TODO: do we need this? maybe for config names?
	//const char allowedCharacters[] = "abcdefghijklmopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	
	class Configuration
	{
	private:
		std::map<std::string, Entry*> entries;
	public:
		Configuration();
		~Configuration();
		
		Entry* getEntry(std::string key);
		template<class T> TypedEntry<T>* getEntry(std::string key)
		{
			std::map<std::string, Entry*>::iterator i = this->entries.find(key);
		
			if (i == this->entries.end())
				return NULL;
		
			Entry* entry = this->entries.at(i->first);
		
			// Check for type
			if (typeid(T).name() != entry->getType())
				throw std::invalid_argument("Requested entry type doesn't equal to actual entry type");
	
			return (TypedEntry<T>*)entry;
		};
		
		bool haveEntry(std::string& key);
		
		template<class T> void addEntry(const std::string name, bool mandatory, T defaultValue)
		{
			std::pair<std::map<std::string, Entry*>::iterator, bool> ret;
			
			ret = this->entries.insert(std::pair<std::string, Entry*>(name, (Entry*)new TypedEntry<T>(mandatory)));
			
			if (!ret.second)
				throw std::invalid_argument("Entry " + name + " already exists.");
		};
		
		void parseStream(std::istream& in);
	};
}
