#include "NumberConverter.h"
#include <ctype.h>
#include <string>

#include "UnknownNumberException.h"
#include "OutOfBoundsException.h"

NumberConverter::NumberConverter()
{
	roman2arabicMap['I'] = 1;
	roman2arabicMap['V'] = 5;
	roman2arabicMap['X'] = 10;
	roman2arabicMap['L'] = 50;
	roman2arabicMap['C'] = 100;
	roman2arabicMap['D'] = 500;
	roman2arabicMap['M'] = 1000;

	ones[0] = "I";
	ones[1] = "X";
	ones[2] = "C";
	ones[3] = "M";

	fives[0] = "V";
	fives[1] = "L";
	fives[2] = "D";
}

NumberConverter::~NumberConverter()
{
}

void NumberConverter::makeUppercase(string &numberString) {

	for (int i = 0; i < numberString.length(); i++)
	{
		numberString[i] = toupper(numberString[i]);
	}
}

NumberConverter::EStringTypes NumberConverter::getStringType(string numberString)
{
	int length = (int)numberString.length();
	bool hasDigit = false;
	bool hasLetter = false;

	for (int i = 0; i < length; i++)
	{
		if (!isdigit(numberString[i]))
		{
			if (!isRomanLetter(numberString[i]))
				throw UnknownNumberException();

			hasLetter = true;
		}
		else
			hasDigit = true;
	}

	if (hasDigit && hasLetter)
		throw UnknownNumberException();

	if (hasDigit && !hasLetter)
		return EStringTypes::OnlyDigits;

	if (!hasDigit && hasLetter)
		return EStringTypes::OnlyLetters;

	return EStringTypes::Blank;
}

bool NumberConverter::isRomanLetter(char letter)
{
	if (letter == 'I' || letter == 'V' || letter == 'X' || letter == 'L' || letter == 'C' || letter == 'D' || letter == 'M')
		return true;
	else
		return false;
}

int NumberConverter::roman2arabic(string romanNumber) {

	int length = (int)romanNumber.length();
	int indexLastLetterRomanNumber = length - 1;
	int arabicNumber = 0;

	for (int i = indexLastLetterRomanNumber; i >= 0; i--)
	{
		if (i < indexLastLetterRomanNumber && roman2arabicMap[romanNumber[i]] < roman2arabicMap[romanNumber[i+1]])
			arabicNumber -= roman2arabicMap[romanNumber[i]];
		else
			arabicNumber += roman2arabicMap[romanNumber[i]];
	}

	return arabicNumber;
}

string NumberConverter::arabic2roman(string arabicNumber) {

	if (atoi(arabicNumber.c_str()) > 3999 || atoi(arabicNumber.c_str()) < 0)
		throw OutOfBoundsException();

	int length = (int)arabicNumber.length();
	int indexLastDigitArabicNumber = length - 1;
	string romanNumber = "";
	int powerOfTen = 0;

	for (int i = indexLastDigitArabicNumber; i >= 0; i--, powerOfTen++)
	{
		if (arabicNumber.at(i) == '9')
			romanNumber = ones[powerOfTen] + ones[powerOfTen + 1] + romanNumber;
		else if (arabicNumber.at(i) == '4')
			romanNumber = ones[powerOfTen] + fives[powerOfTen] + romanNumber;
		else
		{
			int leftovers = arabicNumber.at(i) - '0';
			string stringToBeAdded = "";

			if (leftovers >= 5)
			{
				stringToBeAdded = fives[powerOfTen];
				leftovers -= 5;
			}

			for (int i = 0; i < leftovers; i++)
			{
				stringToBeAdded = stringToBeAdded + ones[powerOfTen];
			}

			romanNumber = stringToBeAdded + romanNumber;
		}

	}

	return romanNumber;
}
