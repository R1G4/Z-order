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

	IMAGEMANAGER->addImage("새배경", "0.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	

	SCENEMANAGER->addScene("테스트씬", new testScene);
	SCENEMANAGER->addScene("에너미", new enemyManager);

	SCENEMANAGER->changeScene("에너미");
	//_em->init();
	
	return S_OK;
}


void playGround::release()
{
	gameNode::release();
	//_em->release();
	
}

void playGround::update()
{
	gameNode::update();
	//_em->update();
	SCENEMANAGER->update();
	
}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ 위에 건들지 마라 ==============================

	IMAGEMANAGER->findImage("새배경")->render(getMemDC());
	
	
	SCENEMANAGER->render();

	//_em->update();
	TIMEMANAGER->render(getMemDC());
	//================= 아래도 건들지 마라 ==============================
	_backBuffer->render(getHDC());
}

