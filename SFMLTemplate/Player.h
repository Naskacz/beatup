#pragma once
#include <string>
class Player
{
	std::string nickname;
public:
	Player(const std::string& nickname);
	void setNickname(std::string& nickname);
	std::string getNickname()const;
};

