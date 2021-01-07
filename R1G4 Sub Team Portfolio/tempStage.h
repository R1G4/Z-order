#pragma once
#include "gameNode.h"
#include "kyoko.h"
class tempStage :
	public gameNode
{
private:
	POINT camera;
	kyoko* _player;
	image* stage1;
	image* stage1Pic;
public:
	HRESULT init();
	void release();
	void update();
	void render();
};

