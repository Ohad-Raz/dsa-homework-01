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
    sf::CircleShape cloud1, cloud2, cloud3, cloud4;
    float cloudOffsetX = 0.f;

    sf::RectangleShape vine;
    sf::ConvexShape leaf;

    sf::CircleShape Sun;
    sf::Texture sunTexture;
    static const int rayCount = 8;
    sf::RectangleShape rays[rayCount];



};
