#include "TopScorers.h"

TopScorers::TopScorers(sf::Font& font,sf::RenderWindow& win, const std::vector<Score>& topScores): window(win){
	title = new sf::Text();
	title->setFont(font);
	title->setString("Top Scorers");
	title->setCharacterSize(40);
	title->setPosition(300, 50);
	title->setFillColor(sf::Color::White);
	title->setOutlineThickness(2);
	title->setOutlineColor(sf::Color::Black);
	for (int i = 0; i < 10 && i < topScores.size(); ++i) {
		scores[i].setFont(font);
		scores[i].setString(topScores[i].nickname + ": "+std::to_string(topScores[i].score));
		scores[i].setCharacterSize(30);
		scores[i].setPosition(100, 150 + i * 40);
		scores[i].setFillColor(sf::Color::Yellow);
		scores[i].setOutlineColor(sf::Color::Black);
		scores[i].setOutlineThickness(2);
	}
}
void TopScorers::draw(sf::RenderWindow& window) {
	window.clear();
	window.draw(*title);
	for (const auto& score : scores) window.draw(score);
}
