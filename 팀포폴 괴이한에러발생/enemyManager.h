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
	//해당 스테이지
	enum STAGE_ENEMY
	{
		STAGE_1 = 1,
		STAGE_2 = 2,
		STAGE_3
	};

	//에너미 종류
	enum ENEMY_KINDS
	{
		ENEMY_GIRL = 0,
		ENEMY_BOY,
		ENEMY_MT,
		ENEMY_CHEERLEADER
	};

private:
	//에너미 혹은 아이템을 담아둘 백터
	typedef vector<enemy*> vEnemy;
	typedef vector<enemy*>::iterator viEnemy;
	typedef vector<item*> vItem;
	vEnemy _vEnemy;
	viEnemy _viEnemy;
	vItem _vItem;
	kyoko* _kyoko;
	STAGE_ENEMY _nowStage;		//현재 스테이지
	ENEMY_KINDS _enemyKinds;	//에너미 종류
	int spawnInterval;			//에너미 스폰 간격
public:
	enemyManager();
	~enemyManager();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void render(POINT camera);

	void removeEnemy(int i);	//해당 에너미 제거
	void removeItem(int i);		//해당 아이템 제거
	void spawn();				//에너미 스폰
	void setEnemy(int stageNum);//스테이지에 따른 에너미 생성
	void addEnemy();			//에너미 추가

	//각 에너미 종류별로 생성
	enemy* setSchoolGirl(float x, float y, enemy::STATE state = enemy::IDLE, enemy::DIRECTION direction = (enemy::DIRECTION)RND->getFromIntTo(0, 2));
	enemy* setSchoolBoy(float x, float y, enemy::STATE state = enemy::IDLE, enemy::DIRECTION direction = (enemy::DIRECTION)RND->getFromIntTo(0, 2));
	enemy* setMT(float x, float y, enemy::STATE state = enemy::IDLE, enemy::DIRECTION direction = (enemy::DIRECTION)RND->getFromIntTo(0, 2));
	enemy* setCheerLeader(float x, float y, enemy::STATE state = enemy::IDLE, enemy::DIRECTION direction = (enemy::DIRECTION)RND->getFromIntTo(0, 2));

	//플레이어 주소를 받아온다
	void setKyokoMemory(kyoko* kyoko) { _kyoko = kyoko; }

	vector<item*> getVItem() { return _vItem; };
	vector<enemy*> getVEnemy() { return _vEnemy; }
	vector<enemy*>::iterator getViEnemy() { return _viEnemy; }
};