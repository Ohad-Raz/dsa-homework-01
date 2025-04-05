#include "Flower.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

Flower::Flower(sf::RenderWindow* win) : window(win) {
    // Center of Flower (lowered)
    center.setRadius(radius);
    center.setFillColor(sf::Color::Yellow);
    center.setPosition({ 85.f, 125.f });

    // Petals (lowered)
    petal1.setRadius(15.f);
    petal1.setFillColor(sf::Color::Red);
    petal1.setPosition({ 90.f, 100.f });

    petal2 = petal1;
    petal2.setPosition({ 90.f, 160.f });

    petal3 = petal1;
    petal3.setPosition({ 60.f, 130.f });

    petal4 = petal1;
    petal4.setPosition({ 120.f, 130.f });

    // Cloud puffs (3 overlapping ellipses with transparency)
    sf::Color cloudColor(200, 200, 200, 180);  // light gray, semi-transparent
    cloud1.setRadius(30.f);
    cloud1.setScale({ 1.5f, 1.f });
    cloud1.setFillColor(cloudColor);
    cloud1.setPosition({ 140.f, 40.f });

    cloud2 = cloud1;
    cloud2.setRadius(25.f);
    cloud2.setFillColor(cloudColor);
    cloud2.setPosition({ 170.f, 35.f });

    cloud3 = cloud1;
    cloud3.setRadius(28.f);
    cloud3.setFillColor(cloudColor);
    cloud3.setPosition({ 160.f, 50.f });

    // Vine (stem) - lowered
    vine.setSize({ 5.f, 80.f });
    vine.setFillColor(sf::Color(0, 100, 0));
    vine.setPosition({ 97.5f, 180.f });

    // Leaf (lowered)
    leaf.setPointCount(4);
    leaf.setPoint(0, { 0.f, 0.f });
    leaf.setPoint(1, { 20.f, 10.f });
    leaf.setPoint(2, { 0.f, 20.f });
    leaf.setPoint(3, { -20.f, 10.f });
    leaf.setFillColor(sf::Color(34, 139, 34));
    leaf.setPosition({ 100.f, 220.f });

    // Sun (starts larger)
    Sun.setRadius(radius + 10.f);
    Sun.setFillColor(sf::Color::Yellow);
    Sun.setPosition({ 30.f, 30.f });

    if (!sunTexture.loadFromFile("animated_sun2.png")) {
        std::cerr << "Could not load sun texture!" << std::endl;
    }
    else {
        Sun.setTexture(&sunTexture);
        Sun.setFillColor(sf::Color::White);  // so texture appears naturally
    }

    // Sun Rays
 /*   for (int i = 0; i < rayCount; ++i) {
        rays[i].setSize(sf::Vector2f(4.f, 35.f));
        rays[i].setOrigin(sf::Vector2f(2.f, 32.f));
        rays[i].setFillColor(sf::Color::Yellow);
        rays[i].setPosition({ 30.f, 30.f });
        rays[i].setRotation(sf::degrees(static_cast<float>(i) * 360.f / rayCount));
    }*/
}

void Flower::draw() {
    float time = clock.getElapsedTime().asSeconds();

    // Animate Sun Pulsing (bigger range)
    if (time > 0.08f) {
        if (shrinking) {
            radius -= 0.5f;
            if (radius <= 20.f) shrinking = false;
        }
        else {
            radius += 0.5f;
            if (radius >= 30.f) shrinking = true;
        }
        Sun.setRadius(radius);
        Sun.setOrigin({ radius, radius }); // to stay centered
        Sun.setPosition({ 30.f, 30.f });
        clock.restart();
    }

    // Animate rays stretching
    float stretch = std::sin(totalTime.getElapsedTime().asSeconds() * 4.f) * 0.3f + 1.f;
    for (int i = 0; i < rayCount; ++i) {
        rays[i].setScale({ 1.f, stretch });
    }

    // Animate cloud movement
    cloudOffsetX -= 0.012f;
    float cloudRightmostX = 130.f + cloudOffsetX + (60.f * 1.5f); // puff3 + scale
    if (cloudRightmostX < 0.f)
        cloudOffsetX = 200.f;


    cloud1.setPosition({ 105.f + cloudOffsetX, 40.f });
    cloud2.setPosition({ 125.f + cloudOffsetX, 35.f });
    cloud3.setPosition({ 130.f + cloudOffsetX, 50.f });

    // Draw all parts
    for (int i = 0; i < rayCount; ++i)
        window->draw(rays[i]);

    window->draw(Sun);
    window->draw(vine);
    window->draw(leaf);
    window->draw(petal1);
    window->draw(petal2);
    window->draw(petal3);
    window->draw(petal4);
    window->draw(cloud1);
    window->draw(cloud2);
    window->draw(cloud3);
    window->draw(center);
}
