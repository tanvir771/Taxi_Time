#include <SFML/Graphics.hpp>
#include "Taxi.h"

#include <iostream>

int main() {

	sf::RenderWindow window(sf::VideoMode(800, 1000), "Taxi Time!", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);
	Game::Taxi taxi = Game::Taxi(window, TAXI_SPRITE_PATH);

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

	int moveUpSpeed = 5; // For when we have a score to speed up the game

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			taxi.controls(event);
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

		std::cout << "BG " << backgroundSprite.getPosition().y << std::endl;
		std::cout << "Secondary BG " << secondaryBGSprite.getPosition().y << std::endl;

		window.clear(sf::Color::Black);
		window.draw(backgroundSprite);
		window.draw(secondaryBGSprite);
		taxi.draw();
		window.display();
	}

	return 0;
}