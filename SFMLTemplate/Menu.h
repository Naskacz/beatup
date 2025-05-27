#pragma once
#include <SFML/Graphics.hpp>
class Menu
{
	sf::RenderWindow& window;
	sf::Text* title;
	sf::Text options[6];
	sf::Sprite backgroundSprite;
	sf::Texture backgroundTexture;
public:
	Menu(sf::Font& font, sf::RenderWindow& window);
	void drawMenu();
	int getClickedIndex(sf::Vector2f mousePos);
};

