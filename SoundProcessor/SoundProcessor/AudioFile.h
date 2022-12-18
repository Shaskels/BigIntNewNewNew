#pragma once
#include <vector>
#include <string>
namespace af {
	const int TwoBytes = 2;
	const int FourBytes = 4;
	enum Bytes {
		FirstByte,
		SecondByte,
		ThirdByte,
		FourthByte
	};
	class AudioFile {
		std::string fileName;
		uint32_t chunkSize;
		uint32_t subChunk1Size;
		uint16_t audioFormat;
		uint16_t numChannels;
		uint32_t sampleRate;
		uint32_t byteRate;
		uint16_t BlockAlign;
		uint16_t bitsPerSample;
		uint16_t subChunkList;
		uint32_t subChunk2Size;
		std::vector<int16_t> list;
		std::vector<int16_t> samples;
	public:
		AudioFile();
		int load(std::string);
		int save(std::string);
		std::vector<int16_t> getSamples();
		void writeNewSamples(std::vector<int16_t>);
	};
}