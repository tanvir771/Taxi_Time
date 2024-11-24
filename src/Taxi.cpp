#include "Taxi.h"

namespace game {
	void Taxi::controls(sf::Event& event)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			// left key is pressed: move our character
			if (getPosition().x > 180) {
				changePosition(-10.f, 0);
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			// left key is pressed: move our character
			if (getPosition().x < 620) {
				changePosition(10.f, 0);
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			// left key is pressed: move our character
			changePosition(0, -10.f);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			// left key is pressed: move our character
			changePosition(0, 10.f);
		}
	}
}