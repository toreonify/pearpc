/* 
 *	HT Editor
 *	except.h
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

#ifndef __EXCEPT_H__
#define __EXCEPT_H__

#include <errno.h>		// for IOException

#include <string>
#include <sstream>

#include "tools/data.h"
#include "tools/str.h"

/**
 *	A exception.
 */
class Exception {
public:
				Exception() throw();
	virtual			~Exception();
/* new */
	virtual std::string &	reason(std::string &result) const;
};

#define MSG_EXCEPTION_MAX_ERRSTR		256

/**
 *	A described exception.
 */
class MsgException: public Exception {
protected:
	char estr[MSG_EXCEPTION_MAX_ERRSTR];
public:
		MsgException(const char *errstr) throw();
		MsgException() throw();
/* new */
	virtual	std::string &reason(std::string &result) const;
};

/**
 *	A formatted described exception.
 */
class MsgfException: public MsgException {
public:
		MsgfException(const char *errstr, ...) throw();
};

/**
 *	A I/O exception.
 */
class IOException: public Exception {
protected:
	std::string errstr;
public:
	int mPosixErrno;

		IOException(int aPosixErrno) throw();
	virtual	~IOException();
/* new */
	virtual	std::string &reason(std::string &result) const;
};

class InternalException: public Exception {
public:
};

/**
 *	A exception, indicating a not-implemented function.
 */
class NotImplementedException: public InternalException {
protected:
	std::string	location;
public:
		NotImplementedException(const std::string &filename, int line_number) throw();
/* new */
	virtual	std::string &reason(std::string &result) const;
};

/**
 *	A exception, indicating a illegal argument.
 */
class IllegalArgumentException: public InternalException {
protected:
	std::string	location;
public:
		IllegalArgumentException(const std::string &filename, int line_number) throw();
/* new */
	virtual	std::string &reason(std::string &result) const;
};

/**
 *	A exception, indicating a illegal type-cast.
 */
class TypeCastException: public InternalException {
protected:
	std::string	aresult;
public:
		TypeCastException(const std::string &cast_type, const std::string &obj_type) throw();
/* new */
	virtual	std::string &reason(std::string &result) const;
};

#endif /* __EXCEPT_H__ */

