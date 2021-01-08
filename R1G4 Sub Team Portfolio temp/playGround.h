#pragma once
#include "gameNode.h"
#include "StartScene.h"
#include "saveLoad.h"
#include "tempStage.h"
#include "loadingScene.h"
#include "BossStage.h"
#include "opTion.h"

class playGround : public gameNode
{
private:
	RECT rc;
	POINT camera;
	image* backGround;


public:
	playGround();
	~playGround();

	virtual HRESULT init();	//�ʱ�ȭ ���� �Լ�
	virtual void release();	//�޸� ���� �Լ�
	virtual void update();	//���� ����
	virtual void render();	//�׸��� ����
	void addScene();
	void addSound();
};
