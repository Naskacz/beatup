#pragma once
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "NoteManager.h"
#include "Player.h"
#include <SFML/Audio.hpp>
#include "Settings.h"
#include "HttpClient.h"
#include <memory>
#include "TopScorers.h"


enum class GameState {
	Menu,
	Playing,
	MapCreator,
	Settings,
	Scoreboard,
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
	sf::Text beatmapFileText;
	bool enteringBeatmapFile = false;
	Settings* settings;
	sf::Text nicknameText;
	std::string nicknameInput;
	bool enteringNickname = false;
    sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	HttpClient httpClient;
	std::unique_ptr<TopScorers> topScorers = nullptr;

	void processEvents();
	void update(sf::Time delta);
	void render();
	void beatmapFileChoice();
	void songFileChoice();

public:
	Game();
	~Game();
	void run();
};

