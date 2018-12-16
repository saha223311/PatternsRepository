#include "pch.h"
#include "../RomanArabicNumbers/RomanArabicConvertor.h"

TEST(TestCaseName, Test_00) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(TestCaseName, Test_01) {
	RomanArabicConvertor convertor;
	unsigned int inputArabic = 555;
	std::string outputRoman;
	EXPECT_EQ(convertor.convertArabicToRoman(inputArabic, outputRoman), RESULT_DONE);
	EXPECT_EQ(outputRoman, "DLV");
}

TEST(TestCaseName, Test_02) {
	RomanArabicConvertor convertor;
	unsigned int inputArabic = 123;
	std::string outputRoman;
	EXPECT_EQ(convertor.convertArabicToRoman(inputArabic, outputRoman), RESULT_DONE);
	EXPECT_EQ(outputRoman, "CXXIII");
}

TEST(TestCaseName, Test_03) {
	RomanArabicConvertor convertor;
	unsigned int inputArabic = 0;
	std::string outputRoman;
	EXPECT_EQ(convertor.convertArabicToRoman(inputArabic, outputRoman), RESULT_DONE);
	EXPECT_EQ(outputRoman, "");
}

TEST(TestCaseName, Test_04) {
	RomanArabicConvertor convertor;
	unsigned int inputArabic = 5000;
	std::string outputRoman;
	EXPECT_EQ(convertor.convertArabicToRoman(inputArabic, outputRoman), WRONG_ARABIC_NUMBER);
}

TEST(TestCaseName, Test_05) {
	RomanArabicConvertor convertor;
	std::string inputRoman = "DLV";
	unsigned int outputArabic;
	EXPECT_EQ(convertor.convertRomanToArabic(inputRoman, outputArabic), RESULT_DONE);
	EXPECT_EQ(outputArabic, 555);
}

TEST(TestCaseName, Test_06) {
	RomanArabicConvertor convertor;
	std::string inputRoman = "MDCLXVI";
	unsigned int outputArabic;
	EXPECT_EQ(convertor.convertRomanToArabic(inputRoman, outputArabic), RESULT_DONE);
	EXPECT_EQ(outputArabic, 1666);
}

TEST(TestCaseName, Test_07) {
	RomanArabicConvertor convertor;
	std::string inputRoman = "DLVIIII";
	unsigned int outputArabic;
	EXPECT_EQ(convertor.convertRomanToArabic(inputRoman, outputArabic), WRONG_ROMAN_NUMBER);
}