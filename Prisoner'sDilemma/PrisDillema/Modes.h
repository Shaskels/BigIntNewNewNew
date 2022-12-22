#pragma once
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

const std::string FAST_MODE = "fast";
const std::string DETAILED_MODE = "detailed";
const std::string TOURNAMENT_MODE = "tournament";

class Mode {
public:
	virtual void StartWith(std::vector <int>, int, std::string, std::string diractory) = 0;
};
class Fast : public Mode{
	void StartWith(std::vector <int>, int, std::string, std::string diractory);
};
class Detailed : public Mode {
	void StartWith(std::vector <int>, int, std::string, std::string diractory);
};
class Tournament : public Mode {
	void StartWith(std::vector <int>, int, std::string, std::string diractory);
};
class ModeFactory {
public:
	virtual Mode* MakeMode() = 0;
	virtual std::string NameOfMode() = 0;
};
class FastFactory : public ModeFactory {
	Mode* MakeMode() {
		return new Fast();
	}
	std::string NameOfMode() {
		return FAST_MODE;
	}
};
class DetailedFactory : public ModeFactory {
	Mode* MakeMode() {
		return new Detailed();
	}
	std::string NameOfMode() {
		return DETAILED_MODE;
	}
};
class TournamentFactory : public ModeFactory {
	Mode* MakeMode() {
		return new Tournament();
	}
	std::string NameOfMode() {
		return TOURNAMENT_MODE;
	}
};
bool isDigit(std::string);
int makeInt(std::string);
int MakeGameMatrix(std::string);
void yearsUpdate(char*, int, std::vector<std::string>&, std::map <int, int>&, std::vector <int>);