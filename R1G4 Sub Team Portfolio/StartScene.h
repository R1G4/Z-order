#pragma once
#include "gameNode.h"
class StartScene :
	public gameNode
{
private:
	LPCSTR openingVideo;
	LPCSTR startVideo;
public:
	StartScene();
	~StartScene();
	HRESULT init();
	void release();
	void update();
	void render();
};

