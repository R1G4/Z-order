#pragma once
#include "gameNode.h"
#include "kyoko.h"

class ghostScene : public gameNode
{
private:
	POINT _camera;
	image* _background;
	kyoko* _kyoko;

public:
	ghostScene() {};
	~ghostScene() {};

	HRESULT init();
	void release();
	void update();
	void render();

};

