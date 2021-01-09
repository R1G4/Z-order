#pragma once
#include "gameNode.h"
#include "kyoko.h"
#include "enemyManager.h"

struct tagChair
{
	RECT rc;
	image* img;
	float x, y;
};

class tempStage :
	public gameNode
{
private:
	RECT _door_rc;

	tagChair chair[8];
	POINT camera;
	kyoko* _player;
	image* stage1;
	image* stage1Pic;
	enemyManager* _em;
public:
	HRESULT init();
	void release();
	void update();
	void render();

	// ∏ ¿Ãµø
	void changeMap();
	void pixelCollision();
};

