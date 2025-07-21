#pragma once
#include "Objects/PlayableObject.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include "PlayableObjectStates/PlayerStates/PlayerBaseState.h"
#include "Objects/PickableObject.h"
#include "Attacks/AttackBehavior.h"

struct PlayerData {
    std::string m_name;
    std::string m_description;
    int m_hp;
    float m_speed; 
    std::shared_ptr<sf::Texture> m_profilePic;
    std::shared_ptr<sf::Texture> m_chracterIcon;
    std::shared_ptr<sf::Texture> m_animationSheet;
    std::string toString() {
        return "name: " + m_name + " desc: " + m_description;
    }
};

class Player : public PlayableObject
{
public:
    explicit Player(const sf::Vector2f pos, const std::string& name, float speed);
    Player(PlayerData data);

    void handleInput(sf::Event event);                 // Reads arrow-key state (?) m_direction
    void update(float dt);
    void handleCollision() override;    

    void setSpeed(float speed);

    bool isAlive() const;
    void resetHP();
    // Keep the player inside the window bounds
    void clampToWindow(const sf::Vector2u& windowSize);

    void setAttack(std::unique_ptr<AttackBehavior> attack);

    void setAniName(const std::string& name);
	
    const PlayableObjectState* getState() const { return m_state.get(); }

    virtual void onStoneHit();
    virtual void onBoxHit();
    virtual void onHandsAttack();
    virtual void onExplosion();
private:
    bool m_alive = true;
};
