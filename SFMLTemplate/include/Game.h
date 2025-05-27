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
	Menu* menu; // wska�nik do menu
	GameState state = GameState::Menu; // stan gry(domy�lnie menu
	sf::RenderWindow window; // okno gry
	// sf::Clock clock; // zegar do pomiaru czasu
	const sf::Time timePerFrame = sf::seconds(1.f / 60.f); // czas na klatk� (60 FPS)
	NoteManager noteManager; // mened�er nut
	sf::Music music; // obiekt muzyki
	std::string songFile; // �cie�ka do pliku z muzyk�
	std::string beatmapFile; // �cie�ka do pliku z beatmap� 
	sf::Text beatmapFileText; // tekst do wy�wietlania nazwy pliku beatmapy
	bool enteringBeatmapFile = false; // flaga do sprawdzania, czy wprowadzamy nazw� pliku beatmapy
	Settings* settings; // wska�nik do ustawie�
	sf::Text nicknameText; // tekst do wy�wietlania nazwy u�ytkownika
	std::string nicknameInput; // nazwa u�ytkownika
	bool enteringNickname = false; // flaga do sprawdzania, czy wprowadzamy nazw� u�ytkownika
	sf::Text nicknameInputText; // tekst do wy�wietlania wprowadzonej nazwy u�ytkownika
	sf::RectangleShape nicknameInputBox; // pole tekstowe dla wprowadzania nazwy u�ytkownika
	sf::Text scoreText; // tekst do wy�wietlania wyniku
	sf::Texture backgroundTexture; // tekstura t�a
	sf::Sprite backgroundSprite; // sprite t�a
	HttpClient httpClient; // klient HTTP do wysy�ania i pobierania wynik�w
	std::unique_ptr<TopScorers> topScorers = nullptr; // wska�nik do obiektu TopScorers

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

