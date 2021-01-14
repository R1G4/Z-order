#pragma once
#include "gameNode.h"

struct tagTab
{
	RECT rc;
	image* img;
	image* minimap;
	image* miniMapOn;
	float x, y;
	bool select;
	bool move;
	int stageNum;
	int HP;
};

class saveLoad :
	public gameNode
{
private:
	tagTab tab[3];
	float movepower;	//세이브 UI 등장

	int intb;
	int count;
	int saveSlot;
public:
	saveLoad();
	~saveLoad();
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void addimage();
	void selecttab();
	void key();
};

