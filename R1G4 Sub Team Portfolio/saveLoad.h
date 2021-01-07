#pragma once
#include "gameNode.h"

struct tagTab
{
	RECT rc;
	image* img;
	float x, y;
	float movepower;	//세이브 UI 등장시에 가속도 조절
	float accel;		//세이브 UI 등장시에 가속도 조절
};

class saveLoad :
	public gameNode
{
private:
	image* _background;
	tagTab tab[3];

public:
	saveLoad();
	~saveLoad();
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	
	void addimage();
};

