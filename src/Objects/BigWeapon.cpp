#include "Objects/BigWeapon.h"


BigWeapon::BigWeapon(const sf::Vector2f pos, const std::string& name, std::unique_ptr<ICommand> cmd)
	:PickableObject(pos, name, std::move(cmd))
{
}

void BigWeapon::update(float dt)
{
    if (!picked()) {
        Object::update(dt);
    }
    if (m_isFlying)
    {

        sf::Vector2f pos = getPosition();
        pos.x += m_velocity.x * dt;
        pos.y += m_velocity.y * dt;


        m_velocity.y += m_gravity * dt;


        if (pos.y >= m_groundY)
        {
            pos.y = m_groundY;
            m_isFlying = false;  
            m_velocity = { 0.f, 0.f };
			m_status = ON_EARTH; 
            setAnimation(AnimationManager::getAnimation("r", getTexture()));
            
            
        }

        setPosition(pos);
    }
	updateAnimation(dt);
    apllySprite();
}

void BigWeapon::throwMe(int direction, float groundY, float speed)
{
    m_xDirThrow = direction;
    m_isFlying = true;
    m_groundY = groundY;

    m_velocity.x = direction * speed;
    m_velocity.y = -100.f; 
    setAnimation(AnimationManager::getAnimation("rock_flying", getTexture()));

}
