// Prisoner'sDilemma.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "Modes.h"
#include "Input.h"

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "RUSSIAN");
    Input in;
    if(GetProgramOptions(argc, argv, in) == ERROR_RES)
        return 0;
    int i;

    if ((in.names).size() < 3) {
        std::cout << "Неправильное количество стратегий";
        return 0;
    }
    std::vector<int> digitNames;
    for (i = 0; i < (in.names).size(); i++) {
        if ((in.namesStrategies).find((in.names[i])) == (in.namesStrategies).end()) {
            std::cout << "Такой стратегии нет(";
            return 0;
        }
        else digitNames.push_back(in.namesStrategies[in.names[i]]);
    }
  
    if (in.mode == "fast") {
        Fast(digitNames, in.steps, in.matrixFile, in.directory);
    }
    else if (in.mode == "detailed") {
        Detailed(digitNames, in.matrixFile, in.directory);
    }
    else if (in.mode == "tournament") {
        Tournament(digitNames, in.matrixFile, in.directory);
    }
    else {
        std::cout << "Неправильное название режима";
        return 0;
    }
    return 0;
}
