#pragma once
#include "gameNode.h"
#include "kyoko.h"
#include "enemyManager.h"
#include "UIManager.h"
#include "opTion.h"

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
	UIManager* UI;
	tagChair tempRcU;
	tagChair tempRcD;
	tagChair chair[8];
	POINT camera;
	kyoko* _player;
	opTion* _opt;
	image* stage1;
	image* stage1Pic;
	enemyManager* _em;
	vector<int> _vZorder;
	char _str[128];
	bool _isDesk;
public:
	HRESULT init();
	void release();
	void update();
	void render();

	// ∏ ¿Ãµø
	void changeMap();
	void pixelCollision();
	void zOrder();
	void quickSort(int a, int b);
};

