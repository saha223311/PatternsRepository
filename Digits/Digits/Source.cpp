#include "DigitHandler.h"

int main(int argc, char *argv[]) {
	DigitHandler dHandler;

	for (int count = 1; count < argc; count += 2) {
		if (std::string(argv[count]) == std::string("-i")) {
			dHandler.setInputFile(argv[count + 1]);
		}
		if (std::string(argv[count]) == std::string("-o")) {
			dHandler.setOutputFile(argv[count + 1]);
		}
	}
	dHandler.processDigits();

	system("pause");
}
