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
	addSound();
	SCENEMANAGER->addScene("시작화면", new StartScene);
	SCENEMANAGER->addScene("세이브로드", new saveLoad);
	SCENEMANAGER->changeScene("시작화면");
	
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
	SCENEMANAGER->render();
	
	TIMEMANAGER->render(getMemDC());
	//================= 아래도 건들지 마라 ==============================
	if(!VIDEOMANAGER->checkPlay())_backBuffer->render(getHDC());
}

void playGround::addSound()
{
	SOUNDMANAGER->addSound("introToStart", "sound/River City Girls OST - WereThe River City Girls ( With Lyrics).mp3", true, true);
	SOUNDMANAGER->addSound("saveLoad", "sound/River City Girls OST - File Select Theme.mp3", true, true);
}

