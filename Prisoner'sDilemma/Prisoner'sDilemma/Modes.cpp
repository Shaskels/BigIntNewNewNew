
#include "Modes.h"
int gameMatrix[9][7] = { 0 };
std::map<int, std::string> strategies = { {1,"AlwaysSayYes"},{2,"AlwaysSayNo"},{3,"Random"},{4,"EyeForEye"},{5,"Statistician"}, {6,"TheEqualizer"}, {7,"ThePredictor"} };
/*enum strategies {
    AlwaysSayYes,
    AlwaysSayNo,
    Random,
    EyeForEye,
    Statistician,
    TheEqualizer,
    ThePredictor
};*/
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
int MakeGameMatrix(std::string matrixFile) {
    std::ifstream f(matrixFile);
    if (!f)
    {
        std::cout << "������������ ��� �����\n";
        return 1;
    }
    std::string c;
    for (int i = 0; i < 6; i++) {
        try {
            f.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            f >> c;
        }
        catch (const std::ios_base::failure& fail) {
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
                std::cout << "������������ ������ �������\n";
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
    if (MakeGameMatrix(matrixFile) == 1)
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
        char answerFirst = (*Prisoner[0]).makeDecision(x, 1);
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
        std::cout << "����� " << place << ": " << it->first << " ��� ����������, ��������� " << strategies.find(it->second)->second << '\n';
        place++;
    }
}
void Detailed(std::vector <int> names, std::string matrixFile) {
    std::vector <Strategies*> Prisoner = MakePrisoners(names);
    if (MakeGameMatrix(matrixFile) == 1)
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
    std::string s;
    std::cout << "������� ����� ������ ��� ������ ���������, ��� ������ ������� quit";
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
        std::cout << "�������: \n";
        for (it = years.begin(); it != years.end(); it++)
        {
            std::cout << "��������� " << strategies.find(it->first)->second << " \n       �������� ������� " << x[i][k] << '\n';
            if (i == 1)
                std::cout << "       ���� ����������: " << it->second << '\n';
            else
                std::cout << "       ���� ����������: " << it->second - gameMatrix[j][k + 4] << " + " << gameMatrix[j][k + 4] << '\n';
            k++;
        }
        // system("pause");
       //  getline(std::cin, s);
        std::cout << "������� ����� ������ ��� �����������, ��� ������ ������� quit";
        std::cin >> s;
        i++;
    }
    std::multimap<int, int> reverseYears = flip_map(years);
    std::map<int, int> ::iterator it;
    int place = 1;
    for (it = reverseYears.begin(); it != reverseYears.end(); it++)
    {
        std::cout << "����� " << place << ": " << it->first << " ��� ����������, ��������� " << strategies.find(it->second)->second << '\n';
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
                x.push_back("");
                x[0] += names[0];
                x[0] += names[1];
                x[0] += names[2];
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
        std::cout << "����� " << place << ": " << it->first << " ��� ����������, ��������� " << strategies.find(it->second)->second << '\n';
        place++;
    }
}
