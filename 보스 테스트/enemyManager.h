#pragma once
#include "gameNode.h"
#include "schoolGirl.h"
#include "kyoko.h"
#include "boss.h"

class enemyManager : public gameNode
{
	enum enemyKinds
	{
		ENEMY_GIRL = 0,
		ENEMY_BOY,
		ENEMY_MT,
		ENEMY_CHEERLEADER
	};

	typedef vector<enemy*> vEnemy;
	typedef vector<enemy*>::iterator viEnemy;
private:
	vEnemy _vEnemy;
	viEnemy _viEnemy;
	kyoko* _kyoko;
	boss* _boss;
public:
	enemyManager();
	~enemyManager();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	void setEnemy();
	virtual void render();
};

