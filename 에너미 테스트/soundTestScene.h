#pragma once
#include "gameNode.h"

class soundTestScene : public gameNode
{
private:

public:
	soundTestScene() {};
	~soundTestScene() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();


};

