#pragma once
#include "Objects/PlayableObject.h"
#include "ComputerPlayerState/ComputerPlayerState.h"

class ComputerPlayer : public PlayableObject{
public:
	ComputerPlayer(const sf::Texture& tex) : PlayableObject(tex) { }
    virtual ~ComputerPlayer() = default;

    // Changes the current state
    void changeState(std::unique_ptr<ComputerPlayerState> newState);

    void onHit();
    void onKnockedDown();
    bool wasHit() const;
    bool wasKnockedDown() const;

    void clearHitFlags();


protected:
    std::unique_ptr<ComputerPlayerState> m_state;
    bool m_wasHit = false;
    bool m_wasKnockedDown = false;

};
