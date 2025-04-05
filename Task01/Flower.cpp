#include "Flower.h"
#include <SFML/Graphics.hpp>
#include <cmath>

Flower::Flower(sf::RenderWindow* win) : window(win) {
    // Center
    center.setRadius(radius);
    center.setFillColor(sf::Color::Yellow);
    center.setPosition({ 85.f, 85.f });

    // Petals
    petal1.setRadius(15.f);
    petal1.setFillColor(sf::Color::Red);
    petal1.setPosition({ 90.f, 60.f });

    petal2 = petal1;
    petal2.setPosition({ 90.f, 120.f });

    petal3 = petal1;
    petal3.setPosition({ 60.f, 90.f });

    petal4 = petal1;
    petal4.setPosition({ 120.f, 90.f });

    // Vine (stem)
    vine.setSize({ 5.f, 80.f });
    vine.setFillColor(sf::Color(0, 100, 0));
    vine.setPosition({ 97.5f, 140.f });

    // Leaf
    leaf.setPointCount(4);
    leaf.setPoint(0, { 0.f, 0.f });
    leaf.setPoint(1, { 20.f, 10.f });
    leaf.setPoint(2, { 0.f, 20.f });
    leaf.setPoint(3, { -20.f, 10.f });
    leaf.setFillColor(sf::Color(34, 139, 34));
    leaf.setPosition({ 100.f, 180.f });

    // Sun
    Sun.setRadius(radius);
    Sun.setFillColor(sf::Color::Yellow);
    Sun.setPosition({ 10.f, 10.f });

    // Sun Rays
    for (int i = 0; i < rayCount; ++i) {
        for (int i = 0; i < rayCount; ++i) {
            rays[i].setSize(sf::Vector2f(4.f, 35.f));  
            rays[i].setOrigin(sf::Vector2f(2.f, 32.f)); 
            rays[i].setFillColor(sf::Color::Yellow);
            rays[i].setPosition({ 30.f, 30.f }); 
            rays[i].setRotation(sf::degrees(static_cast<float>(i) * 360.f / rayCount));
        }


    }
}

void Flower::draw() {
    float time = clock.getElapsedTime().asSeconds();

    // Animate Sun Pulsing
    if (time > 0.08f) {
        if (shrinking) {
            radius -= 0.5f;
            if (radius <= 15.f) shrinking = false;
        }
        else {
            radius += 0.5f;
            if (radius >= 20.f) shrinking = true;
        }
        Sun.setRadius(radius);
        Sun.setOrigin({ radius, radius }); // to stay centered
        Sun.setPosition({ 30.f, 30.f });

        clock.restart();
    }

    // Animate rays stretching with sine wave
    float stretch = std::sin(totalTime.getElapsedTime().asSeconds() * 4.f) * 0.3f + 1.f;
    for (int i = 0; i < rayCount; ++i) {
        rays[i].setScale({ 1.f, stretch });
    }

    // Draw
    for (int i = 0; i < rayCount; ++i)
        window->draw(rays[i]);

    window->draw(Sun);
    window->draw(vine);
    window->draw(leaf);
    window->draw(petal1);
    window->draw(petal2);
    window->draw(petal3);
    window->draw(petal4);
    window->draw(center);
}
