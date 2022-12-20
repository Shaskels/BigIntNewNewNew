// PrisDillema.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "Modes.h"
#include "Input.h"
#include "Factory.h"

const int NUMBER_OF_MODES = 3;

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
	std::vector<ModeFactory*> factory;
	factory.push_back(new FastFactory);
	factory.push_back(new DetailedFactory);
	factory.push_back(new TournamentFactory);
	for (int i = 0; i < NUMBER_OF_MODES; i++) {
		if (factory[i]->NameOfMode() == in.mode) {
			Mode* m = factory[i]->MakeMode();
			m->StartWith(digitNames, in.steps, in.matrixFile, in.directory);
			return 0;
		}
	}
	std::cout << "Неправильное название режима";
	return 0;
}