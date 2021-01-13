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


	//�÷��̾� �� ���ʹ� �̸� ����
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

	//�ش� ���� �÷��̾�� ���ʹ� �ּҸ� �Ѱ��ش�.
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
	//================ ���� �ǵ��� ���� ==============================
	
	SCENEMANAGER->render();

	TIMEMANAGER->render(getMemDC());
	//================= �Ʒ��� �ǵ��� ���� ==============================
	if (!VIDEOMANAGER->checkPlay())_backBuffer->render(getHDC());
}

void playGround::addScene()
{
	//�ش� Ŭ������ ������ �����Ͽ� �߰��Ѵ�.
	//������ �����ϱ� ������
	_tempStage = new tempStage;
	_stage2 = new stage2;
	_stage3 = new stage3;
	_BossStage = new BossStage;
	SCENEMANAGER->addScene("����ȭ��", new StartScene);
	SCENEMANAGER->addScene("���̺�ε�", new saveLoad);
	SCENEMANAGER->addScene("�ε���", new loadingScene);
	SCENEMANAGER->addScene("Stage1", _tempStage);
	SCENEMANAGER->addScene("Stage2", _stage2);
	SCENEMANAGER->addScene("Stage3", _stage3);
	SCENEMANAGER->addScene("BossStage", _BossStage);
}

void playGround::addSound()
{
	SOUNDMANAGER->addSound("introToStart", "sound/BGM/River City Girls OST - WereThe River City Girls ( With Lyrics).mp3", true, true);
}

