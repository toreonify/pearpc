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

#ifndef __CONFIGPARSER_H__
#define __CONFIGPARSER_H__

#include <string>
#include <iostream>

#include "tools/data.h"

enum ConfigType {
	configTypeInt,
	configTypeString,
};

class ConfigEntry: public Object {
public:
	std::string *name;
	bool mandatory;
	bool initialized;
	bool set;
	
	ConfigEntry(const std::string name, bool mandatory);
	virtual ~ConfigEntry();
	
	virtual int	asInt() const;
	virtual std::string	&asString(std::string &result) const;
	
	virtual ConfigType getType() const;
	virtual bool isSet() const;
	virtual bool isInitialized() const;
	
	virtual	int	compareTo(const ConfigEntry *obj) const;
};

class ConfigParser: public Object {
	Container *entries;
	char cur;
	int line;
public:
	ConfigParser();
	virtual	~ConfigParser();

	void	acceptConfigEntryInt(const std::string &name, bool mandatory);
	void	acceptConfigEntryString(const std::string &name, bool mandatory);
	void	acceptConfigEntryIntDef(const std::string &name, int d);
	void	acceptConfigEntryStringDef(const std::string &name, const std::string &d);
	void	loadConfig(std::istream &in);

	ConfigEntry *getEntry(const std::string &name);
	bool	haveKey(const std::string &name);

	// these will throw an exception if key isn't set!
	int	getConfigInt(const std::string &name);
	std::string &getConfigString(const std::string &name, std::string &result);
protected:
	bool	skipWhite(std::istream &in);
	void	read(std::istream &in);
};

#endif
