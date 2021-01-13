#pragma once
#include "gameNode.h"
#include "schoolGirl.h"
#include "schoolBoy.h"
#include "cheerLeader.h"
#include "MT.h"
#include "kyoko.h"
#include "item.h"

class enemyManager : public gameNode
{
	//�ش� ��������
	enum STAGE_ENEMY
	{
		STAGE_1 = 1,
		STAGE_2 = 2,
		STAGE_3
	};

	//���ʹ� ����
	enum ENEMY_KINDS
	{
		ENEMY_GIRL = 0,
		ENEMY_BOY,
		ENEMY_MT,
		ENEMY_CHEERLEADER
	};

private:
	//���ʹ� Ȥ�� �������� ��Ƶ� ����
	typedef vector<enemy*> vEnemy;
	typedef vector<enemy*>::iterator viEnemy;
	typedef vector<item*> vItem;
	vEnemy _vEnemy;
	viEnemy _viEnemy;
	vItem _vItem;
	kyoko* _kyoko;
	STAGE_ENEMY _nowStage;		//���� ��������
	ENEMY_KINDS _enemyKinds;	//���ʹ� ����
	int spawnInterval;			//���ʹ� ���� ����
public:
	enemyManager();
	~enemyManager();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void render(POINT camera);

	void removeEnemy(int i);	//�ش� ���ʹ� ����
	void removeItem(int i);		//�ش� ������ ����
	void spawn();				//���ʹ� ����
	void setEnemy(int stageNum);//���������� ���� ���ʹ� ����
	void addEnemy();			//���ʹ� �߰�

	//�� ���ʹ� �������� ����
	enemy* setSchoolGirl(float x, float y, enemy::STATE state = enemy::IDLE, enemy::DIRECTION direction = (enemy::DIRECTION)RND->getFromIntTo(0, 2));
	enemy* setSchoolBoy(float x, float y, enemy::STATE state = enemy::IDLE, enemy::DIRECTION direction = (enemy::DIRECTION)RND->getFromIntTo(0, 2));
	enemy* setMT(float x, float y, enemy::STATE state = enemy::IDLE, enemy::DIRECTION direction = (enemy::DIRECTION)RND->getFromIntTo(0, 2));
	enemy* setCheerLeader(float x, float y, enemy::STATE state = enemy::IDLE, enemy::DIRECTION direction = (enemy::DIRECTION)RND->getFromIntTo(0, 2));

	//�÷��̾� �ּҸ� �޾ƿ´�
	void setKyokoMemory(kyoko* kyoko) { _kyoko = kyoko; }

	vector<item*> getVItem() { return _vItem; };
	vector<enemy*> getVEnemy() { return _vEnemy; }
	vector<enemy*>::iterator getViEnemy() { return _viEnemy; }
};