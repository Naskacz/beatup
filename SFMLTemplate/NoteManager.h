#pragma once
#include "Note.h"
#include <vector>
#include "Beatmap.h"
#include <SFML/Graphics/Font.hpp>
class NoteManager
{
	std::vector<Note> notes;
	Beatmap beatmap;
	int currentNoteIndex = 0;
	sf::Font font;
	sf::Text wynikText;
	int wynik = 0;

public:
	NoteManager();
	void render(sf::RenderWindow& window, float currentTime);
	void loadBeatmap(const std::string& filename);
	void checkForClicks(sf::Vector2f mousePos);
	void update(sf::Time songTime);
	void addNote(sf::Vector2f position, float time);
	void saveBeatmap(const std::string& filename, const std::string& songName);
	Beatmap& getBeatmap();
};

