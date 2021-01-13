#pragma once
#include "gameNode.h"
#include "UIManager.h"
#include "opTion.h"

class kyoko;
class enemyManager;
class npcManager;

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
	image* stage1;
	image* stage1Pic;
	enemyManager* _em;
	npcManager* _nm;
	vector<int> _vZorder;
	char _str[128];
	bool _isDesk;
	int saveSlot;
	opTion* _opt;
public:
	HRESULT init();
	HRESULT init(int slot);
	void release();
	void update();
	void render();

	// ���̵�
	void changeMap();
	void pixelCollision();
	void AttackCollision();
	void zOrder();
	void quickSort(int a, int b);

	//�÷��̾�, ���ʹ�, Npc�ּ� �ޱ�
	void setObjMemory(kyoko* kyoko, enemyManager* em, npcManager* nm)
	{
		_player = kyoko;
		_em = em;
		_nm = nm;
	}
};

