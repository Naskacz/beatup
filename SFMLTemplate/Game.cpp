#include "Game.h"
#include <iostream>
Game::Game():window(sf::VideoMode(800,600), "Beat Catcher"){
	if (!font.loadFromFile("arial.ttf")) {
		std::cout << "Nie uda³o siê za³adowaæ czcionki" << std::endl;
		exit(1);
	}
	menu = new Menu(font, window);
}

void Game::run() {
	while (window.isOpen()) {
		processEvents();
		update(timePerFrame);
		render();
		sf::sleep(timePerFrame);
	}
}

void Game::processEvents() {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			window.close();

		if (state == GameState::Menu && event.type == sf::Event::MouseButtonPressed) {
			auto mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
			int choice = menu->getClickedIndex(mousePos);
			if (choice == 0) {
				state = GameState::Playing;
			}
			else if (choice == 1) {
				window.close();
			}
		}
	}
	
}
void Game::update(sf::Time) {
	if (state == GameState::Playing) {
		if (clock.getElapsedTime().asSeconds() > 1.f) {
			noteManager.createNote();
			clock.restart();
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			auto mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
			noteManager.checkForClicks(mousePos);
		}
	}
}
void Game::render() {
	window.clear();

	if (state == GameState::Menu) menu->drawMenu();
	else if (state == GameState::Playing) noteManager.render(window);
	window.display();
}