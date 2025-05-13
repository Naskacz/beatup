#include "Note.h"
Note::Note(float X, float Y, float targetTime) : targetTime(targetTime), appearTime(targetTime - 1.0f), ringRadius(80.f), ringThickness(4.f) {
	circle.setRadius(30.f);
	circle.setOrigin(circle.getRadius(), circle.getRadius());
	circle.setFillColor(sf::Color::Red);
	circle.setPosition(X, Y);
}

void Note::render(sf::RenderWindow& window, float currentTime) {
	window.draw(circle);
	if (currentTime >= appearTime && currentTime <= targetTime + 0.5f) {
		ring.setRadius(ringRadius);
		ring.setOrigin(ringRadius, ringRadius);
		ring.setPosition(circle.getPosition());
		ring.setOutlineThickness(ringThickness);
		ring.setOutlineColor(sf::Color::White);
		ring.setFillColor(sf::Color::Transparent);
		window.draw(ring);
	}

}

bool Note::isClicked(sf::Vector2f mousePos) {
	return (circle.getGlobalBounds().contains(mousePos) && isReadyToClick() ? true : false);
}

bool Note::isExpired() const {
	return lifetimeClock.getElapsedTime().asSeconds() > Lifetime;
}

void Note::update(float currentTime) {
	float t = targetTime - currentTime;
	if (countdown > 0 && countdownClock.getElapsedTime().asSeconds() >= 1.f) {
		countdown--;
		countdownClock.restart();
	}
	if (t > 0.f && t < 1.0f) {
		ringRadius = 30.f + (50.f * t);
	}
	else if (t <= 0.f) {
		ringRadius = 30.f;
	}
}

bool Note::isReadyToClick() const {
	float elapsed = lifetimeClock.getElapsedTime().asSeconds();
	return elapsed >= (appearTime - targetTime);
}