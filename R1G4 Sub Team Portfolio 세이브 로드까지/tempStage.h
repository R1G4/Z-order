#pragma once
#pragma warning(disable:4996)
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
	int saveSlot;
public:
	HRESULT init();
	HRESULT init(int slot);
	void release();
	void update();
	void render();

	// ���̵�
	void changeMap();
	void pixelCollision();
	void zOrder();
	void quickSort(int a, int b);
};

