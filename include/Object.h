#pragma once
#include "SFML/Graphics.hpp"

namespace Engine {
	class Object {
	public:
		Object(sf::RenderWindow& window, const std::string& texturePath, float x = 400.f, float y = 800.f);

		void draw();

		bool detectCollision(Object anotherObj);

		// Getters
		sf::Vector2f getPosition();
		
		// Setters
		void changePosition(float x, float y); // change Position adds onto the current position
		void setPosition(float x, float y);	   // This sets the sprite to the specified location

	private:
		sf::Sprite mSprite;
		sf::Texture mTexture;

		// Owner - a window is an owner of all objects
		sf::RenderWindow& mOwnerWindow;
	};
}