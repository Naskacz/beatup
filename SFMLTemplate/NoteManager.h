#pragma once
#include "Note.h"
#include <vector>

class NoteManager
{
	std::vector<Note> notes;
public:
	void render(sf::RenderWindow& window);
	void createNote();
	void checkForClicks(sf::Vector2f mousePos);
};

