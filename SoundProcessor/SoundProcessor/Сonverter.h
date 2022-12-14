#pragma once
#include <vector>
#include "Errors.h"
#define SAMPLE_RATE 44100

class Converter {
public:
	int start2 = 0;
	std::vector<int16_t> samples2;
	virtual int ChangeSamples(std::vector<int16_t>&, int, int) = 0;
};
int CheckErrors(std::vector<int16_t>& samples, int start, int end) {
	Errors r;
	if (start > end) {
		std::cerr << r.errors[20];
		return ERROR_VALUE;
	}
	if (start > samples.size() || end > samples.size() || end < 0 || start < 0) {
		std::cerr << r.errors[20];
		return ERROR_VALUE;
	}
	return SUCCESS;
}
class MuteTheInterval: public Converter {
	int ChangeSamples(std::vector<int16_t>& samples, int start, int end) {
		int startIndex = start * SAMPLE_RATE;
		int endIndex = end * SAMPLE_RATE;
		if (CheckErrors(samples, startIndex, endIndex) == 0)
			return ERROR_VALUE;
		for (int i = startIndex; i <= endIndex; i++) {
			samples[i] = 0;
		}
		return SUCCESS;
	}
};
class Mixer : public Converter {
	int ChangeSamples(std::vector<int16_t>& samples1, int start1, int end1) {
		int startIndex = start2 * SAMPLE_RATE;
		int min = std::min(samples1.size(), samples2.size());
		for (int i = startIndex; i <= std::min(samples1.size(),samples2.size()) - 1; i++) {
			samples1[i] = (samples1[i] + samples2[i]) / 2;
		}
		return SUCCESS;
	}
};
class Revers : public Converter {
	int ChangeSamples(std::vector<int16_t>& samples, int start, int end) {
		int startIndex = start * SAMPLE_RATE;
		int endIndex = end * SAMPLE_RATE;
		if (CheckErrors(samples, startIndex, endIndex) == 0)
			return ERROR_VALUE;
		int16_t tmp;
		for (int i = startIndex; i < (endIndex + startIndex)/ 2; i++) {
			tmp = samples[i];
			samples[i] = samples[endIndex + startIndex - i];
			samples[endIndex + startIndex - i] = tmp;
		}
		return SUCCESS;
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