#include "Menu.h"
Menu::Menu(sf::Font& font, sf::RenderWindow& win) :window(win) {
	title = new sf::Text();
	title->setFont(font);
	title->setString("BeatUp");
	title->setCharacterSize(60);
	title->setPosition(300, 100);
	title->setFillColor(sf::Color::Yellow);
	title->setOutlineThickness(5);
	title->setOutlineColor(sf::Color::Black);
	title->setLetterSpacing(1.5f);

	std::string texts[] = { "Start", "Choose map", "Map creator", "Exit" };
	for (int i = 0; i < 4; i++) {
		options[i].setFont(font);
		options[i].setString(texts[i]);
		options[i].setCharacterSize(30);
		options[i].setPosition(50, 250 + i * 40);
		options[i].setFillColor(sf::Color::Yellow);
		options[i].setOutlineColor(sf::Color::Black);
		options[i].setOutlineThickness(3);
	}
}

void Menu::drawMenu() {
	window.clear(sf::Color::Blue);
	window.draw(*title);
	for (const auto& option : options) window.draw(option);
}

int Menu::getClickedIndex(sf::Vector2f mousePos) {
	for (int i = 0; i < 4;i++) {
		if (options[i].getGlobalBounds().contains(mousePos))
			return i;
	}
	return -1;
}