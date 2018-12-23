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
	std::string resultCodes[3] = { "012345678 ERR\n", "000000051 \n", "0123?5678 ILL\n" };
	EXPECT_EQ(readFile("Result.txt"), resultCodes[0] + resultCodes[1] + resultCodes[2]);
}

TEST(TestCaseName, Test_02) {
	DigitHandler dHandler;
	EXPECT_EQ(dHandler.setInputFile("TestDigits_02.txt"), CORRECT_INPUT_FILE);
	EXPECT_EQ(dHandler.setOutputFile("Result.txt"), CORRECT_OUTPUT_FILE);
	EXPECT_EQ(dHandler.processDigits(), RESULT_DONE);
	std::string resultCodes[1] = { "100000002 \n" };
	std::string a = readFile("Result.txt");
	EXPECT_EQ(readFile("Result.txt"), resultCodes[0]);
}

TEST(TestCaseName, Test_03) {
	DigitHandler dHandler;
	EXPECT_EQ(dHandler.setInputFile("TestDigits_03.txt"), CORRECT_INPUT_FILE);
	EXPECT_EQ(dHandler.setOutputFile("Result.txt"), CORRECT_OUTPUT_FILE);
	EXPECT_EQ(dHandler.processDigits(), RESULT_DONE);
	std::string resultCodes[3] = { "111111110 \n", "11111111? ILL\n", "111111111 ERR\n" };
	EXPECT_EQ(readFile("Result.txt"), resultCodes[0] + resultCodes[1] + resultCodes[2]);
}

TEST(TestCaseName, Test_04) {
	DigitHandler dHandler;
	EXPECT_EQ(dHandler.setInputFile("TestDigits_04.txt"), CORRECT_INPUT_FILE);
	EXPECT_EQ(dHandler.setOutputFile("Result.txt"), CORRECT_OUTPUT_FILE);
	EXPECT_EQ(dHandler.processDigits(), RESULT_DONE);
	std::string resultCodes[2] = { "999999990 \n", "000000000 \n" };
	EXPECT_EQ(readFile("Result.txt"), resultCodes[0] + resultCodes[1]);
}


TEST(TestCaseName, Test_05) {
	DigitHandler dHandler;
	EXPECT_EQ(dHandler.setInputFile("MISSING_FILE.txt"), INCORRECT_INPUT_FILE);
}