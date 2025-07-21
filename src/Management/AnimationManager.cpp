#include "Management/AnimationManager.h"
#include <iostream>

std::map<std::string, AnimationInfo> AnimationManager::s_animationMap;

void AnimationManager::loadAnimations() {
    s_animationMap["walking"] = WALKING;
    s_animationMap["walkingr"] = s_animationMap["walkingb"] =  WALKING_WITH_ROCK;
    s_animationMap["standing"] = STANDING;
    s_animationMap["standingr"] = s_animationMap["standingb"] = STANDING_WITH_ROCK;
    s_animationMap["jumping"] = JUMPING;
    s_animationMap["jumpingr"] = s_animationMap["jumpingb"]  = JUMPING_WITH_ROCK;
    s_animationMap["attackingr"] = s_animationMap["attackingb"] = ATTACKING_WITH_ROCK;
    s_animationMap["attacking"] = ATTACKING;
    s_animationMap["idle"]= IDLE;
	
    s_animationMap["standingk"] = STANDING;
    s_animationMap["jumpingk"] = JUMPING;
    s_animationMap["running"] = RUNNING;
    s_animationMap["runningr"] = RUNNING_WITH_ROCK;


    s_animationMap["walkingk"] = WALKING_WITH_KNIFE;
    s_animationMap["attackingk"] = ATTACKING_WITH_KNIFE;
    s_animationMap["knocked"] = KNOCKED_DOWN;
    s_animationMap["blocking"] = BLOCKING;

    s_animationMap["r"] = ROCK;
	s_animationMap["b"] = ROCK;
	s_animationMap["rock_flying"] = ROCK_FLYING;
    s_animationMap["dead"] = DEAD;

    s_animationMap["gothit"] = GOTHIT;


	s_animationMap["held"] = HELD;
    s_animationMap["boxExploiding"] = BOX_EXPLOIDING;
	s_animationMap["knockedDown"] = KNOCKEDDOWN;
}


Animation AnimationManager::getAnimation(const std::string& aniName, const sf::Texture* texture) {
    auto it = s_animationMap.find(aniName);
    if (it == s_animationMap.end()) {
        throw std::runtime_error("Animation not found: " + aniName);
    }

    const AnimationInfo& info = it->second;

    return Animation(texture, info.x, info.y, info.width, info.height, info.frameCount, info.frameTime, info.loop);
}
