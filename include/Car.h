#include "Object.h"

namespace game {
	class Car : public engine::Object {
	public:
		Car(sf::RenderWindow& window, std::string texturePath) : engine::Object(window, texturePath, 225, 0) {};

		void relocate();
	private:
	};
}