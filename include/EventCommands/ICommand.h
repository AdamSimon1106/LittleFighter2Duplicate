#pragma once
#include <memory>
class PlayableObject;

class  ICommand {
public:
	virtual ~ICommand() = default;
	virtual void execute(PlayableObject& player) = 0;
	virtual std::unique_ptr<ICommand> clone() const = 0;
};