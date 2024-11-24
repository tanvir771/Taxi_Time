#pragma once
#include "Object.h"
#include <vector>

namespace game {
	class Car : public engine::Object {
	public:
		Car(sf::RenderWindow& window, std::string texturePath, float x, float y) : engine::Object(window, texturePath, x, y) {};

		void relocate();
		void randomizeLocation();
	private:
		std::vector<int> possibleLocations = { 225, 415, 625 };
	};
}