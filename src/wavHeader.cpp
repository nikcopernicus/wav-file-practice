#include "wavHeader.h"
#include "soundEffectsException.h"

template<>
void parseBytes<std::string>(std::string& target,const std::vector<uint8_t>& readedFile, size_t& begin, const size_t next) {
	target = std::string(readedFile.begin() + begin, readedFile.begin() + begin + next);
	begin += next;
	return;
}
template<>
void parseBytes<uint32_t>(uint32_t& target, const std::vector<uint8_t>& readedFile, size_t& begin, const size_t next) {
	std::memcpy(&target, &readedFile[begin], sizeof(uint32_t));
	begin += next;
	return;
}
template<>
void parseBytes<uint16_t>(uint16_t& target, const std::vector<uint8_t>& readedFile, size_t& begin, const size_t next) {
	std::memcpy(&target, &readedFile[begin], sizeof(uint16_t));
	begin += next;
	return;
}

wavHeader::wavHeader(const std::string& filepath) {
	const std::vector<uint8_t> data = fileReader::read(filepath, 0);
	size_t count = 0;
	fileSize = (uint32_t)data.size();
	parseBytes(chunkID, data, count, 4);
	parseBytes(chunkSize, data, count, 4);
	parseBytes(format, data, count, 4);
	parseBytes(subchunk1ID, data, count, 4);
	parseBytes(subchunk1Size, data, count, 4);
	parseBytes(audioFormat, data, count, 2);
	parseBytes(numChannels, data, count, 2);
	parseBytes(sampleRate, data, count, 4);
	parseBytes(byteRate, data, count, 4);
	parseBytes(blockAlign, data, count, 2);
	parseBytes(bitsPerSample, data, count, 2);	
	if (audioFormat == 1) {
		while (true) {
			if (count >= data.size()) {
				throw fileException("ERROR: no data chunk in your file!");
				break;
			}
			std::string currentChunkID;
			parseBytes(currentChunkID, data, count, 4);
			if (currentChunkID == "data") {
				subchunk2ID = currentChunkID;
				parseBytes(subchunk2Size, data, count, 4);
				break;
			}
			else {
				uint32_t currentChunkSize;
				parseBytes(currentChunkSize, data, count, 4);
				count += currentChunkSize;
			}
		}
		duration = (double)subchunk2Size / ((double)bitsPerSample / 8.0) / (double)numChannels / (double)sampleRate;
	}
	else {
		throw notImplementedException("ERROR: processing non-PCM files are not implemented yet!");
	}
	if (bitsPerSample == 8) {
		sampleType = sampleTypes::_int8_t;
	}
	else if (bitsPerSample == 16) {
		sampleType = sampleTypes::_int16_t;
	}
	else if (bitsPerSample == 24) {
		sampleType = sampleTypes::_float_t;
	}
	else if (bitsPerSample == 32) {
		sampleType = sampleTypes::_int32_t;
	}
	else {
		sampleType = sampleTypes::_unknown;
	}
}

wavHeader::wavHeader(const std::vector<uint8_t>& data){
	size_t count = 0;
	fileSize = (uint32_t)data.size();
	parseBytes(chunkID, data, count, 4);
	parseBytes(chunkSize, data, count, 4);
	parseBytes(format, data, count, 4);
	parseBytes(subchunk1ID, data, count, 4);
	parseBytes(subchunk1Size, data, count, 4);
	parseBytes(audioFormat, data, count, 2);
	parseBytes(numChannels, data, count, 2);
	parseBytes(sampleRate, data, count, 4);
	parseBytes(byteRate, data, count, 4);
	parseBytes(blockAlign, data, count, 2);
	parseBytes(bitsPerSample, data, count, 2);
	if (audioFormat == 1) {
		while (true) {
			if (count >= data.size()) {
				throw fileException("ERROR: no data chunk in your file!");
				break;
			}
			std::string currentChunkID;
			parseBytes(currentChunkID, data, count, 4);
			if (currentChunkID == "data") {
				subchunk2ID = currentChunkID;
				parseBytes(subchunk2Size, data, count, 4);
				break;
			}
			else {
				uint32_t currentChunkSize;
				parseBytes(currentChunkSize, data, count, 4);
				count += currentChunkSize;
			}			
		}
		duration = (double)subchunk2Size / ((double)bitsPerSample / 8.0) / (double)numChannels / (double)sampleRate;
	}
	else {
		throw notImplementedException("ERROR: processing non-PCM files are not implemented yet!");
	}
	if (bitsPerSample == 8) {
		sampleType = sampleTypes::_int8_t;
	}
	else if (bitsPerSample == 16) {
		sampleType = sampleTypes::_int16_t;
	}
	else if (bitsPerSample == 24) {
		sampleType = sampleTypes::_float_t;
	}
	else if (bitsPerSample == 32) {
		sampleType = sampleTypes::_int32_t;
	}
	else {
		sampleType = sampleTypes::_unknown;
	}

}

bool wavHeader::validate()
{
	if ((chunkID != "RIFF") || (format != "WAVE") || (subchunk1ID != "fmt ") || (subchunk2ID != "data")) {
		return false;
	}
	if (chunkSize + 8 != fileSize) {
		return false;
	}
	if (audioFormat == 1) {
		if (subchunk1Size != 16) {
			return false;
		}
	}
	return true;
}

void wavHeader::printAllData() {
	std::cout << "chunkID: " << chunkID << std::endl;
	std::cout << "chunkSize: " << chunkSize << std::endl;
	std::cout << "format: " << format << std::endl;
	std::cout << "subchunk1ID: " << subchunk1ID << std::endl;
	std::cout << "subchunk1Size: " << subchunk1Size << std::endl;
	std::cout << "audioFormat: " << audioFormat << std::endl;
	std::cout << "numChannels: " << numChannels << std::endl;
	std::cout << "sampleRate: " << sampleRate << std::endl;
	std::cout << "byteRate: " << byteRate << std::endl;
	std::cout << "blockAlign: " << blockAlign << std::endl;
	std::cout << "bitsPerSample: " << bitsPerSample << std::endl;
	std::cout << "sampleType: " << sampleType << std::endl;
	if (audioFormat == 1) {
		std::cout << "subchunk2ID: " << subchunk2ID << std::endl;
		std::cout << "subchunk2Size: " << subchunk2Size << std::endl;
	}
	else {
		throw notImplementedException("ERROR: processing non-PCM files are not implemented yet!");
	}	
	std::cout << "duration: " << duration << std::endl;
	std::cout << "fileSize: " << fileSize << std::endl;
	return;
}

uint16_t wavHeader::getNumChannels() {
	return numChannels;
}

uint32_t wavHeader::getSampleRate() {
	return sampleRate;
}

uint16_t wavHeader::getBitsPerSample() {
	return bitsPerSample;
}

std::string wavHeader::getSampleType() {
	return sampleType;
}

uint32_t wavHeader::getByteRate() {
	return byteRate;
}

double wavHeader::getDuration() {
	return duration;
}
