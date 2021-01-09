#pragma once
#include "gameNode.h"
#include "schoolGirl.h"
#include "kyoko.h"

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
public:
	enemyManager();
	~enemyManager();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	void setEnemy();
	virtual void render();
	virtual void render(POINT camera);
	void setKyokoMemory(kyoko* kyoko) { _kyoko = kyoko; }
};

