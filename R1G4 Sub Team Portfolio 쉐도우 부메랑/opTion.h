#pragma once
#include "gameNode.h"

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
	float movepower;
	bool up, down;
public:
	opTion();
	~opTion();
	HRESULT init();
	void release();
	void update();
	void render();
};

