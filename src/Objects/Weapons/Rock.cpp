#include "Objects/Weapons/Rock.h"

Rock::Rock(const sf::Vector2f pos, const std::string& name)
	:Weapon(pos, name)
{
    Animation rockAnim(
        getTexture(),    // ���� ����� �������� getTexture()
        0, 0,          // x, y � ����� ��������
        58, 58,          // ���� ����� �����
        1,               // ���� �������
        0.15f            // ��� ��� �������
    );

    setAnimation(rockAnim);
}

bool Rock::m_registered = Factory<PickableObject>::registerIt("r", [](const sf::Vector2f& pos, const std::string& name) {
    return std::make_unique<Rock>(pos, name);
    });