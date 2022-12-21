
#include <iostream>
#include <fstream>
#include "Input.h"
#include "AudioFile.h"
#include "Сonverter.h"
#include "ConfigurationFile.h"
#include "Processor.h"
int const MIN_SIZE_MUTE = 2;
int const MIN_SIZE_MIX = 1;
std::string MUTE_CONVERTER = "mute";
std::string MIX_CONVERTER = "mix";
std::string REVERS_CONVERTER = "revers";

int main(int argc, char* argv[])
{
	np::Input in;
	in.GetProgramOptions(argc, argv);
	std::vector<af::AudioFile> files;
	configs::ConfigurationFile config;
	config.getConfigs(in.getFileName(0), config);

	for (int i = 2; i < in.getFilesSize(); i++) {
		std::ifstream f(in.getFileName(i), std::ios_base::binary);
		af::AudioFile file = af::AudioFile(f);
		if (file.load(in.getFileName(i)) == 1)
			return 0;
		files.push_back(file);
	}
	err::Errors r;
	pr::Processor proc;
	try {
		if (files[0].save(in.getFileName(1)) == 1)
			throw r.SaveFileErr;
		for (int j = 0; j < (files[0].getSubChunk2Size() / con::SAMPLE_RATE); j++) {
			configs::ConfigurationFile tmpConfig = config;
			for (int i = 0; i < config.Converters.size(); i++) {
				if (config.Converters[i] == MUTE_CONVERTER) {
					if (config.Times.size() < MIN_SIZE_MUTE) throw r.CommandLineArgErr;
					proc.Mute(files, tmpConfig, j);
				}
				else if (config.Converters[i] == MIX_CONVERTER) {
					if (config.Times.size() < MIN_SIZE_MIX) throw r.CommandLineArgErr;
					proc.Mix(files, tmpConfig, j);
				}
				else if (config.Converters[i] == REVERS_CONVERTER) {
					if (config.Times.size() < MIN_SIZE_MUTE) throw r.CommandLineArgErr;
					proc.Revers(files, tmpConfig, j);
				}
				else {
					throw r.CommandLineErr;
					return ERROR_VALUE;
				}
			}
			files[0].writeToFile(in.getFileName(1));
			for(int i = 0; i < files.size(); i++)
				files[i].readSamples();
		}
	}
	catch (std::string i) {
		std::cerr << i << std::endl;
		return 0;
	}
}