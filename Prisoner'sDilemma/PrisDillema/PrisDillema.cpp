// PrisDillema.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "Modes.h"
#include "Input.h"
#include "Factory.h"

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "RUSSIAN");
	ip::Input in;
	if (in.GetProgramOptions(argc, argv, in) == ERROR_RES)
		return 0;
	int i;

	if ((in.names).size() < NUMBER_OF_PRISONERS) {
			std::cout << "Неправильное количество стратегий";
		return 0;
	}
	std::vector<int> digitNames;
	for (i = 0; i < (in.names).size(); i++) {
		if ((in.namesStrategies).find((in.names[i])) == (in.namesStrategies).end()) {
			std::cout << "Такой стратегии нет(";
			return 0;
		}
		else digitNames.push_back(in.namesStrategies[in.names[i]]);
	}

	if (in.mode == FAST_MODE) {
		Mode mode = Mode(digitNames, in.steps, in.matrixFile, in.directory);
		mode.Fast();
	}
	else if (in.mode == DETAILED_MODE) {
		Mode mode = Mode(digitNames, in.steps, in.matrixFile, in.directory);
		mode.Detailed();
	}
	else if (in.mode == TOURNAMENT_MODE) {
		Mode mode = Mode(digitNames, in.steps, in.matrixFile, in.directory);
		mode.Tournament();
	}
	else {
		std::cout << "Неправильное название режима";
		return 0;
	}
	return 0;
}