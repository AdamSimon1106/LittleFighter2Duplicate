#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Button : public sf::Drawable {
private:
    sf::RectangleShape m_button;
    sf::Text m_text;
    sf::Vector2f calculateShapeCenter() const;
    static sf::Font m_font;
    void centerText();

public:
    Button() = default;

    Button(const std::string& label,
        sf::Vector2f size,
        sf::Vector2f position,
        sf::Color color,
        int charSize);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    bool isClicked(const sf::Vector2f& mousePos) const;
    void setColor(sf::Color color);
    void setTextColor(sf::Color color);
    bool hasValidFont() const;
    void setPosition(sf::Vector2f position);
};