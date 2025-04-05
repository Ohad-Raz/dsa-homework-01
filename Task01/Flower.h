#pragma once
#include <SFML/Graphics.hpp>

class Flower {
public:
    Flower(sf::RenderWindow* win);
    void draw();

private:
    sf::RenderWindow* window;

    // Flower parts
    sf::CircleShape center;
    sf::CircleShape petal1, petal2, petal3, petal4;
    sf::RectangleShape vine;
    sf::ConvexShape leaf;
    sf::CircleShape Sun;

    // Animation state
    sf::Clock clock;
    float radius = 20.f;
    bool shrinking = true;
};
