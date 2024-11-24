#include <iostream>
#include "Object.h"

namespace Engine {
	Object::Object(sf::RenderWindow& window, const std::string& texturePath, float x, float y) : mOwnerWindow(window)
	{
		if (!mTexture.loadFromFile(texturePath)) {
			std::cout << "Failed to load texture - Engine::Object" << std::endl;
		}

		mSprite.setTexture(mTexture);
		mSprite.setScale(0.75f, 0.75f);
		sf::Vector2u textureSize = mTexture.getSize();

		// Set the origin to the center of the original sprite
		mSprite.setOrigin(textureSize.x / 2.0f, textureSize.y / 2.0f);
		mSprite.setPosition(sf::Vector2f(x, y));						// TODO: change to variables
	}

	void Object::draw()
	{
		mOwnerWindow.draw(mSprite);
	}

	sf::Vector2f Object::getPosition()
	{
		return mSprite.getPosition();
	}

	void Object::setPosition(float x, float y)
	{
		sf::Vector2f position = mSprite.getPosition();
		mSprite.setPosition(position.x + x, position.y + y);
	}


}
