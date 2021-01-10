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
	addScene();
	addSound();
	SCENEMANAGER->changeScene("�ε���",0);

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
	
	SCENEMANAGER->render();

	TIMEMANAGER->render(getMemDC());
	//================= �Ʒ��� �ǵ��� ���� ==============================
	if (!VIDEOMANAGER->checkPlay())_backBuffer->render(getHDC());
}

void playGround::addScene()
{
	SCENEMANAGER->addScene("����ȭ��", new StartScene);
	SCENEMANAGER->addScene("���̺�ε�", new saveLoad);
	SCENEMANAGER->addScene("�ε���", new loadingScene);
	SCENEMANAGER->addScene("��������1", new tempStage);
	SCENEMANAGER->addScene("��������2", new stage2);
	SCENEMANAGER->addScene("������������", new BossStage);

}

void playGround::addSound()
{
	SOUNDMANAGER->addSound("introToStart", "sound/BGM/River City Girls OST - WereThe River City Girls ( With Lyrics).mp3", true, true);
	SOUNDMANAGER->addSound("saveLoad", "sound/BGM/River City Girls OST - File Select Theme.mp3", true, true);
}

