#include "PlayerStates/JumpingState.h"
#include"PlayerStates/StandingState.h"

#include "GamePlay/Player.h"

std::unique_ptr<PlayerBaseState> JumpingState::handleInput(Input input)
{
	
	return std::make_unique<StandingState>();
    return nullptr;
}

void JumpingState::enter(Player& player)
{
	std::cout << "enter:: JumpingState\n";

	// תוכל לשנות את המהירות הוורטיקלית של השחקן כאן לדוגמה
	// player.setVerticalSpeed(-jumpSpeed); // אם יש לך פונקציה כזו

    std::cout << "enter:: JumpingState\n";

    const sf::Texture& tex = ResourceManager::instance().getTexture("hunter");

    Animation jumpingAnim(&tex,
        0, 160,       // x, y – נניח שזו שורת הקפיצה
        80, 80,       // width, height
        2,            // 2 פריימים בקפיצה לדוגמה
        0.25f);       // קצב איטי יותר

    player.setAnimation(jumpingAnim);
}

