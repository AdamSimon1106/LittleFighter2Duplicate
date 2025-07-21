#pragma once
#include "Objects/PlayableObject.h"
#include "Objects/PickableObject.h"

#include "PlayableObjectStates/ComputerPlayerState/ComputerPlayerState.h"

class ComputerPlayer : public PlayableObject{
public:

    ComputerPlayer(const sf::Vector2f pos, const std::string& name); 
    ComputerPlayer(PlayerData p);
    virtual ~ComputerPlayer() = default;
    virtual void update(float dt) override;

    // Changes the current state
    void changeState(std::unique_ptr<ComputerPlayerState> newState);
    PlayableObjectState* getState() const;

    void onHit();
    void onKnockedDown();
    bool wasHit() const;
    bool wasKnockedDown() const;
    bool needsEnemyTracking() const;
    void clearHitFlags();
    void setTarget(std::shared_ptr<Object> obj);
    std::shared_ptr<Object> getTarget() override;
    void setBlocking(bool blocking);
    void setControllable(bool control);
    void performAttack(PlayableObject &target);
    void pickUp(PickableObject& pickable);



protected:
    bool m_wasHit = false;
    bool m_wasKnockedDown = false;
    std::shared_ptr<Object> m_target = nullptr;
    bool m_controllable = true;
    bool m_blocking = false;
    bool m_attackTimer = false;
    

private:
    float distance(const sf::Vector2f& a, const sf::Vector2f& b);
    void updateDirection();
    virtual void onStoneHit();
    virtual void onBoxHit();
    virtual void onHandsAttack();
    virtual void onExplosion();
    float m_attackWaitingTime = 5.0f;
    float m_attackCoolDown = 0.f;
    bool m_canAttack = true;
};
