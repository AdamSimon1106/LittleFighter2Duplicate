#include "PlayerStates/AttackingState.h"
#include"PlayerStates/StandingState.h"
#include "GamePlay/Player.h"

std::unique_ptr<PlayerBaseState> AttackingState::handleInput(Input input)
{
    switch (input)
    {
    case END_ATTACK:
        return std::make_unique<StandingState>(input);
        break;
    
    default:
        break;
    }
}

void AttackingState::enter(Player& player)
{
    std::cout << "enter:: AttackingState\n";

    Animation attackAnim(player.getTexture(),
        640, 0,       // שורת האנימציה של התקפה (לפי sprite sheet שלך)
        80, 80,       // גודל פריים
        2,            // 3 פריימים של תקיפה
        0.1f,         // קצב מהיר יחסית
        true);       // לא בלולאה – התקפה קורת פעם אחת

    player.setAnimation(attackAnim);
}
