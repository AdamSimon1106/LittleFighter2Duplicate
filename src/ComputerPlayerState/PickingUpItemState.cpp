//#include "ComputerPlayerState/PickingUpItemState.h"
//#include "GamePlay/ComputerPlayer.h"
//#include "Objects/PickableObject.h"
//#include "ComputerPlayerState/IdleState.h"
//#include <SFML/System/Vector2.hpp>
//#include <cmath>
//
//PickingUpItemState::PickingUpItemState(std::shared_ptr<PickableObject> item)
//    : m_targetItem(std::move(item)) {}
//
//void PickingUpItemState::enter(ComputerPlayer& player) {
//    std::cout << "enter:: PickingUpItemState\n";
//
//    Animation pickingUpItemAnim(player.getTexture(),
//        480, 0,          // x, y
//        80, 80,        // width, height
//        2,             // מספר פריימים
//        0.2f,
//        false);
//
//    player.setAnimation(pickingUpItemAnim);
//    //player.setDiraction(m_input); 
//}
//
//void PickingUpItemState::update(ComputerPlayer& player, float deltaTime) {
//    if (!m_targetItem) {
//        // Item already gone – return to idle
//        player.changeState(std::make_unique<IdleState>());
//        return;
//    }
//
//    sf::Vector2f playerPos = player.getPosition();
//    sf::Vector2f itemPos = m_targetItem->getPosition();
//
//    float distance = std::sqrt(std::pow(playerPos.x - itemPos.x, 2) +
//        std::pow(playerPos.y - itemPos.y, 2));
//
//    const float pickupRange = 40.f;
//    if (distance <= pickupRange) {
//        // Pick up item
//        player.pickUp(*m_targetItem);
//        player.changeState(std::make_unique<IdleState>());
//    }
//    else {
//        // Move toward item
//        sf::Vector2f direction = itemPos - playerPos;
//        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
//        if (length != 0.f)
//            direction /= length;
//
//        player.move(direction * player.getSpeed() * deltaTime);
//    }
//}
//
//void PickingUpItemState::exit(ComputerPlayer& player) {
//    // No cleanup needed for now
//}
