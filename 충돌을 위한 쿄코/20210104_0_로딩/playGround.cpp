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

	
	SCENEMANAGER->addScene("�ε���", new loadingScene);
	SCENEMANAGER->addScene("�����", new inGameScene);
	SCENEMANAGER->addScene("���ɾ�", new ghostScene);

	SCENEMANAGER->changeScene("�ε���");

	
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
	//================ ���� �ǵ��� ���� ==============================
	
	//IMAGEMANAGER->findImage("�����")->render(getMemDC());
	
	
	SCENEMANAGER->render();

	//TIMEMANAGER->render(getMemDC());
	//================= �Ʒ��� �ǵ��� ���� ==============================
	_backBuffer->render(getHDC());
}

