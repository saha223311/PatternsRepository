#pragma once

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

enum ResultType { RESULT_DONE, WRONG_COUNT_OF_NUMBER, CORRECT_INPUT_FILE, CORRECT_OUTPUT_FILE, INCORRECT_INPUT_FILE, INCORRECT_OUTPUT_FILE };

class StreamController {
public:
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
	DigitHandler();
	~DigitHandler() = default;

	ResultType setInputFile(std::string inputFileName);
	ResultType setOutputFile(std::string outputFileName);

	ResultType processDigits();

	std::string scanDigits();
	bool isCorrectDigit(std::string code);
	bool isCorrectCheckSum(std::string code);

private:
	StreamController streamController;

	const short digitWidth = 3;
	const short digitHeight = 3;

	std::map<std::string, std::string> mDigits;
};

ResultType DigitHandler::setInputFile(std::string inputFileName) {
	if (!streamController.createIStream(inputFileName)) {
		return INCORRECT_INPUT_FILE;
	}
	return CORRECT_INPUT_FILE;
}

ResultType DigitHandler::setOutputFile(std::string outputFileName) {
	if (!streamController.createOStream(outputFileName)) {
		return INCORRECT_OUTPUT_FILE;
	}
	return CORRECT_OUTPUT_FILE;
}

ResultType DigitHandler::processDigits() {
	while (!streamController.getIStream()->eof()) {
		std::string code = this->scanDigits();
		std::string state = "";

		if (this->isCorrectDigit(code)) {
			if (!this->isCorrectCheckSum(code)) {
				state = "ERR";
			}
		}
		else {
			state = "ILL";
		}
		*streamController.getOStream() << code << " " << state << std::endl;
	}
	return RESULT_DONE;
}

std::string DigitHandler::scanDigits() {
	std::string digits[9];
	std::string code = "";
	std::string codePiece;

	for (int i = 0; i < digitHeight; ++i) {
		std::getline(*streamController.getIStream(), codePiece);

		for (int j = 0; j < codePiece.length() / 3; ++j) {
			digits[j] += codePiece.substr(j * digitWidth, 3);
		}
	}
	std::getline(*streamController.getIStream(), codePiece);
	for (int i = 0; i < codePiece.length() / 3; ++i) {
		if (mDigits.find(digits[i]) == mDigits.end()) {
			code += "?";
		}
		else {
			code += mDigits[digits[i]];
		}
		digits[i] = "";
	}
	return code;
}

DigitHandler::DigitHandler() {
	mDigits.insert(std::pair<std::string, std::string>(" _ | ||_|", "0"));
	mDigits.insert(std::pair<std::string, std::string>("     |  |", "1"));
	mDigits.insert(std::pair<std::string, std::string>(" _  _||_ ", "2"));
	mDigits.insert(std::pair<std::string, std::string>(" _  _| _|", "3"));
	mDigits.insert(std::pair<std::string, std::string>("   |_|  |", "4"));
	mDigits.insert(std::pair<std::string, std::string>(" _ |_  _|", "5"));
	mDigits.insert(std::pair<std::string, std::string>(" _ |_ |_|", "6"));
	mDigits.insert(std::pair<std::string, std::string>(" _   |  |", "7"));
	mDigits.insert(std::pair<std::string, std::string>(" _ |_||_|", "8"));
	mDigits.insert(std::pair<std::string, std::string>(" _ |_| _|", "9"));
}

bool DigitHandler::isCorrectDigit(std::string code) {
	if (code.find('?') == std::string::npos) {
		return true;
	}
	return false;
}

bool DigitHandler::isCorrectCheckSum(std::string code) {
	int checkSum = 0;
	for (int i = 0; i < 10; ++i) {
		checkSum += (code[i] - 48) * (9 - i);
	}
	if (checkSum % 11 == 0) return true;
	else return false;
}