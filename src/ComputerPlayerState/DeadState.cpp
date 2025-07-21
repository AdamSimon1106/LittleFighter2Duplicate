#pragma once
#include "PlayableObjectStates/ComputerPlayerState/DeadState.h"
#include "Objects/PlayableObject.h"  

void DeadState::enter(PlayableObject& player)
{
	player.setAniName("dead");
	player.dropHeldObj();
	player.setDiraction(RELEASE_DOWN);
	player.setDiraction(RELEASE_RIGHT);
}