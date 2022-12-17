
#include <iostream>
#include <string>
#include <vector>
#include "Input.h"

void showHelp() {
    std::cout << "" << std::endl;
}
int np::Input::GetProgramOptions(const int argc, const char* const argv[]) {
    Errors r;
    if (argc < 4) {
        std::cerr << r.errors[24] << std::endl;
        return ERROR_VALUE;
    }
    std::vector<std::string> sours;

    for (int i = 1; i < argc; i++) {
        sours.push_back(argv[i]);
    }

    for (int i = 0; i < sours.size(); i++) {
        if (sours[i].find("-h") != std::string::npos) {
            showHelp();
        }
        else if (sours[i].find("-c") != std::string::npos) continue;
        else if (sours[i].find("[") != std::string::npos) {
            if (sours[i][sours[i].size() - 1] != ']') {
                std::cerr << r.errors[25] << std::endl;
                return ERROR_VALUE;
            }
            sours[i].pop_back();
            sours[i].erase(0, 1);
            Input::files.push_back(sours[i]);
        }
    }
    return SUCCESS;
}

std::string np::Input::getFileName(int n) {
    return files[n];
}

int np::Input::getFilesSize() {
    return files.size();
}