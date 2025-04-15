#pragma once
#include <SFML/Graphics.hpp>
class Note
{
	sf::CircleShape circle;
public:
	Note(float X, float Y);
	void render(sf::RenderWindow& window);
	bool isClicked(sf::Vector2f mousePos);
};

