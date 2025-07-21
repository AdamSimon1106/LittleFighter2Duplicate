#pragma once
#include "Consts/Consts.h"
#include "Objects/ObjectStates/ObjectBaseState.h"
#include "Objects/PickableObject.h"

class ExplodingObjState : public ObjectBaseState {
public:
    void enter(PickableObject& objobj) override;
    void update(PickableObject& obj, float dt) override;
private:
    sf::Clock m_clock;
	float m_explosionDuration = OBJ_EXPLOTION_TIME;
	float m_elapsedTime = 0.0f; 
};