
#include "Modes.h"

int gameMatrix[MATRIX_LINES][MATRIX_ROWS] = { {0},{0} };

std::map<int, std::string> strategies = { {1,"AlwaysSayYes"},{2,"AlwaysSayNo"},{3,"Random"},{4,"EyeForEye"},{5,"Statistician"}, {6,"TheEqualizer"}, {7,"ThePredictor"} };

std::vector <Strategies*> MakePrisoners(std::vector <int> names) {
    std::vector <Strategies*> Prisoner;
    for (int i = 0; i < names.size(); i++) {
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
            theEqualizerFactory factory;
            Prisoner.push_back(factory.makeStrategies());
            break;
        }
        case 7:
        {
            thePredictorFactory factory;
            Prisoner.push_back(factory.makeStrategies());
            break;
        }
        default:
            break;
        }
    }
    return Prisoner;
}
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
void printing(std::map <int, int> years) {
    std::multimap<int, int> reverseYears = flip_map(years);
    std::map<int, int> ::iterator it;
    int place = 1;
    for (it = reverseYears.begin(); it != reverseYears.end(); it++)
    {
        std::cout << "Место " << place << ": " << it->first << " лет заключения, стратегия " << strategies.find(it->second)->second << '\n';
        place++;
    }
}
void yearsUpdate(char* answers, int i, std::vector<std::string>& x, std::map <int, int>& years, std::vector <int> names) {
    for (int j = 0; j < MATRIX_ROWS; j++) {
        if (answers[FIRST_PRISONER] == gameMatrix[j][0] && answers[SECOND_PRINSONER] == gameMatrix[j][1] && answers[THIRD_PRISONER] == gameMatrix[j][2]) {
            x.push_back("");
            x[i] += answers[FIRST_PRISONER];
            x[i] += answers[SECOND_PRINSONER];
            x[i] += answers[THIRD_PRISONER];
            years[names[FIRST_PRISONER]] += gameMatrix[j][MATRIX_YEARS_1];
            years[names[SECOND_PRINSONER]] += gameMatrix[j][MATRIX_YEARS_2];
            years[names[THIRD_PRISONER]] += gameMatrix[j][MATRIX_YEARS_3];
            break;
        }
    }
}
int MakeGameMatrix(std::string matrixFile) {
    std::ifstream f(matrixFile);
    if (!f)
    {
        std::cout << "Неправильное имя файла\n";
        return ERROR_RES;
    }
    std::string c;
    for (int i = 0; i < MATRIX_ROWS - 1; i++) {
        try {
            f.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            f >> c;
        }
        catch (const std::ios_base::failure& fail) {
            std::cout << fail.what() << '\n';
            return ERROR_RES;
        }
    }
    for (int i = 0; i < MATRIX_LINES; i++) {
        for (int j = 0; j < MATRIX_ROWS; j++) {
            try {
                f.exceptions(std::ifstream::failbit | std::ifstream::badbit);
                f >> c;
            }
            catch (const std::ios_base::failure& fail) {
                std::cout << fail.what() << '\n';
                return ERROR_RES;
            }
            if (c != "C" && c != "D" && c != "=>" && isDigit(c) == 0 && c != "0") {
                std::cout << "Неправильный формат матрицы\n";
                return ERROR_RES;
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
void Fast(std::vector <int> names, int steps, std::string matrixFile, std::string diractory) {
    std::vector <Strategies*> Prisoner = MakePrisoners(names);
    if (Prisoner.size() < names.size()) {
        std::cout << "Упс! Такой стартегии нет" << '\n';
    }
    if (MakeGameMatrix(matrixFile) == ERROR_RES)
        return;
    std::map <int, int> years;
    std::vector<std::string> stat;
    stat.push_back("");
    stat[0] += names[FIRST_PRISONER];
    stat[0] += names[SECOND_PRINSONER];
    stat[0] += names[THIRD_PRISONER];
    years[names[FIRST_PRISONER]] = 0;
    years[names[SECOND_PRINSONER]] = 0;
    years[names[THIRD_PRISONER]] = 0;
    for (int i = 1; i < steps + 1; i++) {
        char answers[3];
        answers[FIRST_PRISONER] = (*Prisoner[FIRST_PRISONER]).makeDecision(stat, FIRST_PRISONER, diractory);
        answers[SECOND_PRINSONER] = (*Prisoner[SECOND_PRINSONER]).makeDecision(stat, SECOND_PRINSONER, diractory);
        answers[THIRD_PRISONER] = (*Prisoner[THIRD_PRISONER]).makeDecision(stat, THIRD_PRISONER, diractory);
        if (answers[0] == ERROR_RES || answers[1] == ERROR_RES || answers[2] == ERROR_RES) {
            std::cout << "Невозможно прочитать конфгурационный файл\n";
            return;
        }
        yearsUpdate(answers, i, stat, years, names);
    }
    printing(years);
}
void Detailed(std::vector <int> names, std::string matrixFile, std::string diractory) {
    std::vector <Strategies*> Prisoner = MakePrisoners(names);
    if (Prisoner.size() < names.size()) {
        std::cout << "Упс! Такой стартегии нет" << '\n';
    }
    if (MakeGameMatrix(matrixFile) == ERROR_RES)
        return;
    std::map <int, int> years;
    std::vector<std::string> stat;
    stat.push_back("");
    stat[0] += names[FIRST_PRISONER];
    stat[0] += names[SECOND_PRINSONER];
    stat[0] += names[THIRD_PRISONER];
    years[names[FIRST_PRISONER]] = 0;
    years[names[SECOND_PRINSONER]] = 0;
    years[names[THIRD_PRISONER]] = 0;
    std::string s;
    std::cout << "Введите любой символ для начала симуляции, для выхода введите quit\n";
    std::cin >> s;
    // system("pause");
    // getline(std::cin, s);
    int i = 1;
    while (s != "quit") {
        char answers[3];
        answers[FIRST_PRISONER] = (*Prisoner[FIRST_PRISONER]).makeDecision(stat, FIRST_PRISONER, diractory);
        answers[SECOND_PRINSONER] = (*Prisoner[SECOND_PRINSONER]).makeDecision(stat, SECOND_PRINSONER, diractory);
        answers[THIRD_PRISONER] = (*Prisoner[THIRD_PRISONER]).makeDecision(stat, THIRD_PRISONER, diractory);
        if (answers[0] == ERROR_RES || answers[1] == ERROR_RES || answers[2] == ERROR_RES) {
            std::cout << "Невозможно прочитать конфгурационный файл\n";
            return;
        }
        yearsUpdate(answers, i, stat, years, names);
        std::map<int, int> ::iterator it;
        int k = 0;
        std::cout << "Рейтинг: \n";
        for (it = years.begin(); it != years.end(); it++)
        {
            std::cout << "Стритегия " << strategies.find(it->first)->second << " \n       Принятое решение " << stat[i][k] << '\n';
            std::cout << "       Годы заключения: " << it->second << '\n';
            k++;
        }
        // system("pause");
       //  getline(std::cin, s);
        std::cout << "Введите любой символ для продолжения, для выхода введите quit\n";
        std::cin >> s;
        i++;
    }
    printing(years);
}
void Tournament(std::vector <int> names, std::string matrixFile, std::string diractory) {
    std::vector <Strategies*> Prisoner = MakePrisoners(names);
    if (Prisoner.size() < names.size()) {
        std::cout << "Упс! Такой стартегии нет" << '\n';
    }
    if (MakeGameMatrix(matrixFile) == ERROR_RES)
        return;
    std::map <int, int> years;
    for (int i = 0; i < names.size(); i++) {
        years[names[i]] = 0;
    }
    for (int i = 0; i < names.size(); i++) {
        for (int j = i + 1; j < names.size(); j++) {
            for (int k = j + 1; k < names.size(); k++) {
                std::vector<std::string> stat;
                stat.push_back("");
                stat[0] += names[FIRST_PRISONER];
                stat[0] += names[SECOND_PRINSONER];
                stat[0] += names[THIRD_PRISONER];
                for (int h = 0; h < 3; h++) {
                    char answers[3];
                    answers[FIRST_PRISONER] = (*Prisoner[FIRST_PRISONER]).makeDecision(stat, FIRST_PRISONER, diractory);
                    answers[SECOND_PRINSONER] = (*Prisoner[SECOND_PRINSONER]).makeDecision(stat, SECOND_PRINSONER, diractory);
                    answers[THIRD_PRISONER] = (*Prisoner[THIRD_PRISONER]).makeDecision(stat, THIRD_PRISONER, diractory);
                    if (answers[FIRST_PRISONER] == ERROR_RES || answers[SECOND_PRINSONER] == ERROR_RES || answers[THIRD_PRISONER] == ERROR_RES) {
                        std::cout << "Невозможно прочитать конфгурационный файл\n";
                        return;
                    }
                    yearsUpdate(answers, i, stat, years, names);
                }
            }
        }
    }
    printing(years);
}
