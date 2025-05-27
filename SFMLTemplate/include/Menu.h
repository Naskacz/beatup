#pragma once
#include <SFML/Graphics.hpp>
class Menu
{
	sf::RenderWindow& window; // referencja do okna
	sf::Text* title; // wskaünik do tytu≥u
	sf::Text options[6]; // tablica opcji menu
	sf::Sprite backgroundSprite; // sprite t≥a
	sf::Texture backgroundTexture; // tekstura t≥a
public:
	Menu(sf::Font& font, sf::RenderWindow& window);
	void drawMenu();
	int getClickedIndex(sf::Vector2f mousePos);
};

