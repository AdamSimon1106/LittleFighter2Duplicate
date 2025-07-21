#pragma once

class AttackBehavior {
public:
	virtual ~AttackBehavior() = default;
	virtual void attack() = 0;
};
