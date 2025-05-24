#include "Menu.h"
#include "iostream"
Menu::Menu(sf::Font& font, sf::RenderWindow& win) :window(win) {
	title = new sf::Text();
	title->setFont(font);
	title->setString("BeatUp");
	title->setCharacterSize(60);
	title->setPosition(300, 100);
	title->setFillColor(sf::Color::White);
	title->setOutlineThickness(5);
	title->setOutlineColor(sf::Color::Black);
	title->setLetterSpacing(1.5f);

	std::string texts[] = { "Start", "Choose map", "Map creator", "Settings", "Exit"};
	for (int i = 0; i < 5; i++) {
		options[i].setFont(font);
		options[i].setString(texts[i]);
		options[i].setCharacterSize(30);
		options[i].setPosition(50, 250 + i * 40);
		options[i].setFillColor(sf::Color::Yellow);
		options[i].setOutlineColor(sf::Color::Black);
		options[i].setOutlineThickness(3);
	}
	if (!backgroundTexture.loadFromFile("backgroundMenu.png")) {
		std::cerr << "Can't load background texture" << std::endl;
	}
	backgroundSprite.setScale((float)window.getSize().x/backgroundTexture.getSize().x, (float)window.getSize().y/backgroundTexture.getSize().y);
	backgroundSprite.setTexture(backgroundTexture);
}

void Menu::drawMenu() {
	window.clear();
	window.draw(backgroundSprite);
	window.draw(*title);
	for (const auto& option : options) window.draw(option);
}

int Menu::getClickedIndex(sf::Vector2f mousePos) {
	for (int i = 0; i < 5;i++) {
		if (options[i].getGlobalBounds().contains(mousePos))
			return i;
	}
	return -1;
}