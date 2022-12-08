#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include "Errors.h"

class AudioFile {
public:
	std::string fileName;
	int16_t numChannels;
	int32_t sampleRate;
	int32_t byteRate;
	int16_t bitsPerSample;
	int32_t subChunk2Size;
	std::vector<int16_t> samples;

	AudioFile();
	AudioFile(std::string);
	int load(std::string);
	bool save(std::string);
	uint32_t getSampleRate() const;
	int getNumChannels() const;
	int getBitDepth() const;
	int getNumSamplesPerChannel() const;
	double getLengthInSeconds() const;
	void printSummary() const;
};
AudioFile::AudioFile() {
	numChannels = 1;
	sampleRate = 44100;
	byteRate = 16;
	samples.resize(0);
	bitsPerSample = 16;
	subChunk2Size = 0;
}
int16_t convertToIntTwoBytes(char* buf) {
	int16_t n;
	unsigned char b1 = buf[0];
	unsigned char b2 = buf[1];
	n = (b2 << 8) | b1;
	return n;
}
int32_t convertToIntFourBytes(char* buf) {
	int32_t n;
	unsigned char b1 = buf[0];
	unsigned char b2 = buf[1];
	unsigned char b3 = buf[2];
	unsigned char b4 = buf[3];
	n = (b4 << 24) | (b3 << 16) | (b2 << 8) | b1;
	return n;
}
int load(std::string fileName, AudioFile f) {
	std::ifstream in(fileName, std::ios::binary);
	try {
		if (!in.good()) throw 1;
		char buf[4] = {0};
		if (!in.read(buf, 4)) throw 16; // RIFF
		if (buf[0] != 'R' || buf[1] != 'I' || buf[2] != 'F' || buf[3] != 'F')
			throw 17;
		if (!in.read(buf, 4)) throw 3;
		if (!in.read(buf, 4)) throw 18; // WAVE
		if (buf[0] != 'W' || buf[1] != 'A' || buf[2] != 'V' || buf[3] != 'E')
			throw 19;
		//if (!in.read(buf, 4)) throw 3;
		//if (!in.read(buf, 4)) throw 4;
		if (!in.read(buf, 4)) throw 5;
		if (!in.read(buf, 4)) throw 6;
		if (!in.read(buf, 2)) throw 7;
		if (!in.read(buf, 2)) throw 8;
		f.numChannels = convertToIntTwoBytes(buf);

		if (!in.read(buf, 4)) throw 9;
		f.sampleRate = convertToIntFourBytes(buf);

		if (!in.read(buf, 4)) throw 10;
		f.byteRate = convertToIntFourBytes(buf);

		if (!in.read(buf, 2)) throw 11;
		if (!in.read(buf, 2)) throw 12;
		f.bitsPerSample = convertToIntTwoBytes(buf);

		if (!in.read(buf, 4)) throw 13;
		if (!in.read(buf, 4)) throw 14;
		f.subChunk2Size = convertToIntFourBytes(buf);

		int16_t sample;
		for (int i = 0; i < f.subChunk2Size; i++) {
			if (!in.read(buf, 2))  throw 15;
			sample = convertToIntTwoBytes(buf);
			(f.samples).push_back(sample);
		}
	}
	catch (int i) {
		Errors r;
		std::cerr << r.errors[i] << std::endl; 
		return 1;
	}
	return 0;
}