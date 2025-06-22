#include "Management/AnimationManager.h"

std::map<std::string, AnimationInfo> AnimationManager::s_animationMap;

void AnimationManager::loadAnimations() {
    s_animationMap["walking"] = WALKING;
    s_animationMap["walkingr"] = WALKING_WITH_ROCK;
    s_animationMap["standing"] = STANDING;
    s_animationMap["standingr"] = STANDING_WITH_ROCK;
    s_animationMap["jumping"] = JUMPING;
    s_animationMap["jumpingr"] = JUMPING_WITH_ROCK;
    s_animationMap["attackingr"] = ATTACKING_WITH_ROCK;
    s_animationMap["attacking"] = ATTACKING;



}

Animation AnimationManager::getAnimation(const std::string& aniName, const sf::Texture* texture) {
    auto it = s_animationMap.find(aniName);
    if (it == s_animationMap.end()) {
        throw std::runtime_error("Animation not found: " + aniName);
    }

    const AnimationInfo& info = it->second;

    return Animation(texture, info.x, info.y, info.width, info.height, info.frameCount, info.frameTime, info.loop);
}
