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
	std::vector<Note> notes; // wektor nut
	std::vector<Note> creatorNotes; // wektor nut dla kreatora map
	Beatmap beatmap; // obiekt beatmapy
	int currentNoteIndex = 0; // indeks aktualnej nuty
	sf::Font font; // czcionka do wyœwietlania tekstu
	sf::Text scoreText; // tekst do wyœwietlania wyniku
	int score = 0; // aktualny wynik 
	int streak = 0; // licznik serii
	float streakMultiplier = 1; // mno¿nik serii
	std::vector<FloatingText> floatingTexts; // wektor floatingTexts
	sf::Time lastUpdateTime = sf::Time::Zero; // czas ostatniej aktualizacji

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

