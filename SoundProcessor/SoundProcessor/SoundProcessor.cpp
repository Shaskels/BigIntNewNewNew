
#include <iostream>
#include "Input.h"
#include "AudioFile.h"
#include "Сonverter.h"
#include "ConfigurationFile.h"
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
    try {
        for (int i = 0; i < config.Converters.size(); i++) {
            if (config.Converters[i] == MUTE_CONVERTER) {
                con::MuteTheIntervalFactory factory;
                con::Converter* con = factory.MakeConverter();
                if (config.Times.size() < 2) throw 22;
                std::vector<int16_t> samples = files[0].getSamples();
                (*con).ChangeSamples(samples, config.Times[0], config.Times[1]);
                files[0].writeNewSamples(samples);
                auto begin = config.Times.cbegin();
                config.Times.erase(begin, begin + 2);
            }
            else if (config.Converters[i] == MIX_CONVERTER) {
                con::MixerFactory factory;
                con::Converter* con = factory.MakeConverter();
                if (config.Times.size() < 1) throw 22;
                con->start2 = config.Times[0];
                con->samples2 = files[config.Links[0] - 1].getSamples();
                std::vector<int16_t> samples = files[0].getSamples();
                (*con).ChangeSamples(samples, 0, 0);
                files[0].writeNewSamples(samples);
                auto begin = config.Times.cbegin();
                config.Times.erase(begin, begin + 1);
                begin = config.Links.cbegin();
                config.Links.erase(begin, begin + 1);
            }
            else if (config.Converters[i] == REVERS_CONVERTER) {
                con::ReversFactory factory;
                con::Converter* con = factory.MakeConverter();
                if (config.Times.size() < 2) throw 22;
                std::vector<int16_t> samples = files[0].getSamples();
                files[0].writeNewSamples(samples);
                (*con).ChangeSamples(samples, config.Times[0], config.Times[1]);
                auto begin = config.Times.cbegin();
                config.Times.erase(begin, begin + 1);
            }
            else {
                throw 23;
                return ERROR_VALUE;
            }
        }
        if (files[0].save(in.getFileName(0)) == 1)
            throw 24;
    }
    catch(int i) {
        Errors r;
        std::cerr << r.errors[i] << std::endl;
        return 0;
    }
}
