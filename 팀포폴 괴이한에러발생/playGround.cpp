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

	//SCENEMANAGER->changeScene("로딩씬",3,3);
	SCENEMANAGER->changeScene("세이브로드");


	//플레이어 및 에너미 미리 생성
	_player = new kyoko;
	_em = new enemyManager;

	return S_OK;
}


void playGround::release()
{
	gameNode::release();

}

void playGround::update()
{
	gameNode::update();

	//해당 씬에 플레이어와 에너미 주소를 넘겨준다.
	_tempStage->setObjMemory(_player, _em);
	_stage2->setObjMemory(_player, _em);
	_stage3->setObjMemory(_player, _em);
	_BossStage->setObjMemory(_player, _em);

	SCENEMANAGER->update();
	EFFECTMANAGER->update();
	KEYANIMANAGER->update();
	SOUNDMANAGER->update();
}

void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ 위에 건들지 마라 ==============================
	
	SCENEMANAGER->render();

	TIMEMANAGER->render(getMemDC());
	//================= 아래도 건들지 마라 ==============================
	if (!VIDEOMANAGER->checkPlay())_backBuffer->render(getHDC());
}

void playGround::addScene()
{
	//해당 클래스를 변수로 선언하여 추가한다.
	//참조를 쉽게하기 위함임
	_tempStage = new tempStage;
	_stage2 = new stage2;
	_stage3 = new stage3;
	_BossStage = new BossStage;
	SCENEMANAGER->addScene("시작화면", new StartScene);
	SCENEMANAGER->addScene("세이브로드", new saveLoad);
	SCENEMANAGER->addScene("로딩씬", new loadingScene);
	SCENEMANAGER->addScene("Stage1", _tempStage);
	SCENEMANAGER->addScene("Stage2", _stage2);
	SCENEMANAGER->addScene("Stage3", _stage3);
	SCENEMANAGER->addScene("BossStage", _BossStage);
}

void playGround::addSound()
{
	SOUNDMANAGER->addSound("introToStart", "sound/BGM/River City Girls OST - WereThe River City Girls ( With Lyrics).mp3", true, true);
}

