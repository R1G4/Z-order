#include "stdafx.h"
#include "playGround.h"

playGround::playGround()
{
}


playGround::~playGround()
{
}

HRESULT playGround::init()
{
	gameNode::init(true);

	
	SCENEMANAGER->addScene("로딩씬", new loadingScene);
	SCENEMANAGER->addScene("협곡씬", new inGameScene);

	SCENEMANAGER->changeScene("로딩씬");

	
	return S_OK;
}


void playGround::release()
{
	gameNode::release();

	
}

void playGround::update()
{
	gameNode::update();


	SCENEMANAGER->update();
	
}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ 위에 건들지 마라 ==============================
	
	//IMAGEMANAGER->findImage("새배경")->render(getMemDC());
	
	
	SCENEMANAGER->render();

	TIMEMANAGER->render(getMemDC());
	//================= 아래도 건들지 마라 ==============================
	_backBuffer->render(getHDC());
}

