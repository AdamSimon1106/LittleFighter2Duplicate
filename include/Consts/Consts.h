#pragma once
#include <SFML/Graphics.hpp>

// DIMENSIONS
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 800;
const float GRID_SIZE = 50.f;
const sf::Vector2f SCREEN_SIZE(SCREEN_WIDTH, SCREEN_HEIGHT);
const float X_BOUND = -25.f;
const float Y_BOUND = 380.f;
const float BOUNDS_WIDTH = 1050.f;
const float BOUNDS_HEIGHT = 420.f;

const sf::FloatRect WORLD_BOUNDS(X_BOUND, Y_BOUND, BOUNDS_WIDTH, BOUNDS_HEIGHT);
const sf::FloatRect BOUNDS_WITH_JUMP(X_BOUND, Y_BOUND - 100.f, BOUNDS_WIDTH, BOUNDS_HEIGHT+100.f);

const sf::FloatRect SEARCHING_BOUNDS(X_BOUND + 75.f, Y_BOUND + 70.f, BOUNDS_WIDTH - 150.f, BOUNDS_HEIGHT - 120.f);

// DIRECTIONS
const float LEFT = -1.f;
const float RIGHT = 1.f;

// PHYSICS (SPEED, GRAVITY, ECT.)
const sf::Vector2f OBJ_OFFSET(2.f, -62.f);
const float ALLY_SPEED = 200.f;
const float ENEMY_SPEED = 40.f;
const float BIG_WEAPON_THROWING_SPEED = 700.f;
const float BIG_WEAPON_GRAVITY = 1000.f;
const float OBJ_DROP_SPEED = 400.f;


// DAMAGES
const int HANDS_DAMAGE = 30;
const int BIG_WEAPON_DAMAGE = 50;
const int EXPLOSION_DAMAGE = 70;


// RANGES
const float HANDS_ATTACK_RANGE = 60.f;
const float PICK_UP_RANGE = 40.f;


// TIMING PARAMS
const float KNOCKED_CHECK_DELAY = 1.5f;
const float WAVE_DELAY = 1.0f;
const float LEVEL_DELAY = 2.0f;

const float OBJECT_COOLDOWN = 5.0f;
const float ATTACK_COOLDOWN = 1.0f;

const float BLOCK_DURATION = 0.7f;
const float RETREAT_DURATION = 1.0f;
const float ATTACK_DURATION = 0.15f;

const float HIT_RECOVERY_TIME = 0.5f;
const float KNOCKED_RECOVERY_TIME = 1.5f;
const float OBJ_EXPLOTION_TIME = 0.65f;

// STATS
const int PLAYER_HP = 500;
const int ALLY_HP = 500;
const int ENEMY_HP = 100;


