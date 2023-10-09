#include "modes.h"
#include "soundEffects.h"
#include "wavHeader.h"

void runModeTest(const paramsTest& cfg) {
	std::cout << "mode = \'testmode\'"<< std::endl;
	std::ifstream fin(cfg.fname);
	if (fin.good()) {
		std::cout << "fname = \'" << cfg.fname << "\'" << std::endl;
	}
	else {
		std::cout << "File does not exists" << std::endl;
	}
	fin.close();
	
}

void runModeHex(const paramsHex& cfg) {
	soundEffects soundEffects;

	soundEffects.read(cfg.fname,cfg.length);
	soundEffects.showFirstHex();

}

void runModeReadHeader(const paramsReadHeader& cfg) {
	wavHeader wavHeader(cfg.fname);
	if (wavHeader.validate() == false) {
		std::cout << "Header is not OK! Probably it's not WAV file!" << std::endl;
		return;
	}
	else {
		std::cout << "Header is OK!" << std::endl;
	}
	if (cfg.needToPrint == true) {
		wavHeader.printAllData();
	}
	return;
}

void runModeHelp() {
	std::cout << "USAGE:" << std::endl;
	std::cout << "simple-dsp.exe MODE PARAM1 PARAM2 ..." << std::endl << std::endl;
	std::cout << "MODE = help" << std::endl;
	std::cout << "\tWill print this help" << std::endl << std::endl;
	std::cout << "MODE = testmode" << std::endl;
	std::cout << "\tPARAM1 = path to a file" << std::endl;
	std::cout << "\t\tWill test if the file is exists" << std::endl;
	std::cout << "MODE = printhex" << std::endl;
	std::cout << "\tPARAM1 = path to a file" << std::endl;
	std::cout << "\tPARAM2 = size of reading" << std::endl;
	std::cout << "\t\tWill print first 256 bytes as hex" << std::endl;
	std::cout << "MODE = readheader" << std::endl;
	std::cout << "\tPARAM1 = path to a file" << std::endl;
	std::cout << "\tPARAM2 = 0 or 1," << std::endl;
	std::cout << "\t0 - to validate header, 1 - to validate and print header" << std::endl;
	std::cout << "\t\tWill read header, validate and print it if you want" << std::endl;
}
