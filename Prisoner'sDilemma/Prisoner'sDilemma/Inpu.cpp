#include "Input.h"

int ip::Input::GetProgramOptions(const int argc, const char* const argv[], ip::Input& in) {
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