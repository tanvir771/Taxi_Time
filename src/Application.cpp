#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <random>

#include "Taxi.h"
#include "Car.h"

#include <iostream> // temporarily for loggin

int main() {

	sf::RenderWindow window(sf::VideoMode(800, 1000), "Taxi Time!", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);
	std::unique_ptr <game::Taxi> taxi = std::make_unique<game::Taxi>(window, TAXI_SPRITE_PATH);

	std::vector<std::shared_ptr<game::Car>> carsVect;
	for (int i = 0; i < 10; i++) {
		std::shared_ptr<game::Car> car = std::make_shared<game::Car>(window, CAR_PATH, 0.f, -200.f);
		car->randomizeLocation();
		carsVect.push_back(car);
	}

	sf::Texture backgroundText;
	backgroundText.setRepeated(true);
	if (!backgroundText.loadFromFile(BACKGROUND_PATH)) {
		std::cout << "Could not load background texture" << std::endl;
	}

	sf::Sprite backgroundSprite;
	backgroundSprite.setTexture(backgroundText);

	sf::Sprite secondaryBGSprite;
	secondaryBGSprite.setTexture(backgroundText);

	// Get the window size
	sf::Vector2u windowSize = window.getSize();

	// Get the texture size
	sf::Vector2u textureSize = backgroundText.getSize();

	// Compute the scale factors to fit the texture to the window size
	float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
	float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

	// Set the scale of the sprite
	backgroundSprite.setScale(scaleX, scaleY);
	secondaryBGSprite.setScale(scaleX, scaleY);
	secondaryBGSprite.setPosition(0, backgroundSprite.getPosition().y - windowSize.y);

	double moveUp = backgroundSprite.getPosition().y; 
	double secondaryMoveDown = backgroundSprite.getPosition().y - windowSize.y;

	sf::Clock clock;

	int moveUpSpeed = 10; // For when we have a score to speed up the game

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			taxi->controls(event);
		}

		float elapsedTime = clock.getElapsedTime().asSeconds();
		clock.restart();

		moveUp += moveUpSpeed;

		if (backgroundSprite.getPosition().y > 1000) {
			moveUp = 0;
		}
		else if (secondaryBGSprite.getPosition().y > 1000) {
			secondaryMoveDown = 0;
		}

		backgroundSprite.setPosition(0, moveUp);
		secondaryBGSprite.setPosition(0, secondaryMoveDown + moveUp);

		window.clear(sf::Color::Black);
		window.draw(backgroundSprite);
		window.draw(secondaryBGSprite);
		taxi->draw();
	
		for (auto& car : carsVect) {
			car->draw();
			car->changePosition(0, 3);
			if (car->detectCollision(*taxi)) {
				car->relocate();
			}
		}

		window.display();
	}

	return 0;
}