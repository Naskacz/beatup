#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <iostream>
class Note
{
	sf::CircleShape circle;
	sf::Clock lifetimeClock;
	sf::Clock countdownClock;
	float Lifetime = 3.0f;
	int countdown = Lifetime;
public:
	Note(float X, float Y);
	void render(sf::RenderWindow& window);
	bool isClicked(sf::Vector2f mousePos);
	bool isExpired() const;
	bool isReadyToClick() const;
	void update();
};

