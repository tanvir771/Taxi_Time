#include "Object.h"

namespace Game {
	class Car : public Engine::Object {
	public:
		Car(sf::RenderWindow& window, std::string texturePath) : Engine::Object(window, texturePath, 225, 0) {};

		void relocate();
	private:
	};
}