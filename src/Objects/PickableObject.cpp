#include "Objects/PickableObject.h"
//#include "Objects/ObjectStates/IdleObjState.h"


PickableObject::PickableObject(const sf::Vector2f pos, const std::string& name, std::unique_ptr<ICommand> cmd)
	:Object(pos, name), m_name(name), m_command(std::move(cmd)), m_range(250.f)
{
	m_offset = OBJ_OFFSET;
}

const std::string& PickableObject::getName()
{
	return m_name;
}

void PickableObject::move(sf::Vector2f goal)
{
	m_goalPosition = goal;
	setPosition(m_goalPosition + m_offset);
	
	
}

std::unique_ptr<ICommand> PickableObject::getHitCommand()
{
	 return std::move(m_command->clone());
}

void PickableObject::markAsUsed()
{
	m_used = true;
}

bool PickableObject::isUsed() const
{
	return m_used;
}

void PickableObject::setHolder(PlayableObject* holder)
{
	m_holder = holder;
}

PlayableObject* PickableObject::getHolder() const
{
	return m_holder;
}

void PickableObject::setState(std::unique_ptr<ObjectBaseState> state)
{
	m_state = std::move(state);
	if (m_state) {
		m_state->enter(*this);
	}
}

const int PickableObject::getXDirThrow() const
{
	return m_xDirThrow; 
}

void PickableObject::putBack()
{
    m_status = ON_EARTH;
	setHolder(nullptr);
    m_justDropped = true;
    m_dropTarget = getPosition() - (m_offset + m_offset);
}


void PickableObject::drop(float dt)
{
    sf::Vector2f dir = m_dropTarget - getPosition();
    float distance = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    float moveDist = OBJ_DROP_SPEED * dt;

    if (distance <= moveDist || distance == 0.f) {
        setPosition(m_dropTarget);
        m_justDropped = false;
    }
    else {
        sf::Vector2f step = dir / distance * moveDist;
        setPosition(getPosition() + step);
    }
}
