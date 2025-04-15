#include "Menu.h"
Menu::Menu(sf::Font& font, sf::RenderWindow& win) :window(win) {
	title = new sf::Text();
	title->setFont(font);
	title->setString("BeatUp");
	title->setCharacterSize(50);
	title->setPosition(200, 100);
	title->setFillColor(sf::Color::White);

	std::string texts[] = { "Start", "Exit"};
	for (int i = 0; i < 2; i++) {
		options[i].setFont(font);
		options[i].setString(texts[i]);
		options[i].setCharacterSize(30);
		options[i].setPosition(300, 250 + i * 60);
		options[i].setFillColor(sf::Color::White);
	}
}

void Menu::drawMenu() {
	window.draw(*title);
	for (const auto& option : options) window.draw(option);
}

int Menu::getClickedIndex(sf::Vector2f mousePos) {
	for (int i = 0; i < 2;i++) {
		if (options[i].getGlobalBounds().contains(mousePos))
			return i;
	}
	return -1;
}