#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

<<<<<<< Updated upstream
#define FIRST_PRISONER 0
#define SECOND_PRINSONER 1
#define THIRD_PRISONER 2
#define MATRIX_YEARS_1 4
#define MATRIX_YEARS_2 5
#define MATRIX_YEARS_3 6
#define MATRIX_LINES 8
#define MATRIX_ROWS 7
#define ERROR_RES 1

void Fast(std::vector <int>, int, std::string, std::string diractory);
void Detailed(std::vector <int>, std::string, std::string diractory);
void Tournament(std::vector <int>, std::string, std::string diractory);
bool isDigit(std::string);
int makeInt(std::string);
int MakeGameMatrix(std::string);
void yearsUpdate(char*, int, std::vector<std::string>&, std::map <int, int>&, std::vector <int>);


class Strategies {
public:
	//virtual ~Strategies() {};
	virtual char makeDecision(std::vector<std::string>, int im, std::string diractory) = 0;
};
std::vector <Strategies*> MakePrisoners(std::vector <int>);
class alwaysSayYes : public Strategies {
	char makeDecision(std::vector<std::string> x, int im, std::string diractory) {
		return 'C';
	}
};
class alwaysSayNo : public Strategies {
	char makeDecision(std::vector<std::string> x, int im, std::string diractory) {
		return 'D';
	}
};
class random : public Strategies {
	char makeDecision(std::vector<std::string> x, int im, std::string diractory) {
		int random_number = rand() % 2;
		if (random_number == 0) return 'C';
		else return 'D';
	}
};
class eyeForEye : public Strategies {
	char makeDecision(std::vector<std::string> x, int im, std::string diractory) {
		char answer;
		char ch;
		int i = 0;
		diractory += "\\EyeForEye.txt";
		std::ifstream f(diractory);
		while(i != 1) {
			try {
				f.exceptions(std::ifstream::failbit | std::ifstream::badbit);
				f >> ch;
				if (ch == '=') {
					f >> answer;
					i++;
				}
			}
			catch (const std::ios_base::failure& fail) {
				std::cout << fail.what() << '\n';
				return 1;
			}
		}
		f.close();
		if (x.size() == 1) {
			return answer;
		}
		int first, second;
		if (im == FIRST_PRISONER) { first = SECOND_PRINSONER; second = THIRD_PRISONER; }
		else if (im == SECOND_PRINSONER) { first = FIRST_PRISONER; second = THIRD_PRISONER; }
		else { first = FIRST_PRISONER; second = THIRD_PRISONER; }
		if (x[x.size() - 1][first] == 'C' || x[x.size() - 1][second] == 'C')
			return 'C';
		return 'D';
	}
};
class statistician : public Strategies {
	char makeDecision(std::vector<std::string> x, int im, std::string diractory) {
		const size_t numberOfAnswers = 3;
		char answer[numberOfAnswers];
		char ch;
		int i = 0;
		diractory += "\\Statistician.txt";
		std::ifstream f(diractory);
		while (i != numberOfAnswers) {
			try {
				f.exceptions(std::ifstream::failbit | std::ifstream::badbit);
				f >> ch;
				if (ch == '=') {
					f >> answer[i];
					i++;
				}
			}
			catch (const std::ios_base::failure& fail) {
				std::cout << fail.what() << '\n';
				return 1;
			}
		}
		f.close();
		if (x.size() == 1) {
			return answer[0];
		}
		int first, second;
		if (im == FIRST_PRISONER) { first = SECOND_PRINSONER; second = THIRD_PRISONER; }
		else if (im == SECOND_PRINSONER) { first = FIRST_PRISONER; second = THIRD_PRISONER; }
		else { first = FIRST_PRISONER; second = THIRD_PRISONER; }
		float probability1 = 0, probability2 = 0;
		float one = 1;
		for (int i = 0; i < x.size(); i++) {
			if (x[i][first] == answer[1])
				probability1 += one / x.size();
			if (x[i][second] == answer[1])
				probability2 += one / x.size();
		}
		float answer2 = answer[2] - '0';
		if (probability1 >= answer2 / 10 || probability2 >= answer2 / 10) {
			return 'C';
		}
		return 'D';
	}
};
class theEqualizer : public Strategies {
	char makeDecision(std::vector<std::string> x, int im, std::string diractory) {
		const size_t numberOfAnswers = 3;
		char answer[numberOfAnswers];
		char ch;
		int i = 0;
		diractory += "\\TheEqualizer.txt";
		std::ifstream f(diractory);
		int years[3];
		while (i != numberOfAnswers) {
			try {
				f.exceptions(std::ifstream::failbit | std::ifstream::badbit);
				f >> ch;
				std::string num;
				if (ch == '=') {
					f >> ch;
					while (isdigit(ch)) {
						num.push_back(ch);
						f >> ch;
					}
					years[i] = makeInt(num);
					i++;
				}
			}
			catch (const std::ios_base::failure& fail) {
				std::cout << fail.what() << '\n';
				return 1;
			}
		}
		f.close();
		if (x.size() == 1) {
			return 'C';
		}
		int first, second;
		if (im == FIRST_PRISONER) { first = SECOND_PRINSONER; second = THIRD_PRISONER; }
		else if (im == SECOND_PRINSONER) { first = FIRST_PRISONER; second = THIRD_PRISONER; }
		else { first = FIRST_PRISONER; second = THIRD_PRISONER; }
		extern int gameMatrix[MATRIX_LINES][MATRIX_ROWS];
		for (int j = 0; j < MATRIX_LINES; j++) {
			if (x[x.size() - 1][first] == gameMatrix[j][first] && x[x.size() - 1][second] == gameMatrix[j][second] && x[x.size() - 1][im] == gameMatrix[j][im - 1]) {
				years[first] += gameMatrix[j][first + 4];
				years[second] += gameMatrix[j][second + 4];
				years[im] += gameMatrix[j][im + 4];
				break;
			}
		}
		std::ofstream fout(diractory);
		fout << "yearsFirst=" << years[FIRST_PRISONER] << '\n';
		fout << "yearsSecond=" << years[SECOND_PRINSONER] << '\n';
		fout << "yearsThird=" << years[THIRD_PRISONER] << "_\n";

		fout.close();
		if (years[im] >= years[first] || years[im] >= years[second]) {
			return 'C';
		}
		else return 'D';
		return 'C';
	}
};
class ThePredictor : public Strategies {
	char makeDecision(std::vector<std::string> x, int im, std::string diractory){
		char answer;
		char ch;
		int i = 0;
		std::string diractory1 = diractory + "\\ThePredictor.txt";
		std::ifstream f(diractory1);
		while (i != 1) {
			try {
				f.exceptions(std::ifstream::failbit | std::ifstream::badbit);
				f >> ch;
				if (ch == '=') {
					f >> answer;
					i++;
				}
			}
			catch (const std::ios_base::failure& fail) {
				std::cout << fail.what() << '\n';
				return 1;
			}
		}
		f.close();
		std::vector<int> names;
		if (im == FIRST_PRISONER) { names.push_back(x[0][SECOND_PRINSONER]); names.push_back(x[0][THIRD_PRISONER]); }
		else if (im == SECOND_PRINSONER) { names.push_back(x[0][FIRST_PRISONER]); names.push_back(x[0][THIRD_PRISONER]); }
		else { names.push_back(x[0][FIRST_PRISONER]); names.push_back(x[0][SECOND_PRINSONER]); }
		names.push_back(answer - '0');
		std::vector <Strategies*> Prisoner = MakePrisoners(names);
		char answerFirst = (*Prisoner[FIRST_PRISONER]).makeDecision(x, FIRST_PRISONER, diractory);
		char answerSecond = (*Prisoner[SECOND_PRINSONER]).makeDecision(x, SECOND_PRINSONER, diractory);
		if (answerFirst == 'C' && answerSecond == 'C')
			return 'C';
		if (answerFirst == 'C' && answerSecond == 'D')
			return 'D';
		if (answerFirst == 'D' && answerSecond == 'C')
			return 'C';
		if (answerFirst == 'D' && answerSecond == 'D')
			return 'D';
		return 'C';
	}
};
class StrategiesFactory {
public:
	virtual Strategies* makeStrategies() = 0;
};
class alwaysSayYesFactory : public StrategiesFactory {
public:
	Strategies* makeStrategies() override {
		return new alwaysSayYes();
	}
};
class alwaysSayNoFactory : public StrategiesFactory {
public:
	Strategies* makeStrategies() {
		return new alwaysSayNo();
	}
};
class randomFactory : public StrategiesFactory {
public:
	Strategies* makeStrategies() {
		return new random();
	}
};
class eyeForEyeFactory : public StrategiesFactory {
public:
	Strategies* makeStrategies() {
		return new eyeForEye();
	}
};
class statisticianFactory : public StrategiesFactory {
public:
	Strategies* makeStrategies() {
		return new statistician();
	}
};
class theEqualizerFactory : public StrategiesFactory {
public:
	Strategies* makeStrategies() {
		return new theEqualizer();
	}
};
class thePredictorFactory : public StrategiesFactory {
public:
	Strategies* makeStrategies() {
		return new ThePredictor();
	}
};
=======
class Mode {
private:
	std::vector <int> digitNames;
	int steps;
	std::string matrixFile;
	std::string diractory;
public:
	Mode(std::vector <int>, int, std::string, std::string diractory);
	void Fast();
	void Detailed();
	void Tournament();
};

bool isDigit(std::string);
int makeInt(std::string);
int MakeGameMatrix(std::string);
void yearsUpdate(char*, int, std::vector<std::string>&, std::map <int, int>&, std::vector <int>);
>>>>>>> Stashed changes
