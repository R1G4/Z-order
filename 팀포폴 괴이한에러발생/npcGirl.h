#pragma once
#include "npc.h"

class npcGirl :public npc
{

public:
	npcGirl();
	~npcGirl();

	virtual HRESULT init(float x, float y, STATE state, DIRECTION direction);
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void render(POINT camera);
};