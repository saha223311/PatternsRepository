#pragma once

#include <iostream>
#include <fstream>
#include <map>
#include <string>

enum ResultType { RESULT_DONE, WRONG_DIGIT_NUMBER, WRONG_COUNT_OF_NUMBER, CORRECT_INPUT_FILE, CORRECT_OUTPUT_FILE, INCORRECT_INPUT_FILE, INCORRECT_OUTPUT_FILE };

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
private:
	StreamController streamController;

	const short digitWidth = 3;
	const short digitHeight = 3;
	std::string digits[10];

	std::map<std::string, short> mDigits;
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
	std::istream* istream = streamController.getIStream();
	std::ostream* ostream = streamController.getOStream();

	std::string tmpRow;
	bool isFullRow = true;
	while (isFullRow) {
		for (int i = 0; i < digitHeight; ++i) {
			std::getline(*istream, tmpRow);
			
			if (tmpRow.length() / 3 > 10) {
				return WRONG_COUNT_OF_NUMBER;
			}
			else if (tmpRow.length() / 3 != 10) {
				isFullRow = false;
			}

			for (int j = 0; j < tmpRow.length() / 3; ++j) {
				digits[j] += tmpRow.substr(j * digitWidth, 3);
			}
		}
		std::getline(*istream, tmpRow);
		for (int i = 0; i < tmpRow.length() / 3; ++i) {
			if (mDigits.find(digits[i]) == mDigits.end()) {
				return WRONG_DIGIT_NUMBER;
			}
			*ostream << mDigits[digits[i]];
			digits[i] = "";
		}
		*ostream << std::endl;
	}

	return RESULT_DONE;
}

DigitHandler::DigitHandler() {
	mDigits.insert(std::pair<std::string, short>(" _ | ||_|", 0));
	mDigits.insert(std::pair<std::string, short>("     |  |", 1));
	mDigits.insert(std::pair<std::string, short>(" _  _||_ ", 2));
	mDigits.insert(std::pair<std::string, short>(" _  _| _|", 3));
	mDigits.insert(std::pair<std::string, short>("   |_|  |", 4));
	mDigits.insert(std::pair<std::string, short>(" _ |_  _|", 5));
	mDigits.insert(std::pair<std::string, short>(" _ |_ |_|", 6));
	mDigits.insert(std::pair<std::string, short>(" _   |  |", 7));
	mDigits.insert(std::pair<std::string, short>(" _ |_||_|", 8));
	mDigits.insert(std::pair<std::string, short>(" _ |_| _|", 9));
}