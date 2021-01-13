#pragma once
#include "gameNode.h"
#include "UIManager.h"

//������ �ϴ� ��� ���Ŀ� ���ʹ̸� ������ �����ϼ�
class kyoko;
class enemyManager;

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

	// ���̵�
	void changeMap();

	//�÷��̾� ���ʹ� �ּ� �ޱ�
	//������ �ϴ� ��� ���Ŀ� ���ʹ̸� ������ �����ϼ�
	void setObjMemory(kyoko* kyoko, enemyManager* em)
	{
		_player = kyoko;
		_em = em;
	}
};

