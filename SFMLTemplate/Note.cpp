#include "Note.h"
Note::Note(float X, float Y){
	circle.setRadius(20.f);
	circle.setFillColor(sf::Color::Red);
	circle.setPosition(X, Y);
}
void Note::render(sf::RenderWindow& window) {
	window.draw(circle);
}
bool Note::isClicked(sf::Vector2f mousePos) {
	return circle.getGlobalBounds().contains(mousePos.x, mousePos.y);
}
