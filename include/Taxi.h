#include "Object.h"

namespace Game {
	class Taxi : public Engine::Object {
	public:
		Taxi(sf::RenderWindow& window, std::string texturePath) : Engine::Object(window, texturePath) {};

		void controls(sf::Event& event);
	};
}