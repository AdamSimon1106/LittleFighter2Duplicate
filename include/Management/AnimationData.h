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
inline const AnimationInfo WALKING_WITH_ROCK = { 320, 160, 80, 80, 4, 0.2f, true};
inline const AnimationInfo STANDING = { 0, 0, 80, 80, 4, 0.2f, true };
inline const AnimationInfo STANDING_WITH_ROCK = { 240, 160, 80, 80, 0, 0.2f, false };;
inline const AnimationInfo JUMPING = { 0, 520, 80, 80, 4, 0.2f, false };

