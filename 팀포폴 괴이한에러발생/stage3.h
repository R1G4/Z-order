#pragma once
#include "gameNode.h"
#include "kyoko.h"
#include "UIManager.h"
#include "enemyManager.h"
#include "opTion.h"
enum LockState {
	NOTYET,
	CHECK,
	LOCKED
};
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
	image* chain[4];
	image* Lock;
	int lockCount;
	kyoko* _player;
	enemyManager* _em;
	opTion* _opt;
	UIManager*UI;
	RECT lockCheckRc;
	tagGidoong Lobj;
	vector<int> _vZorder2;
	int alpha;
	int saveSlot;
	POINT camera;
	RECT _door_rc;
public:
	virtual HRESULT init(int slot);
	virtual void release();
	virtual void update();
	virtual void render();
	void chainLock();
	void changeScene();
	virtual void ItemCollision();
	void zOrder();
	virtual void pixelCollision();
	virtual void AttackCollision();
};

