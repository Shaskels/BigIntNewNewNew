#include <vector>
#include <iostream>
#include "Errors.h"
#include "�onverter.h"

int CheckErrors(std::vector<int16_t>& samples, int start, int end) {
	err::Errors r;
	if (start > end) {
		std::cerr << r.IncorArguments;
		return ERROR_VALUE;
	}
	if (start > samples.size() || end > samples.size() || end < 0 || start < 0) {
		std::cerr << r.IncorArguments;
		return ERROR_VALUE;
	}
	return SUCCESS;
}
int con::MuteTheInterval::ChangeSamples(std::vector<int16_t>& samples, int start, int end) {
	int startIndex = start * SAMPLE_RATE;
	int endIndex = end * SAMPLE_RATE;
	if (CheckErrors(samples, startIndex, endIndex) == 0)
		return ERROR_VALUE;
	for (int i = startIndex; i <= endIndex; i++) {
		samples[i] = 0;
	}
	return SUCCESS;
}
int con::Mixer::ChangeSamples(std::vector<int16_t>& samples1, int start1, int end1) {
	int startIndex = start2 * SAMPLE_RATE;
	int min = std::min(samples1.size(), samples2.size());
	for (int i = startIndex; i <= std::min(samples1.size(), samples2.size()) - 1; i++) {
		samples1[i] = (samples1[i] + samples2[i]) / 2;
	}
	return SUCCESS;
}
int con::Revers::ChangeSamples(std::vector<int16_t>& samples, int start, int end) {
	int startIndex = start * SAMPLE_RATE;
	int endIndex = end * SAMPLE_RATE;
	if (CheckErrors(samples, startIndex, endIndex) == 0)
		return ERROR_VALUE;
	int16_t tmp;
	for (int i = startIndex; i < (endIndex + startIndex) / 2; i++) {
		tmp = samples[i];
		samples[i] = samples[endIndex + startIndex - i];
		samples[endIndex + startIndex - i] = tmp;
	}
	return SUCCESS;
}
con::Converter* con::MuteTheIntervalFactory::MakeConverter() {
	return new MuteTheInterval();
}
con::Converter* con::MixerFactory::MakeConverter() {
	return new Mixer();
}
con::Converter* con::ReversFactory::MakeConverter() {
	return new Revers();
}
std::vector<std::string> con::MuteTheIntervalFactory::Reference() {
	std::vector<std::string> s = {
		"The mute converter drowns out the interval.\n",
		"There is silence in the output stream at the specified time interval, the rest is like in the input stream.",
		"To use the converter, you need to enter its name, then two numbers : the beginning of the interval, the end of the interval\n"
	};
	return s;
}
std::vector<std::string> con::MixerFactory::Reference() {
	std::vector<std::string> s = {
		"The mix converter combines two tracks.\n",
		"Each sample is the average of the corresponding samples of the input streams.",
		"The length of the output stream corresponds to the length of the main input stream.",
		"If the additional stream is longer than the main one, then part of it is cut off, and if it is shorter, then the output stream outside it is equal to the main input stream.\n",
		"To use the converter, you need to specify its name and one number - the start time of the change"
	};
	return s;
}
std::vector<std::string> con::ReversFactory::Reference() {
	std::vector<std::string> s = {
		"The converter flips the track.\n",
		"The first sample becomes the last, the second - the penultimate, and so on..",
		"To use the converter, you need to enter its name and two numbers: the beginning of the change, the end of the change.\n"
	};
	return s;
}