#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <iostream>
class Note
{
	sf::CircleShape circle; //g³ówne kó³ko
	sf::CircleShape ring; //pierœcieñ wokó³ kó³ka
	sf::Clock lifetimeClock; //zegar czasu ¿ycia nuty
	float Lifetime = 2.0f; //czas ¿ycia nuty
	float targetTime; //czas, kiedy nuta powinna byæ klikniêta idealnie
	float appearTime; //czas, kiedy nuta pojawia siê na ekranie
	float ringRadius; //promieñ pierœcienia
	float ringThickness; //gruboœæ pierœcienia
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

