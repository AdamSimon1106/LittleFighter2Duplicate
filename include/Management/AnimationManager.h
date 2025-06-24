#pragma once

#include <map>
#include <string>
#include "Animation.h"
#include "AnimationData.h"  // כי שם יש את AnimationInfo

class AnimationManager {
public:
    static Animation getAnimation(const std::string& aniName, const sf::Texture* texture);

    static void loadAnimations();

private:
    static std::map<std::string, AnimationInfo> s_animationMap;
};
