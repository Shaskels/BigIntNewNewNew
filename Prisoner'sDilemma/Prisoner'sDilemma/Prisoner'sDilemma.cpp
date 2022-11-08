// Prisoner'sDilemma.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <vector>
#include "Modes.h"


int main()
{
    setlocale(LC_ALL, "RUSSIAN");
    std::vector <int> names;
    std::string mode;
    std::string matrixFile;
    std::cout << "Выберите режим: fast, detailed, tournament\n";
    std::cin >> mode;
    if (mode == "fast") {
        int steps;
        std::cout << "Введите номера стратегий: \n 1 alwaysSayYes, \n 2 alwaysSayNo, \n" <<
            " 3 random, \n 4 eyeForEye, \n 5 Statistician, \n 6 theEqualizer \n 7 ThePredictor \n ";
        int name;
        for (int i = 0; i < 3; i++) {
            std::cin >> name;
            if (name > 7 || name < 1) {
                std::cout << "Неправильный номер стратегии\n";
                return 0;
            }
            for (int j = 0; j < names.size(); j++) {
                if (name == names[j])
                    std::cout << "Предупреждение! Вы уже вводили эту стратегию";
            }
            names.push_back(name);
        }
        std::cout << "Введите количество шагов симуляции\n";
        std::cin >> steps;
        std::cout << "Введите название файла с матрицей игры\n";
        std::cin >> matrixFile;
        Fast(names, steps, matrixFile);
    }
    else if (mode == "detailed") {
        std::cout << "Введите номера стратегий: \n 1 alwaysSayYes, \n 2 alwaysSayNo, \n" <<
            " 3 random, \n 4 eyeForEye, \n 5 Statistician, \n 6 theEqualizer \n 7 ThePredictor \n ";
        int name;
        for (int i = 0; i < 3; i++) {
            std::cin >> name;
            if (name > 7 || name < 1) {
                std::cout << "Неправильный номер стратегии";
                return 0;
            }
            for (int j = 0; j < names.size(); j++) {
                if (name == names[j])
                    std::cout << "Предупреждение! Вы уже вводили эту стратегию";
            }
            names.push_back(name);
        }
        std::cout << "Введите название файла с матрицей игры\n";
        std::cin >> matrixFile;
        Detailed(names, matrixFile);
    }
    else if (mode == "tournament") {
        std::cout << "Введите количество стратегий(от 3 до 6)";
        int n;
        std::cin >> n;
        if (n > 7 || n < 3) {
            std::cout << "Неправильное количество стратегий";
            return 0;
        }
        std::cout << "Введите номера стратегий: \n 1 alwaysSayYes, \n 2 alwaysSayNo, \n" <<
            " 3 random, \n 4 eyeForEye, \n 5 Statistician, \n 6 theEqualizer \n 7 ThePredictor \n ";
        int name;
        for (int i = 0; i < n; i++) {
            std::cin >> name;
            if (name > 7 || name < 1) {
                std::cout << "Неправильный номер стратегии";
                return 0;
            }
            for (int j = 0; j < names.size(); j++) {
                if (name == names[j])
                    std::cout << "Предупреждение! Вы уже вводили эту стратегию";
            }
            names.push_back(name);
        }
        std::cout << "Введите название файла с матрицей игры\n";
        std::cin >> matrixFile;
        Tournament(names, matrixFile);
    }
    else {
        std::cout << "Неправильное название режима";
        return 0;
    }
    return 0;
}
