// Prisoner'sDilemma.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include "Strategies.h"
std::vector<std::string> x;
std::map<int, std::string> strategies = { {1,"AlwaysSayYes"},{2,"AlwaysSayNo"},{3,"Random"},{4,"EyeForEye"},{5,"Statistician"}, {6,"TheEqualizer"} };
/*enum strategies {
    AlwaysSayYes,
    AlwaysSayNo,
    Random,
    EyeForEye,
    Statistician,
    TheEqualizer
};*/
std::multimap<int, int> flip_map(std::map<int, int>& mymap)
{
    std::multimap<int, int> multiMap;

    std::map<int, int> ::iterator it;
    for (it = mymap.begin(); it != mymap.end(); it++)
    {
        multiMap.insert(std::make_pair(it->second, it->first));
    }

    return multiMap;
}
void Fast(std::vector <int> names, int steps, std::string matrixFile) {
    std::vector <Strategies*> Prisoner;
    for (int i = 0; i < 3; i++) {
        switch (names[i]) 
        {
            case 1:
            {
                alwaysSayYesFactory factory;
                Prisoner.push_back(factory.makeStrategies());
                break;
            }
            case 2: 
            {
                alwaysSayNoFactory factory;
                Prisoner.push_back(factory.makeStrategies());
                break;
            }
            case 3: 
            {
                randomFactory factory;
                Prisoner.push_back(factory.makeStrategies());
                break;
            }
            case 4: 
            {
                eyeForEyeFactory factory;
                Prisoner.push_back(factory.makeStrategies());
                break;
            }
            case 5: 
            {
                statisticianFactory factory;
                Prisoner.push_back(factory.makeStrategies());
                break;
            }
            case 6:
            {
                break;
            }
        }
    }
    const unsigned int rows = 8;
    const unsigned int lines = 9;
    char gameMatrix[lines][rows];
    std::ifstream f(matrixFile);
    if (!f)
    {
        std::cout << "Неправильное имя файла\n";
        return;
    }
    char c;
    for (int i = 0; i < 12; i++) {
        f >> c;
    }
    for (int i = 1; i < 9; i++) {
        for (int j = 0; j < 8; j++) {
            f >> c;
            if (c != 'C' && c != 'D' && c != '=' && c != '>' && isdigit(c) == 0 && c != '0') {
                std::cout << "Неправильный формат матрицы\n";
                return;
            }
            gameMatrix[i][j] = c;
        }
    }
    std::map <int, int> years;
    years[names[0]] = 0;
    years[names[1]] = 0;
    years[names[2]] = 0;
    for (int i = 0; i < steps; i++) {
        char answerFirst =  (*Prisoner[0]).makeDecision(x, 1);
        char answerSecond = (*Prisoner[1]).makeDecision(x, 2);
        char answerThird = (*Prisoner[2]).makeDecision(x, 3);
        for (int j = 1; j < 9; j++) {
            if (answerFirst == gameMatrix[j][0] && answerSecond == gameMatrix[j][1] && answerThird == gameMatrix[j][2]) {
                x.push_back("");
                x[i] += answerFirst;
                x[i] += answerSecond;
                x[i] += answerThird;
                years[names[0]] += gameMatrix[j][5] - '0';
                years[names[1]] += gameMatrix[j][6] - '0';
                years[names[2]] += gameMatrix[j][7] - '0';
            }
        }
    }
    std::multimap<int, int> reverseYears = flip_map(years);
    std::map<int, int> ::iterator it;
    int place = 1;
    for (it = reverseYears.begin(); it != reverseYears.end(); it++)
    {
        std::cout << "Место " << place << ": " << it->first << " лет заключения, стратегия " << strategies.find(it->second)->second << '\n';
        place++;
    }
}
void Detailed(std::vector <int> names, std::string matrixFile) {

}
void Tournament(std::vector <int> names, std::string matrixFile) {

}

int main()
{
    setlocale(LC_ALL, "RUSSIAN");
    std::vector <int> names;
    std::string mode;
    std::string matrixFile;
    std::cout << "Выберите режим: fast, detailed, tournament";
    std::cin >> mode;
    if (mode == "fast") {
        int steps;
        std::cout << "Введите номера стратегий: \n 1 alwaysSayYes, \n 2  alwaysSayNo, \n" <<
            " 3 random, \n 4  eyeForEye, \n 5  theWorseTheBetter, \n 6 theEqualizer \n";
        int name;
        for (int i = 0; i < 3; i++) {
            std::cin >> name;
            if (name > 6 || name < 1) {
                std::cout << "Неправильный номер стратегии";
                return 0;
            }
            names.push_back(name);
        }
        std::cin >> steps;
        std::cin >> matrixFile;
        Fast(names, steps, matrixFile);
    }
    else if (mode == "detailed") {
        std::cout << "Введите номера стратегий: \n 1 alwaysSayYes, \n 2  alwaysSayNo, \n" <<
            " 3 random, \n 4  eyeForEye, \n 5  theWorseTheBetter, \n 6 theEqualizer \n";
        int name;
        for (int i = 0; i < 3; i++) {
            std::cin >> name;
            if (name > 6 || name < 1) {
                std::cout << "Неправильный номер стратегии";
                return 0;
            }
            names.push_back(name);
        }
        std::cin >> matrixFile;
        Detailed(names, matrixFile);
    }
    else if (mode == "tournament") {
        std::cout << "Введите количество стратегий(от 3 до 6)";
        int n;
        std::cin >> n;
        if (n > 6 || n < 3) {
            std::cout << "Неправильное количество стратегий";
            return 0;
        }
        std::cout << "Введите номера стратегий: \n 1 alwaysSayYes, \n 2  alwaysSayNo, \n" <<
            " 3 random, \n 4  eyeForEye, \n 5  theWorseTheBetter, \n 6 theEqualizer \n";
        int name;
        for (int i = 0; i < n; i++) {
            std::cin >> name;
            if (name > 6 || name < 1) {
                std::cout << "Неправильный номер стратегии";
                names.push_back(name);
            }
            std::cin >> matrixFile;
            Tournament(names, matrixFile);
        }
    }
    else {
        std::cout << "Неправильное название режима";
        return 0;
    }
    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
