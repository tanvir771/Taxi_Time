#pragma once
#include <SFML/Graphics.hpp>

namespace Collisions {
    // Check for SAT collision (handles transformations)
    bool SATCollision(const sf::Sprite& sprite1, const sf::Sprite& sprite2);
}