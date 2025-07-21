#include "EventCommands/HandsAttackCommand.h"
#include "PlayableObjectStates/ComputerPlayerState/BlockingState.h"
#include <memory>

void HandsAttackCommand::execute(PlayableObject& player)
{
	player.reduceHp(HANDS_DAMAGE);
	player.onHandsAttack();
}

std::unique_ptr<ICommand> HandsAttackCommand::clone() const {
    return std::make_unique<HandsAttackCommand>(*this);
};