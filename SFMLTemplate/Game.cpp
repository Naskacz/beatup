#include "Game.h"
#include "tinyfiledialogs.h"
#include <iostream>
#include <filesystem>
#include <vector>
#include <cpr/cpr.h>
#include <pqxx/pqxx>
#include <crow.h>

int Note::counter = 0;
Game::~Game() {
	delete menu;
	delete settings;
	if (topScorers) {
		topScorers.reset();
	}
}
Game::Game() :window(sf::VideoMode(800, 600), "BeatUp") {
	if (!font.loadFromFile("arial.ttf")) {
		std::cout << "Nie udalo sie zaladowac czcionki" << std::endl;
		exit(1);
	}	
	menu = new Menu(font, window);
	settings = new Settings(window, font);
	nicknameText.setFont(font);
	nicknameText.setCharacterSize(30);
	nicknameText.setString(settings->getNickname());
	nicknameText.setFillColor(sf::Color::White);
	nicknameText.setOutlineColor(sf::Color::Black);
	nicknameText.setOutlineThickness(2);
	sf::FloatRect bounds = nicknameText.getLocalBounds();
	nicknameText.setPosition(790 - bounds.width, 10);
	if (!backgroundTexture.loadFromFile("backgroundGame.png")) {
		std::cerr << "Nie mozna zaladowac tekstury tla" << std::endl;
	}
	backgroundSprite.setScale((float)window.getSize().x / backgroundTexture.getSize().x, (float)window.getSize().y / backgroundTexture.getSize().y);
	backgroundSprite.setTexture(backgroundTexture);

	beatmapFileText.setFont(font);
	beatmapFileText.setCharacterSize(30);
	beatmapFileText.setPosition(200, 200);
	beatmapFileText.setFillColor(sf::Color::White);

	window.setKeyRepeatEnabled(true);
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
				noteManager.clearNotes();
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
				noteManager.clearNotes();
				beatmapFileChoice();
				std::cout << beatmapFile << std::endl;
				state = GameState::Menu;
				return;
			}
			else if (choice == 2) {
				state = GameState::MapCreator;
				noteManager.clearNotes();
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
				enteringNickname = true;
				nicknameInput.clear();
			}
			else if (choice == 2) {
				state = GameState::Menu;
			}
		}
		if (state == GameState::Settings && enteringNickname) {
			if (event.type == sf::Event::TextEntered) {
				if (event.text.unicode == 8) { // Backspace
					if (!nicknameInput.empty()) nicknameInput.pop_back();
				}
				else if (event.text.unicode >= 32 && event.text.unicode < 127) { // Printable characters
					nicknameInput += static_cast<char>(event.text.unicode);
					std::cout << nicknameInput << std::endl;
				}
				settings->setNickname(nicknameInput);
				//nicknameText.setString(nicknameInput);
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
				if (!nicknameInput.empty()) {
					settings->setNickname(nicknameInput);
					nicknameText.setString(settings->getNickname());
					sf::FloatRect bounds = nicknameText.getLocalBounds();
					nicknameText.setPosition(790 - bounds.width, 10);
					enteringNickname = false;
					state = GameState::Menu;
				}
			}
		}
				
		// ======================= GAME STATE PLAYING =========================
		if (state == GameState::Playing && (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::KeyPressed)) {
			if (event.mouseButton.button == sf::Mouse::Left || event.key.code == sf::Keyboard::Z || event.key.code == sf::Keyboard::X) {
				noteManager.checkForClicks(mousePos, music.getPlayingOffset());
			}
		}
		// PLAYING/MAPCREATOR TO MENU
		if ((state == GameState::Playing || state == GameState::MapCreator) && event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Escape) {
				state = GameState::Menu;
				music.stop();
				enteringBeatmapFile = false;
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
		if (state == GameState::MapCreator) {
			std::cout << beatmapFile << std::endl;
			if (!enteringBeatmapFile && (
				music.getStatus() == sf::SoundSource::Status::Stopped ||
				(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter))) {
				enteringBeatmapFile = true;
				music.stop();
				beatmapFile.clear();
				beatmapFileText.setString("Zapisz mape jako: ");
			}
			if (event.type == sf::Event::TextEntered && enteringBeatmapFile) {
				std::cout << "TextEntered: " << event.text.unicode << std::endl;
				if (event.text.unicode == 8) {
					if (!beatmapFile.empty()) beatmapFile.pop_back();
				}
				else if (event.text.unicode >= 32 && event.text.unicode < 127) {
					beatmapFile += static_cast<char>(event.text.unicode);
				}
				beatmapFileText.setString("Zapisz mape jako: " + beatmapFile);
				continue; 
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
				// TUTAJ by³ problem — upewniamy siê, ¿e Enter dzia³a
				if (!beatmapFile.empty()) {
					noteManager.saveBeatmap("beatmaps\\" + beatmapFile + ".txt", songFile);
					enteringBeatmapFile = false;
					state = GameState::Menu;
				}
			}
				
		}
		// ========================= GAME STATE SCOREBOARD =========================
		if (event.type == sf::Event::KeyPressed && state==GameState::Scoreboard) {
			state = GameState::Menu;
		}
	}
}
void Game::update(sf::Time) {
	if (state == GameState::Playing) {
		noteManager.update(music.getPlayingOffset());
		if (music.getStatus() == sf::SoundSource::Status::Stopped) {
			std::string filenameSongFile = std::filesystem::path(songFile).filename().string();
			Score s{
				settings->getNickname(),
				noteManager.getScore(),
				filenameSongFile
			};
			std::string resp;
			/*std::cout << "{\"nickname\":\"" << s.nickname << "\",\"score\":" << s.score << ",\"song\":\"" << s.song << "\"}" << std::endl;*/
			if (httpClient.sendScore(s, resp)) {
				std::cout << "Score sent: " << resp << "\n";
			}
			else {
				std::cerr << "Failed to send score: " << resp << "\n";
			}
			music.stop();
			std::vector<Score> topScores;
			std::string songName = s.song;
			httpClient.fetchScores(songName, topScores);
			topScorers = std::make_unique<TopScorers>(font, window, topScores);
			state = GameState::Scoreboard;
		}
	}
	if (state == GameState::MapCreator) {
		noteManager.update(music.getPlayingOffset());
	}
	if (state == GameState::Menu) {
	
	}
	if (state == GameState::Settings) {

	}
}

void Game::render() {
	window.clear();

	if (state==GameState::Scoreboard) {
		window.draw(backgroundSprite);
		topScorers->draw(window);
	}

	if (state == GameState::Menu) menu->drawMenu();
	else if (state == GameState::Playing) {
		window.clear();
		window.draw(backgroundSprite);
		noteManager.render(window, music.getPlayingOffset().asSeconds());
	}
	else if (state == GameState::MapCreator) {
		window.draw(backgroundSprite);
		noteManager.render(window, music.getPlayingOffset().asSeconds());
		if (enteringBeatmapFile) {
			window.draw(beatmapFileText);
		}
	}
	else if (state == GameState::Settings) {
		settings->drawSettings();
		if (enteringNickname) {
			settings->drawInput();
		}
	}
	window.draw(nicknameText);
	window.display();
}
