#include "Management/CollisionHandling.h"

#include "GamePlay/Player.h"
#include "Objects/Weapons/Rock.h"

#include <map>
#include <typeindex>
#include <iostream>
#include <SFML/Window/Keyboard.hpp>

namespace {

    // ? �������� �������: ���� ���� �� ��� ����� ����
    void playerRock(Object& playerObj, Object& rockObj) {
        auto& player = static_cast<Player&>(playerObj);
        auto& rock = static_cast<Rock&>(rockObj);

        //if (rock.isPickedUp())
            return;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            //player.pickUp(rock);
           // rock.markAsPickedUp();
            std::cout << "Player picked up the rock.\n";
        }
    }


    // ������� � Rock ? Player
    void rockPlayer(Object& rockObj, Object& playerObj) {
        playerRock(playerObj, rockObj);
    }

    // �������
    using HitFunctionPtr = void(*)(Object&, Object&);
    using Key = std::pair<std::type_index, std::type_index>;
    using HitMap = std::map<Key, HitFunctionPtr>;

    // ����� ����������
    HitMap initializeCollisionMap() {
        HitMap map;

        map[{typeid(Player), typeid(Rock)}] = &playerRock;
        map[{typeid(Rock), typeid(Player)}] = &rockPlayer;

        return map;
    }

    // ����� �������� �������� �������
    HitFunctionPtr lookup(const std::type_index& class1, const std::type_index& class2) {
        static HitMap collisionMap = initializeCollisionMap();

        auto it = collisionMap.find({ class1, class2 });
        if (it != collisionMap.end())
            return it->second;

        return nullptr;
    }

} // end anonymous namespace

// �������� �������� ������� �� ��������
void processCollision(Object& object1, Object& object2) {
    auto func = lookup(typeid(object1), typeid(object2));
    if (!func)
        throw UnknownCollision(object1, object2);

    func(object1, object2);
}
