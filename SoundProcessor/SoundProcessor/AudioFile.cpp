#include "AudioFile.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "Errors.h"

af::AudioFile::AudioFile() {
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
int af::AudioFile::load(std::string fileName) {
	std::ifstream in(fileName, std::ios::binary);
	try {
		if (!in.good()) throw 1;
		char buf[4] = { 0 };
		if (!in.read(buf, 4)) throw 16; // RIFF
		if (buf[0] != 'R' || buf[1] != 'I' || buf[2] != 'F' || buf[3] != 'F')
			throw 17;

		if (!in.read(buf, 4)) throw 3;
		chunkSize = convertToIntFourBytes(buf);

		if (!in.read(buf, 4)) throw 18; // WAVE
		if (buf[0] != 'W' || buf[1] != 'A' || buf[2] != 'V' || buf[3] != 'E')
			throw 19;

		if (!in.read(buf, 4)) throw 5;
		if (!in.read(buf, 4)) throw 6;
		subChunk1Size = convertToIntFourBytes(buf);

		if (!in.read(buf, 2)) throw 7;
		audioFormat = convertToIntTwoBytes(buf);

		if (!in.read(buf, 2)) throw 8;
		numChannels = convertToIntTwoBytes(buf);

		if (!in.read(buf, 4)) throw 9;
		sampleRate = convertToIntFourBytes(buf);

		if (!in.read(buf, 4)) throw 10;
		byteRate = convertToIntFourBytes(buf);

		if (!in.read(buf, 2)) throw 11;
		BlockAlign = convertToIntTwoBytes(buf);
		if (!in.read(buf, 2)) throw 12;
		bitsPerSample = convertToIntTwoBytes(buf);

		int16_t lst;
		if (!in.read(buf, 4)) throw 13;
		while (buf[0] != 'd' && buf[1] != 'a' && buf[2] != 't' && buf[3] != 'a') {
			if (!in.read(buf, 4)) throw 14;
			subChunkList = convertToIntFourBytes(buf);
			for (int i = 0; i < subChunkList / 2; i++) {
				if (!in.read(buf, 2)) throw 13;
				lst = convertToIntTwoBytes(buf);
				list.push_back(lst);
			}
			if (!in.read(buf, 4)) throw 13;
		}
		if (!in.read(buf, 4)) throw 14;
		subChunk2Size = convertToIntFourBytes(buf);

		int16_t sample;
		for (int i = 0; i < subChunk2Size / 2; i++) {
			if (!in.read(buf, 2))  throw 15;
			sample = convertToIntTwoBytes(buf);
			(samples).push_back(sample);
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
int af::AudioFile::save(std::string fileName) {
	try {
		std::vector<uint8_t> buf;
		convertStringToChar(buf, "RIFF", 0);
		if (chunkSize == 0) throw 3;
		convert32ToChar(buf, chunkSize, 4);
		convertStringToChar(buf, "WAVE", 8);
		convertStringToChar(buf, "fmt ", 12);
		if (subChunk1Size == 0) throw 6;
		convert32ToChar(buf, subChunk1Size, 16);
		if (audioFormat == 0) throw 7;
		convert16ToChar(buf, audioFormat, 20);
		if (numChannels == 0) throw 8;
		convert16ToChar(buf, numChannels, 22);
		if (sampleRate == 0) throw 9;
		convert32ToChar(buf, sampleRate, 24);
		if (byteRate == 0) throw 10;
		convert32ToChar(buf, byteRate, 28);
		if (BlockAlign == 0) throw 11;
		convert16ToChar(buf, BlockAlign, 32);
		if (bitsPerSample == 0) throw 12;
		convert16ToChar(buf, bitsPerSample, 34);
		convertStringToChar(buf, "LIST", 36);
		convert32ToChar(buf, subChunkList, 40);
		for (int i = 0; i < subChunkList / 2; i++) {
			convert16ToChar(buf, list[i], 44 + i * 2);
		}
		convertStringToChar(buf, "data", 44 + subChunkList);
		if (subChunk2Size == 0) throw 14;
		convert32ToChar(buf, subChunk2Size, 48 + subChunkList);
		for (int i = 0; i < subChunk2Size / 2; i++) {
			convert16ToChar(buf, samples[i], 52 + subChunkList + i * 2);
		}
		writeToFile(buf, "out.wav");
	}
	catch (int i) {
		Errors r;
		std::cerr << r.errors[i] << std::endl;
		return 1;
	}
	return 0;
}

std::vector<int16_t> af::AudioFile::getSamples() {
	return samples;
}

void af::AudioFile::writeNewSamples(std::vector<int16_t> samp) {
	samples = samp;
}