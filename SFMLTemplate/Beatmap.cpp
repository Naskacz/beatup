#include "Beatmap.h"
#include <fstream>
#include <sstream>
#include <iostream>
Beatmap::Beatmap(){}
bool Beatmap::loadFromFile(const std::string& filename) {
	std::cout << filename << std::endl;
	notes.clear();
	std::ifstream file(filename);
	if (!file.is_open()) return false;

	std::getline(file, songFile);
	float time, x, y;
	while (file >> time >> x >> y)
	{
		notes.push_back({ x,y,time });
	}

	return true;
}
