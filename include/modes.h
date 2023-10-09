#ifndef MODES_H
#define MODES_H

#include <iostream>
#include <fstream>

namespace modes {
	static const std::string help = "help";
	static const std::string test = "testmode";
	static const std::string hex = "printhex";
	static const std::string readheader = "readheader";
}

struct paramsTest {
	std::string fname;
};

void runModeTest(const paramsTest& cfg);

struct paramsHex {
	std::string fname;
	size_t length;
};

void runModeHex(const paramsHex& cfg);

struct paramsReadHeader {
	std::string fname;
	bool needToPrint;
};

void runModeReadHeader(const paramsReadHeader& cfg);

void runModeHelp();

#endif
