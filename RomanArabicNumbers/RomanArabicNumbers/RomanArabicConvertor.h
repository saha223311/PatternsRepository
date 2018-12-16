#pragma once
#include <string>
#include <map>

enum ResultType { RESULT_DONE, WRONG_ROMAN_NUMBER, WRONG_ARABIC_NUMBER };

class RomanArabicConvertor
{
public:
	ResultType convertRomanToArabic(std::string iRoman, unsigned int& oArabic);
	ResultType convertArabicToRoman(unsigned int iArabic, std::string& oRoman);
private:
	const int COUNT_OF_NUM = 13;
	std::map<char, int> mRomeNums = { {'M',  1000}, {'D',  500}, {'C',  100}, {'L',  50}, {'X',  10}, {'V', 5}, {'I', 1} };
	unsigned int arabicNums[13] = { 1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1 };
	std::string romanNums[13] = { "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I" };

	bool isRomanNum(std::string iRoman);
	bool isArabicnNum(unsigned int iArabic);
};

bool RomanArabicConvertor::isRomanNum(std::string iRoman) {
	int currentRomanNum = COUNT_OF_NUM - 1;
	std::string reverseRomanNums[13] = { "M", "MC", "D", "DC", "C", "CX", "L", "LX", "X", "XI", "V", "VI", "I" };

	std::reverse(iRoman.begin(), iRoman.end());
	int currentSymbol = 0;
	int numRepeated = 0;
	while ((currentSymbol != iRoman.length() - 1)) {
		if ((currentRomanNum < 0) || (numRepeated > 3)) {
			return false;
		}
		if (iRoman.find(reverseRomanNums[currentRomanNum], currentSymbol) == currentSymbol) {
			currentSymbol += reverseRomanNums[currentRomanNum].length();
			numRepeated++;
		}
		else {
			currentRomanNum--;
			numRepeated = 0;
		}
	}
	return true;
}

bool RomanArabicConvertor::isArabicnNum(unsigned int iArabic) {
	if (iArabic > 3000) {
		return false;
	}
	return true;
}

ResultType RomanArabicConvertor::convertRomanToArabic(std::string iRoman, unsigned int& oArabic) {
	if (!this->isRomanNum(iRoman)) {
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

ResultType RomanArabicConvertor::convertArabicToRoman(unsigned int iArabic, std::string& oRoman) {
	if (!this->isArabicnNum(iArabic)) {
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
