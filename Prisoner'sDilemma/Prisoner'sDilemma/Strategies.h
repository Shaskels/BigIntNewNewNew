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
		if (im == 1) { first = 2; second = 3; }
		else if (im == 2) { first = 1; second = 3; }
		else { first = 1; second = 2; }
		for (int i = 0; i < x.size(); i++) {
			if (x[i][first] == 'D' || x[i][second] == 'D')
				return 'D';
		}
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
