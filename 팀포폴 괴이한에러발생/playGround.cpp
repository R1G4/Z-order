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

	//SCENEMANAGER->changeScene("�ε���",3,3);
	SCENEMANAGER->changeScene("���̺�ε�");

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
	EFFECTMANAGER->update();
	KEYANIMANAGER->update();
	SOUNDMANAGER->update();
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
	SCENEMANAGER->addScene("Stage1", new tempStage);
	SCENEMANAGER->addScene("Stage2", new stage2);
	SCENEMANAGER->addScene("Stage3", new stage3);
	SCENEMANAGER->addScene("BossStage", new BossStage);
}

void playGround::addSound()
{
	SOUNDMANAGER->addSound("introToStart", "sound/BGM/River City Girls OST - WereThe River City Girls ( With Lyrics).mp3", true, true);
}

