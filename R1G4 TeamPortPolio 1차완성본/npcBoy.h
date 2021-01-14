#pragma once
#include "npc.h"

class npcBoy :public npc
{

public:
	npcBoy();
	~npcBoy();

	virtual HRESULT init(float x, float y, STATE state, DIRECTION direction);
	virtual void release();
	virtual void update();
	virtual void render(POINT camera);
};

