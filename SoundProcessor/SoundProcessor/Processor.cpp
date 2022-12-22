#include "Processor.h"

std::string MUTE_CONVERTER = "mute";
std::string MIX_CONVERTER = "mix";
std::string REVERS_CONVERTER = "revers";

void pr::MuteProc::ProcType(std::vector<af::AudioFile>& files, configs::ConfigurationFile& config, int sec) {
    if (sec < config.Times[START] || sec > config.Times[END]) {
        auto begin = config.Times.cbegin();
        config.Times.erase(begin, begin + 2);
        return;
    }
    con::MuteTheIntervalFactory factory;
    con::Converter* con = factory.MakeConverter();
    std::vector<int16_t> samples = files[START].getSamples();
    (*con).ChangeSamples(samples);
    files[START].writeNewSamples(samples);
    auto begin = config.Times.cbegin();
    config.Times.erase(begin, begin + 2);
}
void pr::MixProc::ProcType(std::vector<af::AudioFile>& files, configs::ConfigurationFile& config, int sec) {
    if (sec < config.Times[START] || sec * con::SAMPLE_RATE > files[config.Links[START] - 1].getSubChunk2Size()) {
        auto begin = config.Times.cbegin();
        config.Times.erase(begin, begin + 1);
        return;
    }
    con::MixerFactory factory;
    con::Converter* con = factory.MakeConverter();
    con->samples2 = files[config.Links[START] - 1].getSamples();
    std::vector<int16_t> samples = files[START].getSamples();
    (*con).ChangeSamples(samples);
    files[START].writeNewSamples(samples);
    auto begin = config.Times.cbegin();
    config.Times.erase(begin, begin + 1);
    begin = config.Links.cbegin();
    config.Links.erase(begin, begin + 1);
}
void pr::ReversProc::ProcType(std::vector<af::AudioFile>& files, configs::ConfigurationFile& config, int sec) {
    if (sec == 30)
        int i = 0;
    if (sec < config.Times[START] || sec > config.Times[END]) {
        auto begin = config.Times.cbegin();
        config.Times.erase(begin, begin + 2);
        return;
    }
    con::ReversFactory factory;
    con::Converter* con = factory.MakeConverter();
    std::vector<int16_t> samples = files[START].getSamples();
    (*con).ChangeSamples(samples);
    files[START].writeNewSamples(samples);
    auto begin = config.Times.cbegin();
    config.Times.erase(begin, begin + 2);
}
int pr::CreateFiles(np::Input in, std::vector<af::AudioFile>& files) {
    for (int i = 2; i < in.getFilesSize(); i++) {
        af::AudioFile file;
        if (file.load(in.getFileName(i)) == 1)
            return 0;
        files.push_back(file);
    }
    return 1;
}
pr::Processor* pr::MuteProcFactory::MakeProc() {
    return new MuteProc();
}
pr::Processor* pr::MixProcFactory::MakeProc() {
    return new MixProc();
}
pr::Processor* pr::ReversProcFactory::MakeProc() {
    return new ReversProc();
}
std::string pr::MuteProcFactory::GetProcName() {
    return  MUTE_CONVERTER;
}
std::string pr::MixProcFactory::GetProcName() {
    return  MIX_CONVERTER;
}
std::string pr::ReversProcFactory::GetProcName() {
    return  REVERS_CONVERTER;
}

int pr::Processing(np::Input in, std::vector<af::AudioFile>& files, configs::ConfigurationFile& config) {
    std::vector<pr::ProcFactory*> factory;
    factory.push_back(new pr::MuteProcFactory);
    factory.push_back(new pr::MixProcFactory);
    factory.push_back(new pr::ReversProcFactory);
    err::Errors r;

    try {
        if (files[0].save(in.getFileName(1)) == 1)
            throw r.SaveFileErr;
        for (int second = 0; second < (files[0].getSubChunk2Size() / (con::SAMPLE_RATE * 2)) + 1; second++) {
            configs::ConfigurationFile tmpConfig = config;
            int f = 0;
            for (int i = 0; i < config.Converters.size(); i++) {
                for (int j = 0; j < factory.size(); j++) {
                    if (factory[j]->GetProcName() == config.Converters[i]) {
                        f = 1;
                        pr::Processor* proc = factory[j]->MakeProc();
                        proc->ProcType(files, tmpConfig, second);
                    }
                }
            }
            if (f == 0) {
                throw r.CommandLineErr;
            }
            files[0].writeToFile(in.getFileName(1));
            for (int i = 0; i < files.size(); i++) {
                if (files[i].getSubChunk2Size() >= (second + 1) * con::SAMPLE_RATE * 2)
                    files[i].readSamples();
            }
        }
    }
    catch (std::string i) {
        std::cerr << i << std::endl;
        return ERROR_VALUE;
    }
    return SUCCESS;
}