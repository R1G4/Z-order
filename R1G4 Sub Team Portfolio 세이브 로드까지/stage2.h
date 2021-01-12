#pragma once
#pragma warning(disable:4996)
#include "gameNode.h"
#include "kyoko.h"
#include"UIManager.h"
#include "enemyManager.h"
#include"opTion.h"
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
	opTion* _opt;
	enemyManager* _em;
	int alpha;
	vector<int> _vZorder2;
	int saveSlot;
public:
	virtual HRESULT init();
	HRESULT init(int slot);
	virtual void release();
	virtual void update();
	virtual void render();
	void DeleteProduct();
	void quickSort(int a,int b);
	void zOrder();
	// ÇÈ¼¿ Ãæµ¹
	void pixelCollision();
};

