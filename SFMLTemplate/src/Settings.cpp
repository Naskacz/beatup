#include "Settings.h"
#include "iostream"
Settings::Settings(sf::RenderWindow& window, sf::Font& font):window(window) {
	title = new sf::Text();
	title->setFont(font);
	title->setString("Settings");
	title->setCharacterSize(60);
	title->setFillColor(sf::Color::White);
	title->setOutlineThickness(5);
	title->setOutlineColor(sf::Color::Black);
	title->setPosition(300, 100);
	title->setLetterSpacing(1.5f);

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
	if (!backgroundTexture.loadFromFile("images\\backgroundMenu.png")) {
		std::cerr << "Can't load background texture" << std::endl;
	}
	backgroundSprite.setScale((float)window.getSize().x / backgroundTexture.getSize().x, (float)window.getSize().y / backgroundTexture.getSize().y);
	backgroundSprite.setTexture(backgroundTexture);

	nicknameInputBox.setSize(sf::Vector2f(200, 40));
	nicknameInputBox.setFillColor(sf::Color::White);
	nicknameInputBox.setOutlineColor(sf::Color::Black);
	nicknameInputBox.setOutlineThickness(2);
	nicknameInputBox.setPosition(50, 205);

	nicknameText.setFont(font);
	nicknameText.setCharacterSize(30);
	nicknameText.setString(nicknameInput);
	nicknameText.setFillColor(sf::Color::Black);
	sf::FloatRect bounds = nicknameText.getLocalBounds();
	nicknameText.setOrigin(bounds.left, bounds.top);
	nicknameText.setPosition(nicknameInputBox.getPosition().x + 5.f, nicknameInputBox.getPosition().y + (nicknameInputBox.getSize().y - bounds.height) / 2.f - 5.f);
}

void Settings::setNickname(const std::string str) {
	nicknameInput = str;
	nicknameText.setString(nicknameInput);
}
std::string& Settings::getNickname() {
	return nicknameInput;
}

void Settings::drawSettings() {
	window.draw(backgroundSprite);
	window.draw(*title);
	for (const auto& option : options) window.draw(option);
}
void Settings::drawInput() {
	window.draw(nicknameInputBox);
	window.draw(nicknameText);
}
int Settings::getClickedIndex(sf::Vector2f mousePos) {
	for (int i = 0; i < 3; i++) {
		if (options[i].getGlobalBounds().contains(mousePos))
			return i;
	}
	return -1;
}