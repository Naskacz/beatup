#include "Settings.h"

Settings::Settings(sf::RenderWindow& window, sf::Font& font):window(window) {
	title = new sf::Text();
	title->setFont(font);
	title->setString("Settings");
	title->setCharacterSize(30);
	title->setFillColor(sf::Color::White);
	title->setPosition(100, 100);
	std::string texts[] = { "Nickname", "Audio", "Exit"};
	for (int i = 0; i < 3; i++) {
		options[i].setFont(font);
		options[i].setString(texts[i]);
		options[i].setCharacterSize(30);
		options[i].setPosition(50, 250 + i * 40);
		options[i].setFillColor(sf::Color::Yellow);
		options[i].setOutlineColor(sf::Color::Black);
		options[i].setOutlineThickness(3);
	}
}

void Settings::setNickname(const std::string str) {
	nicknameInput = str;
}
std::string& Settings::getNickname() {
	return nicknameInput;
}

void Settings::drawSettings() {
	window.clear(sf::Color::Blue);
	window.draw(*title);
	for (const auto& option : options) window.draw(option);
}
int Settings::getClickedIndex(sf::Vector2f mousePos) {
	for (int i = 0; i < 3; i++) {
		if (options[i].getGlobalBounds().contains(mousePos))
			return i;
	}
	return -1;
}