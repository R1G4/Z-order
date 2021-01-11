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
	tagMenu conball;
	tagMenu volumebar;
	float movepower;
	float volume;
	bool up, down;
public:
	opTion();
	~opTion();
	HRESULT init();
	void release();
	void update();
	void render();
	void volumeCon();
};

