#pragma once
#include <SFML/Graphics.hpp>
class Settings
{
	sf::RenderWindow& window; // referencja do okna
	sf::Text* title; // wska�nik do tytu�u
	sf::Text options[3]; // tablica opcji ustawie�
	std::string nicknameInput = "Guest"; // nazwa u�ytkownika
	sf::Text nicknameText; // tekst do wy�wietlania nazwy u�ytkownika
	sf::Texture backgroundTexture; // tekstura t�a
	sf::Sprite backgroundSprite; // sprite t�a
	sf::RectangleShape nicknameInputBox; // prostok�t dla wprowadzania nazwy u�ytkownika
public:
	Settings(sf::RenderWindow& window, sf::Font& font);
	void setNickname(const std::string str);
	std::string& getNickname();
	void drawSettings();
	int getClickedIndex(sf::Vector2f mousePos);
	void drawInput();
};

