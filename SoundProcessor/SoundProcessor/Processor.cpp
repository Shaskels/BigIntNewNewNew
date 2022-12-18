#include "Processor.h"

void pr::Processor::Mute(std::vector<af::AudioFile>& files, configs::ConfigurationFile& config) {
    con::MuteTheIntervalFactory factory;
    con::Converter* con = factory.MakeConverter();
    std::vector<int16_t> samples = files[START].getSamples();
    (*con).ChangeSamples(samples,  config.Times[START], config.Times[END]);
    files[START].writeNewSamples(samples);
    auto begin = config.Times.cbegin();
    config.Times.erase(begin, begin + 2);
}
void pr::Processor::Mix(std::vector<af::AudioFile>& files, configs::ConfigurationFile& config) {
    con::MixerFactory factory;
    con::Converter* con = factory.MakeConverter();
    con->start2 = config.Times[START];
    con->samples2 = files[config.Links[START] - 1].getSamples();
    std::vector<int16_t> samples = files[START].getSamples();
    (*con).ChangeSamples(samples, 0, 0);
    files[START].writeNewSamples(samples);
    auto begin = config.Times.cbegin();
    config.Times.erase(begin, begin + 1);
    begin = config.Links.cbegin();
    config.Links.erase(begin, begin + 1);
}
void pr::Processor::Revers(std::vector<af::AudioFile>& files, configs::ConfigurationFile& config) {
    con::ReversFactory factory;
    con::Converter* con = factory.MakeConverter();
    std::vector<int16_t> samples = files[START].getSamples();
    (*con).ChangeSamples(samples, config.Times[START], config.Times[END]);
    files[START].writeNewSamples(samples);
    auto begin = config.Times.cbegin();
    config.Times.erase(begin, begin + 1);
}