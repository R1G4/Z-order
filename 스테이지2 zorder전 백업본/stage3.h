#pragma once
#include "gameNode.h"
#include "kyoko.h"
#include "UIManager.h"
#include "enemyManager.h"
#include "opTion.h"

struct tagGidoong
{
	RECT rc;
	float x, y;
	image* img;
};

class stage3 : public gameNode
{
private:
	image* stage3;
	image* stage3Pic;
	
	kyoko* _player;
	enemyManager* _em;
	opTion* _opt;
	UIManager*UI;

	tagGidoong Lobj;
	vector<int> _vZorder2;
	int alpha;
	int saveSlot;
	POINT camera;

public:
	virtual HRESULT init(int slot);
	virtual void release();
	virtual void update();
	virtual void render();
	
	void pixelCollision();
};

