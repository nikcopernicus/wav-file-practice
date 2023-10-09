#include "soundEffects.h"
#include "modes.h"
#include "fileReader.h"
#include "soundEffectsException.h"
#include <iostream>


void soundEffects::read(const std::string& filepath,const size_t size) {
	parsedSound = fileReader::read(filepath,size);
}

void soundEffects::showFirstNormal(const size_t length, const size_t width) {
	for (size_t i = 0; i < length; i++) {
		for (size_t j = 0; j < width; j++) {
			if (i * length + j >= parsedSound.size()) {
				return;
			}
			std::cout << (int)parsedSound[i * length + j] << " ";
		}
		std::cout << std::endl;
	}
}


void soundEffects::showFirstHex(const size_t length,const size_t width) {
	for (size_t i = 0; i < length; i++) {
		for (size_t j = 0; j < width; j++) {
			if (i * length + j >= parsedSound.size()) {
				return;
			}
			std::cout << std::hex << (int)parsedSound[i * length + j] << " ";
		}
		std::cout << std::endl;
	}
}
