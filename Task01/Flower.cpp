#include "Flower.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

Flower::Flower(sf::RenderWindow* win) : window(win) {
	// Flower center
	center.setRadius(radius);
	center.setFillColor(sf::Color::Yellow);
	center.setPosition({ 85.f, 125.f });

	// Petals
	petal1.setRadius(15.f);
	petal1.setFillColor(sf::Color::Red);
	petal1.setPosition({ 90.f, 100.f });
	petal2 = petal1; petal2.setPosition({ 90.f, 160.f });
	petal3 = petal1; petal3.setPosition({ 60.f, 130.f });
	petal4 = petal1; petal4.setPosition({ 120.f, 130.f });

	// Vine and leaf
	vine.setSize({ 5.f, 80.f });
	vine.setFillColor(sf::Color(0, 100, 0));
	vine.setPosition({ 97.5f, 180.f });

	leaf.setPointCount(4);
	leaf.setPoint(0, { 0.f, 0.f });
	leaf.setPoint(1, { 20.f, 10.f });
	leaf.setPoint(2, { 0.f, 20.f });
	leaf.setPoint(3, { -20.f, 10.f });
	leaf.setFillColor(sf::Color(34, 139, 34));
	leaf.setPosition({ 100.f, 220.f });

	// Cloud (semi-transparent ellipses)
	sf::Color cloudColor(200, 200, 200, 180);
	cloud1.setRadius(30.f); cloud1.setScale({ 1.5f, 1.f }); cloud1.setFillColor(cloudColor);
	cloud1.setPosition({ 140.f, 40.f });
	cloud2 = cloud1; cloud2.setRadius(25.f); cloud2.setPosition({ 170.f, 35.f });
	cloud3 = cloud1; cloud3.setRadius(28.f); cloud3.setPosition({ 160.f, 50.f });

	// Sun/Moon
	Sun.setRadius(radius + 10.f);
	Sun.setOrigin({ radius + 10.f, radius + 10.f });
	Sun.setPosition({ 30.f, 30.f });
	if (!sunTexture.loadFromFile("resources/animated_sun.png"))
		std::cerr << "Failed to load sun texture\n";
	Sun.setTexture(&sunTexture);
	Sun.setFillColor(sf::Color::White);

	// Sky background full screen
	skyBackground.setSize({ 200.f, 250.f });  // Adjust to your window size
	skyBackground.setPosition({ 0.f, 0.f });
	skyColor = sf::Color(135, 206, 250); // light blue

	// Generate stars
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

	// Animate pulsing sun/moon
	if (time > 0.08f) {
		radius += shrinking ? -0.5f : 0.5f;
		if (radius <= 20.f) shrinking = false;
		if (radius >= 30.f) shrinking = true;

		Sun.setRadius(radius);
		Sun.setOrigin({ radius, radius });
		clock.restart();
	}

	// Animate sun/moon moving to the right
	sunOffsetX += 0.012f;
	if (sunOffsetX > 240.f) {  // wraps when it goes offscreen
		sunOffsetX = -60.f;
		isDay = !isDay;

		std::string texturePath = isDay ? "resources/animated_sun.png" : "resources/animated_moon.png";
		if (!sunTexture.loadFromFile(texturePath)) {
			std::cerr << "Failed to load texture: " << texturePath << std::endl;
		}
		else {
			Sun.setTexture(&sunTexture);
			Sun.setFillColor(sf::Color::White);
		}
	}

	// Place and rotate sun/moon
	Sun.setPosition({ 30.f + sunOffsetX, 30.f });
	Sun.rotate(sf::degrees(0.01f));


	// Animate cloud to the left
	cloudOffsetX -= 0.012f;
	cloud1.setPosition({ 105.f + cloudOffsetX, 40.f });
	cloud2.setPosition({ 125.f + cloudOffsetX, 35.f });
	cloud3.setPosition({ 130.f + cloudOffsetX, 50.f });

	// Reset cloud if it exits left
	float cloudRightmostX = 130.f + cloudOffsetX + (60.f * 1.5f);
	if (cloudRightmostX < 0.f)
		cloudOffsetX = 200.f;

	// Draw everything
// Smoothly fade sky color
	sf::Color dayColor(135, 206, 250);   // sky blue
	sf::Color nightColor(10, 10, 30);    // dark navy
	float transition = isDay ? 0.02f : -0.02f;

	skyColor.r = std::clamp(static_cast<int>(skyColor.r + transition * (dayColor.r - nightColor.r)), 0, 255);
	skyColor.g = std::clamp(static_cast<int>(skyColor.g + transition * (dayColor.g - nightColor.g)), 0, 255);
	skyColor.b = std::clamp(static_cast<int>(skyColor.b + transition * (dayColor.b - nightColor.b)), 0, 255);

	skyBackground.setFillColor(skyColor);
	window->draw(skyBackground);

	// Draw stars only at night
	if (!isDay) {
		for (int i = 0; i < starCount; ++i)
			window->draw(stars[i]);
	}

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

