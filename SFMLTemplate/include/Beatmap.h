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
	std::vector<NoteInfo> notes; // wektor nut
	std::string songFile; // nazwa pliku z muzyk¹
public:
	Beatmap();
	bool loadFromFile(const std::string& filename);
	const std::vector<NoteInfo>& getNotes() const {return notes;}
	void clearNotes() { notes.clear(); }
	const std::string& getSongFile() const {return songFile;}
};

