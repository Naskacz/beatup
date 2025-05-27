#pragma once
#include <SFML/Graphics.hpp>
class Settings
{
	sf::RenderWindow& window;
	sf::Text* title;
	sf::Text options[3];
	std::string nicknameInput = "Guest";
	sf::Text nicknameText;
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	sf::RectangleShape nicknameInputBox;
public:
	Settings(sf::RenderWindow& window, sf::Font& font);
	void setNickname(const std::string str);
	std::string& getNickname();
	void drawSettings();
	int getClickedIndex(sf::Vector2f mousePos);
	void drawInput();
};

