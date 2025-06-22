
#pragma once
#include <memory>
class Player;

class JumpPhaseBase {
public:
    virtual ~JumpPhaseBase() = default;
    virtual std::unique_ptr<JumpPhaseBase> update(Player& player, float dt) = 0;
};