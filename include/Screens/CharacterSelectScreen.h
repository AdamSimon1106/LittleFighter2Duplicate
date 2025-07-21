#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <optional>
#include "IScreen.h"
#include "UI/Background.h"


struct PlayerData;

class CharacterSelectScreen : public IScreen {
public:
    CharacterSelectScreen(sf::RenderWindow& window, GameManager& manager);
    void update(sf::Time deltaTime) override;
    void handleEvents(sf::Event& ev) override;
    void render() override;

private:
    std::vector<std::pair<std::string,std::shared_ptr<PlayerData>>> m_characters;
    bool m_selectionMode = false;
    bool m_selected = false;
    int m_currentIndex = 0;
    // General UI
    sf::RectangleShape m_frame;
    sf::RectangleShape m_namePlaceholder;
    sf::RectangleShape m_descPlaceholder;
    sf::Text m_instructionText;
    sf::Text m_title;
    sf::Text m_nameLabel;
    sf::Text m_descLabel;
    std::optional<Background> m_backGround;
    sf::Font m_font;
    float m_opacityTime = 0.f;

    // Character frame
    sf::RectangleShape m_profilePlaceholder;
    sf::Texture m_placeholderTex;
    sf::Sprite m_profileSprite;
    sf::Text m_characterName;
    sf::Text m_characterDescription;
    sf::Text m_placeholderText;
   
};
