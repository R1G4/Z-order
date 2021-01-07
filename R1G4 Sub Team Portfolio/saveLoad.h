#pragma once
#include "gameNode.h"

struct tagTab
{
	RECT rc;
	image* img;
	float x, y;
	bool select;
	bool move;
};

class saveLoad :
	public gameNode
{
private:
	tagTab tab[3];
	float movepower;	//세이브 UI 등장

	int intb;
	int count;
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

