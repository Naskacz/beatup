#pragma once
#include "Note.h"
#include <vector>
#include "Beatmap.h"

class NoteManager
{
	std::vector<Note> notes;
	Beatmap beatmap;
	int currentNoteIndex = 0;

public:
	void render(sf::RenderWindow& window);
	void loadBeatmap(const std::string& filename);
	void createNote();
	void checkForClicks(sf::Vector2f mousePos);
	void update(sf::Time songTime);
};

