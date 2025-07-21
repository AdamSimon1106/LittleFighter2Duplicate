#include "Screens/CharacterSelectScreen.h"
#include "Screens/IScreen.h"
#include "Screens/InGameScreen.h"
#include "Management/ResourceManager.h"
#include "Management/GameManager.h"
#include "Gameplay/Player.h"
#include <cmath> 
#include <iostream>

CharacterSelectScreen::CharacterSelectScreen(sf::RenderWindow& window, GameManager& manager)
    : IScreen(window,manager)
{
    m_characters = ResourceManager::instance().getCharacters();
    // Load font
    if (m_font.getInfo().family.empty()) {
        if (!m_font.loadFromFile("C:/Windows/Fonts/arialbd.ttf")) {
            throw std::runtime_error("Font failed to load!");
        }
    }
    sf::Vector2f screenSize = static_cast<sf::Vector2f>(m_window.getSize());
  
    m_backGround = Background(screenSize, sf::Color::Black);
    
    m_frame.setSize(screenSize * 0.9f);
    m_frame.setPosition(
        (screenSize.x - m_frame.getSize().x) / 2.f,
        (screenSize.y - m_frame.getSize().y) / 2.f
    );

    m_frame.setFillColor(sf::Color(0,0,102));
    m_frame.setOutlineColor(sf::Color(102,102,225));
    m_frame.setOutlineThickness(2.f);
    
    sf::Vector2f framePos = m_frame.getPosition();
    sf::Vector2f frameSize = m_frame.getSize();
    
    m_title.setFont(m_font);
    m_title.setString("Character Selection");
    m_title.setCharacterSize(38);
    m_title.setFillColor(sf::Color::White);
    sf::FloatRect textBounds = m_title.getLocalBounds();
    m_title.setOrigin(textBounds.width / 2.f, textBounds.height / 2.f);
    m_title.setPosition(
        framePos.x + frameSize.x / 2.f,
        framePos.y + 30.f // adjust vertical offset from top
    );
    
    // Set placeholder size and position
    m_profilePlaceholder.setSize({ 300.f, 300.f });
    m_profilePlaceholder.setFillColor(sf::Color::Black);

    sf::Vector2f placeholderSize = m_profilePlaceholder.getSize();
    m_profilePlaceholder.setPosition(
        framePos.x + (frameSize.x - placeholderSize.x) / 2.f,
        framePos.y + (frameSize.y - placeholderSize.y) / 4.f
    );

    // Set size (width same as profilePlaceholder, height 20)
    placeholderSize = m_profilePlaceholder.getSize();
    sf::Vector2f basePosition = m_profilePlaceholder.getPosition();

    sf::Vector2f labelSize(placeholderSize.x, 40.f);

    // Name Placeholder (first row under profile)
    m_namePlaceholder.setSize(labelSize);
    m_namePlaceholder.setFillColor(sf::Color::Black);
    m_namePlaceholder.setPosition(
        basePosition.x,
        basePosition.y + placeholderSize.y + 10.f // 10px spacing below profile
    );

    // Description Placeholder (below name)
    m_descPlaceholder.setSize(labelSize);
    m_descPlaceholder.setFillColor(sf::Color::Black);
    m_descPlaceholder.setPosition(
        basePosition.x,
        m_namePlaceholder.getPosition().y + labelSize.y + 5.f // 5px spacing between name and desc
    );

    // Common settings
    float labelPadding = 10.f;
    // Name Label
    m_nameLabel.setFont(m_font);
    m_nameLabel.setString("Name");
    m_nameLabel.setCharacterSize(18);
    m_nameLabel.setFillColor(sf::Color::White);

    // Center vertically with placeholder
    sf::FloatRect nameBounds = m_nameLabel.getLocalBounds();
    m_nameLabel.setOrigin(0.f, nameBounds.height / 2.f);
    m_nameLabel.setPosition(
        m_namePlaceholder.getPosition().x - nameBounds.width - labelPadding,
        m_namePlaceholder.getPosition().y + m_namePlaceholder.getSize().y / 2.f - 5.f
    );

    // Description Label
    m_descLabel.setFont(m_font);
    m_descLabel.setString("Description");
    m_descLabel.setCharacterSize(18);
    m_descLabel.setFillColor(sf::Color::White);

    sf::FloatRect descBounds = m_descLabel.getLocalBounds();
    m_descLabel.setOrigin(0.f, descBounds.height / 2.f);
    m_descLabel.setPosition(
        m_descPlaceholder.getPosition().x - descBounds.width - labelPadding,
        m_descPlaceholder.getPosition().y + m_descPlaceholder.getSize().y / 2.f - 5.f
    );

    // Placeholder text
    m_placeholderText.setFont(m_font);
    m_placeholderText.setString("Press \nATTACK to \nchoose a character");
    m_placeholderText.setCharacterSize(20);
    m_placeholderText.setFillColor(sf::Color::White);
    sf::FloatRect textRect = m_placeholderText.getLocalBounds();
    m_placeholderText.setOrigin(textRect.width / 2.f, textRect.height / 2.f);
    m_placeholderText.setPosition(
        m_profilePlaceholder.getPosition().x + m_profilePlaceholder.getSize().x / 2.f,
        m_profilePlaceholder.getPosition().y + m_profilePlaceholder.getSize().y / 2.f
    );

    // Name
    m_characterName.setFont(m_font);
    m_characterName.setCharacterSize(18);
    m_characterName.setFillColor(sf::Color::White);

    m_characterName.setPosition(
        m_namePlaceholder.getPosition().x + 5.f, // small padding inside the placeholder
        m_namePlaceholder.getPosition().y + (m_namePlaceholder.getSize().y - m_characterName.getCharacterSize()) / 2.f - 2.f
    );

    // Description 
    m_characterDescription.setFont(m_font);
    m_characterDescription.setCharacterSize(14);
    m_characterDescription.setFillColor(sf::Color(180, 180, 180));

    m_characterDescription.setPosition(
        m_descPlaceholder.getPosition().x + 5.f,
        m_descPlaceholder.getPosition().y + (m_descPlaceholder.getSize().y - m_characterDescription.getCharacterSize()) / 2.f - 2.f
    );

    m_profileSprite.setPosition(m_profilePlaceholder.getPosition());
}

void CharacterSelectScreen::update(sf::Time deltaTime)
{
    // Animate placeholder text opacity using sine wave
    m_opacityTime += deltaTime.asSeconds();
    float alpha = 128 + 127 * std::sin(m_opacityTime * 12.f); // Pulses between 1 and 255
    sf::Color c = m_placeholderText.getFillColor();
    c.a = static_cast<sf::Uint8>(alpha);
    m_placeholderText.setFillColor(c);
}

void CharacterSelectScreen::handleEvents(sf::Event& ev)
{
    if (ev.type == sf::Event::KeyPressed) {
        if (ev.key.code == sf::Keyboard::Enter && !m_selectionMode) {
            m_selectionMode = true;
            m_placeholderText.setString("");
            m_profileSprite.setTexture(*m_characters[m_currentIndex].second->m_profilePic);

            sf::Vector2f desiredSize = m_profilePlaceholder.getSize();
            sf::Vector2f desiredPos = m_profilePlaceholder.getPosition();

            sf::Vector2u textureSize = m_profileSprite.getTexture()->getSize();
            m_profileSprite.setScale(
                desiredSize.x / textureSize.x,
                desiredSize.y / textureSize.y
            );
            m_profileSprite.setPosition(desiredPos);

            m_characterName.setString(m_characters[m_currentIndex].second->m_name);
            m_characterDescription.setString(m_characters[m_currentIndex].second->m_description);
        }

        else if (m_selectionMode) {

            if (ev.key.code == sf::Keyboard::Right) {
                m_currentIndex = (m_currentIndex + 1) % m_characters.size();
            }
            else if (ev.key.code == sf::Keyboard::Left) {
                m_currentIndex = (m_currentIndex + m_characters.size() - 1) % m_characters.size();
            }

            m_profileSprite.setTexture(*m_characters[m_currentIndex].second->m_profilePic);
            m_characterName.setString(m_characters[m_currentIndex].second->m_name);
            m_characterDescription.setString(m_characters[m_currentIndex].second->m_description);

            if (ev.key.code == sf::Keyboard::Enter) {

                std::vector<std::shared_ptr<Ally>> allies;
                size_t nextIndex = (m_currentIndex + 1) % m_characters.size();
                size_t prevIndex = (m_currentIndex + m_characters.size() - 1) % m_characters.size();

                allies.push_back(std::make_shared<Ally>(*m_characters[nextIndex].second));
                allies.push_back(std::make_shared<Ally>(*m_characters[prevIndex].second));

                m_manager.switchScreen(std::make_unique<InGameScreen>(
                    m_window,
                    m_manager,
                    m_characters[m_currentIndex].second,
                    allies
                ));
            }
        }
    }
}



void CharacterSelectScreen::render()
{
    if (m_backGround) m_backGround->draw(m_window,sf::RenderStates::Default);
    m_window.draw(m_frame);
    m_window.draw(m_title);
    if (!m_selectionMode) m_window.draw(m_profilePlaceholder);
    else m_window.draw(m_profileSprite);
    m_window.draw(m_namePlaceholder);
    m_window.draw(m_descPlaceholder);
    m_window.draw(m_nameLabel);
    m_window.draw(m_descLabel);
    m_window.draw(m_placeholderText);
    m_window.draw(m_characterName);
    m_window.draw(m_characterDescription);
}
