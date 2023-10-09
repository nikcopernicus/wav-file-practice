#include <iostream>
#include <string>
#include "fileReader.h"

template <typename T>
void parseBytes(T& target, const std::vector<uint8_t>& readedFile, size_t& begin, const size_t next);
namespace sampleTypes {
	static const std::string _int8_t = "int8_t";
	static const std::string _int16_t = "int16_t";
	static const std::string _int32_t = "int32_t";
	static const std::string _float_t = "float";
	static const std::string _unknown = "unknown";
}

class wavHeader {
private: std::string chunkID;
private: uint32_t chunkSize;
private: std::string format;
private: std::string subchunk1ID;
private: uint32_t subchunk1Size;
private: uint16_t audioFormat;
private: uint16_t numChannels;
private: uint32_t sampleRate;
private: uint32_t byteRate;
private: uint16_t blockAlign;
private: uint16_t bitsPerSample;
private: std::string subchunk2ID;
private: uint32_t subchunk2Size;
private: uint32_t fileSize;
private: double duration;
private: std::string sampleType;

public: wavHeader(const std::string& filepath);
public: wavHeader(const std::vector <uint8_t>& data);
public: bool validate();
public: void printAllData();

public: uint16_t getNumChannels();
public: uint32_t getSampleRate();
public: uint16_t getBitsPerSample();
public: std::string getSampleType();
public: uint32_t getByteRate();
public: double getDuration();

};
