#pragma once
#include "SFML/Graphics.hpp"

namespace Engine {
	class Object {
	public:
		Object(sf::RenderWindow& window, const std::string& texturePath, float x = 400.f, float y = 800.f);

		void draw();
		void setPosition(float x, float y);

	private:
		sf::Sprite mSprite;
		sf::Texture mTexture;

		// Owner - a window is an owner of all objects
		sf::RenderWindow& mOwnerWindow;
	};
}