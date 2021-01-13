#pragma once
#include "npc.h"

class npcTeacher :public npc
{

public:
	npcTeacher();
	~npcTeacher();

	virtual HRESULT init(float x, float y, STATE state, DIRECTION direction);
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void render(POINT camera);
};





