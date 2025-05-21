#include "Player.h"
Player::Player(const std::string& nickname): nickname(nickname) {}
void Player::setNickname(std::string& nickname) {
	this->nickname = nickname;
}
std::string Player::getNickname()const { return nickname; }