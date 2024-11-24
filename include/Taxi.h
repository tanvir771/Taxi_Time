#include "Object.h"

namespace game {
	class Taxi : public engine::Object {
	public:
		Taxi(sf::RenderWindow& window, std::string texturePath) : engine::Object(window, texturePath) {};

		void controls(sf::Event& event);
	};
}