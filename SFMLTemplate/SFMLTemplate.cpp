#include <SFML/Graphics.hpp>
#include <iostream>

void handleEvent(sf::RenderWindow* window)
{
    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window->close();
        }
    }
}

int main()
{
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "CMake SFML Project");
    window->setFramerateLimit(144);

    while (window->isOpen())
    {
        handleEvent(window);

        window->clear(sf::Color::Red);
        window->display();
    }

    delete window;
    return 0;
}
