#pragma once

#include "IState.h"
#include "Management/Controller.h"
#include "Gameplay/Level.h"

class InGame : public IState {
public:

private:
	Controller& m_controller;
};
