
#include <iostream>
#include "Input.h"
#include "AudioFile.h"
#include "Сonverter.h"

int main(int argc, char* argv[])
{
    Input in;
    GetProgramOptions(argc, argv, in);
    AudioFile file1;
    load(in.files[0], file1);
    MuteTheIntervalFactory factory;
    Converter* con = factory.MakeConverter();
    (*con).ChangeSamples(file1.samples, 5, 33);
    save("out.wav", file1);
}
