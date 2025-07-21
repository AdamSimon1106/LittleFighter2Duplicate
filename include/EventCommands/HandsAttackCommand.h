#include "EventCommands/ICommand.h"
#include "Objects/PlayableObject.h"

class HandsAttackCommand : public ICommand {
public:
    HandsAttackCommand() = default;
    void execute(PlayableObject& player) override ;
    std::unique_ptr<ICommand> clone() const override;
};

