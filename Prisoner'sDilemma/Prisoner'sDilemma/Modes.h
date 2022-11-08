#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
void Fast(std::vector <int>, int, std::string);
void Detailed(std::vector <int>, std::string);
void Tournament(std::vector <int>, std::string);
class Strategies {
public:
	//virtual ~Strategies() {};
	virtual char makeDecision(std::vector<std::string>, int im) = 0;
};
std::vector <Strategies*> MakePrisoners(std::vector <int>);
class alwaysSayYes : public Strategies {
	char makeDecision(std::vector<std::string> x, int im) {
		return 'C';
	}
};
class alwaysSayNo : public Strategies {
	char makeDecision(std::vector<std::string> x, int im) {
		return 'D';
	}
};
class random : public Strategies {
	char makeDecision(std::vector<std::string> x, int im) {
		int random_number = rand() % 2;
		if (random_number == 0) return 'C';
		else return 'D';
	}
};
class eyeForEye : public Strategies {
	char makeDecision(std::vector<std::string> x, int im) {
		if (x.size() == 0) {
			return 'C';
		}
		int first, second;
		if (im == 1) { first = 1; second = 2; }
		else if (im == 2) { first = 0; second = 2; }
		else { first = 0; second = 1; }
		for (int i = 0; i < x.size(); i++) {
			if (x[i][first] == 'C' || x[i][second] == 'C')
				return 'C';
		}
		return 'D';
	}
};
class statistician : public Strategies {
	char makeDecision(std::vector<std::string> x, int im) {
		if (x.size() == 0) {
			return 'C';
		}
		int first, second;
		if (im == 1) { first = 1; second = 2; }
		else if (im == 2) { first = 0; second = 2; }
		else { first = 0; second = 1; }
		float probability1 = 0, probability2 = 0;
		for (int i = 0; i < x.size(); i++) {
			if (x[i][first] == 'C')
				probability1 += 1 / x.size();
			if (x[i][second] == 'C')
				probability2 += 1 / x.size();
		}
		if (probability1 >= 0.5 && probability2 >= 0.5) {
			return 'C';
		}
		return 'D';
	}
};
class theEqualizer : public Strategies {
	char makeDecision(std::vector<std::string> x, int im) {
		if (x.size() == 0) {
			return 'C';
		}
		int first, second;
		if (im == 1) { first = 1; second = 2; }
		else if (im == 2) { first = 0; second = 2; }
		else { first = 0; second = 1; }
		int yearsFirst = 0;
		int yearsSecond = 0;
		int yearsMe = 0;
		extern int gameMatrix[9][7];
		for (int i = 0; i < x.size(); i++) {
			for (int j = 1; j < 9; j++) {
				if (x[i][first] == gameMatrix[j][0] && x[i][second] == gameMatrix[j][1] && x[i][im - 1] == gameMatrix[j][2]) {
					yearsFirst += gameMatrix[j][4];
					yearsSecond += gameMatrix[j][5];
					yearsMe += gameMatrix[j][6];
					break;
				}
			}
		}
		if (yearsMe >= yearsFirst || yearsMe >= yearsSecond) {
			return 'C';
		}
		else return 'D';
		return 'C';
	}
};
class ThePredictor : public Strategies {
	char makeDecision(std::vector<std::string> x, int im){
	std::vector<int> names;
	if (im == 1) { names.push_back(x[0][1]); names.push_back(x[0][2]); }
	else if (im == 2) { names.push_back(x[0][0]); names.push_back(x[0][2]); }
	else { names.push_back(x[0][0]); names.push_back(x[0][1]); }
	names.push_back(2);
	std::vector <Strategies*> Prisoner = MakePrisoners(names);
	char answerFirst = (*Prisoner[0]).makeDecision(x, 1);
	char answerSecond = (*Prisoner[1]).makeDecision(x, 2);
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
/*std::vector <Strategies*> MakePrisoners(std::vector <int> names) {
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
/*char ThePredictor::makeDecision(std::vector<std::string> x, int im) {
	std::vector<int> names;
	if (im == 1) { names.push_back(x[0][1]); names.push_back(x[0][2]); }
	else if (im == 2) { names.push_back(x[0][0]); names.push_back(x[0][2]); }
	else { names.push_back(x[0][0]); names.push_back(x[0][1]); }
	names.push_back(2);
	std::vector <Strategies*> Prisoner = MakePrisoners(names);
	char answerFirst = (*Prisoner[0]).makeDecision(x, 1);
	char answerSecond = (*Prisoner[1]).makeDecision(x, 2);
	if (answerFirst == 'C' && answerSecond == 'C')
		return 'C';
	if (answerFirst == 'C' && answerSecond == 'D')
		return 'D';
	if (answerFirst == 'D' && answerSecond == 'C')
		return 'C';
	if (answerFirst == 'D' && answerSecond == 'D')
		return 'D';
	return 'C';
}*/