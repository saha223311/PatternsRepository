#pragma once
#include <string>
#include <map>

class RomanArabicConvertor
{
public:
	static enum ResultType { RESULT_DONE, WRONG_ROMAN_NUMBER, WRONG_ARABIC_NUMBER };

	static ResultType convertRomanToArabic(const std::string& iRoman, unsigned int& oArabic);
	static ResultType convertArabicToRoman(unsigned int iArabic, std::string& oRoman);
private:
	static const int COUNT_OF_NUM = 13;

	static bool isRomanNum(const std::string& iRoman);
	static bool isArabicnNum(unsigned int iArabic);
};

bool RomanArabicConvertor::isRomanNum(const std::string& iRoman) {
	if (iRoman.empty()) {
		return false;
	}
	int currentRomanNum = COUNT_OF_NUM - 1;
	std::string reverseIRoman = iRoman;
	std::reverse(reverseIRoman.begin(), reverseIRoman.end());
	std::string reverseRomanNums[COUNT_OF_NUM] = { "M", "MC", "D", "DC", "C", "CX", "L", "LX", "X", "XI", "V", "VI", "I" };

	int currentSymbol = 0;
	int numRepeated = 0;	
	while ((currentSymbol != reverseIRoman.size())) {
		if ((currentRomanNum < 0) || (numRepeated > 3)) {
			return false;
		}
		if (reverseIRoman.find(reverseRomanNums[currentRomanNum], currentSymbol) == currentSymbol) {
			currentSymbol += reverseRomanNums[currentRomanNum].size();
			numRepeated++;
			if (reverseRomanNums[currentRomanNum].size() != 1) numRepeated += 2;
		}
		else {
			currentRomanNum--;
			numRepeated = 0;
		}
	}
	return true;
}

bool RomanArabicConvertor::isArabicnNum(unsigned int iArabic) {
	if (iArabic > 3000 || iArabic < 1) {
		return false;
	}
	return true;
}

RomanArabicConvertor::ResultType RomanArabicConvertor::convertRomanToArabic(const std::string& iRoman, unsigned int& oArabic) {
	std::map<char, int> mRomeNums = { {'M',  1000}, {'D',  500}, {'C',  100}, {'L',  50}, {'X',  10}, {'V', 5}, {'I', 1} };

	if (!isRomanNum(iRoman)) {
		return WRONG_ROMAN_NUMBER;
	}
	oArabic = 0;
	for (int i = 0; i < iRoman.size(); ++i) {
		if ((i < iRoman.size() - 1) && (mRomeNums.at(iRoman[i]) < mRomeNums.at(iRoman[i + 1]))) {
			oArabic -= mRomeNums[iRoman[i]];
		}
		else {
			oArabic += mRomeNums[iRoman[i]];
		}
	}
	return RESULT_DONE;
}

RomanArabicConvertor::ResultType RomanArabicConvertor::convertArabicToRoman(unsigned int iArabic, std::string& oRoman) {
	const unsigned int arabicNums[COUNT_OF_NUM] = { 1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1 };
	const std::string romanNums[COUNT_OF_NUM] = { "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I" };

	if (!isArabicnNum(iArabic)) {
		return WRONG_ARABIC_NUMBER;
	}
	oRoman = "";
	for (int i = 0; i < COUNT_OF_NUM; ++i)
	{
		while (iArabic >= arabicNums[i]) {
			iArabic -= arabicNums[i];
			oRoman += romanNums[i];
		}
	}
	return RESULT_DONE;
}
