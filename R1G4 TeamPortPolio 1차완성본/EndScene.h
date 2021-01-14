#pragma once
#include "gameNode.h"
class EndScene :
	public gameNode
{
private:
	LPCSTR TheEnd;
public:
	HRESULT init();
	void release();
	void update();
	void render();
};

