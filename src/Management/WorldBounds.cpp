#pragma once
#include "Management/WorldBounds.h"
#include <SFML/Graphics.hpp>
#include <iostream>

bool WorldBounds::contains(const sf::FloatRect& rect) const {
    return m_bounds.contains(rect.left, rect.top) &&
        m_bounds.contains(rect.left + rect.width, rect.top + rect.height);

}

sf::Vector2f WorldBounds::clampPosition(const sf::FloatRect& objBounds) const
{
    sf::Vector2f fixed = { objBounds.left, objBounds.top };

    if (objBounds.left < m_bounds.left) {
        fixed.x += m_bounds.left - objBounds.left;
    }
    if (objBounds.left + objBounds.width > m_bounds.left + m_bounds.width) {
        fixed.x -= ((objBounds.left + objBounds.width) - (m_bounds.left + m_bounds.width));
    }
    if (objBounds.top < m_bounds.top) {
        fixed.y += m_bounds.top - objBounds.top;
    }
    if (objBounds.top + objBounds.height > m_bounds.top + m_bounds.height) {
        fixed.y -= ((objBounds.top + objBounds.height) - (m_bounds.top + m_bounds.height));
    }
    return fixed;
}







