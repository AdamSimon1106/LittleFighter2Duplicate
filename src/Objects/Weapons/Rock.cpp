#include "Objects/Weapons/Rock.h"

Rock::Rock(const sf::Vector2f pos, const std::string& name)
	:Weapon(pos, name)
{
	
    setAnimation(AnimationManager::getAnimation(getName(), getTexture()));
    sf::Vector2f offset(10.f, -35.f);
    m_offset = offset;
    
}

void Rock::update(float dt)
{
    if (m_isFlying)
    {
        // עדכון מיקום:
        sf::Vector2f pos = getPosition();
        pos.x += m_velocity.x * dt;
        pos.y += m_velocity.y * dt;

        // עדכון מהירות Y עם Gravity:
        m_velocity.y += m_gravity * dt;

        // האם נחתנו?
        if (pos.y >= m_groundY)
        {
            pos.y = m_groundY;
            m_isFlying = false;  // הפסיק לעוף
            m_velocity = { 0.f, 0.f };
            std::cout << "Rock landed!\n";
        }

        setPosition(pos);
    }
	apllySprite();
}

//need to get the direction and groundY from the player
void Rock::throwRock(int direction, float groundY, float speed)
{
    m_isFlying = true;
    m_groundY = groundY;

    // מהירות התחלתית:
    m_velocity.x = direction * speed;
    m_velocity.y = -400.f;  // לזרוק קצת למעלה (שלילי כי Y יורד למטה)
	setAnimation(AnimationManager::getAnimation("rock_flying", getTexture()));

    std::cout << "Rock thrown! Velocity x=" << m_velocity.x << " y=" << m_velocity.y << " groundY=" << m_groundY << "\n";
}

bool Rock::m_registered = Factory<PickableObject>::registerIt("r", [](const sf::Vector2f& pos, const std::string& name) {
    return std::make_unique<Rock>(pos, name);
    });