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
	EXPECT_EQ(dHandler.setInputFile("TestDigits_01.txt"), StreamController::RESULT_DONE);
	EXPECT_EQ(dHandler.setOutputFile("Result.txt"), StreamController::RESULT_DONE);
	EXPECT_EQ(dHandler.processDigits(), StreamController::RESULT_DONE);
	std::string resultCodes[4] = { "012345678 ERR\n", "000000051\n", "012315678 ERR\n", "012345678 ERR\n"};
	EXPECT_EQ(readFile("Result.txt"), resultCodes[0] + resultCodes[1] + resultCodes[2] + resultCodes[3]);
}

TEST(TestCaseName, Test_02) {
	DigitHandler dHandler;
	EXPECT_EQ(dHandler.setInputFile("TestDigits_02.txt"), StreamController::RESULT_DONE);
	EXPECT_EQ(dHandler.setOutputFile("Result.txt"), StreamController::RESULT_DONE);
	EXPECT_EQ(dHandler.processDigits(), StreamController::RESULT_DONE);
	std::string resultCodes[1] = { "100000002\n" };
	EXPECT_EQ(readFile("Result.txt"), resultCodes[0]);
}

TEST(TestCaseName, Test_03) {
	DigitHandler dHandler;
	EXPECT_EQ(dHandler.setInputFile("TestDigits_03.txt"), StreamController::RESULT_DONE);
	EXPECT_EQ(dHandler.setOutputFile("Result.txt"), StreamController::RESULT_DONE);
	EXPECT_EQ(dHandler.processDigits(), StreamController::RESULT_DONE);
	std::string resultCodes[3] = { "111111110\n", "111111111 ERR\n", "111111111 ERR\n" };
	EXPECT_EQ(readFile("Result.txt"), resultCodes[0] + resultCodes[1] + resultCodes[2]);
}

TEST(TestCaseName, Test_04) {
	DigitHandler dHandler;
	EXPECT_EQ(dHandler.setInputFile("TestDigits_04.txt"), StreamController::RESULT_DONE);
	EXPECT_EQ(dHandler.setOutputFile("Result.txt"), StreamController::RESULT_DONE);
	EXPECT_EQ(dHandler.processDigits(), StreamController::RESULT_DONE);
	std::string resultCodes[2] = { "999999990\n", "000000000\n" };
	EXPECT_EQ(readFile("Result.txt"), resultCodes[0] + resultCodes[1]);
}


TEST(TestCaseName, Test_05) {
	DigitHandler dHandler;
	EXPECT_EQ(dHandler.setInputFile("MISSING_FILE.txt"), StreamController::INCORRECT_INPUT_FILE);
}