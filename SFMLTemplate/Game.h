#pragma once
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "NoteManager.h"
#include "Player.h"
#include <SFML/Audio.hpp>
#include "Settings.h"
enum class GameState {
	Menu,
	Playing,
	MapCreator,
	Settings,
	Exit
};

class Game
{
	sf::Font font;
	Menu* menu;
	GameState state = GameState::Menu;
	sf::RenderWindow window;
	sf::Clock clock;
	const sf::Time timePerFrame = sf::seconds(1.f / 60.f);
	NoteManager noteManager;
	sf::Music music;
	std::string songFile;
	std::string beatmapFile;
	Settings* settings;
	sf::Text nicknameText;

	void processEvents();
	void update(sf::Time delta);
	void render();
	void beatmapFileChoice();
	void songFileChoice();
public:
	Game();
	void run();
};

