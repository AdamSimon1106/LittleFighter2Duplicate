#include "EventCommands\ExplodeCommand.h"

void ExplodeCommand::execute(PlayableObject& player)
{
	player.reduceHp(EXPLOSION_DAMAGE);
	player.onExplosion();
}
std::unique_ptr<ICommand> ExplodeCommand::clone() const {
	return std::make_unique<ExplodeCommand>(*this);
};
