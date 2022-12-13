#pragma once
#include <vector>

#define sampleRate 44100

class Converter {
public:
	int start2 = 0;
	std::vector<int16_t> samples2;
	virtual int ChangeSamples(std::vector<int16_t>&, int, int) = 0;
};

class MuteTheInterval: public Converter {
	int ChangeSamples(std::vector<int16_t>& samples, int start, int end) {
		int startIndex = start * sampleRate;
		int endIndex = end * sampleRate;
		for (int i = startIndex; i <= endIndex; i++) {
			samples[i] = 0;
		}
		return 0;
	}
};
class Mixer : public Converter {

	/*Mixer(int s, std::vector<int16_t> samp) {
		start2 = s;
		samples2 = samp;
	}*/
	int ChangeSamples(std::vector<int16_t>& samples1, int start1, int end1) {
		int startIndex = start1 * sampleRate;
		int endIndex = end1 * sampleRate;
		int changeStart = start2 * sampleRate;
		for (int i = startIndex; i <= endIndex; i++) {
			samples1[i] = (samples1[i] + samples2[changeStart + i - startIndex]) / 2;
		}
		return 0;
	}
};
class Revers : public Converter {
	int ChangeSamples(std::vector<int16_t>& samples, int start, int end) {
		int startIndex = start * sampleRate;
		int endIndex = end * sampleRate;
		int16_t tmp;
		for (int i = startIndex; i < (endIndex + startIndex)/ 2; i++) {
			tmp = samples[i];
			samples[i] = samples[endIndex + startIndex - i];
			samples[endIndex + startIndex - i] = tmp;
		}
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
public:
	Converter* MakeConverter() {
		return new Mixer();
	}
};
class ReversFactory : public ConverterFactory{
public:
	Converter* MakeConverter() {
		return new Revers();
	}
};