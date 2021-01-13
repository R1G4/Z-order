#pragma once
#include "gameNode.h"
#include"UIManager.h"
#include "opTion.h"

class kyoko;
class enemyManager;

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
	RECT _door_rc;
public:
	virtual HRESULT init();
	HRESULT init(int slot);
	virtual void release();
	virtual void update();
	virtual void render();
	void changeScene();
	void quickSort(int a,int b);
	void zOrder();
	// �ȼ� �浹
	virtual void pixelCollision();
	virtual void ItemCollision();
	// ��Ʈ �浹
	virtual void AttackCollision();

	//�÷��̾� ���ʹ� �ּ� �ޱ�
	void setObjMemory(kyoko* kyoko, enemyManager* em)
	{
		_player = kyoko;
		_em = em;
	}
};

