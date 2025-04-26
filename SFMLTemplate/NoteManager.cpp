#include "NoteManager.h"
#include <iostream>
void NoteManager::render(sf::RenderWindow& window) {
	for (auto& note:notes) {
		note.render(window);
	}
}

void NoteManager::createNote() {
	float X = rand() % 760 + 20;
	float Y = rand() % 760 + 20;
	notes.emplace_back(X, Y);
}

void NoteManager::loadBeatmap(const std::string& filename) {
	beatmap.loadFromFile(filename);
}

void NoteManager::checkForClicks(sf::Vector2f mousePos) {
	for (auto it = notes.begin();it != notes.end();) {
		if (it->isClicked(mousePos) && it == notes.begin()) {
			notes.erase(it);
			break;
		}
		++it;
	}
}

void NoteManager::update(sf::Time songTime) {
	while (currentNoteIndex < beatmap.getNotes().size() &&
		beatmap.getNotes()[currentNoteIndex].time <= songTime.asSeconds()) {
		auto& info = beatmap.getNotes()[currentNoteIndex];
		notes.emplace_back(info.x, info.y);
		currentNoteIndex++;
	}

	for (auto& note : notes) {
		note.update();
	}
	notes.erase(std::remove_if(
		notes.begin(), notes.end(), 
		[](const Note& note) {return note.isExpired();}),
		notes.end()
	);
}

