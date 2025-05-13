#include "Game.h"
#include <iostream>
Game::Game() :window(sf::VideoMode(800, 600), "Beat Catcher") {
	if (!font.loadFromFile("arial.ttf")) {
		std::cout << "Nie udalo sie zaladowac czcionki" << std::endl;
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
		auto mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
		// ======================= GAME STATE MENU =========================
		if (state == GameState::Menu && event.type == sf::Event::MouseButtonPressed) {
			int choice = menu->getClickedIndex(mousePos);
			if (choice == 0) {
				state = GameState::Playing;
				noteManager.loadBeatmap(beatmapName + "txt");
				songName = noteManager.getBeatmap().getSongName();
				if (!music.openFromFile(songName)) {
					std::cout << "Nie udalo siê zaladowac muzyki" << std::endl;
				}
				music.play();
				return;
			}
			else if (choice == 1) {
				std::cout << "Wybierz mape: ";
				std::cin >> beatmapName;
				std::cout << std::endl;
				state = GameState::Menu;
			}
			else if (choice == 2) {
				state = GameState::MapCreator;
				std::cout << "Wybierz plik z muzyka: ";
				std::cin >> songName;
				std::cout << std::endl;
				if (!music.openFromFile(songName)) {
					std::cout << "Nie udalo sie zaladowac muzyki" << std::endl;
					exit(1);
				}
				music.play();
				return;
			}
			else if (choice == 3) {
				window.close();
			}
		}
		// ======================= GAME STATE PLAYING =========================
		if (state == GameState::Playing && event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				noteManager.checkForClicks(mousePos);
			}
		}
		// PLAYING/MAPCREATOR TO MENU
		if ((state == GameState::Playing || state == GameState::MapCreator) && event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Escape) {
				state = GameState::Menu;
				music.stop();
			}
		}
		// ======================= GAME STATE MAP CREATOR =========================
		if (state == GameState::MapCreator && event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				float currentTime = music.getPlayingOffset().asSeconds();
				noteManager.addNote(mousePos, currentTime);
			}
		}
		// MAP CREATOR SAVE AND TO MENU
		if (state == GameState::MapCreator && event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Enter) {
				music.stop();
				std::cout << "Zapisz mape jako: ";
				std::cin >> beatmapName;
				std::cout << std::endl;
				noteManager.saveBeatmap(beatmapName + "txt", songName);
				state = GameState::Menu;
			}
		}
	}
}
void Game::update(sf::Time) {
	if (state == GameState::Playing) {
		noteManager.update(music.getPlayingOffset());
	}
	if (state == GameState::MapCreator) {
		/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			state = GameState::Menu;
		}*/
	}
	if (state == GameState::Menu) {
		menu->drawMenu();
	}
}

void Game::render() {
	window.clear();

	if (state == GameState::Menu) menu->drawMenu();
	else if (state == GameState::Playing) noteManager.render(window, music.getPlayingOffset().asSeconds());
	else if (state == GameState::MapCreator) noteManager.render(window, music.getPlayingOffset().asSeconds());
	window.display();
}