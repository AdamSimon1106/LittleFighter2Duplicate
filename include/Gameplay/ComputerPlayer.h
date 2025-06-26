#pragma once
#include "Objects/PlayableObject.h"
#include "Objects/PickableObject.h"

#include "ComputerPlayerState/ComputerPlayerState.h"

class ComputerPlayer : public PlayableObject{
public:

    ComputerPlayer(const sf::Vector2f pos, const std::string& name); 
    virtual ~ComputerPlayer() = default;
    virtual void update(float dt) override;

    // Changes the current state
    void changeState(std::unique_ptr<ComputerPlayerState> newState);
    ComputerPlayerState* getState() const;

    void onHit();
    void onKnockedDown();
    bool wasHit() const;
    bool wasKnockedDown() const;
    bool needsEnemyTracking() const;
    void clearHitFlags();
    void setTargetEnemy(PlayableObject* target);
    //sf::Vector2f getPosition();
    PlayableObject* getTarget();
    void setBlocking(bool blocking);
    void setControllable(bool control);
    void performAttack(PlayableObject &target);
    void pickUp(PickableObject& pickable);

protected:
    std::unique_ptr<ComputerPlayerState> m_state;
    bool m_wasHit = false;
    bool m_wasKnockedDown = false;
    PlayableObject* m_target = nullptr;
    sf::Vector2f m_position;
    bool m_controllable = true;
    bool m_blocking = false;

private:
    float distance(const sf::Vector2f& a, const sf::Vector2f& b);

};
