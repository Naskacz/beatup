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
void NoteManager::checkForClicks(sf::Vector2f mousePos) {
	for (auto it = notes.begin();it != notes.end();) {
		if (it->isClicked(mousePos)) {
			notes.erase(it);
			break;
		}
		++it;
	}
}