#include "Objects/PlayableObject.h"

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

void PlayableObject::updateScale()
{
    sf::Vector2f pos = getPosition();
    float dx = pos.x - m_prevPosition.x;


    if (dx > 0.01f)
        setScale(1);  // moving right
    else if (dx < -0.01f)
        setScale(-1); // moving left

    m_prevPosition = pos;
}

float PlayableObject::getSpeed() const
{
    return m_speed;
}

void PlayableObject::move(const sf::Vector2f& delta) {
    m_sprite.move(delta);
}

void PlayableObject::setAniName(const std::string& name)
{
    m_aniName = name;
}

std::string PlayableObject::getName() const
{
    return m_name;
}

bool PlayableObject::isAttacked() const
{
    return m_underAttack;
}

void PlayableObject::attack()
{
    m_underAttack = true;
}