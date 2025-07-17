#include "Objects/PlayableObject.h"
#include "Objects/PickableObject.h"
#include "PlayableObjectStates/ComputerPlayerState/DeadState.h"


void PlayableObject::setState(std::unique_ptr<PlayableObjectState> newState)
{
    m_state = std::move(newState);
    m_state->enter(*this);
}

void PlayableObject::handleCommand(std::unique_ptr<ICommand> command)
{
	std::cout << getName() << " is handling command\n";
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
        m_direction.x = -1.f;
        m_dir = Direction::LEFT;
        setScale(-1);
        break;
    case PRESS_RIGHT:
        m_direction.x = 1.f;
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
        m_direction.y = -1.f;
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
        m_direction.y = 1.f;
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
    std::cout << "\nin dropHeldObj \n\n";
;    if (m_heldObject) {
        m_attackRange = 50.f;
        m_strategyName = "";
        m_heldObject->putBack();
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
  /*  // Reduce health
    m_health -= damageAmount;

    // Clamp health to non-negative
    if (m_health < 0)
        m_health = 0;

    // Optionally: play a hurt animation or effect
    setAnimation("Hurt");

    // Optionally: apply knockback or visual feedback
    applyKnockback();

    // Check for death
    if (m_health == 0)
        onDeath(); */
}

void PlayableObject::resetDirection()
{
	std::cout << "Resetting direction for " << getName() << std::endl;
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
        setScale(1);  // moving right
    else if (dx < -0.01f)
        setScale(-1); // moving left


    //int dir = static_cast<int>(m_dir);
    //dir *= -1;
    //m_dir = static_cast<Direction>(dir);
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
void PlayableObject::onHandsAttack()
{
    if (m_hp <= 0) {
        m_hp = 0;
        m_potentialHp = 0;
        setState(std::make_unique<DeadState>());
    }
    m_state->onHandsAttack(*this);

}
void PlayableObject::onStoneHit()
{
	moveSprite({ 100.f, 0.f }); // simulate knockback effect
    if (m_hp <= 0) {
        m_hp = 0;
        m_potentialHp = 0;
        setState(std::make_unique<DeadState>());
    }
    m_state->onStoneHit(*this);
}

void PlayableObject::onBoxHit()
{
    if (m_hp <= 0) {
        m_hp = 0;
        m_potentialHp = 0;
        setState(std::make_unique<DeadState>());
    }
    m_state->onBoxHit(*this);
}

void PlayableObject::onExplosion()
{
    if (m_hp <= 0) {
        m_hp = 0;
        m_potentialHp = 0;
        setState(std::make_unique<DeadState>());
    }
	m_state->onExplosion(*this);
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
