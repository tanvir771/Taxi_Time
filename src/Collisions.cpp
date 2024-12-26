#include <SFML/Graphics.hpp>
#include "Collisions.h"
#include <cmath>
#include <array>

std::array<sf::Vector2f, 4> getTransformedPoints(const sf::Sprite& sprite) {
    std::array<sf::Vector2f, 4> points;

    sf::FloatRect localBounds = sprite.getLocalBounds();
    sf::Transform transform = sprite.getTransform();

    points[0] = transform.transformPoint(sf::Vector2f(localBounds.left, localBounds.top)); // Top-left
    points[1] = transform.transformPoint(sf::Vector2f(localBounds.left + localBounds.width, localBounds.top)); // Top-right
    points[2] = transform.transformPoint(sf::Vector2f(localBounds.left + localBounds.width, localBounds.top + localBounds.height)); // Bottom-right
    points[3] = transform.transformPoint(sf::Vector2f(localBounds.left, localBounds.top + localBounds.height)); // Bottom-left

    return points;
}
namespace Collisions {
	bool SATCollision(const sf::Sprite& sprite1, const sf::Sprite& sprite2)
    {
        float epsilon = 0.001f;
        auto points1 = getTransformedPoints(sprite1);
        auto points2 = getTransformedPoints(sprite2);

        std::vector<sf::Vector2f> axes;

        auto addAxes = [&axes](const std::array<sf::Vector2f, 4>& points) {
            for (int i = 0; i < 4; ++i) {
                sf::Vector2f edge = points[(i + 1) % 4] - points[i];
                axes.push_back(sf::Vector2f(-edge.y, edge.x)); // Perpendicular vector
            }
        };

        addAxes(points1);
        addAxes(points2);

        auto project = [](const std::array<sf::Vector2f, 4>& points, const sf::Vector2f& axis) {
            float min = (points[0].x * axis.x + points[0].y * axis.y);
            float max = min;

            for (const auto& point : points) {
                float projection = (point.x * axis.x + point.y * axis.y);
                if (projection < min) min = projection;
                if (projection > max) max = projection;
            }

            return std::make_pair(min, max);
        };

        for (const auto& axis : axes) {
            auto projection1 = project(points1, axis);
            auto projection2 = project(points2, axis);

            float min1 = projection1.first;
            float max1 = projection1.second;
            float min2 = projection2.first;
            float max2 = projection2.second;

            // Check if projections overlap with a small epsilon buffer
            if (max1 + epsilon < min2 || max2 + epsilon < min1) {
                return false; // Found a separating axis, no collision
            }
        }

        return true; // No separating axis found, collision detected
    }
}
