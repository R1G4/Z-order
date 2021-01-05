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
	backGround = IMAGEMANAGER->addImage("���", "image/backGround.bmp", 2880, 1800, true, RGB(255, 0, 255));
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
	//================ ���� �ǵ��� ���� ==============================

	TIMEMANAGER->render(getMemDC());
	//================= �Ʒ��� �ǵ��� ���� ==============================
	_backBuffer->render(getHDC());
}

