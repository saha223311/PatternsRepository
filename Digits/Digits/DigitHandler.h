#pragma once

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

class StreamController {
public:
	enum ResultType { RESULT_DONE, WRONG_COUNT_OF_NUMBER, INCORRECT_INPUT_FILE, INCORRECT_OUTPUT_FILE };

	StreamController() : istream(&std::cin), ostream(&std::cout), ifstream(nullptr), ofstream(nullptr) {};
	~StreamController();

	bool createIStream(std::string inputStreamFile);
	bool createOStream(std::string outputStreamFile);

	std::istream* getIStream() const;
	std::ostream* getOStream() const;
private:
	std::istream* istream;
	std::ostream* ostream;

	std::ifstream* ifstream;
	std::ofstream* ofstream;
};

bool StreamController::createIStream(std::string inputStreamFile) {
	ifstream = new std::ifstream(inputStreamFile);
	if (!*ifstream) {
		return false;
	}
	istream = ifstream;
	return true;
}

bool StreamController::createOStream(std::string outputStreamFile) {
	ofstream = new std::ofstream(outputStreamFile);
	if (!*ofstream) {
		return false;
	}
	ostream = ofstream;
	return true;
}

std::istream* StreamController::getIStream() const {
	return istream;
}

std::ostream* StreamController::getOStream() const {
	return ostream;
}

StreamController::~StreamController() {
	if (!(ifstream == nullptr)) {
		ifstream->close();
		delete ifstream;
	}
	if (!(ofstream == nullptr)) {
		ofstream->close();
		delete ofstream;
	}

}

class DigitHandler {
public:
	DigitHandler() = default;
	~DigitHandler() = default;

	StreamController::ResultType setInputFile(std::string inputFileName);
	StreamController::ResultType setOutputFile(std::string outputFileName);

	StreamController::ResultType processDigits();

	std::vector<std::string> scanDigits();
	std::string calcDigits(std::vector<std::string> digits);

	std::string getPossibleNums(std::string code);
	std::vector<std::string> getCorrectDigits(std::string code, std::string possibleNums);

	bool isCorrectDigit(std::string code);
	bool isCorrectCheckSum(std::string code);

private:
	StreamController streamController;

	static const short digitWidth = 3;
	static const short digitHeight = 3;

	const std::map<std::string, std::string> mDigits = {	{" _ "
															 "| |"
															 "|_|", "0"},
															{"   "
															 "  |"
															 "  |", "1"},
															{" _ "
															 " _|"
															 "|_ ", "2"},
															{" _ "
															 " _|"
															 " _|", "3"},
															{"   "
															 "|_|"
															 "  |", "4"},
															{" _ "
															 "|_ "
															 " _|", "5"},
															{" _ "
															 "|_ "
															 "|_|", "6"},
															{" _ "
															 "  |"
															 "  |", "7"},
															{" _ "
															 "|_|"
															 "|_|", "8"},
															{" _ "
															 "|_|"
															 " _|", "9"}
	};

};

StreamController::ResultType DigitHandler::setInputFile(std::string inputFileName) {
	if (!streamController.createIStream(inputFileName)) {
		return StreamController::INCORRECT_INPUT_FILE;
	}
	return StreamController::RESULT_DONE;
}

StreamController::ResultType DigitHandler::setOutputFile(std::string outputFileName) {
	if (!streamController.createOStream(outputFileName)) {
		return StreamController::INCORRECT_OUTPUT_FILE;
	}
	return StreamController::RESULT_DONE;
}

StreamController::ResultType DigitHandler::processDigits() {
	std::ostream* out = streamController.getOStream();
	while (!streamController.getIStream()->eof()) {
		std::vector<std::string> rawDigits = this->scanDigits();
		std::string code = this->calcDigits(rawDigits);

		if (this->isCorrectDigit(code)) {
			if (!this->isCorrectCheckSum(code)) {
				*out << code << " " << "ERR" << std::endl;
			}
			else {
				*out << code << std::endl;
			}
		}
		else {
			std::string nums;
			for (auto d : rawDigits) {
				if (mDigits.find(d) == mDigits.end()) {
					nums = getPossibleNums(d);
					break;
				}
			}

			std::vector<std::string> correctCodes = getCorrectDigits(code, nums);
			if (correctCodes.empty()) {
				*out << code << " " << "ILL" << std::endl;
			}
			else {
				for (auto correctCode : correctCodes) {
					if (!this->isCorrectCheckSum(correctCode)) {
						*out << correctCode << " " << "ERR" << std::endl;
					}
					else {
						*out << correctCode << std::endl;
					}
				}
			}
		}
	}
	return StreamController::RESULT_DONE;
}

std::string DigitHandler::getPossibleNums(std::string code) {
	std::string possibleNums = "";
	for (auto& item : mDigits) {
		int diff = 0;
		for (int i = 0; i < item.first.size(); ++i) {
			if (code[i] != item.first[i]) {
				diff++;
			}
		}
		if (diff == 1) {
			possibleNums += item.second;
		}
	}
	return possibleNums;
}

std::vector<std::string> DigitHandler::getCorrectDigits(std::string code, std::string possibleNums) {
	std::vector<std::string> correctDigits;
	size_t incorrectSymbolIndex = code.find('?');
	std::string tempDigit(code);
	for (auto possibleNum : possibleNums) {
		tempDigit[incorrectSymbolIndex] = possibleNum;
		correctDigits.push_back(tempDigit);
	}
	return correctDigits;
}

std::vector<std::string> DigitHandler::scanDigits() {
	std::vector<std::string> digits(9);
	std::string codePiece;

	for (int i = 0; i < digitHeight; ++i) {
		std::getline(*streamController.getIStream(), codePiece);

		for (int j = 0; j < 9; ++j) {
			digits[j] += codePiece.substr(j * digitWidth, 3);
		}
	}
	std::getline(*streamController.getIStream(), codePiece);
	return digits;
}

std::string DigitHandler::calcDigits(std::vector<std::string> digits) {
	std::string code = "";
	for (int i = 0; i < 9; ++i) {
		if (mDigits.find(digits[i]) == mDigits.end()) {
			code += "?";
		}
		else {
			code += mDigits.at(digits[i]);
		}
		digits[i] = "";
	}
	return code;
}

bool DigitHandler::isCorrectDigit(std::string code) {
	return code.find('?') == std::string::npos;
}

bool DigitHandler::isCorrectCheckSum(std::string code) {
	int checkSum = 0;
	for (int i = 0; i < 10; ++i) {
		checkSum += (code[i] - 48) * (9 - i);
	}
	return checkSum % 11 == 0;
}