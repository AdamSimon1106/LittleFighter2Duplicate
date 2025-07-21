#include "objects/ObjectStates/ExplodingObjState.h"

void ExplodingObjState::enter(PickableObject& obj)
{
	m_clock.restart();
	obj.setAnimation(AnimationManager::getAnimation("boxExploiding", &ResourceManager::instance().getTexture("broken")));
	obj.setSize(2); // Set size for explosion effect
	//sound
}

void ExplodingObjState::update(PickableObject& obj, float dt)
{
	m_elapsedTime += dt;
	if (m_elapsedTime > m_explosionDuration) {
		obj.markAsUsed();
		obj.setState(nullptr); 
	}
}


