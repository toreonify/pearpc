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
 
#include <ctype.h>
#include "configparser.h"
#include "tools/except.h"
#include "tools/snprintf.h"

// TODO: remove
ConfigParser *gConfig;

ConfigEntry::ConfigEntry(const std::string name, bool mandatory)
{
	this->name = new std::string(name);
	this->mandatory = mandatory;
	this->initialized = false;
	this->set = false;
}

ConfigEntry::~ConfigEntry()
{
	delete this->name;
}

ConfigType ConfigEntry::getType() const
{
	throw MsgException("Untyped entry, cannot get type");
}

int ConfigEntry::asInt() const
{
	throw MsgfException("Untyped entry, cannot be interpreted %y as Integer", this->name);
}

std::string &ConfigEntry::asString(std::string &result) const
{
	throw MsgfException("Untyped entry, cannot be interpreted %y as String", this->name);
}

int ConfigEntry::compareTo(const ConfigEntry *obj) const
{
	return this->name->compare(*(obj->name));
}

bool ConfigEntry::isSet() const
{
	return this->set;
}

bool ConfigEntry::isInitialized() const
{
	return this->initialized;
}
	

class ConfigEntryInt: public ConfigEntry {
	int value;
public:

	ConfigEntryInt(const std::string &name, bool mandatory)
		:ConfigEntry(name, mandatory)
	{
	}

	ConfigEntryInt(const std::string &name, int defaultValue)
		:ConfigEntry(name, false)
	{
		value = defaultValue;
		initialized = true;
	}
	
	virtual ConfigType getType() const
	{
		return configTypeInt;
	}
	
	void setValue(int v)
	{
		this->value = v;
		this->initialized = true;
		this->set = true;
	}
	
	virtual int asInt() const
	{
		return value;
	}
	
	virtual std::string &asString(std::string &result) const
	{
		throw MsgfException("ConfigEntryInt cannot be interpreted %y as String", this->name);
	}
};

class ConfigEntryString: public ConfigEntry {
	std::string value;
public:

	ConfigEntryString(const std::string &name, bool mandatory)
		:ConfigEntry(name, mandatory)
	{
	}
	
	ConfigEntryString(const std::string &name, const std::string &defaultValue)
		: ConfigEntry(name, false), value(defaultValue)
	{
		this->initialized = true;
	}
	
	virtual ConfigType getType() const
	{
		return configTypeString;
	}
	
	void setValue(const std::string &s)
	{
		this->value = s;
		this->initialized = true;
		this->set = true;
	}
	
	virtual std::string &asString(std::string &result) const
	{
		result = this->value;
		return result;
	}
	
	virtual int asInt() const
	{
		throw MsgfException("ConfigEntryString cannot be interpreted %y as Integer", this->name);
	}
};



ConfigParser::ConfigParser()
{
	entries = new AVLTree(true);
}

ConfigParser::~ConfigParser()
{
	delete entries;
}
	
void ConfigParser::acceptConfigEntryInt(const std::string &name, bool mandatory)
{
	ConfigEntry *entry = new ConfigEntryInt(name, mandatory);
	if (!entries->insert(entry)) throw MsgfException("duplicate config entry '%y'", &name);
}

void ConfigParser::acceptConfigEntryString(const std::string &name, bool mandatory)
{
	ConfigEntry *entry = new ConfigEntryString(name, mandatory);
	if (!entries->insert(entry)) throw MsgfException("duplicate config entry '%y'", &name);
}

void ConfigParser::acceptConfigEntryIntDef(const std::string &name, int d)
{
	ConfigEntry *entry = new ConfigEntryInt(name, d);
	if (!entries->insert(entry)) throw MsgfException("duplicate config entry '%y'", &name);
}

void ConfigParser::acceptConfigEntryStringDef(const std::string &name, const std::string &d)
{
	ConfigEntry *entry = new ConfigEntryString(name, d);
	if (!entries->insert(entry)) throw MsgfException("duplicate config entry '%y'", &name);
}

bool ConfigParser::skipWhite(std::istream &in)
{
	while (cur == ' ' || cur == '\t' || cur == '\r') {
		if (!in.read(&cur, 1)) return false;
	}
	return true;
}

#define INV 0xff
byte mapchar[]={
	' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', 10,' ',' ',' ',' ',' ', // 0-15
	' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', // 16-31
	' ','!','"','#','$','%','&', 39,'(',')','*','+',',','-','.','/', // 32-47
	'0','0','0','0','0','0','0','0','0','0',':',';','<','=','>','?', // 48-63
	'@','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A', // 64-79
	'A','A','A','A','A','A','A','A','A','A','A','[', 92,']','^','_', // 80-95
	INV,'A','A','A','A','A','A','A','A','A','A','A','A','A','A','A', // 96-111
	'A','A','A','A','A','A','A','A','A','A','A','{','|','}','~',INV, // 112-127
	INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,
	INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,
	INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,
	INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,
	INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,
	INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,
	INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,
	INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV
};

void ConfigParser::loadConfig(std::istream &in)
{
	read(in);
	foreach(ConfigEntry, e, *entries, {
		if (e->mandatory && !e->isInitialized()) {
			throw MsgfException("config entry '%y' is not set.", e->name);
		}
	});
}

void ConfigParser::read(std::istream &in)
{
	if (!in.read(&cur, 1)) return;
	line = 1;
	while (true) {
		if (!skipWhite(in)) return;
		if (cur == '#') {
			// skip comment
			do {
				if (!in.read(&cur, 1)) return;
			} while (cur != '\n');
			if (!in.read(&cur, 1)) return;
			line++;
			continue;
		}
		if (cur == '\r') {
			if (!in.read(&cur, 1)) return;
			continue;
		}
		if (cur == '\n') {
			if (!in.read(&cur, 1)) return;
			line++;
			continue;
		}
		byte m = mapchar[cur];
		std::string ident;
		if (m != 'A' && m != '_') throw MsgfException("invalid character '%c' (%02x) in line %d.", cur, cur, line);
		do {
			ident += cur;
			if (!in.read(&cur, 1)) throw MsgfException("syntax error in line %d.", line);
			m = mapchar[cur];
		} while (m == 'A' || m == '0' || m == '_');
		
		ConfigEntry *e = getEntry(ident);
		if (!e) throw MsgfException("unknown identifier '%s' in line %d.", ident.c_str(), line);
		if (e->isSet()) throw MsgfException("config entry '%y' is already set in line %d.", e->name, line);
		
		if (!skipWhite(in)) throw MsgfException("%s expected in line %d.", "'='", line);
		if (cur != '=') throw MsgfException("%s expected in line %d.", "'='", line);
		if (!in.read(&cur, 1) || !skipWhite(in)) throw MsgfException("syntax error in line %d.", line);
		m = mapchar[cur];
		
		if (e->getType() == configTypeInt) {
			if (m != '0') throw MsgfException("%s expected in line %d.", "integer", line);
			std::string n;
			do {
				n += cur;
				if (!in.read(&cur, 1)) cur = ' ';
				m = mapchar[cur];
			} while (m == '0' || m == 'A');
			if (cur == '\n' || cur == '\r' || cur == ' ' || cur == '\t' || cur == '#') {
				// nothing to do
			} else {
				cur = tolower(cur);
				if (cur == 'h' || cur == 'o' || cur == 'b' || cur == 'd') {
					n += cur;
					if (!in.read(&cur, 1)) cur = ' ';
				} else {
					throw MsgfException("%s expected in line %d.", "integer", line);
				}
			}
			uint64 u = std::strtoul(n.c_str(), NULL, 10);
			
			//if (!n.toInt64(u)) throw MsgfException("%s expected in line %d.", "integer", line);
			
			((ConfigEntryInt *)e)->setValue(u);
		} else {
			if (m != '"') throw MsgfException("%s expected in line %d.", "'\"'", line);
			std::string s;
			int oldline = line;
			do {
				s += cur;
				if (!in.read(&cur, 1)) throw MsgfException("unterminated string in line %d (starts in line %d).", line, oldline);
				m = mapchar[cur];
				if (m == '\n') line++;
			} while (m != '"');
			s.erase(0, 1);
			((ConfigEntryString *)e)->setValue(s);
			if (!in.read(&cur, 1)) cur = ' ';
		}
		if (!skipWhite(in)) return;
		if (cur == '#') continue;
		if (cur != '\n') throw MsgfException("syntax error in line %d.", line);
	}
}

ConfigEntry *ConfigParser::getEntry(const std::string &name)
{
	ConfigEntry empty(name, false);
	return (ConfigEntry *)entries->get(entries->find(&empty));
}

int ConfigParser::getConfigInt(const std::string &name)
{
	ConfigEntry empty(name, false);
	ConfigEntry *entry = (ConfigEntry *)entries->get(entries->find(&empty));
	if (!entry) throw MsgfException("unknown entry '%y'", &name);
	if (!entry->isInitialized()) throw MsgfException("%y is not set!", &name);
	return entry->asInt();
}

std::string &ConfigParser::getConfigString(const std::string &name, std::string &result)
{
	ConfigEntry empty(name, false);
	ConfigEntry *entry = (ConfigEntry *)entries->get(entries->find(&empty));
	if (!entry) throw MsgfException("unknown entry '%y'", &name);
	if (!entry->isInitialized()) throw MsgfException("%y is not set!", &name);
	return entry->asString(result);
}

bool ConfigParser::haveKey(const std::string &name)
{
	ConfigEntry empty(name, false);
	ConfigEntry *entry = (ConfigEntry *)entries->get(entries->find(&empty));
	return entry && entry->isSet();
}

