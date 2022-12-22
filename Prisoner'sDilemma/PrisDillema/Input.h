#pragma once
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <boost/program_options.hpp>
namespace po = boost::program_options;
namespace ip {
    class Input {
    public:
        std::map<std::string, int> namesStrategies = { {"AlwaysSayYes",1},{"AlwaysSayNo", 2},{"Random", 3},{"EyeForEye", 4},{"Statistician", 5}, {"TheEqualizer", 6}, {"ThePredictor", 7} };
        std::string mode = "fast";
        std::string matrixFile = "GameMatrix1.txt";
        int steps = 6;
        std::vector <std::string> names;
        std::string directory;

        int GetProgramOptions(const int argc, const char* const argv[], ip::Input& in);
    };
}
