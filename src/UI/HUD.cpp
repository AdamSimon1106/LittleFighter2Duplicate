#include "UI/HUD.h"
#include <SFML/Graphics.hpp>
#include <Objects/PlayableObject.h>
#include "Gameplay/Enemy.h"
#include <iostream>
HUD::HUD(const sf::Vector2u screenSize, const std::vector<std::shared_ptr<PlayableObject>>& members) : m_members(members) {
    // Step 1: HUD frame setup (top 15% of screen, blue color)
    float frameWidth = static_cast<float>(screenSize.x);
    float frameHeight = static_cast<float>(screenSize.y * 0.15f);
    m_frame.setSize(sf::Vector2f(frameWidth, frameHeight));
    m_frame.setPosition(0.f, 0.f);
    m_frame.setFillColor(sf::Color(0,0,102));
    
    m_infoFrame.setSize(sf::Vector2f(frameWidth, 40.f));
    m_infoFrame.setPosition(0.f, frameHeight);
    m_infoFrame.setFillColor(sf::Color(0, 0, 0));

    if (!m_font.loadFromFile("resources/Fonts/lesterbold.ttf")) {
        std::cerr << "Failed to load font\n";
        return;
    }
   //allies info 
    m_alliesInfo.setFont(m_font);
    m_alliesInfo.setString("Hp : malan");
    m_alliesInfo.setCharacterSize(20);
    m_alliesInfo.setPosition(20.f, frameHeight + 5.f);
    m_alliesInfo.setFillColor(sf::Color::White);
    //level info
    m_levelInfo.setFont(m_font);
    m_levelInfo.setString("0-0");
    m_levelInfo.setCharacterSize(20);
    m_levelInfo.setOrigin(.5f, 0.f);
    m_levelInfo.setPosition(frameWidth / 2, frameHeight + 5.f);
    m_levelInfo.setFillColor(sf::Color::White);
    //enemy info
    m_enemyInfo.setFont(m_font);
    m_enemyInfo.setString("amout - malan hp - lot");
    m_enemyInfo.setCharacterSize(20);
    m_enemyInfo.setPosition(frameWidth - m_enemyInfo.getGlobalBounds().width - 20.f, frameHeight + 5.f);
    m_enemyInfo.setFillColor(sf::Color::White);

    int numFrames = 3;
    float spacing = 20.f; 
    float totalSpacing = spacing * (numFrames + 1);
    float characterWidth = (frameWidth - totalSpacing) / numFrames;
    float characterHeight = frameHeight * 0.8f;
    float yOffset = (frameHeight - characterHeight) / 2.f;

 
    for (int i = 0; i < numFrames; ++i) {
        float x = spacing + i * (characterWidth + spacing);
        sf::Vector2f size(characterWidth, characterHeight);
        sf::Vector2f position(x, yOffset);
        m_characterFrames.emplace_back(size, position, members[i]);
    }
}
void HUD::update(const std::vector<std::shared_ptr<PlayableObject>>& allies, const std::vector< std::shared_ptr<Enemy>>& enemies, const std::string levelInfo)
{
    std::string alliesInfo, enemyInfo;
    int alliesHp = 0, enemyHp = 0;
    for (const auto& p : allies) {
        alliesHp += p->getHp();
    }
    alliesInfo = "amount - " + std::to_string(allies.size()) + " hp - " + std::to_string(alliesHp);
    for (const auto& p : enemies) {
        enemyHp += p->getHp();
    }
    enemyInfo = "amount - " + std::to_string(enemies.size()) + " hp - " + std::to_string(enemyHp);

    m_alliesInfo.setString(alliesInfo);
    m_enemyInfo.setString(enemyInfo);
    m_levelInfo.setString(levelInfo);
    for (auto& frame : m_characterFrames) {
        frame.update();
    }
}
void HUD::draw(sf::RenderWindow& window) {

    window.draw(m_frame);
    window.draw(m_infoFrame);
    window.draw(m_alliesInfo);
    window.draw(m_levelInfo);
    window.draw(m_enemyInfo);

    for (auto& frame : m_characterFrames) {
        frame.draw(window);
    }
}

// ----- CharacterFrame methods -----

HUD::CharacterFrame::CharacterFrame(const sf::Vector2f size, const sf::Vector2f position, const std::shared_ptr<PlayableObject>& member): m_member(member) {
    m_frame.setSize(size);
    m_frame.setOrigin(0.5f, 0.5f);
    m_frame.setPosition(position);
    m_frame.setFillColor(sf::Color(20, 20, 140));
    m_frame.setOutlineThickness(-3.f);
    m_frame.setOutlineColor(sf::Color(0, 0, 70));

    // Set icon texture
    m_icon.setTexture(*member->getIcon());
    m_icon.setPosition(position.x + size.x * .03f, position.y + size.y * .1f);
    sf::IntRect texRect = m_icon.getTextureRect();

    float targetHeight = size.y * 0.7f;
    float aspectRatio = static_cast<float>(texRect.width) / texRect.height;
    float targetWidth = targetHeight * aspectRatio;

    m_icon.setScale(targetWidth / texRect.width, targetHeight / texRect.height);

    //set HealthBar
    sf::Vector2f iconBound = m_icon.getGlobalBounds().getSize();
    sf::Vector2f fullBarSize(size.x - iconBound.x - 50.f, 20.f);
    sf::Vector2f barPosition(m_icon.getPosition().x + iconBound.x + 20.f, m_icon.getPosition().y);
    
    m_hpBar.setFillColor(sf::Color(255, 0, 0));
    m_hpBar.setPosition(barPosition);
    m_hpBar.setSize(fullBarSize);
  
    m_potentialHpBar.setFillColor(sf::Color(140, 0, 0));
    m_potentialHpBar.setPosition(barPosition);
    m_potentialHpBar.setSize(fullBarSize);
    
    m_hpBarPlaceholder.setFillColor(sf::Color(90, 90, 190));
    m_hpBarPlaceholder.setPosition(barPosition);
    m_hpBarPlaceholder.setSize(fullBarSize);

	m_maxHp = m_member->getHp();         // Use member!
    
}


void HUD::CharacterFrame::update() {
    float maxHp = m_maxHp;         // Use member!
    float potentialHp = m_member->getPotentialHp();
    float currHp = m_member->getHp();

    if (currHp <= 0) {
		m_potentialHpBar.setSize(sf::Vector2f(0.f, m_potentialHpBar.getSize().y));
		m_hpBar.setSize(sf::Vector2f(0.f, m_hpBar.getSize().y));
    }

    if (maxHp <= 0.f || potentialHp <= 0.f)
        return;

    float fullWidth = m_hpBarPlaceholder.getGlobalBounds().width;
    float height = m_hpBarPlaceholder.getGlobalBounds().height;

    // Potential as percent of max
    m_potentialHpBar.setSize(sf::Vector2f(potentialHp / maxHp * fullWidth, height));
    
    // Current as percent of potential
    m_hpBar.setSize(sf::Vector2f(currHp / maxHp * fullWidth, height));
}


void HUD::CharacterFrame::draw(sf::RenderWindow& window) {
    window.draw(m_frame);
    window.draw(m_icon);
    window.draw(m_hpBarPlaceholder);
    window.draw(m_potentialHpBar);
    window.draw(m_hpBar);
}

float HUD::CharacterFrame::getMaxHp() const
{
    return m_maxHp;
}

void HUD::CharacterFrame::setMaxlHp(const float amount)
{
    m_maxHp = amount;
}


float HUD::CharacterFrame::getPotentialHp() const
{
    return m_potentialHp;
}

void HUD::CharacterFrame::setPotentialHp(const float amount)
{
    m_potentialHp = amount;
}

float HUD::CharacterFrame::getCurrHp() const
{
    return m_currHp;
}

void HUD::CharacterFrame::setCurrHp(const float amount)
{
    m_currHp = amount;
}
