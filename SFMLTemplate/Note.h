#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <iostream>
class Note
{
	sf::CircleShape circle;
	sf::CircleShape ring;
	sf::Clock lifetimeClock;
	sf::Clock countdownClock;
	float Lifetime = 2.0f;
	int countdown = Lifetime;
	float targetTime;
	float appearTime;
	float ringRadius;
	float ringThickness;
public:
	static int counter;
	Note(float X, float Y, float targetTime);
	void render(sf::RenderWindow& window, float currentTime);
	bool isClicked(sf::Vector2f mousePos);
	bool isExpired() const;
	bool isReadyToClick() const;
	void update(float currentTime);
	float getX() const { return circle.getPosition().x; }
	float getY() const { return circle.getPosition().y; }
	float getTime() const { return targetTime; }
	static int getCounter() { return counter; }
};

