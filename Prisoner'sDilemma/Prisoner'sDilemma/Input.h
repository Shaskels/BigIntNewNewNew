#pragma once
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <boost/program_options.hpp>
namespace po = boost::program_options;
class Input {
public:
	std::map<std::string, int> namesStrategies = { {"AlwaysSayYes",1},{"AlwaysSayNo", 2},{"Random", 3},{"EyeForEye", 4},{"Statistician", 5}, {"TheEqualizer", 6}, {"ThePredictor", 7} };

	std::string mode = "fast";
	std::string matrixFile = "GameMatrix1.txt";
	int steps = 6;
	std::vector <std::string> names;
	std::string directory = "D:\Configurationfiles";

	int GetProgramOptions(const int, const char* const);
};

int GetProgramOptions(const int argc, const char* const argv[], Input& in) {
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "Show help")
        ("names", po::value<std::vector<std::string>>(&(in.names)), "Strategies names")
        ("mode", po::value<std::string>(&(in.mode)), "Mode name")
        ("steps", po::value<int>(&(in.steps)), "Count of steps")
        ("directory", po::value<std::string>(&(in.directory)), "Name of diractory")
        ("file", po::value<std::string>(&(in.matrixFile)), "File name");
    po::variables_map args;
    try {
        po::store(po::parse_command_line(argc, argv, desc), args);
        po::notify(args);
    }
    catch (po::error const& e) {
        std::cout << e.what() << '\n';
        return 1;
    }
    return 0;
}

