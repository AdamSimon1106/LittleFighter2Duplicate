#include "PlayerStates/WeaponHoldingState.h"
#include "Gameplay/Player.h"

WeaponHolding::WeaponHolding(Input input, weaponType weapon)
	:m_weaponType(weapon)
{
	m_input = input;
}

std::unique_ptr<PlayerBaseState> WeaponHolding::handleInput(Input input)
{
	return std::unique_ptr<PlayerBaseState>();
}

void WeaponHolding::enter(Player& player)
{
    std::cout << "WeaponHolding\n";

    Animation weaponAnim(nullptr, 0, 0, 0, 0, 0, 0); // Dummy init

    switch (m_weaponType)
    {
    case weaponType::Rock:
        weaponAnim = Animation(player.getTexture(),
            240, 160,       // x, y
            80, 80,         // width, height
            1,              // frames
            0.2f,           // frame time
            false           // looping
        );
        break;

    case weaponType::Knife:
        weaponAnim = Animation(player.getTexture(),
            160, 160, 80, 80, 3, 0.15f, true); // ãåâîä ìÎKnife
        break;

    default:
        std::cerr << "Unknown weapon type in WeaponHolding::enter\n";
        return;
    }

    player.setAnimation(weaponAnim);
    player.setDiraction(m_input);
}


void WeaponHolding::update(Player& player, float dt)
{
}
