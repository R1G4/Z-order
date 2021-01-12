#pragma once
#pragma warning(disable:4996)
#include "gameNode.h"
#include"kyoko.h"
#include"enemyManager.h"
struct tagMenu
{
	image* img;
	RECT rc;
	float x, y;
};

class opTion :
	public gameNode
{
private:
	tagMenu menu;
	tagMenu conball;
	tagMenu volumebar;
	float movepower;
	float volume;
	bool up, down;
	int stageNum;
	int currentHP;
	int saveSlot;
	enemyManager* em;
	kyoko* _kyoko;
public:
	opTion();
	~opTion();
	HRESULT init();
	void release();
	void update();
	void render();
	void volumeCon();
	void setStageName(int num) { stageNum = num; }
	void setSlot(int num) { saveSlot = num; }
	float getVolume() { return volume; }
	void setKyokoAddressLink(kyoko* Kyoko) { _kyoko = Kyoko; }
	void setEnemyAddressLink(enemyManager* Em) { em = Em; }
};

