#include "Management/AnimationManager.h"

std::map<std::string, AnimationInfo> AnimationManager::s_animationMap;

void AnimationManager::loadAnimations() {
    s_animationMap["walking"] = WALKING;
    s_animationMap["walkingrock"] = WALKING_WITH_ROCK;
    s_animationMap["standing"] = STANDING;
    s_animationMap["standingrock"] = STANDING_WITH_ROCK;
    s_animationMap["jumping"] = JUMPING;


}

Animation AnimationManager::getAnimation(const std::string& aniName, const sf::Texture* texture) {
    auto it = s_animationMap.find(aniName);
    if (it == s_animationMap.end()) {
        throw std::runtime_error("Animation not found: " + aniName);
    }

    const AnimationInfo& info = it->second;

    return Animation(texture, info.x, info.y, info.width, info.height, info.frameCount, info.frameTime, info.loop);
}
