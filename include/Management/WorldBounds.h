#include <SFML/Graphics.hpp>


class WorldBounds {
public:
    WorldBounds(const sf::FloatRect& bounds) : m_bounds(bounds) {}
    bool contains(const sf::FloatRect& rect) const;
    sf::Vector2f clampPosition(const sf::FloatRect& objBounds) const;

private:
    sf::FloatRect m_bounds;
};
