#pragma once
#include "Note.h"
#include <vector>
#include "Beatmap.h"
#include <SFML/Graphics/Font.hpp>
struct FloatingText {
	sf::Text text;
	sf::Vector2f velocity;
	sf::Time lifetime;
};

class NoteManager
{
	std::vector<Note> notes;
	std::vector<Note> creatorNotes;
	Beatmap beatmap;
	int currentNoteIndex = 0;
	sf::Font font;
	sf::Text scoreText;
	int score = 0;
	int streak = 0;
	float streakMultiplier = 1;
	std::vector<FloatingText> floatingTexts;
	sf::Time lastUpdateTime = sf::Time::Zero;

public:
	NoteManager();
	void render(sf::RenderWindow& window, float currentTime);
	void loadBeatmap(const std::string& filename);
	void checkForClicks(sf::Vector2f mousePos, sf::Time songTime);
	void update(sf::Time songTime);
	void addNote(sf::Vector2f position, float time);
	void saveBeatmap(const std::string& filename, const std::string& songName);
	int getScore() const { return score; };
	void clearNotes();
	Beatmap& getBeatmap();
};

