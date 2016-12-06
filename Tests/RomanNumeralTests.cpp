#include <gtest\gtest.h>
#include <gmock\gmock.h>
#include "NumberConverter.h"
#include "UnknownNumberException.h"
#include "OutOfBoundsException.h"

using namespace testing;
using namespace std;

class TestFixture : public Test {

public:
	NumberConverter *numberConverter;

	void SetUp() override {
		numberConverter = new NumberConverter();
	}

	void TearDown() override {
		delete numberConverter;
	}
};

TEST_F(TestFixture, MakeUppercase) {

	string romanNumber = "xv";

	numberConverter->makeUppercase(romanNumber);

	ASSERT_THAT(romanNumber, Eq(string("XV")));
}

TEST_F(TestFixture, OnlyDigits) {

	string arabicNumber = "1";

	NumberConverter::EStringTypes stringType = numberConverter->getStringType(arabicNumber);

	ASSERT_THAT(stringType, Eq(NumberConverter::EStringTypes::OnlyDigits));
}

TEST_F(TestFixture, OnlyLetters) {

	string romanNumber = "X";

	NumberConverter::EStringTypes stringType = numberConverter->getStringType(romanNumber);

	ASSERT_THAT(stringType, Eq(NumberConverter::EStringTypes::OnlyLetters));
}

TEST_F(TestFixture, UnknownNumber1) {

	string unknownNumber = "1X";

	try {
		NumberConverter::EStringTypes stringType = numberConverter->getStringType(unknownNumber);
		FAIL() << "Expected unknown number exception";
	}
	catch (UnknownNumberException const& err) {
		EXPECT_EQ(err.what(), string("Unknown number. Please do not use numbers and letters at the same time, and use only valid roman letters."));
	}
	catch (...) {
		FAIL() << "Expected unknown number exception";
	}
}

TEST_F(TestFixture, UnknownNumber2) {

	string unknownNumber = "X1";

	try {
		NumberConverter::EStringTypes stringType = numberConverter->getStringType(unknownNumber);
		FAIL() << "Expected unknown number exception";
	}
	catch (UnknownNumberException const& err) {
		EXPECT_EQ(err.what(), string("Unknown number. Please do not use numbers and letters at the same time, and use only valid roman letters."));
	}
	catch (...) {
		FAIL() << "Expected unknown number exception";
	}
}

TEST_F(TestFixture, Blank) {

	string blankNumber = "";

	NumberConverter::EStringTypes numberType = numberConverter->getStringType(blankNumber);

	ASSERT_THAT(numberType, Eq(NumberConverter::EStringTypes::Blank));
}

TEST_F(TestFixture, CheckIfRomanLetter) {

	ASSERT_THAT(numberConverter->isRomanLetter('A'), Eq(false));
	ASSERT_THAT(numberConverter->isRomanLetter('B'), Eq(false));
	ASSERT_THAT(numberConverter->isRomanLetter('C'), Eq(true));
	ASSERT_THAT(numberConverter->isRomanLetter('D'), Eq(true));
	ASSERT_THAT(numberConverter->isRomanLetter('E'), Eq(false));
	ASSERT_THAT(numberConverter->isRomanLetter('F'), Eq(false));
	ASSERT_THAT(numberConverter->isRomanLetter('G'), Eq(false));
	ASSERT_THAT(numberConverter->isRomanLetter('H'), Eq(false));
	ASSERT_THAT(numberConverter->isRomanLetter('I'), Eq(true));
	ASSERT_THAT(numberConverter->isRomanLetter('J'), Eq(false));
	ASSERT_THAT(numberConverter->isRomanLetter('K'), Eq(false));
	ASSERT_THAT(numberConverter->isRomanLetter('L'), Eq(true));
	ASSERT_THAT(numberConverter->isRomanLetter('M'), Eq(true));
	ASSERT_THAT(numberConverter->isRomanLetter('N'), Eq(false));
	ASSERT_THAT(numberConverter->isRomanLetter('O'), Eq(false));
	ASSERT_THAT(numberConverter->isRomanLetter('P'), Eq(false));
	ASSERT_THAT(numberConverter->isRomanLetter('Q'), Eq(false));
	ASSERT_THAT(numberConverter->isRomanLetter('R'), Eq(false));
	ASSERT_THAT(numberConverter->isRomanLetter('S'), Eq(false));
	ASSERT_THAT(numberConverter->isRomanLetter('T'), Eq(false));
	ASSERT_THAT(numberConverter->isRomanLetter('U'), Eq(false));
	ASSERT_THAT(numberConverter->isRomanLetter('V'), Eq(true));
	ASSERT_THAT(numberConverter->isRomanLetter('W'), Eq(false));
	ASSERT_THAT(numberConverter->isRomanLetter('X'), Eq(true));
	ASSERT_THAT(numberConverter->isRomanLetter('Y'), Eq(false));
	ASSERT_THAT(numberConverter->isRomanLetter('Z'), Eq(false));
}

TEST_F(TestFixture, Arabic2Roman) {

	string arabicNumber = "1";
	string romanNumber = "";

	romanNumber = numberConverter->arabic2roman(arabicNumber);

	ASSERT_THAT(romanNumber, Eq("I"));
}

TEST_F(TestFixture, Roman2Arabic0) {

	string romanNumber = "";
	int arabicNumber = 0;

	arabicNumber = numberConverter->roman2arabic(romanNumber);
	ASSERT_THAT(arabicNumber, Eq(0));
}

TEST_F(TestFixture, Roman2Arabic1) {

	string romanNumber = "I";
	int arabicNumber = 0;

	arabicNumber = numberConverter->roman2arabic(romanNumber);
	ASSERT_THAT(arabicNumber, Eq(1));
}

TEST_F(TestFixture, Roman2Arabic4) {

	string romanNumber = "IV";
	int arabicNumber = 0;

	arabicNumber = numberConverter->roman2arabic(romanNumber);
	ASSERT_THAT(arabicNumber, Eq(4));
}

TEST_F(TestFixture, Roman2Arabic876) {

	string romanNumber = "DCCCLXXVI";
	int arabicNumber = 0;

	arabicNumber = numberConverter->roman2arabic(romanNumber);
	ASSERT_THAT(arabicNumber, Eq(876));
}

TEST_F(TestFixture, Roman2Arabic1234) {

	string romanNumber = "MCCXXXIV";
	int arabicNumber = 0;

	arabicNumber = numberConverter->roman2arabic(romanNumber);
	ASSERT_THAT(arabicNumber, Eq(1234));
}

TEST_F(TestFixture, Arabic2Roman0) {

	string arabicNumber = "0";
	string romanNumber = "";

	romanNumber = numberConverter->arabic2roman(arabicNumber);
	ASSERT_THAT(romanNumber, Eq(string("")));
}

TEST_F(TestFixture, Arabic2Roman1) {

	string arabicNumber = "1";
	string romanNumber = "";

	romanNumber = numberConverter->arabic2roman(arabicNumber);
	ASSERT_THAT(romanNumber, Eq(string("I")));
}

TEST_F(TestFixture, Arabic2Roman4) {

	string arabicNumber = "4";
	string romanNumber = "";

	romanNumber = numberConverter->arabic2roman(arabicNumber);
	ASSERT_THAT(romanNumber, Eq(string("IV")));
}

TEST_F(TestFixture, Arabic2Roman876) {

	string arabicNumber = "876";
	string romanNumber = "";

	romanNumber = numberConverter->arabic2roman(arabicNumber);
	ASSERT_THAT(romanNumber, Eq(string("DCCCLXXVI")));
}

TEST_F(TestFixture, Arabic2Roman1234) {

	string arabicNumber = "1234";
	string romanNumber = "";

	romanNumber = numberConverter->arabic2roman(arabicNumber);
	ASSERT_THAT(romanNumber, Eq(string("MCCXXXIV")));
}

TEST_F(TestFixture, Arabic2RomanOutOfBoundsLow) {

	string arabicNumber = "-1";
	string romanNumber = "";

	try {
		romanNumber = numberConverter->arabic2roman(arabicNumber);
		FAIL() << "Expected out of bounds exception";
	}
	catch (OutOfBoundsException const& err) {
		EXPECT_EQ(err.what(), string("Your number is out of bounds. Please enter a number between 0 and 3999."));
	}
	catch (...) {
		FAIL() << "Expected out of bounds exception";
	}
}

TEST_F(TestFixture, Arabic2RomanOutOfBoundsHigh) {

	string arabicNumber = "4000";
	string romanNumber = "";

	try {
		romanNumber = numberConverter->arabic2roman(arabicNumber);
		FAIL() << "Expected out of bounds exception";
	}
	catch (OutOfBoundsException const& err) {
		EXPECT_EQ(err.what(), string("Your number is out of bounds. Please enter a number between 0 and 3999."));
	}
	catch (...) {
		FAIL() << "Expected out of bounds exception";
	}
}


