#include "NoteManager.h"
#include <iostream>
#include <fstream>
#include <string>

NoteManager::NoteManager(){
	if (!font.loadFromFile("arial.ttf")) {
		std::cout << "Nie udalo sie zaladowac czcionki" << std::endl;
		exit(1);
	}
	scoreText.setFont(font);
	scoreText.setString(std::to_string(score));
	scoreText.setCharacterSize(40);
	scoreText.setPosition(20, 10);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setOutlineColor(sf::Color::Black);
	scoreText.setOutlineThickness(2);
}

void NoteManager::render(sf::RenderWindow& window, float currentTime) {
	window.draw(scoreText);
	for (auto& note:notes) {
		note.render(window, currentTime);
	}
	for (const auto& ft : floatingTexts) {
		window.draw(ft.text);
	}
}
void NoteManager::checkForClicks(sf::Vector2f mousePos, sf::Time songTime) {
	for (auto it = notes.begin();it != notes.end();) {
		if (it->isClicked(mousePos) && it == notes.begin()) {
			std::string message;
			if (abs(songTime.asSeconds() - it->getTime()) < 0.05f) {
				message = "Perfect!";
				std::cout << message << std::endl;
				score += 250*streakMultiplier;
				streak++;
				streakMultiplier+=0.002;
				
			}
			else if (abs(songTime.asSeconds() - it->getTime()) < 0.2f) {
				message = "Great!";
				std::cout << message << std::endl;
				score  += 150*streakMultiplier;
				streak++;
				streakMultiplier += 0.002;
			}
			else {
				message = "Good!";
				std::cout << message << std::endl;
				score += 100*streakMultiplier;
				streak++;
				streakMultiplier += 0.002;
			}
			FloatingText ft;
			ft.text.setFont(font);
			ft.text.setString(message);
			ft.text.setCharacterSize(30);
			ft.text.setFillColor(sf::Color::Yellow);
			ft.text.setOutlineColor(sf::Color::Black);
			ft.text.setOutlineThickness(2);
			sf::FloatRect textBounds = ft.text.getLocalBounds();
			ft.text.setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f);
			ft.text.setPosition(mousePos);
			ft.velocity = sf::Vector2f(0.f, -50.f); // leci nuta do góry
			ft.lifetime = sf::seconds(1.f);
			floatingTexts.push_back(ft);

			notes.erase(it);
			break;
		}
		else {
			FloatingText ft;
			ft.text.setFont(font);
			ft.text.setString("Missed!");
			ft.text.setCharacterSize(30);
			ft.text.setFillColor(sf::Color::Red);
			ft.text.setOutlineColor(sf::Color::Black);
			ft.text.setOutlineThickness(2);
			sf::FloatRect textBounds = ft.text.getLocalBounds();
			ft.text.setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f);
			ft.text.setPosition(mousePos);
			ft.velocity = sf::Vector2f(0.f, -50.f); // leci nuta do góry
			ft.lifetime = sf::seconds(1.f);
			floatingTexts.push_back(ft);
			streak = 0;
			streakMultiplier = 1.0f;
		}
		++it;
	}
}
void NoteManager::update(sf::Time songTime) {
	sf::Time deltaTime = songTime - lastUpdateTime;
	lastUpdateTime = songTime;
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
	for (auto it = floatingTexts.begin(); it != floatingTexts.end();) {
		it->lifetime -= deltaTime;
		if (it->lifetime <= sf::Time::Zero) {
			it = floatingTexts.erase(it);
		}
		else {
			it->text.move(it->velocity * deltaTime.asSeconds());
			++it;
		}
	}
	notes.erase(std::remove_if(
		notes.begin(), notes.end(), 
		[](const Note& note) {return note.isExpired();}),
		notes.end()
	);
	
	floatingTexts.erase(std::remove_if(
		floatingTexts.begin(), floatingTexts.end(),
		[](const FloatingText& ft) { return ft.lifetime <= sf::Time::Zero; }),
		floatingTexts.end()
	);
	scoreText.setString(std::to_string(score) + " x" + std::to_string(streak));

}
void NoteManager::addNote(sf::Vector2f position, float time) {
	notes.emplace_back(position.x, position.y, time);
	creatorNotes.emplace_back(position.x, position.y, time);
}
void NoteManager::saveBeatmap(const std::string& filename, const std::string& songName) {
	std::ofstream file(filename);
	file << songName << "\n";
	for (const auto& note : creatorNotes) {
		file << note.getTime() << " " << note.getX() << " " << note.getY() << "\n";
	}
	file.close();
}
void NoteManager::loadBeatmap(const std::string& filename) {
	beatmap.loadFromFile(filename);
	currentNoteIndex = 0;
	notes.clear();
	creatorNotes.clear();
}
void NoteManager::clearNotes() {
	notes.clear();
	creatorNotes.clear();
	currentNoteIndex = 0;
	score = 0;
	scoreText.setString(std::to_string(score));
	floatingTexts.clear();
}
Beatmap& NoteManager::getBeatmap() {
	return beatmap;
}