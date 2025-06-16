#pragma once
#include "Objects/PlayableObject.h"
#include "ComputerPlayerState/ComputerPlayerState.h"

class ComputerPlayer : public PlayableObject{
public:

    ComputerPlayer(const sf::Vector2f pos, const std::string& name) : PlayableObject(pos, name) { }
    virtual ~ComputerPlayer() = default;
    void update(float dt);

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
    sf::Vector2f getPosition();

protected:
    std::unique_ptr<ComputerPlayerState> m_state;
    bool m_wasHit = false;
    bool m_wasKnockedDown = false;
    PlayableObject* m_target = nullptr;
    sf::Vector2f m_position;

private:
    float distance(const sf::Vector2f& a, const sf::Vector2f& b);

};
