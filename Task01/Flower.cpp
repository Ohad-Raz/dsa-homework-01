#include "Flower.h"
#include <cmath>
#include <iostream>

using namespace std;

Flower::Flower(sf::RenderWindow* win) : window(win) {
    // Center
    center.setRadius(radius);
    center.setFillColor(sf::Color(255, 221, 51));
    center.setPosition({ 85.f, 125.f });

    // Main petals (bright orange)
    sf::Color mainPetalColor(255, 69, 0);
    petal1.setRadius(15.f); petal1.setFillColor(mainPetalColor); petal1.setPosition({ 90.f, 100.f });
    petal2 = petal1; petal2.setPosition({ 90.f, 160.f });
    petal3 = petal1; petal3.setPosition({ 60.f, 130.f });
    petal4 = petal1; petal4.setPosition({ 120.f, 130.f });

    // Diagonal petals (darker orange)
    sf::Color diagPetalColor(255, 99, 71);
    petal5.setRadius(15.f); petal5.setFillColor(diagPetalColor); petal5.setPosition({ 68.f, 108.f }); // top-left
    petal6 = petal5; petal6.setPosition({ 112.f, 108.f }); // top-right
    petal7 = petal5; petal7.setPosition({ 68.f, 152.f }); // bottom-left
    petal8 = petal5; petal8.setPosition({ 112.f, 152.f }); // bottom-right

    // Vine & Leaf
    vine.setSize({ 5.f, 80.f }); vine.setFillColor(sf::Color(34, 139, 34)); vine.setPosition({ 97.5f, 180.f });
    leaf.setPointCount(4);
    leaf.setPoint(0, { 0.f, 0.f }); leaf.setPoint(1, { 20.f, 10.f });
    leaf.setPoint(2, { 0.f, 20.f }); leaf.setPoint(3, { -20.f, 10.f });
    leaf.setFillColor(sf::Color(34, 139, 34)); leaf.setPosition({ 100.f, 220.f });

    // Clouds
    sf::Color cloudColor(200, 200, 200, 180);
    cloud1.setRadius(30.f); cloud1.setScale({ 1.5f, 1.f }); cloud1.setFillColor(cloudColor); cloud1.setPosition({ 140.f, 40.f });
    cloud2 = cloud1; cloud2.setRadius(25.f); cloud2.setPosition({ 170.f, 35.f });
    cloud3 = cloud1; cloud3.setRadius(28.f); cloud3.setPosition({ 160.f, 50.f });

    // Sun/Moon
    Sun.setRadius(radius + 10.f);
    Sun.setOrigin({ radius + 10.f, radius + 10.f }); Sun.setPosition({ 30.f, 30.f });
    if (!sunTexture.loadFromFile("resources/animated_sun.png"))
        cout << "Failed to load sun texture\n";
    Sun.setTexture(&sunTexture); Sun.setFillColor(sf::Color::White);

    // Backgrounds
    skyBackground.setSize({ 200.f, 250.f });
    skyBackground.setPosition({ 0.f, 0.f });
    groundBackground.setSize({ 200.f, 50.f });
    groundBackground.setPosition({ 0.f, 250.f });
    skyColor = sf::Color(135, 206, 235); // default
    groundColor = sf::Color(0, 0, 0); // will be updated

    // Stars
    for (int i = 0; i < starCount; ++i) {
        stars[i].setRadius(1.5f);
        stars[i].setFillColor(sf::Color::White);
        stars[i].setPosition({
            static_cast<float>(rand() % 200),
            static_cast<float>(rand() % 120)
            });
    }
}

void Flower::draw() {
    float time = clock.getElapsedTime().asSeconds();

    // Pulsing sun/moon
    if (time > 0.08f) {
        radius += shrinking ? -0.5f : 0.5f;
        if (radius <= 20.f) shrinking = false;
        if (radius >= 30.f) shrinking = true;

        Sun.setRadius(radius);
        Sun.setOrigin({ radius, radius });
        clock.restart();
    }

    // Sun/Moon movement
    sunOffsetX += 0.012f;
    if (sunOffsetX > 240.f) {
        sunOffsetX = -60.f;
        isDay = !isDay;
        string texturePath = isDay ? "resources/animated_sun.png" : "resources/animated_moon.png";
        if (!sunTexture.loadFromFile(texturePath))
            cout << "Failed to load texture: " << texturePath << endl;
        else {
            Sun.setTexture(&sunTexture);
            Sun.setFillColor(sf::Color::White);
        }
    }
    Sun.setPosition({ 30.f + sunOffsetX, 30.f });
    Sun.rotate(sf::degrees(0.01f));

    // Cloud movement
    cloudOffsetX -= 0.012f;
    if (130.f + cloudOffsetX + (60.f * 1.5f) < 0.f) cloudOffsetX = 200.f;
    cloud1.setPosition({ 105.f + cloudOffsetX, 40.f });
    cloud2.setPosition({ 125.f + cloudOffsetX, 35.f });
    cloud3.setPosition({ 130.f + cloudOffsetX, 50.f });

    // Sky & Ground transitions
    sf::Color daySky(135, 206, 235), nightSky(25, 25, 112);  // sky
    sf::Color dayGround(34, 139, 34), nightGround(10, 30, 60); // ground (was black, now navy)
    sf::Color targetSky = isDay ? daySky : nightSky;
    sf::Color targetGround = isDay ? dayGround : nightGround;

    skyColor.r += (targetSky.r - skyColor.r) * 0.05f;
    skyColor.g += (targetSky.g - skyColor.g) * 0.05f;
    skyColor.b += (targetSky.b - skyColor.b) * 0.05f;
    groundColor.r += (targetGround.r - groundColor.r) * 0.05f;
    groundColor.g += (targetGround.g - groundColor.g) * 0.05f;
    groundColor.b += (targetGround.b - groundColor.b) * 0.05f;

    skyBackground.setFillColor(skyColor);
    groundBackground.setFillColor(groundColor);

    // Draw order
    window->draw(skyBackground);
    if (!isDay) for (int i = 0; i < starCount; ++i) window->draw(stars[i]);
    window->draw(Sun);

    // Flower parts
    window->draw(vine);
    window->draw(leaf);
    window->draw(petal1); window->draw(petal2);
    window->draw(petal3); window->draw(petal4);
    window->draw(petal5); window->draw(petal6);
    window->draw(petal7); window->draw(petal8);
    window->draw(center);

    // Clouds & ground
    window->draw(cloud1); window->draw(cloud2); window->draw(cloud3);
    window->draw(groundBackground);
}
