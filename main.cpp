#include <gmock\gmock.h>
#include <gtest\gtest.h>
#include <iostream>

#include "NumberConverter.h"
#include <exception>

using namespace testing;
using namespace std;

int main(int argc, char* argv[]) {

	InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();

	system("pause");
	system("cls");

	string number;

	cout << ">> Enter an arabic OR roman number to be converted: " << endl << endl;

	cin >> number;

	NumberConverter *converter = new NumberConverter();

	converter->makeUppercase(number);

	try {
		NumberConverter::EStringTypes stringType = converter->getStringType(number);
	
		if (stringType == NumberConverter::EStringTypes::Blank || stringType == NumberConverter::EStringTypes::OnlyLetters)
			cout << endl << ">> Your roman number in arabic form is:" << endl << endl << converter->roman2arabic(number) << endl << endl;
		else if (stringType == NumberConverter::EStringTypes::OnlyDigits)
			cout << endl << ">> Your arabic number in roman form is:" << endl << endl << converter->arabic2roman(number) << endl << endl;
	}
	catch (exception const& e) {
		cout << endl << ">>" << e.what() << endl << endl;
		system("pause");
		return 0;
	}

	system("pause");
	return 0;
}