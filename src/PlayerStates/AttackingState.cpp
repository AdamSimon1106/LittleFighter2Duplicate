#include "PlayerStates/AttackingState.h"
#include"PlayerStates/StandingState.h"
#include "GamePlay/Player.h"

std::unique_ptr<PlayerBaseState> AttackingState::handleInput(Input input)
{
    return std::make_unique<StandingState>(input);
    return nullptr;
}

void AttackingState::enter(Player& player)
{
    std::cout << "enter:: AttackingState\n";

    const sf::Texture& tex = ResourceManager::instance().getTexture("hunter");

    Animation attackAnim(&tex,
        0, 240,       // שורת האנימציה של התקפה (לפי sprite sheet שלך)
        80, 80,       // גודל פריים
        3,            // 3 פריימים של תקיפה
        0.1f,         // קצב מהיר יחסית
        false);       // לא בלולאה – התקפה קורת פעם אחת

    player.setAnimation(attackAnim);

    // אופציונלי: עצירת תנועה
    //player.setVelocity({ 0.f, 0.f });

    // אופציונלי: הגדרת טיימר לסיום התקיפה (כמו בקפיצה)
    // נניח שיש לך attack timer בתוך ה־state

}
