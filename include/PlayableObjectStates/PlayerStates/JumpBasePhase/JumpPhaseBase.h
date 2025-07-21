
#pragma once
#include <memory>
class PlayableObject;

class JumpPhaseBase {
public:
    virtual ~JumpPhaseBase() = default;
    virtual std::unique_ptr<JumpPhaseBase> update(PlayableObject& player, float dt) = 0;
};