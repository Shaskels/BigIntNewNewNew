
#include <iostream>
#include "Input.h"
#include "AudioFile.h"
#include "Сonverter.h"
#include "ConfigurationFile.h"

int main(int argc, char* argv[])
{
    Input in;
    GetProgramOptions(argc, argv, in);
    std::vector<AudioFile> files;
    ConfigurationFile config;
    getConfigs(in.files[0],config);
    for (int i = 2; i < in.files.size(); i++) {
        AudioFile file;
        load(in.files[i], file);
        files.push_back(file);
    }
    for (int i = 0; i < config.Converters.size(); i++) {
        if (config.Converters[i] == "mute") {
            MuteTheIntervalFactory factory;
            Converter* con = factory.MakeConverter();
            (*con).ChangeSamples(files[0].samples, config.Times[0], config.Times[1]);
            auto begin = config.Times.cbegin();
            config.Times.erase(begin, begin + 2);
        }
        else if (config.Converters[i] == "mix") {
            MixerFactory factory;
            Converter* con = factory.MakeConverter();
            con->start2 = config.Times[0];
            con->samples2 = files[config.Links[0] - 1].samples;
            (*con).ChangeSamples(files[0].samples, 0, 0);
            auto begin = config.Times.cbegin();
            config.Times.erase(begin, begin + 1);
            begin = config.Links.cbegin();
            config.Links.erase(begin, begin + 1);
        }
        else if (config.Converters[i] == "revers") {
            ReversFactory factory;
            Converter* con = factory.MakeConverter();
            (*con).ChangeSamples(files[0].samples, config.Times[0], config.Times[1]);
            auto begin = config.Times.cbegin();
            config.Times.erase(begin, begin + 1);
        }
        else {
            std::cerr << "Error! There is no such converter";
            return ERROR_VALUE;
        }
    }
    save(in.files[1], files[0]);
}
