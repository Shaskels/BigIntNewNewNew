// Prisoner'sDilemma.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <vector>
#include "Modes.h"

std::map<std::string, int> namesStrategies = { {"AlwaysSayYes",1},{"AlwaysSayNo", 2},{"Random", 3},{"EyeForEye", 4},{"Statistician", 5}, {"TheEqualizer", 6}, {"ThePredictor", 7} };

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "RUSSIAN");

    std::string mode = "";
    std::string matrixFile = "GameMatrix1.cpp";
    std::string tmp;
    std::vector <int> names;
    std::string directory;
    int i;
    for (i = 1; i < argc; i++) {
        tmp = std::string(argv[i]);
        if (tmp == "fast" || tmp == "detailed" || tmp == "tournament") {
            mode = tmp;
            break;
        }
        else {
            if (namesStrategies.find(argv[i]) == namesStrategies.end()) {
                std::cout << "Такой стратегии не нет";
                return 0;
            }
            else
                names.push_back(namesStrategies[argv[i]]);
        }
    }
    if (mode == "") {
        std::cout << "Неправильное название режима";
        return 0;
    }
    if (names.size() < 3) {
        std::cout << "Неправильное количество стратегий";
        return 0;
    }


    if (mode == "fast") {
        int steps = 6;
        for (int j = i + 1; j < argc; j++) {
            tmp = std::string(argv[j]);
            if (isDigit(tmp))
                steps = std::stoi(argv[j]);
            else if (tmp.find(".") != std::string::npos)
                matrixFile = tmp;
            else
                directory = tmp;
        }
        Fast(names, steps, matrixFile, directory);
    }
    else if (mode == "detailed") {
        for (int j = i + 1; j < argc; j++) {
            tmp = std::string(argv[j]);
            if (tmp.find(".") != std::string::npos)
                matrixFile = tmp;
            else
                directory = tmp;
        }
        Detailed(names, matrixFile, directory);
    }
    else if (mode == "tournament") {
        for (int j = i + 1; j < argc; j++) {
            tmp = std::string(argv[j]);
            if (tmp.find(".") != std::string::npos)
                matrixFile = tmp;
            else
                directory = tmp;
        }
        Tournament(names, matrixFile, directory);
    }
    else {
        std::cout << "Неправильное название режима";
        return 0;
    }
    return 0;
}
