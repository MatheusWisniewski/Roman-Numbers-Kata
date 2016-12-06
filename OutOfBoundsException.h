#pragma once

#include <exception>

using namespace std;

class OutOfBoundsException : public exception {

public:

	OutOfBoundsException() :
		exception("Your number is out of bounds. Please enter a number between 0 and 3999.")
	{}

	virtual ~OutOfBoundsException() throw() {}
};