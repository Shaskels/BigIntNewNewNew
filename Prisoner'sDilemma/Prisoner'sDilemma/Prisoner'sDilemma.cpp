// Prisoner'sDilemma.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <vector>
#include <boost/program_options.hpp>
#include "Modes.h"

std::map<std::string, int> namesStrategies = { {"AlwaysSayYes",1},{"AlwaysSayNo", 2},{"Random", 3},{"EyeForEye", 4},{"Statistician", 5}, {"TheEqualizer", 6}, {"ThePredictor", 7} };

namespace po = boost::program_options;

std::string mode = "fast";
std::string matrixFile = "GameMatrix1.cpp";
int steps = 6;
std::vector <std::string> names;
std::string directory = "D:\Configurationfiles";

int GetProgramOptions(const int argc, const char *const argv[]) {
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "Show help")
        ("names", po::value<std::vector<std::string>>(&names), "Strategies names")
        ("mode", po::value<std::string>(&mode), "Mode name")
        ("steps", po::value<int>(&steps), "Count of steps")
        ("directory", po::value<std::string>(&directory), "Name of diractory")
        ("file", po::value<std::string>(&matrixFile), "File name");
    po::variables_map args;
    try {
        po::store(po::parse_command_line(argc, argv, desc), args);
        po::notify(args);
    }
    catch(po::error const& e) {
        std::cout << e.what() << '\n';
        return 1;
    }
    return 0;
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "RUSSIAN");

    GetProgramOptions(argc, argv);
    int i;

    if (names.size() < 3) {
        std::cout << "Неправильное количество стратегий";
        return 0;
    }
    std::vector<int> digitNames;
    for (i = 0; i < names.size(); i++) {
        if (namesStrategies.find(names[i]) == namesStrategies.end()) {
            std::cout << "Такой стратегии нет(";
            return 0;
        }
        else digitNames.push_back(namesStrategies[names[i]]);
    }
  
    if (mode == "fast") {
        Fast(digitNames, steps, matrixFile, directory);
    }
    else if (mode == "detailed") {
        Detailed(digitNames, matrixFile, directory);
    }
    else if (mode == "tournament") {
        Tournament(digitNames, matrixFile, directory);
    }
    else {
        std::cout << "Неправильное название режима";
        return 0;
    }
    return 0;
}
