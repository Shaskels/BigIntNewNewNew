#pragma once
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

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