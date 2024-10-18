#include <SFML/Graphics.hpp>

#include <iostream>

int main() {

	sf::RenderWindow window(sf::VideoMode(800, 1000), "Taxi Time!", sf::Style::Titlebar | sf::Style::Close);

	sf::Texture texture;
	if (!texture.loadFromFile(TAXI_SPRITE_PATH)) {
		std::cout << "Couldn't load texture!" << std::endl;
	}

	sf::Sprite sprite;
	sprite.setScale(0.75f, 0.75f);
	sf::Vector2u textureSize = texture.getSize();

	// Set the origin to the center of the original sprite
	sprite.setOrigin(textureSize.x / 2.0f, textureSize.y / 2.0f);
	sprite.setPosition(sf::Vector2f(400.f, 800.f));

	sprite.setTexture(texture);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		window.clear(sf::Color::Black);
		window.draw(sprite);
		window.display();
	}

	return 0;
}