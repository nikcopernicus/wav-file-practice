#include "fileReader.h"
#include "soundEffectsException.h"
#include <string>
#include <vector>
#include <fstream>
#include <exception>

std::vector<uint8_t> fileReader::read(const std::string& filepath, size_t length) {

	std::ifstream fin(filepath, std::ifstream::binary);

	if (!fin.good()) {
		throw fileException("ERROR:Can't reach file!");
	}
	std::vector<uint8_t> result;

	fin.seekg(0, std::ios::end);
	const size_t size = fin.tellg();
	fin.seekg(0, std::ios::beg);

	if (length == 0) {
		length = size;
	}

	if (length > size) {
		throw argumentsException("ERROR:Input length bigger than file size!");
	}

	result.resize(length, 0x0);
	try {
		fin.read((char*)result.data(), result.size());
	}
	catch (std::exception e) {
		throw fileException("ERROR:Can't read file!");
	}

	return result;

}
