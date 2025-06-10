
#include "../include/UI/Button.h"
#include <iostream>

sf::Font Button::m_font;

Button::Button(const std::string& label, sf::Vector2f size, sf::Vector2f position, sf::Color color, int charSize) {

    if (m_font.getInfo().family.empty()) {
        if (!m_font.loadFromFile("C:/Windows/Fonts/arialbd.ttf")) {
            throw std::runtime_error("Font failed to load!");
        }
    }

    m_button.setSize(size);
    m_button.setPosition(position);
    m_button.setFillColor(color);
    m_button.setOutlineThickness(2);
    m_button.setOutlineColor(sf::Color::Black);

    m_text.setFont(m_font);
    m_text.setString(label);
    m_text.setCharacterSize(charSize);
    m_text.setFillColor(sf::Color::White);
    m_text.setPosition(0, 0);
    centerText();
}

sf::Vector2f Button::calculateShapeCenter() const {
    return m_button.getPosition() + (m_button.getSize() / 2.0f);
}

void Button::centerText() {
    sf::FloatRect textBounds = m_text.getLocalBounds();
    m_text.setOrigin(
        textBounds.left + textBounds.width / 2.0f,
        textBounds.top + textBounds.height / 2.0f
    );
    m_text.setPosition(calculateShapeCenter());
}


void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_button, states);
    target.draw(m_text, states);
}


bool Button::isClicked(const sf::Vector2f& mousePos) const {
    return m_button.getGlobalBounds().contains(mousePos);
}

void Button::setPosition(sf::Vector2f position) {
    m_button.setPosition(position);
    centerText();
}

void Button::setColor(sf::Color color)
{
    m_button.setFillColor(color);
}

void Button::setTextColor(sf::Color color)
{
    m_text.setFillColor(color);
}

bool Button::hasValidFont() const {
    return m_text.getFont() != nullptr;
}