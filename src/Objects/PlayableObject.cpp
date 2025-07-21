#include "Objects/PlayableObject.h"
#include "Objects/PickableObject.h"

void PlayableObject::setState(std::unique_ptr<PlayableObjectState> newState)
{
    m_state = std::move(newState);
    m_state->enter(*this);
}

void PlayableObject::handleCommand(std::unique_ptr<ICommand> command)
{
    command->execute(*this);
}

void PlayableObject::pickUpObject(std::shared_ptr<PickableObject> obj)
{
    m_heldObject = obj;
    m_heldObject->setHolder(this);
    m_attackRange = obj->getRange();
    m_strategyName = obj->getName();
    obj->pick();
    auto attack = Factory<AttackBehavior>::createAttackBehavior(m_strategyName, m_heldObject, this);
    if (attack)
    {
        m_attack = std::move(attack);
    }
}

void PlayableObject::setDiraction(Input input)
{
    switch (input)
    {
    case PRESS_LEFT:
        m_direction.x = LEFT;
        m_dir = Direction::LEFT;
        setScale(-1);
        break;
    case PRESS_RIGHT:
        m_direction.x = RIGHT;
        m_dir = Direction::RIGHT;
        setScale(1);
        break;
    case RELEASE_LEFT:
        if (m_direction.x < 0.f)
            m_direction.x = 0.f;
        break;
    case RELEASE_RIGHT:
        if(m_direction.x > 0.f)
            m_direction.x = 0.f;
        break;
    case PRESS_JUMP:
    case PRESS_UP:
        m_direction.y = LEFT;
        break;
    case PRESS_FALLING:
    case RELEASE_UP:
        if (m_direction.y > 0.f)
            m_direction.y = 0.f;
        break;
    case RELEASE_DOWN:
		if (m_direction.y < 0.f)
            m_direction.y = 0.f;
        break;
    case PRESS_DOWN:
        m_direction.y = RIGHT;
        break;
    default:
        break;
    }
}

void PlayableObject::attack()
{

    if (m_attack)
    {
        m_attack->attack();
    }
    
    if (m_heldObject)
    {
        m_heldObject->throwIt();
        m_heldObject = nullptr;

        m_attack = Factory<AttackBehavior>::createAttackBehavior("h", nullptr, this);
    }


}

std::shared_ptr<PickableObject> PlayableObject::getHeldObj() const
{
    return m_heldObject;
}

void PlayableObject::dropHeldObj() {
;    if (m_heldObject) {
        m_attackRange = HANDS_ATTACK_RANGE;
        m_strategyName = "";
        m_heldObject->putBack();
        m_heldObject->setHolder(nullptr);
        m_heldObject = nullptr;
    }
    auto attack = Factory<AttackBehavior>::createAttackBehavior(m_strategyName, m_heldObject, this);
    if (attack)
    {
        m_attack = std::move(attack);
    }
}

void PlayableObject::setStrategyName(const std::string& name)
{
    m_strategyName = name;
}

void PlayableObject::takeDamage(int damageAmount) {

}

void PlayableObject::resetDirection()
{
    if (m_direction.x != 0 || m_direction.y != 0)
    {
        m_direction = { 0.f, 0.f };
    }
}

void PlayableObject::updateScale()
{
    sf::Vector2f pos = getPosition();
    float dx = pos.x - m_prevPosition.x;
    if (dx > 0.01f)
        setScale(RIGHT);  // moving right
    else if (dx < -0.01f)
        setScale(LEFT); // moving left

}

bool PlayableObject::isHoldingWeapon(std::shared_ptr<PickableObject> obj) const
{
    return m_heldObject != nullptr;
}

float PlayableObject::getSpeed() const
{
    return m_speed;
}

void PlayableObject::move(const sf::Vector2f& delta) {
    getSprite().move(delta);
    if (m_heldObject)
    {
        m_heldObject->move(getPosition());
    }
}

void PlayableObject::move(float dt)
{
    m_prevPosition = getPosition();
    sf::Vector2f velocity = m_direction;

    // Normalize diagonal movement (to prevent faster diagonal movement)
    if (velocity.x != 0.f && velocity.y != 0.f)
    {
        constexpr float invSqrt2 = 0.70710678118f;
        velocity.x *= invSqrt2;
        velocity.y *= invSqrt2;
    }
    // Apply speed and delta time
    sf::Vector2f delta(velocity.x * m_speed * dt,
        velocity.y * m_speed * dt);
    moveSprite(delta);
    if (m_heldObject)
    {
        m_heldObject->move(getPosition());
    }

}
void PlayableObject::setAniName(const std::string& name)
{
    m_aniName = name;
}
std::string PlayableObject::getName() const
{
    return m_name;
}
void PlayableObject::reduceHp(int amountToReduce)
{
    m_hp -= amountToReduce;
    m_potentialHp -= amountToReduce / 3;
}
void PlayableObject::tookItem()
{
    m_needItem = false;
}
void PlayableObject::wantItem()
{
    m_needItem = true;
}
bool PlayableObject::needItem()
{
    return m_needItem;
}

void PlayableObject::startAttackTimer()
{
    m_attackTimer = true;

}
bool PlayableObject::canAttack() {
    return m_canAttack;
}



void PlayableObject::adjustRange(float range)
{
    m_attackRange = range;
}
float PlayableObject::getAttackRange() const
{
    return m_attackRange;
}
std::string PlayableObject::getStrategyName() {
    return m_strategyName;
}
void PlayableObject::updateHp() {
    m_hpClock += 1;
    if (m_hpClock == 36 && m_hp < m_potentialHp)
    {
        m_hp += 1;
    }
    m_hpClock = m_hpClock % 36;
}
std::shared_ptr<sf::Texture> PlayableObject::getIcon() const
{
    return m_icon;
}

float PlayableObject::getHitCooldown() const
{
    return m_hitCooldown;
}
void PlayableObject::setHitCooldown(float cooldown)
{
	m_hitCooldown = cooldown;
}

