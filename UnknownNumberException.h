#pragma once

#include <exception>

using namespace std;

class UnknownNumberException : public exception {

public:

	UnknownNumberException() :
		exception("Unknown number. Please do not use numbers and letters at the same time, and use only valid roman letters.")
	{}

	virtual ~UnknownNumberException() throw() {}
};