#include <SFML/Graphics.hpp>
#include "Taxi.h"

#include <iostream>

int main() {

	sf::RenderWindow window(sf::VideoMode(800, 1000), "Taxi Time!", sf::Style::Titlebar | sf::Style::Close);
	
	Game::Taxi taxi = Game::Taxi(window, TAXI_SPRITE_PATH);

	sf::Texture backgroundText;
	backgroundText.setRepeated(true);
	if (!backgroundText.loadFromFile(BACKGROUND_PATH)) {
		std::cout << "Could not load background texture" << std::endl;
	}

	sf::Sprite backgroundSprite;
	backgroundSprite.setTexture(backgroundText);

	// Get the window size
	sf::Vector2u windowSize = window.getSize();

	// Get the texture size
	sf::Vector2u textureSize = backgroundText.getSize();

	// Compute the scale factors to fit the texture to the window size
	float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
	float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

	// Set the scale of the sprite
	backgroundSprite.setScale(scaleX, scaleY);


	// Create a texture rectangle that will "scroll" the background
	sf::IntRect textureRect(0, 0, windowSize.x / scaleX, windowSize.y / scaleY);

	// Variables for controlling the smoothness of scrolling
	float scrollSpeed = 600.0f;  // Controls the speed of scrolling (pixels per second)
	float currentOffset = 0.0f;  // Offset in the y-direction

	// Clock to track time
	sf::Clock clock;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			taxi.controls(event);
		}

		// Get the delta time (time elapsed between frames)
		float deltaTime = clock.restart().asSeconds();

		// Move the texture rectangle downward (scrolling effect)
		textureRect.top -= static_cast<int>(scrollSpeed * deltaTime);

		// Reset the texture rectangle if it moves past the texture's height
		if (textureRect.top < textureSize.y) {
			textureRect.top = 0;
		}


		// Apply the scrolling texture rectangle to the sprite
		backgroundSprite.setTextureRect(textureRect);


		window.clear(sf::Color::Black);
		window.draw(backgroundSprite);
		taxi.draw();
		window.display();
	}

	return 0;
}