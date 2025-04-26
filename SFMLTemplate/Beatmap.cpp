#include "Beatmap.h"
#include <fstream>
#include <sstream>

Beatmap::Beatmap(){}
bool Beatmap::loadFromFile(const std::string& filename) {
	std::ifstream file(filename);
	if (!file.is_open()) return false;

	float time, x, y;
	while (file >> time >> x >> y) notes.push_back({ time,x,y });

	return true;
}
const std::vector<NoteInfo>& Beatmap::getNotes() const {
	return notes;
}