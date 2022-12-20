
#include <iostream>
#include "Input.h"
#include "AudioFile.h"
#include "Сonverter.h"
#include "ConfigurationFile.h"
<<<<<<< Updated upstream
=======
#include "Processor.h"

int const MIN_SIZE_MUTE = 2;
int const MIN_SIZE_MIX = 1;

std::string MUTE_CONVERTER = "mute";
std::string MIX_CONVERTER = "mix";
std::string REVERS_CONVERTER = "revers";
>>>>>>> Stashed changes

int main(int argc, char* argv[])
{
    Input in;
    GetProgramOptions(argc, argv, in);
    std::vector<AudioFile> files;
    Configs::ConfigurationFile config;
    Configs::getConfigs(in.files[0],config);
    for (int i = 2; i < in.files.size(); i++) {
        AudioFile file;
        if(load(in.files[i], file) == 1)
            return 0;
        files.push_back(file);
    }
    try {
        for (int i = 0; i < config.Converters.size(); i++) {
            if (config.Converters[i] == "mute") {
                MuteTheIntervalFactory factory;
                Converter* con = factory.MakeConverter();
                if (config.Times.size() < 2) throw 22;
                (*con).ChangeSamples(files[0].samples, config.Times[0], config.Times[1]);
                auto begin = config.Times.cbegin();
                config.Times.erase(begin, begin + 2);
            }
            else if (config.Converters[i] == "mix") {
                MixerFactory factory;
                Converter* con = factory.MakeConverter();
                if (config.Times.size() < 1) throw 22;
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
                if (config.Times.size() < 2) throw 22;
                (*con).ChangeSamples(files[0].samples, config.Times[0], config.Times[1]);
                auto begin = config.Times.cbegin();
                config.Times.erase(begin, begin + 1);
            }
            else {
                throw 23;
                return ERROR_VALUE;
            }
        }
        if (save(in.files[1], files[0]) == 1)
            throw 24;
    }
    catch(int i) {
        Errors r;
        std::cerr << r.errors[i] << std::endl;
        return 0;
    }
}
