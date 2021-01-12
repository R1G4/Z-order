#pragma once
#include "gameNode.h"
#include "kyoko.h"
#include"UIManager.h"
#include "enemyManager.h"
#include "opTion.h"
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
	enemyManager* _em;
	int alpha;
	vector<int> _vZorder2;
	opTion* _opt;
	int saveSlot;
public:
	virtual HRESULT init();
	HRESULT init(int slot);
	virtual void release();
	virtual void update();
	virtual void render();
	void quickSort(int a,int b);
	void zOrder();
	// �ȼ� �浹
	virtual void pixelCollision();
	virtual void ItemCollision();
	// ��Ʈ �浹
	virtual void AttackCollision();
};

