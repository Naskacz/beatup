#pragma once
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "NoteManager.h"
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
	sf::Font font; // czcionka
	Menu* menu; // wskaŸnik do menu
	GameState state = GameState::Menu; // stan gry(domyœlnie menu
	sf::RenderWindow window; // okno gry
	// sf::Clock clock; // zegar do pomiaru czasu
	const sf::Time timePerFrame = sf::seconds(1.f / 60.f); // czas na klatkê (60 FPS)
	NoteManager noteManager; // mened¿er nut
	sf::Music music; // obiekt muzyki
	std::string songFile; // œcie¿ka do pliku z muzyk¹
	std::string beatmapFile; // œcie¿ka do pliku z beatmap¹ 
	sf::Text beatmapFileText; // tekst do wyœwietlania nazwy pliku beatmapy
	bool enteringBeatmapFile = false; // flaga do sprawdzania, czy wprowadzamy nazwê pliku beatmapy
	Settings* settings; // wskaŸnik do ustawieñ
	sf::Text nicknameText; // tekst do wyœwietlania nazwy u¿ytkownika
	std::string nicknameInput; // nazwa u¿ytkownika
	bool enteringNickname = false; // flaga do sprawdzania, czy wprowadzamy nazwê u¿ytkownika
	sf::Text nicknameInputText; // tekst do wyœwietlania wprowadzonej nazwy u¿ytkownika
	sf::RectangleShape nicknameInputBox; // pole tekstowe dla wprowadzania nazwy u¿ytkownika
	sf::Text scoreText; // tekst do wyœwietlania wyniku
	sf::Texture backgroundTexture; // tekstura t³a
	sf::Sprite backgroundSprite; // sprite t³a
	HttpClient httpClient; // klient HTTP do wysy³ania i pobierania wyników
	std::unique_ptr<TopScorers> topScorers = nullptr; // wskaŸnik do obiektu TopScorers

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

