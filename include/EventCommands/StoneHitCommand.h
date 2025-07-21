#include "EventCommands/ICommand.h"
#include "Objects/PlayableObject.h"

class StoneHitCommand : public ICommand {
public:
	StoneHitCommand() = default;
	void execute(PlayableObject& player) override;
	std::unique_ptr<ICommand> clone() const override;

};