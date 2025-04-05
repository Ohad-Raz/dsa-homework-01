#pragma once
#include <SFML/Graphics.hpp>

class Flower {
public:
    Flower(sf::RenderWindow* win);
    void draw();

private:
    sf::RenderWindow* window;
    float radius = 20.f;
    bool shrinking = true;
    sf::Clock clock;
    sf::Clock totalTime;

    sf::CircleShape center;
    sf::CircleShape petal1, petal2, petal3, petal4;
    sf::RectangleShape vine;
    sf::ConvexShape leaf;

    sf::CircleShape Sun;
    static const int rayCount = 8;
    sf::RectangleShape rays[rayCount];

};
