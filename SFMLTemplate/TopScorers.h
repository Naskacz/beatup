#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "HttpClient.h"
class TopScorers
{
	sf::Text* title;
	sf::Text scores[10];
	sf::RenderWindow& window;
public:
	TopScorers(sf::Font& font, sf::RenderWindow& win, const std::vector<Score>& topScores);
	void draw(sf::RenderWindow& window);
};

