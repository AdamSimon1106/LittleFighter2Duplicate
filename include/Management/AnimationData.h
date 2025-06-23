#pragma once

struct AnimationInfo {
    int x;
    int y;
    int width;
    int height;
    int frameCount;
    float frameTime;
    bool loop;
};


inline const AnimationInfo WALKING = { 320, 0, 80, 80, 4, 0.2f, true };
inline const AnimationInfo WALKING_WITH_ROCK = { 320, 160, 80, 80, 4, 0.2f, true };
inline const AnimationInfo STANDING = { 0, 0, 80, 80, 4, 0.2f, true };
inline const AnimationInfo STANDING_WITH_ROCK = { 320, 160, 80, 80, 0, 0.2f, false };
inline const AnimationInfo JUMPING = { 0, 500, 80, 80, 4, 0.1f, false };

inline const AnimationInfo JUMPING_WITH_ROCK = { 0, 520, 80, 80, 4, 0.1f, false };
inline const AnimationInfo ATTACKING_WITH_ROCK = { 560, 160, 80, 80, 2, 0.1f, false };
inline const AnimationInfo ATTACKING = { 0, 80, 80, 80, 4, 0.1f, false };
inline const AnimationInfo KNIFE = { 0, 0, 40, 40, 1, 0.2f, false};
inline const AnimationInfo ROCK = { 0, 0, 58, 58, 1, 0.2f, false };
inline const AnimationInfo ATTACKING_WITH_KNIFE = { 0, 0, 58, 58, 1, 0.2f, false };



