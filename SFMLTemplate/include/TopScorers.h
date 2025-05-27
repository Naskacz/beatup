#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "HttpClient.h"
class TopScorers
{
	sf::Text* title; // wskaŸnik do tytu³u
	sf::Text scores[10]; // tablica do przechowywania wyników
	sf::RenderWindow& window; // referencja do okna
public:
	TopScorers(sf::Font& font, sf::RenderWindow& win, const std::vector<Score>& topScores);
	void draw(sf::RenderWindow& window);
};

