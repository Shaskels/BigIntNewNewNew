#pragma once
#include <vector>

#define byteRate 44100

class Converter {
public:
	virtual int ChangeSamples(std::vector<int16_t>&, int, int) = 0;
};

class MuteTheInterval: public Converter {
	int ChangeSamples(std::vector<int16_t>& samples, int start, int end) {
		int startIndex = start * byteRate;
		int endIndex = end * byteRate;
		for (int i = startIndex; i < endIndex; i++) {
			samples[i] = 0;
		}
		return 0;
	}
};
class Mixer : public Converter {
	int ChangeSamples(std::vector<int16_t>& samples, int start, int end) {
		return 0;
	}
};
class Replace : public Converter {
	int ChangeSamples(std::vector<int16_t>& samples, int start, int end) {
		return 0;
	}
};
class ConverterFactory {
public:
	virtual Converter* MakeConverter() = 0;
};
class MuteTheIntervalFactory : public ConverterFactory {
public:
	Converter* MakeConverter() {
		return new MuteTheInterval();
	}
};
class MixerFactory : public ConverterFactory {
	Converter* MakeConverter() {
		return new Mixer();
	}
};
class ReplaceFactory : public ConverterFactory{
	Converter* MakeConverter() {
		return new Replace();
	}
};