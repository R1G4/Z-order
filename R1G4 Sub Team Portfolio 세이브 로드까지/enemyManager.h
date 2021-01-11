#pragma once
#include "gameNode.h"
#include "schoolGirl.h"
#include "schoolBoy.h"
#include "cheerLeader.h"
#include "MT.h"
#include "kyoko.h"

class enemyManager : public gameNode
{
	enum STAGE_ENEMY
	{
		STAGE_1 = 1,
		STAGE_2
	};
	enum ENEMY_KINDS
	{
		ENEMY_GIRL = 0,
		ENEMY_BOY,
		ENEMY_MT,
		ENEMY_CHEERLEADER
	};

private:
	typedef vector<enemy*> vEnemy;
	typedef vector<enemy*>::iterator viEnemy;

	vEnemy _vEnemy;
	viEnemy _viEnemy;
	kyoko* _kyoko;
	STAGE_ENEMY _nowStage;
	ENEMY_KINDS _enemyKinds;
	int spawnInterval;
public:
	enemyManager();
	~enemyManager();

	virtual HRESULT init(int stageNum);

	virtual void release();
	virtual void update();

;	void spawn();
	void setEnemy();
	void addEnemy();

	enemy* setSchoolGirl(float x, float y, enemy::STATE state = enemy::IDLE, enemy::DIRECTION direction = (enemy::DIRECTION)RND->getFromIntTo(0, 2));
	enemy* setSchoolBoy(float x, float y, enemy::STATE state = enemy::IDLE, enemy::DIRECTION direction = (enemy::DIRECTION)RND->getFromIntTo(0, 2));
	enemy* setMT(float x, float y, enemy::STATE state = enemy::IDLE, enemy::DIRECTION direction = (enemy::DIRECTION)RND->getFromIntTo(0, 2));
	enemy* setCheerLeader(float x, float y, enemy::STATE state = enemy::IDLE, enemy::DIRECTION direction = (enemy::DIRECTION)RND->getFromIntTo(0, 2));


	virtual void render();
	virtual void render(POINT camera);
	void setKyokoMemory(kyoko* kyoko) { _kyoko = kyoko; }

	vector<enemy*> getVEnemy() { return _vEnemy; }
	vector<enemy*>::iterator getViEnemy() { return _viEnemy; }
};

