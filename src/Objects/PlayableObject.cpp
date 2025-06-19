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
float PlayableObject::getSpeed() const
{
    return m_speed;
}

void PlayableObject::move(const sf::Vector2f& delta) {
    m_sprite.move(delta);
}
