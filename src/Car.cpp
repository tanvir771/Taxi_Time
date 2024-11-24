#include <random>
#include "Car.h"

#include <iostream>

namespace game {
	void Car::relocate()
	{
		randomizeLocation();
	}

	void Car::randomizeLocation()
	{
		std::random_device rd;             
		std::mt19937 gen(rd());        
		std::uniform_int_distribution<std::mt19937::result_type> dist(0, possibleLocations.size() - 1);

		// Generate and print a random integer between 200 and 800
		int random_int = dist(gen);
		std::cout << random_int << std::endl;
		setPosition(possibleLocations[random_int], -200);
	}
}