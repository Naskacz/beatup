#include <crow.h>
#include <pqxx/pqxx>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"

int main()
{
    //std::cout << "Starting game... " << std::endl;
    Game game;
    game.run();
    return 0;
}
