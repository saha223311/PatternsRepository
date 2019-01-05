#pragma once
#include <string>
#include <map>

// Было бы неплохо чаще использовать ключевое слово const

// Статусы точно не стоит в глобальный scope помещать
// Если enum, то лучше его разместить в классе конвертера
enum ResultType { RESULT_DONE, WRONG_ROMAN_NUMBER, WRONG_ARABIC_NUMBER };

// В этом классе можно все сделать static
class RomanArabicConvertor
{
public:
	// Неэффективная передача аргумента iRoman, можно по const-ref
	// И не только здесь
	ResultType convertRomanToArabic(std::string iRoman, unsigned int& oArabic);
	ResultType convertArabicToRoman(unsigned int iArabic, std::string& oRoman);
private:
	const int COUNT_OF_NUM = 13;
	std::map<char, int> mRomeNums = { {'M',  1000}, {'D',  500}, {'C',  100}, {'L',  50}, {'X',  10}, {'V', 5}, {'I', 1} };
	// В качестве размера массива нужно передать именованную константу
	// Иначе размеры массивов могут перестать совпадать в какой-то момент
	unsigned int arabicNums[13] = { 1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1 };
	std::string romanNums[13] = { "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I" };

	bool isRomanNum(std::string iRoman);
	bool isArabicnNum(unsigned int iArabic);
};

// Что будет если передать сюда пустую строку?
bool RomanArabicConvertor::isRomanNum(std::string iRoman) {
	int currentRomanNum = COUNT_OF_NUM - 1;
	// Эта штука явно как-то связана romanNums нужно как минимум занести в классе
	// Лучше не копи-пастить, а вычислить
	// Да еще и магическая константа
	std::string reverseRomanNums[13] = { "M", "MC", "D", "DC", "C", "CX", "L", "LX", "X", "XI", "V", "VI", "I" };

	// можно не изменеять контейнер, а использовать reverse_iterator
	std::reverse(iRoman.begin(), iRoman.end());
	int currentSymbol = 0;
	int numRepeated = 0;
	while ((currentSymbol != iRoman.length() - 1)) {
		// Не все символы могут повторяться 3 раза
		// Что насчет теста IXIXIX ?
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
