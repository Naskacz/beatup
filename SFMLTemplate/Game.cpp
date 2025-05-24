#include "Game.h"
#include "tinyfiledialogs.h"
#include <iostream>
#include <filesystem>
#include <vector>
int Note::counter = 0;

Game::Game() :window(sf::VideoMode(800, 600), "Beat Catcher") {
	if (!font.loadFromFile("arial.ttf")) {
		std::cout << "Nie udalo sie zaladowac czcionki" << std::endl;
		exit(1);
	}
	menu = new Menu(font, window);
	settings = new Settings(window, font);
	nicknameText.setFont(font);
	nicknameText.setString(settings->getNickname());
	nicknameText.setFillColor(sf::Color::White);
	nicknameText.setOutlineColor(sf::Color::Black);
	nicknameText.setOutlineThickness(2);
	nicknameText.setPosition(700, 0);
}
void Game::beatmapFileChoice() {
	std::filesystem::path folder = std::filesystem::current_path();
	if (!std::filesystem::exists(folder)) {
		std::cerr << "Folder nie istnieje: " << folder << "\n";
		return;
	}
	std::string fullPath = folder.string() + "\\beatmaps\\";
	beatmapFile = tinyfd_openFileDialog(
		"Wybierz plik z beatmap¹",
		fullPath.c_str(),
		0, nullptr, nullptr, 0);
	if (!beatmapFile.empty()) {
		std::filesystem::path path(beatmapFile);
		std::vector<std::string> parts;
		for (const auto& part : path)parts.push_back(part.string());
		std::string lastTwo = parts[parts.size() - 2] + "/" + parts[parts.size() - 1];
		beatmapFile = lastTwo;
	}
	else {
		std::cout << "cos poszlo nie tak"<<std::endl;
	}
}
void Game::songFileChoice() {
	std::filesystem::path folder = std::filesystem::current_path();
	if (!std::filesystem::exists(folder)) {
		std::cerr << "Folder nie istnieje: " << folder << "\n";
		return;
	}
	std::string fullPath = folder.string() + "\\songs\\";
	songFile = tinyfd_openFileDialog(
		"Wybierz plik z muzyk¹",
		fullPath.c_str(),
		0, nullptr, nullptr, 0);
	if (!songFile.empty()) {
		std::filesystem::path path(songFile);
		std::vector<std::string> parts;
		for (const auto& part : path)parts.push_back(part.string());
		std::string lastTwo = parts[parts.size() - 2] + "/" + parts[parts.size() - 1];
		songFile = lastTwo;
	}
	else {
		std::cout << "cos poszlo nie tak" << std::endl;
	}
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
				Note::counter = 0;
				if (beatmapFile.empty())beatmapFileChoice();
				noteManager.loadBeatmap(beatmapFile);
				songFile = noteManager.getBeatmap().getSongFile();
				if (!music.openFromFile(songFile)) {
					std::cout << "Nie udalo siê zaladowac muzyki" << std::endl;
					state = GameState::Menu;
				}
				sf::sleep(sf::seconds(1));
				music.play();
				return;
			}
			else if (choice == 1) {
				beatmapFileChoice();
				std::cout << beatmapFile << std::endl;
				state = GameState::Menu;
				return;
			}
			else if (choice == 2) {
				state = GameState::MapCreator;
				Note::counter = 0;
				songFileChoice();
				std::cout << std::endl;
				if (!music.openFromFile(songFile)) {
					std::cout << "Nie udalo sie zaladowac muzyki" << std::endl;
					state = GameState::Menu;
				}
				sf::sleep(sf::seconds(0.1f));
				music.play();
				return;
			}
			else if (choice == 3) {
				state = GameState::Settings;
				return;
			}
			else if (choice == 4) {
				window.close();
			}
		}
		// ======================= GAME STATE SETTINGS ========================
		if (state == GameState::Settings && event.type == sf::Event::MouseButtonPressed)
		{
			int choice = settings->getClickedIndex(mousePos);
			if (choice == 0) {
				std::string str;
				std::cin >> str;
				settings->setNickname(str);
				nicknameText.setString(settings->getNickname());
			}
			else if (choice == 2) {
				state = GameState::Menu;
			}
		}
		// ======================= GAME STATE PLAYING =========================
		if (state == GameState::Playing && event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				noteManager.checkForClicks(mousePos, music.getPlayingOffset());
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
				std::cin >> beatmapFile;
				std::cout << std::endl;
				noteManager.saveBeatmap("beatmaps\\"+beatmapFile+".txt", songFile);
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

	}
	if (state == GameState::Menu) {
	
	}
	if (state == GameState::Settings) {

	}
}

void Game::render() {
	window.clear();

	if (state == GameState::Menu) menu->drawMenu();
	else if (state == GameState::Playing) {
		window.clear(sf::Color::Yellow);
		noteManager.render(window, music.getPlayingOffset().asSeconds());
	}
	else if (state == GameState::MapCreator) {
		noteManager.render(window, music.getPlayingOffset().asSeconds());

	}
	else if (state == GameState::Settings) {
		settings->drawSettings();
	}
	window.draw(nicknameText);
	window.display();
}