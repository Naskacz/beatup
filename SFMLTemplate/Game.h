#pragma once
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "NoteManager.h"
enum class GameState {
	Menu,
	Playing,
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

	void processEvents();
	void update(sf::Time delta);
	void render();
public:
	Game();
	void run();
};

