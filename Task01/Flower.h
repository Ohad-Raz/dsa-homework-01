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
    bool isDay = true;

    sf::Clock clock;
    sf::Clock totalTime;

    sf::CircleShape center;
    sf::CircleShape petal1, petal2, petal3, petal4;
    sf::RectangleShape vine;
    sf::ConvexShape leaf;

    sf::CircleShape cloud1, cloud2, cloud3;
    float cloudOffsetX = 0.f;

    sf::CircleShape Sun;
    float sunOffsetX = 0.f;
    sf::Texture sunTexture;

    sf::RectangleShape skyBackground;
    sf::RectangleShape groundBackground;
    sf::Color skyColor;
    sf::Color groundColor;

    static const int starCount = 20;
    sf::CircleShape stars[starCount];
};
