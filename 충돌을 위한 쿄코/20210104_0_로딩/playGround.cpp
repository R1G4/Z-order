#include "stdafx.h"
#include "playGround.h"

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

playGround::playGround()
{
}


playGround::~playGround()
{
}

HRESULT playGround::init()
{
	gameNode::init(true);

	
	SCENEMANAGER->addScene("·Îµù¾À", new loadingScene);
	SCENEMANAGER->addScene("Çù°î¾À", new inGameScene);
	SCENEMANAGER->addScene("¸®°É¾À", new ghostScene);

	SCENEMANAGER->changeScene("·Îµù¾À");

	
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
	//================ À§¿¡ °ÇµéÁö ¸¶¶ó ==============================
	
	//IMAGEMANAGER->findImage("»õ¹è°æ")->render(getMemDC());
	
	
	SCENEMANAGER->render();

	//TIMEMANAGER->render(getMemDC());
	//================= ¾Æ·¡µµ °ÇµéÁö ¸¶¶ó ==============================
	_backBuffer->render(getHDC());
}

