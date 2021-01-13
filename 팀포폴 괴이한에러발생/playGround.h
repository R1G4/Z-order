#pragma once
#include "gameNode.h"
#include "StartScene.h"
#include "saveLoad.h"
#include "tempStage.h"
#include "stage2.h"
#include "stage3.h"
#include "BossStage.h"
#include "loadingScene.h"
#include "opTion.h"
#include "kyoko.h"
#include "enemyManager.h"
#include "npcManager.h"

class playGround : public gameNode
{
private:
	RECT rc;
	POINT camera;
	image* backGround;
	tempStage* _tempStage;
	stage2* _stage2;
	stage3* _stage3;
	BossStage* _BossStage;
	kyoko* _player;
	enemyManager* _em;
	npcManager* _nm;
public:
	playGround();
	~playGround();

	virtual HRESULT init();	//초기화 전용 함수
	virtual void release();	//메모리 해제 함수
	virtual void update();	//연산 전용
	virtual void render();	//그리기 전용
	void addScene();
	void addSound();
};

