#pragma once
#include <vector>
#include <tuple>
#include <string>
struct NoteInfo {
	float x;
	float y;
	float time;
};

class Beatmap
{
	std::vector<NoteInfo> notes;
	std::string songFile;
public:
	Beatmap();
	bool loadFromFile(const std::string& filename);
	const std::vector<NoteInfo>& getNotes() const {return notes;}
	const std::string& getSongFile() const {return songFile;}
};

