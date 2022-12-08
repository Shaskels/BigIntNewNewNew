#pragma once

#include <boost/program_options.hpp>
#include <iostream>

namespace po = boost::program_options;
class Input {
public:
    
    std::vector<std::string> files;

    int GetProgramOptions(const int, const char* const);
};
void showHelp(po::options_description desc) {
    std::cout << "Some help" << std::endl;
}
int GetProgramOptions(const int argc, const char* const argv[], Input& in) {
    po::options_description desc("Allowed options");
    desc.add_options()
        ("-h", "Show help")
        ("-c", po::value<std::vector<std::string>>(&(in.files)), "File name");
    po::variables_map args;
    if (argc == 1) {
        showHelp(desc);
    }
    try {
        po::store(po::parse_command_line(argc, argv, desc), args);
        po::notify(args);
        if (args.find("-h") != args.end())
            showHelp(desc);
    }
    catch (po::error const& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
    return 0;
}