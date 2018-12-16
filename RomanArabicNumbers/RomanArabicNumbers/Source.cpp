#include <iostream>
#include "RomanArabicConvertor.h"

int main() {
	RomanArabicConvertor convertor;

	//std::cout << convertor.isRomanNum("CCCLIIII");

	unsigned int enterArabic;
	std::string outputRoman;
	std::cin >> enterArabic;
	if (convertor.convertArabicToRoman(enterArabic, outputRoman) == RESULT_DONE) {
		std::cout << outputRoman << std::endl;
	}

	std::string enterRoman;
	unsigned int outputArabic;
	std::cin >> enterRoman;
	if (convertor.convertRomanToArabic(enterRoman, outputArabic) == RESULT_DONE) {
		std::cout << outputArabic << std::endl;
	}

	system("pause");
}