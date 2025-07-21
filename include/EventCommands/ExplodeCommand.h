#include "EventCommands/ICommand.h"
#include "Objects/PlayableObject.h"

class ExplodeCommand : public ICommand {
public:
	ExplodeCommand() = default;
	void execute(PlayableObject& player) override;
	std::unique_ptr<ICommand> clone() const override;

};