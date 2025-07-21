#include "EventCommands/ICommand.h"
#include "Objects/PlayableObject.h"

class BoxHitCommand : public ICommand {
public:
	BoxHitCommand() = default;
	void execute(PlayableObject& player) override;
	std::unique_ptr<ICommand> clone() const override;

};