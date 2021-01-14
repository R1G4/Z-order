#pragma once
#include "gameNode.h"
#define LOADINGMAX 50

class progressBar;

class loadingScene : public gameNode
{
private:
	progressBar* _loadingBar;
	image* _background;
	image* _back;
	animation* _loading;
	int nextScene;
	int saveSlot;
public:
	loadingScene();
	~loadingScene();

	int _currentCount;

	HRESULT init(int SceneNum, int slot);
	void release();
	void update();
	void render();
};

static DWORD CALLBACK threadFunction(LPVOID lpParameter);
