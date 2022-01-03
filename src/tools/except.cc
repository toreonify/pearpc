/* 
 *	HT Editor
 *	except.cc
 *
 *	Copyright (C) 1999-2002 Stefan Weyergraf
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

#include <cstdio>
#include <cstdarg>
#include <cstring>

#include "except.h"
#include "snprintf.h"

/*
 *	class Exception
 */

Exception::Exception() throw()
{
}

Exception::~Exception()
{
}

std::string &Exception::reason(std::string &result) const
{
	result = "Unknown Exception";
	return result;
}

/*
 *	class MsgException
 */
MsgException::MsgException() throw()
{
}

MsgException::MsgException(const char *e) throw()
{
	strncpy(estr, e, sizeof estr-1);
	estr[sizeof estr-1] = 0;
}

std::string &MsgException::reason(std::string &result) const
{
	result = estr;
	return result;
}

/*
 *	class MsgfException
 */
MsgfException::MsgfException(const char *e,...) throw()
{
	va_list va;
	va_start(va, e);
	ht_vsnprintf(estr, sizeof estr, e, va);
	va_end(va);
}

/*
 *	class IOException
 */

//#include <signal.h>
IOException::IOException(int aPosixErrno) throw()
{
	mPosixErrno = aPosixErrno;
	errstr = strerror(mPosixErrno);
//	raise(SIGTRAP);
}

IOException::~IOException()
{
}

std::string &IOException::reason(std::string &result) const
{
	result = "I/O error: " + errstr;
	return result;
}

/*
 *	class NotImplementedException
 */

NotImplementedException::NotImplementedException(const std::string &filename, int line_number) throw()
{
	if (line_number) {
		std::stringstream ss;
		ss << filename << ":" << line_number;
		location = ss.str();
	} else {
		location = filename;
	}
}

std::string &NotImplementedException::reason(std::string &result) const
{
	result = "Function not implemented";
	if (!location.empty()) result += ": "+location;
	return result;
}

/*
 *	class IllegalArgumentException
 */

IllegalArgumentException::IllegalArgumentException(const std::string &filename, int line_number) throw()
{
	if (line_number) {
		std::stringstream ss;
		ss << filename << ":" << line_number;
		location = ss.str();
	} else {
		location = filename;
	}
}

std::string &IllegalArgumentException::reason(std::string &result) const
{
	result = "Illegal argument";
	if (!location.empty()) result += ": "+location;
	return result;
}

/*
 *	class TypeCastException
 */

TypeCastException::TypeCastException(const std::string &cast_type, const std::string &obj_type) throw()
{
	std::stringstream ss;
	ss << "(" << cast_type << ") " << obj_type;
	aresult = ss.str();
}

std::string &TypeCastException::reason(std::string &result) const
{
	result = "Bad type cast";
	if (!aresult.empty()) result += ": "+aresult;
	return result;
}

