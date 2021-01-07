#pragma once
#include "gameNode.h"

class selectScene : public gameNode
{
public:
	selectScene() {};
	~selectScene() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

};

