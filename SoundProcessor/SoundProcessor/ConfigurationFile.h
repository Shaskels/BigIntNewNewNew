#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "Errors.h"
class ConfigurationFile {
public:
	std::vector<std::string> Converters;
	std::vector<int> Times;
	std::vector<int> Links;

	int getConfigs(std::string);
};
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
		t = (s[i] - '0') + t * 10;
	}
	return t;
}
int getConfigs(std::string file, ConfigurationFile& conf) {
	Errors r;
	std::ifstream f(file, std::ios_base::in);
	if (!f) {
		std::cerr << r.errors[21] << std::endl;
	}
	std::string str;
	std::string c;
	int i = 0;
	f >> c;
	while (c != "!") {
		try {
			f.exceptions(std::ifstream::failbit | std::ifstream::badbit);
			if (c == "#")
				getline(f, str, '\n');
			else {
				if (isDigit(c))
					conf.Times.push_back(makeInt(c));
				else if (c[0] == '$') {
					c[0] = '0';
					conf.Links.push_back(makeInt(c));
				}
				else {
					conf.Converters.push_back(c);
				}
			}
			f >> c;
		}
		catch (const std::ios_base::failure& fail) {
			std::cerr << fail.what() << '\n';
			return ERROR_VALUE;
		}
	}
	return SUCCESS;
}