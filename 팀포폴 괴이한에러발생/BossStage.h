#pragma once
#include "gameNode.h"
#include "kyoko.h"
#include "enemyManager.h"
#include "UIManager.h"
class BossStage : public gameNode
{

private:
	RECT _door_rc;
	UIManager* UI;
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
};

