#pragma once
#include <SFML/Graphics.hpp>
class Settings
{
	sf::RenderWindow& window; // referencja do okna
	sf::Text* title; // wskaŸnik do tytu³u
	sf::Text options[3]; // tablica opcji ustawieñ
	std::string nicknameInput = "Guest"; // nazwa u¿ytkownika
	sf::Text nicknameText; // tekst do wyœwietlania nazwy u¿ytkownika
	sf::Texture backgroundTexture; // tekstura t³a
	sf::Sprite backgroundSprite; // sprite t³a
	sf::RectangleShape nicknameInputBox; // prostok¹t dla wprowadzania nazwy u¿ytkownika
public:
	Settings(sf::RenderWindow& window, sf::Font& font);
	void setNickname(const std::string str);
	std::string& getNickname();
	void drawSettings();
	int getClickedIndex(sf::Vector2f mousePos);
	void drawInput();
};

