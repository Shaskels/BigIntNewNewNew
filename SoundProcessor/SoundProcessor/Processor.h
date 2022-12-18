#pragma once
#include "Ñonverter.h"
#include "ConfigurationFile.h"
#include "AudioFile.h"
#include <vector>
namespace pr {
	int const START = 0;
	int const END = 1;
	class Processor {
	public:
		void Mute(std::vector<af::AudioFile>&, configs::ConfigurationFile&);
		void Mix(std::vector<af::AudioFile>&, configs::ConfigurationFile&);
		void Revers(std::vector<af::AudioFile>&, configs::ConfigurationFile&);
	};
}
