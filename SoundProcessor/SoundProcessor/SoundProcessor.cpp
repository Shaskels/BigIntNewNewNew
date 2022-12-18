
#include <iostream>
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
        af::AudioFile file;
        if(file.load(in.getFileName(i)) == 1)
            return 0;
        files.push_back(file);
    }
    err::Errors r;
    pr::Processor proc;
    try {
        for (int i = 0; i < config.Converters.size(); i++) {
            if (config.Converters[i] == MUTE_CONVERTER) {
                if (config.Times.size() < MIN_SIZE_MUTE) throw r.CommandLineArgErr;
                proc.Mute(files,config);
            }
            else if (config.Converters[i] == MIX_CONVERTER) {
                if (config.Times.size() < MIN_SIZE_MIX) throw r.CommandLineArgErr;
                proc.Mix(files, config);
            }
            else if (config.Converters[i] == REVERS_CONVERTER) {
                if (config.Times.size() < MIN_SIZE_MUTE) throw r.CommandLineArgErr;
                proc.Revers(files, config);
            }
            else {
                throw r.CommandLineErr;
                return ERROR_VALUE;
            }
        }
        if (files[0].save(in.getFileName(0)) == 1)
            throw r.SaveFileErr;
    }
    catch(std::string i) {
        std::cerr << i << std::endl;
        return 0;
    }
}
