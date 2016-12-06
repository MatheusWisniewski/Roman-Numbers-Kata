#pragma once

#include <map>

using namespace std;

class NumberConverter {

public:
	NumberConverter();
	~NumberConverter();

	enum EStringTypes {
		Blank,
		OnlyDigits,
		OnlyLetters
	};

	map <char, int> roman2arabicMap;
	map <int, string> ones;
	map <int, string> fives;

	void makeUppercase(string &numberString);

	EStringTypes getStringType(string numberString);
	bool isRomanLetter(char letter);

	int roman2arabic(string romanNumber);
	string arabic2roman(string romanNumber);


};

