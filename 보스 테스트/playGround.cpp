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

	IMAGEMANAGER->addImage("�����", "0.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	

	SCENEMANAGER->addScene("�׽�Ʈ��", new testScene);
	SCENEMANAGER->addScene("���ʹ�", new enemyManager);

	SCENEMANAGER->changeScene("���ʹ�");
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
	//================ ���� �ǵ��� ���� ==============================

	IMAGEMANAGER->findImage("�����")->render(getMemDC());
	
	
	SCENEMANAGER->render();

	//_em->update();
	TIMEMANAGER->render(getMemDC());
	//================= �Ʒ��� �ǵ��� ���� ==============================
	_backBuffer->render(getHDC());
}

