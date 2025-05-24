#include "NoteManager.h"
#include <iostream>
#include <fstream>
#include <string>

NoteManager::NoteManager(){
	if (!font.loadFromFile("arial.ttf")) {
		std::cout << "Nie udalo sie zaladowac czcionki" << std::endl;
		exit(1);
	}
	wynikText.setFont(font);
	wynikText.setString(std::to_string(wynik));
	wynikText.setCharacterSize(40);
	wynikText.setPosition(20, 10);
	wynikText.setFillColor(sf::Color::White);
	wynikText.setOutlineColor(sf::Color::Black);
	wynikText.setOutlineThickness(2);
}

void NoteManager::render(sf::RenderWindow& window, float currentTime) {
	window.draw(wynikText);
	for (auto& note:notes) {
		note.render(window, currentTime);
	}
}
void NoteManager::checkForClicks(sf::Vector2f mousePos, sf::Time songTime) {
	for (auto it = notes.begin();it != notes.end();) {
		if (it->isClicked(mousePos) && it == notes.begin()) {
			if (abs(songTime.asSeconds() - it->getTime()) < 0.05f) {
				std::cout << "Perfect!" << std::endl;
				wynik += 250;
			}
			else if (abs(songTime.asSeconds() - it->getTime()) < 0.2f) {
				std::cout << "Great!" << std::endl;
				wynik += 150;
			}
			else {
				std::cout << "Good!" << std::endl;
				wynik += 100;
			}
			notes.erase(it);
			break;
		}
		++it;
	}
}
void NoteManager::update(sf::Time songTime) {
	const float appearLeadTime = 1.0f;
	const auto& beatmapNotes = beatmap.getNotes();
	while (currentNoteIndex < beatmap.getNotes().size() &&
		beatmapNotes[currentNoteIndex].time - appearLeadTime <= songTime.asSeconds()) {
		const auto& info = beatmapNotes[currentNoteIndex];
		notes.emplace_back(info.x, info.y, info.time);
		currentNoteIndex++;
	}
	for (auto& note : notes) {
		note.update(songTime.asSeconds());
	}
	notes.erase(std::remove_if(
		notes.begin(), notes.end(), 
		[](const Note& note) {return note.isExpired();}),
		notes.end()
	);
	wynikText.setString(std::to_string(wynik));

}
void NoteManager::addNote(sf::Vector2f position, float time) {
	notes.emplace_back(position.x, position.y, time);
}
void NoteManager::saveBeatmap(const std::string& filename, const std::string& songName) {
	std::ofstream file(filename);
	file << songName << "\n";
	for (const auto& note : notes) {
		file << note.getTime() << " " << note.getX() << " " << note.getY() << "\n";
	}
	file.close();
}
void NoteManager::loadBeatmap(const std::string& filename) {
	beatmap.loadFromFile(filename);
	currentNoteIndex = 0;
	notes.clear();
}
Beatmap& NoteManager::getBeatmap() {
	return beatmap;
}