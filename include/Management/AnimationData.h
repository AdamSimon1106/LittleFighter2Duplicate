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


inline const AnimationInfo WALKING = { 0, 0, 80, 80, 4, 0.1f, true};
inline const AnimationInfo WALKING_WITH_ROCK = { 0, 80, 80, 80, 4, 0.1f, true};
