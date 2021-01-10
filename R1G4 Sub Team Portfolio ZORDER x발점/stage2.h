#pragma once
#include "gameNode.h"
#include "kyoko.h"
#include"UIManager.h"
struct tagObj
{
	RECT rc;
	float x, y;
	image* img;
};

class stage2 : public gameNode
{

private:
	UIManager* UI;
	POINT camera;
	tagObj Lobj;
	tagObj Robj;
	image* stage2;
	image* stage2Pic;
	kyoko* _player;
	int alpha;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	// ÇÈ¼¿ Ãæµ¹
	void pixelCollision();
};

