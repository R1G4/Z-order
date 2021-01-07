#include"stdafx.h"
#include"tempStage.h"
void tempStage ::picCollision()
{
	probeX = (_player->getShadow().left + _player->getShadow().right) / 2;
	probeY = (_player->getShadow().top + _player->getShadow().bottom) / 2;
}