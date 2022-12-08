
#include <iostream>
#include "Input.h"
#include "AudioFile.h"
int main(int argc, char* argv[])
{
    Input in;
    GetProgramOptions(argc, argv, in);
    AudioFile file1;
    load(in.files[0], file1);
}
