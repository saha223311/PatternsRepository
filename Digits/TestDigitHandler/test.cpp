#include "pch.h"
#include "../Digits/DigitHandler.h"

std::string readFile(const std::string& fileName) {
	std::string strFile;
	std::ifstream file;

	file.open(fileName);
	getline(file, strFile, '\0');
	file.close();

	return strFile;
}

TEST(TestCaseName, Test_00) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(TestCaseName, Test_01) {
	DigitHandler dHandler;
	EXPECT_EQ(dHandler.setInputFile("TestDigits_01.txt"), CORRECT_INPUT_FILE);
	EXPECT_EQ(dHandler.setOutputFile("Result.txt"), CORRECT_OUTPUT_FILE);
	EXPECT_EQ(dHandler.processDigits(), RESULT_DONE);
	EXPECT_EQ(readFile("Result.txt"), "0123456789\n0123456\n");
}

TEST(TestCaseName, Test_02) {
	DigitHandler dHandler;
	EXPECT_EQ(dHandler.setInputFile("TestDigits_02.txt"), CORRECT_INPUT_FILE);
	EXPECT_EQ(dHandler.setOutputFile("Result.txt"), CORRECT_OUTPUT_FILE);
	EXPECT_EQ(dHandler.processDigits(), RESULT_DONE);
	EXPECT_EQ(readFile("Result.txt"), "0124679\n");
}

TEST(TestCaseName, Test_03) {
	DigitHandler dHandler;
	EXPECT_EQ(dHandler.setInputFile("TestDigits_03.txt"), CORRECT_INPUT_FILE);
	EXPECT_EQ(dHandler.setOutputFile("Result.txt"), CORRECT_OUTPUT_FILE);
	EXPECT_EQ(dHandler.processDigits(), RESULT_DONE);
	EXPECT_EQ(readFile("Result.txt"), "1111111111\n111111111\n");
}

TEST(TestCaseName, Test_04) {
	DigitHandler dHandler;
	EXPECT_EQ(dHandler.setInputFile("TestDigits_04.txt"), CORRECT_INPUT_FILE);
	EXPECT_EQ(dHandler.setOutputFile("Result.txt"), CORRECT_OUTPUT_FILE);
	EXPECT_EQ(dHandler.processDigits(), RESULT_DONE);
	EXPECT_EQ(readFile("Result.txt"), "0123456789\n0000000000\n0123456789\n0000000000\n012345\n");
}

TEST(TestCaseName, Test_05) {
	DigitHandler dHandler;
	EXPECT_EQ(dHandler.setInputFile("TestDigits_05.txt"), CORRECT_INPUT_FILE);
	EXPECT_EQ(dHandler.setOutputFile("Result.txt"), CORRECT_OUTPUT_FILE);
	EXPECT_EQ(dHandler.processDigits(), WRONG_DIGIT_NUMBER);
}

TEST(TestCaseName, Test_06) {
	DigitHandler dHandler;
	EXPECT_EQ(dHandler.setInputFile("TestDigits_06.txt"), CORRECT_INPUT_FILE);
	EXPECT_EQ(dHandler.setOutputFile("Result.txt"), CORRECT_OUTPUT_FILE);
	EXPECT_EQ(dHandler.processDigits(), WRONG_COUNT_OF_NUMBER);
}

TEST(TestCaseName, Test_07) {
	DigitHandler dHandler;
	EXPECT_EQ(dHandler.setInputFile("MISSING_FILE.txt"), INCORRECT_INPUT_FILE);
}