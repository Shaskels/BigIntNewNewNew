#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include "Errors.h"

class AudioFile {
public:
	std::string fileName;
	int32_t chunkSize;
	int32_t subChunk1Size;
	int16_t audioFormat;
	int16_t numChannels;
	int32_t sampleRate;
	int32_t byteRate;
	int16_t BlockAlign;
	int16_t bitsPerSample;
	int32_t subChunk2Size;
	std::vector<int16_t> samples;

	AudioFile();
	AudioFile(std::string);
	int load(std::string);
	int save(std::string);
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
int load(std::string fileName, AudioFile& f) {
	std::ifstream in(fileName, std::ios::binary);
	try {
		if (!in.good()) throw 1;
		char buf[4] = {0};
		if (!in.read(buf, 4)) throw 16; // RIFF
		if (buf[0] != 'R' || buf[1] != 'I' || buf[2] != 'F' || buf[3] != 'F')
			throw 17;

		if (!in.read(buf, 4)) throw 3;
		f.chunkSize = convertToIntFourBytes(buf);

		if (!in.read(buf, 4)) throw 18; // WAVE
		if (buf[0] != 'W' || buf[1] != 'A' || buf[2] != 'V' || buf[3] != 'E')
			throw 19;

		if (!in.read(buf, 4)) throw 5;
		if (!in.read(buf, 4)) throw 6;
		f.subChunk1Size = convertToIntFourBytes(buf);

		if (!in.read(buf, 2)) throw 7;
		f.audioFormat = convertToIntTwoBytes(buf);

		if (!in.read(buf, 2)) throw 8;
		f.numChannels = convertToIntTwoBytes(buf);

		if (!in.read(buf, 4)) throw 9;
		f.sampleRate = convertToIntFourBytes(buf);

		if (!in.read(buf, 4)) throw 10;
		f.byteRate = convertToIntFourBytes(buf);

		if (!in.read(buf, 2)) throw 11;
		f.BlockAlign = convertToIntTwoBytes(buf);
		if (!in.read(buf, 2)) throw 12;
		f.bitsPerSample = convertToIntTwoBytes(buf);

		if (!in.read(buf, 4)) throw 13;
		if (!in.read(buf, 4)) throw 14;
		f.subChunk2Size = convertToIntFourBytes(buf);

		int16_t sample;
		for (int i = 0; i < f.chunkSize / 2 - 18; i++) {
			if (!in.read(buf, 2))  throw 15;
			sample = convertToIntTwoBytes(buf);
			(f.samples).push_back(sample);
		}
		in.close();
	}
	catch (int i) {
		Errors r;
		in.close();
		std::cerr << r.errors[i] << std::endl; 
		return 1;
	}
	return 0;
}
void addBack(std::vector<uint8_t>& buf, int n) {
	for (int i = 0; i < n; i++) {
		buf.push_back(0);
	}
}
void convert32ToChar(std::vector<uint8_t>& buf, int32_t x, int startIndex) {
	addBack(buf, 4);
	buf[startIndex + 3] = (x >> 24) & 0xFF;
	buf[startIndex + 2] = (x >> 16) & 0xFF;
	buf[startIndex + 1] = (x >> 8) & 0xFF;
	buf[startIndex + 0] = x & 0xFF;
}
void convert16ToChar(std::vector<uint8_t>& buf, int16_t x, int startIndex) {
	addBack(buf, 2);
	buf[startIndex + 1] = (x >> 8) & 0xFF;
	buf[startIndex + 0] = x & 0xFF;
}
void convertStringToChar(std::vector<uint8_t>& buf, std::string x, int startIndex) {
	addBack(buf, 4);
	for (int i = 0; i < 4; i++) {
		buf[startIndex + i] = (uint8_t)x[i];
	}
}
void writeToFile(std::vector<uint8_t>& buf, std::string fileName) {
	std::ofstream out(fileName, std::ios::binary);
	if (!out) throw 20;
	for (int i = 0; i < buf.size(); i++) {
		char x = (char)buf[i];
		out.write(&x, sizeof(char));
	}
	out.close();
}
int save(std::string fileName, AudioFile f) {
	std::vector<uint8_t> buf;
	convertStringToChar(buf, "RIFF", 0);
	convert32ToChar(buf, f.chunkSize, 4);
	convertStringToChar(buf, "WAVE", 8);
	convertStringToChar(buf, "fmt ", 12);
	convert32ToChar(buf, f.subChunk1Size, 16);
	convert16ToChar(buf, f.audioFormat, 20);
	convert16ToChar(buf, f.numChannels, 22);
	convert32ToChar(buf, f.sampleRate, 24);
	convert32ToChar(buf, f.byteRate, 28);
	convert16ToChar(buf, f.BlockAlign, 32);
	convert32ToChar(buf, f.bitsPerSample, 34);
	convert32ToChar(buf, f.subChunk2Size, 38);
	for (int i = 0; i < f.chunkSize / 2 - 18; i++) {
		convert16ToChar(buf, f.samples[i], 42 + i * 2);
	}
	writeToFile(buf, "out.wav");
	return 0;
}