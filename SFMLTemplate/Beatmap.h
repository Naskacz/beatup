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
public:
	Beatmap();
	bool loadFromFile(const std::string& filename);
	const std::vector<NoteInfo>& getNotes() const;
};

