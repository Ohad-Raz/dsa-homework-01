#include <SFML/Graphics.hpp>
#include "Flower.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 200, 300 }), "Animated Flower");

    Flower flower(&window);

    while (window.isOpen())
    {
        while (const std::optional<sf::Event> event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        flower.draw();  
        window.display();
    }
}
