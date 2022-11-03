//#include "ObjectFactory.h"
#pragma once
class Strategies {
public:
	//virtual ~Strategies() {};
	virtual char makeDecision(std::vector<std::string>, int im) = 0;
};
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
		if (yearsMe >= yearsFirst || yearsMe >= yearsSecond ) {
			return 'C';
		}
		else return 'D';
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
