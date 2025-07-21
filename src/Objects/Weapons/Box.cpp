#include "Objects/Weapons/Box.h"
#include "Objects/ObjectStates/ExplodingObjState.h"
#include "EventCommands/BoxHitCommand.h"
#include "EventCommands/ExplodeCommand.h"

Box::Box(const sf::Vector2f pos, const std::string& name)
	:BigWeapon(pos, name, std::make_unique<BoxHitCommand>())
{
	setAnimation(AnimationManager::getAnimation(name, getTexture()));
	
}

void Box::update(float dt)
{
    if (!picked()) {
        Object::update(dt);
    }
    if (isExploded())

    {
		m_command = std::make_unique<ExplodeCommand>();
    }
    if (m_isFlying)
    {
        sf::Vector2f pos = getPosition();
        pos.x += m_velocity.x * dt;
        pos.y += m_velocity.y * dt;

        m_velocity.y += m_gravity * dt;

        if (pos.y >= m_groundY)
        {
			explode(); 
            pos.y = m_groundY;
            m_isFlying = false;
            m_velocity = { 0.f, 0.f };
            
			setState(std::make_unique<ExplodingObjState>());
            
        }

        setPosition(pos);
    }
    if (getState())
    {
        getState()->update(*this, dt);
    }

    updateAnimation(dt);
    apllySprite();
}





bool Box::m_registered = Factory<PickableObject>::registerIt("b", [](const sf::Vector2f& pos, const std::string& name) {
	return std::make_unique<Box>(pos, name);
	});
