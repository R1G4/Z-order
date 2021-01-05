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
	rc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 50, 50);
	backGround = IMAGEMANAGER->addImage("배경", "image/backGround.bmp", 2880, 1800, true, RGB(255, 0, 255));
	//camera = CAMERAMANAGER->CameraMake(rc.left, rc.top, BOTH,backGround);
	return S_OK;
}


void playGround::release()
{
	gameNode::release();
	
}

void playGround::update()
{
	gameNode::update();



}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ 위에 건들지 마라 ==============================

	TIMEMANAGER->render(getMemDC());
	//================= 아래도 건들지 마라 ==============================
	_backBuffer->render(getHDC());
}

