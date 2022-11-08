// Prisoner'sDilemma.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include "Strategies.h"
int gameMatrix[9][7] = { 0 };
std::map<int, std::string> strategies = { {1,"AlwaysSayYes"},{2,"AlwaysSayNo"},{3,"Random"},{4,"EyeForEye"},{5,"Statistician"}, {6,"TheEqualizer"}, {7,"ThePredictor"}};
/*enum strategies {
    AlwaysSayYes,
    AlwaysSayNo,
    Random,
    EyeForEye,
    Statistician,
    TheEqualizer,
    ThePredictor
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
bool isDigit(std::string s) {
    for (int i = 0; i < s.size(); i++) {
        if (!isdigit(s[i]))
            return false;
    }
    return true;
}
int makeInt(std::string s) {
    int t = 0;
    int level = 1;
    for (int i = 0; i < s.size(); i++) {
        t = (s[i] - '0') + t * level;
        level *= 10;
    }
    return t;
}
int MakeGameMatrix(std::string matrixFile) {
    std::ifstream f(matrixFile);
    if (!f)
    {
        std::cout << "Неправильное имя файла\n";
        return 1;
    }
    std::string c;
    for (int i = 0; i < 6; i++) {
        try {
            f.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            f >> c;
        } catch (const std::ios_base::failure& fail) {
            std::cout << fail.what() << '\n';
            return 1;
        }
    }
    for (int i = 1; i < 9; i++) {
        for (int j = 0; j < 7; j++) {
            try {
                f.exceptions(std::ifstream::failbit | std::ifstream::badbit);
                f >> c;
            }
            catch (const std::ios_base::failure& fail) {
                std::cout << fail.what() << '\n';
                return 1;
            }
            if (c != "C" && c != "D" && c != "=>" && isDigit(c) == 0 && c != "0") {
                std::cout << "Неправильный формат матрицы\n";
                return 1;
            }
            if (isDigit(c)) {
                gameMatrix[i][j] = makeInt(c);
            }
            else {
                gameMatrix[i][j] = c[0];
            }
        }
    }
    f.close();
    return 0;
}
void Fast(std::vector <int> names, int steps, std::string matrixFile) {
    std::vector <Strategies*> Prisoner = MakePrisoners(names);
    if(MakeGameMatrix(matrixFile) == 1)
        return;
    std::map <int, int> years;
    std::vector<std::string> x;
    x.push_back("");
    x[0] += names[0];
    x[0] += names[1];
    x[0] += names[2];
    years[names[0]] = 0;
    years[names[1]] = 0;
    years[names[2]] = 0;
    for (int i = 1; i < steps + 1; i++) {
        char answerFirst =  (*Prisoner[0]).makeDecision(x, 1);
        char answerSecond = (*Prisoner[1]).makeDecision(x, 2);
        char answerThird = (*Prisoner[2]).makeDecision(x, 3);
        for (int j = 1; j < 9; j++) {
            if (answerFirst == gameMatrix[j][0] && answerSecond == gameMatrix[j][1] && answerThird == gameMatrix[j][2]) {
                x.push_back("");
                x[i] += answerFirst;
                x[i] += answerSecond;
                x[i] += answerThird;
                years[names[0]] += gameMatrix[j][4];
                years[names[1]] += gameMatrix[j][5];
                years[names[2]] += gameMatrix[j][6];
                break;
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
    std::vector <Strategies*> Prisoner = MakePrisoners(names);
    if (MakeGameMatrix(matrixFile) == 1)
        return;
    std::map <int, int> years;
    std::vector<std::string> x;
    x[0] += names[0] - '0';
    x[0] += names[1] - '0';
    x[0] += names[2] - '0';
    years[names[0]] = 0;
    years[names[1]] = 0;
    years[names[2]] = 0;
    std::string s;
    std::cout << "Введите любой символ для начала симуляции, для выхода введите quit";
    std::cin >> s;
    // system("pause");
    // getline(std::cin, s);
    int i = 1;
    while (s != "quit") {
        char answerFirst = (*Prisoner[0]).makeDecision(x, 1);
        char answerSecond = (*Prisoner[1]).makeDecision(x, 2);
        char answerThird = (*Prisoner[2]).makeDecision(x, 3);
        int j;
        for (j = 1; j < 9; j++) {
            if (answerFirst == gameMatrix[j][0] && answerSecond == gameMatrix[j][1] && answerThird == gameMatrix[j][2]) {
                x.push_back("");
                x[i] += answerFirst;
                x[i] += answerSecond;
                x[i] += answerThird;
                years[names[0]] += gameMatrix[j][4];
                years[names[1]] += gameMatrix[j][5];
                years[names[2]] += gameMatrix[j][6];
                break;
            }
        }
        std::map<int, int> ::iterator it;
        int k = 0;
        std::cout << "Рейтинг: \n";
        for (it = years.begin(); it != years.end(); it++)
        {
            std::cout << "Стритегия " << strategies.find(it->first)->second << " \n       Принятое решение " << x[i][k] << '\n';
            if (i == 1)
                std::cout << "       Годы заключения: " << it->second << '\n';
            else
                std::cout << "       Годы заключения: " << it->second - gameMatrix[j][k + 4] << " + " << gameMatrix[j][k + 4] << '\n';
            k++;
        }
        // system("pause");
       //  getline(std::cin, s);
        std::cout << "Введите любой символ для продолжения, для выхода введите quit";
        std::cin >> s;
        i++;
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
void Tournament(std::vector <int> names, std::string matrixFile) {
    std::vector <Strategies*> Prisoner = MakePrisoners(names);
    if (MakeGameMatrix(matrixFile) == 1)
        return;
    std::map <int, int> years;
    for (int i = 0; i < names.size(); i++) {
        years[names[i]] = 0;
    }
    for (int i = 0; i < names.size(); i++) {
        for (int j = i + 1; j < names.size(); j++) {
            for (int k = j + 1; k < names.size(); k++) {
                 std::vector<std::string> x;
                 x[0] += names[0] - '0';
                 x[0] += names[1] - '0';
                 x[0] += names[2] - '0';
                 for (int h = 1; h < 4; h++) {
                      char answerFirst = (*Prisoner[i]).makeDecision(x, 1);
                      char answerSecond = (*Prisoner[j]).makeDecision(x, 2);
                      char answerThird = (*Prisoner[k]).makeDecision(x, 3);
                      for (int g = 1; g < 9; g++) {
                          if (answerFirst == gameMatrix[g][0] && answerSecond == gameMatrix[g][1] && answerThird == gameMatrix[g][2]) {
                              x.push_back("");
                              x[h] += answerFirst;
                              x[h] += answerSecond;
                              x[h] += answerThird;
                              years[names[i]] += gameMatrix[g][4];
                              years[names[j]] += gameMatrix[g][5];
                              years[names[k]] += gameMatrix[g][6];
                              break;
                          }
                      }
                 }
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
