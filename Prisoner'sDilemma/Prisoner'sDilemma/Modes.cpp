
#include "Modes.h"
<<<<<<< Updated upstream

=======
#include "Factory.h"
>>>>>>> Stashed changes
int gameMatrix[MATRIX_LINES][MATRIX_ROWS] = { {0},{0} };

std::map<int, std::string> strategies = { {1,"AlwaysSayYes"},{2,"AlwaysSayNo"},{3,"Random"},{4,"EyeForEye"},{5,"Statistician"}, {6,"TheEqualizer"}, {7,"ThePredictor"} };

<<<<<<< Updated upstream
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
=======
Mode::Mode(std::vector <int> names, int p, std::string str, std::string dir) {
    digitNames = names;
    steps = p;
    matrixFile = str;
    diractory = dir;
}
std::vector <Strategies*> MakePrisoners(std::vector <int> names) {
    std::vector<Strategies*> Prisoner;
    std::vector<StrategiesFactory*> factory;
    factory.push_back(new alwaysSayYesFactory);
    factory.push_back(new alwaysSayNoFactory);
    factory.push_back(new randomFactory);
    factory.push_back(new eyeForEyeFactory);
    factory.push_back(new statisticianFactory);
    factory.push_back(new theEqualizerFactory);
    factory.push_back(new thePredictorFactory);

    for (int i = 0; i < names.size(); i++) {
        for (int j = 0; j < factory.size(); j++) {
            if ((*factory[j]).getStrategType() == names[i]) {
                Prisoner.push_back(factory[j]->makeStrategies());
                break;
            }
>>>>>>> Stashed changes
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
void InitializationYearsAndStat(std::map <int, int>& years, std::vector<std::string>& stat, std::vector <int> names) {
    stat.push_back("");
    stat[0] += names[FIRST_PRISONER];
    stat[0] += names[SECOND_PRINSONER];
    stat[0] += names[THIRD_PRISONER];
    years[names[FIRST_PRISONER]] = 0;
    years[names[SECOND_PRINSONER]] = 0;
    years[names[THIRD_PRISONER]] = 0;
}
<<<<<<< Updated upstream
void PrisonerAnswer(char answers[3], std::string diractory, std::vector <Strategies*> Prisoner, std::vector<std::string> stat) {
=======
void PrisonerAnswer(char answers[NUMBER_OF_PRISONERS], std::string diractory, std::vector <Strategies*> Prisoner, std::vector<std::string> stat) {
>>>>>>> Stashed changes
    answers[FIRST_PRISONER] = (*Prisoner[FIRST_PRISONER]).makeDecision(stat, FIRST_PRISONER, diractory);
    answers[SECOND_PRINSONER] = (*Prisoner[SECOND_PRINSONER]).makeDecision(stat, SECOND_PRINSONER, diractory);
    answers[THIRD_PRISONER] = (*Prisoner[THIRD_PRISONER]).makeDecision(stat, THIRD_PRISONER, diractory);
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
<<<<<<< Updated upstream
        if (answers[FIRST_PRISONER] == gameMatrix[j][0] && answers[SECOND_PRINSONER] == gameMatrix[j][1] && answers[THIRD_PRISONER] == gameMatrix[j][2]) {
=======
        if (answers[FIRST_PRISONER] == gameMatrix[j][FIRST_PRISONER] && answers[SECOND_PRINSONER] == gameMatrix[j][SECOND_PRINSONER] && answers[THIRD_PRISONER] == gameMatrix[j][THIRD_PRISONER]) {
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
void Fast(std::vector <int> names, int steps, std::string matrixFile, std::string diractory) {
    std::vector <Strategies*> Prisoner = MakePrisoners(names);
    if (Prisoner.size() < names.size()) {
=======
void Mode::Fast() {
    std::vector <Strategies*> Prisoner = MakePrisoners(digitNames);
    if (Prisoner.size() < digitNames.size()) {
>>>>>>> Stashed changes
        std::cout << "Упс! Такой стартегии нет" << '\n';
    }
    if (MakeGameMatrix(matrixFile) == ERROR_RES)
        return;
    std::map <int, int> years;
    std::vector<std::string> stat;
<<<<<<< Updated upstream
    InitializationYearsAndStat(years, stat, names);
    for (int i = 1; i < steps + 1; i++) {
        char answers[3];
        PrisonerAnswer(answers, diractory, Prisoner, stat);
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
=======
    InitializationYearsAndStat(years, stat, digitNames);
    for (int i = 1; i < steps + 1; i++) {
        char answers[3];
        PrisonerAnswer(answers, diractory, Prisoner, stat);
        if (answers[THIRD_PRISONER] == ERROR_RES || answers[SECOND_PRINSONER] == ERROR_RES || answers[THIRD_PRISONER] == ERROR_RES) {
            std::cout << "Невозможно прочитать конфгурационный файл\n";
            return;
        }
        yearsUpdate(answers, i, stat, years, digitNames);
    }
    printing(years);
}
void Mode::Detailed() {
    std::vector <Strategies*> Prisoner = MakePrisoners(digitNames);
    if (Prisoner.size() < digitNames.size()) {
>>>>>>> Stashed changes
        std::cout << "Упс! Такой стартегии нет" << '\n';
    }
    if (MakeGameMatrix(matrixFile) == ERROR_RES)
        return;
    std::map <int, int> years;
    std::vector<std::string> stat;
<<<<<<< Updated upstream
    InitializationYearsAndStat(years, stat, names);
=======
    InitializationYearsAndStat(years, stat, digitNames);
>>>>>>> Stashed changes
    std::string s;
    std::cout << "Введите любой символ для начала симуляции, для выхода введите quit\n";
    std::cin >> s;
    int i = 1;
<<<<<<< Updated upstream
    while (s != "quit") {
=======
    while (s != KEY_WORD) {
>>>>>>> Stashed changes
        char answers[3];
        PrisonerAnswer(answers, diractory, Prisoner, stat);
        if (answers[0] == ERROR_RES || answers[1] == ERROR_RES || answers[2] == ERROR_RES) {
            std::cout << "Невозможно прочитать конфгурационный файл\n";
            return;
        }
<<<<<<< Updated upstream
        yearsUpdate(answers, i, stat, years, names);
=======
        yearsUpdate(answers, i, stat, years, digitNames);
>>>>>>> Stashed changes
        std::map<int, int> ::iterator it;
        int k = 0;
        std::cout << "Рейтинг: \n";
        for (it = years.begin(); it != years.end(); it++)
        {
            std::cout << "Стритегия " << strategies.find(it->first)->second << " \n       Принятое решение " << stat[i][k] << '\n';
            std::cout << "       Годы заключения: " << it->second << '\n';
            k++;
        }
        std::cout << "Введите любой символ для продолжения, для выхода введите quit\n";
        std::cin >> s;
        i++;
    }
    printing(years);
}
<<<<<<< Updated upstream
void Tournament(std::vector <int> names, std::string matrixFile, std::string diractory) {
    std::vector <Strategies*> Prisoner = MakePrisoners(names);
    if (Prisoner.size() < names.size()) {
=======
void Mode::Tournament() {
    std::vector <Strategies*> Prisoner = MakePrisoners(digitNames);
    if (Prisoner.size() < digitNames.size()) {
>>>>>>> Stashed changes
        std::cout << "Упс! Такой стартегии нет" << '\n';
    }
    if (MakeGameMatrix(matrixFile) == ERROR_RES)
        return;
    std::map <int, int> years;
<<<<<<< Updated upstream
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
=======
    for (int i = 0; i < digitNames.size(); i++) {
        years[digitNames[i]] = 0;
    }
    for (int i = 0; i < digitNames.size(); i++) {
        for (int j = i + 1; j < digitNames.size(); j++) {
            for (int k = j + 1; k < digitNames.size(); k++) {
                std::vector<std::string> stat;
                stat.push_back("");
                stat[0] += digitNames[FIRST_PRISONER];
                stat[0] += digitNames[SECOND_PRINSONER];
                stat[0] += digitNames[THIRD_PRISONER];
                for (int h = 0; h < NUMBER_OF_PRISONERS; h++) {
                    char answers[NUMBER_OF_PRISONERS];
>>>>>>> Stashed changes
                    PrisonerAnswer(answers, diractory, Prisoner, stat);
                    if (answers[FIRST_PRISONER] == ERROR_RES || answers[SECOND_PRINSONER] == ERROR_RES || answers[THIRD_PRISONER] == ERROR_RES) {
                        std::cout << "Невозможно прочитать конфгурационный файл\n";
                        return;
                    }
<<<<<<< Updated upstream
                    yearsUpdate(answers, i, stat, years, names);
=======
                    yearsUpdate(answers, i, stat, years, digitNames);
>>>>>>> Stashed changes
                }
            }
        }
    }
    printing(years);
}
