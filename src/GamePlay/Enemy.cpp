#include "GamePlay/Enemy.h"


Enemy::Enemy(const sf::Vector2f pos, const std::string& name, float speed)
    : ComputerPlayer(pos, name)
{
    m_speed = speed;
    // Starts with IdleState
    changeState(std::make_unique<IdleState>());
}


void Enemy::update(float dt)
{
    ComputerPlayer::update(dt);  // �� ����� �� ��state
}

void Enemy::handleCollision() {
    // ����� �� ����� �� ���� ��������, �� ����� ��� �������
}




bool Enemy::isAlive() const {
    return m_alive;
}
